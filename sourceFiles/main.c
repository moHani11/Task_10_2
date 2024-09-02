#include <xc.h>
#include <avr/io.h>
#include "headerfile.h"


int com1A1 = PORT_7;  // register: TCCR1A
int com1A0 = PORT_6;  // register: TCCR1A
int wgm12 = PORT_3 ;  // register: TCCR1B
int wgm11 = PORT_1 ; // register: TCCR1A
int wgm10 = PORT_0 ; // register: TCCR1A
int cs10 = PORT_0;  // register: TCCR1B

void init_PWM(void){
    
    set_bit(DDRB, PORT_1);

    clear_bit(TCCR1A, com1A0);
    set_bit(TCCR1A, com1A1);

    set_bit(TCCR1B, wgm12);
    set_bit(TCCR1A, wgm10);
    set_bit(TCCR1A, wgm11);
           
//    OCR1A = 1024;
    set_bit(TCCR1B, cs10);
}

void update_pwm(int duty_cycle){
   OCR1A = duty_cycle;
} 


void settingAdcPin(void){
    
    //setting REFS0 to 1 make the ADC Vrefrence to  AVCC with external capacitor at AREF pin
    // by connecting the AVCC to 5 volt and connecting the AREF pin to a capacitor we get better stability for the ADC reading
    set_predefined_bit(ADMUX, REFS0);
    
    // choosing which PIN will be the analog input pin
    set_predefined_bit(ADMUX, MUX2);
    set_predefined_bit(ADMUX, MUX1); // this configuration sets pin 6 ADC as the input analog pin
    // I chose pin 6 as there is no digital input biffer
        
    set_predefined_bit(ADCSRA, ADEN); // Writing this bit to one enables the ADC.
    set_predefined_bit(ADCSRA, ADSC);  // write this bit to one to start each conversion
    set_predefined_bit(ADCSRA, ADPS1);  
    set_predefined_bit(ADCSRA, ADPS2); // setting the ADSP1, ADSP2 sets the division factor between the system clock frequency and the input clock to 64
    
}


unsigned char spiTransfer(unsigned char sData)
{
    unsigned char xData;
    PORTB &= ~(0X04);
    SPDR = sData;
   // while ((SPSR & 0X80) == 0);
    xData = SPDR;
    PORTB |= 0X04;
    return(xData);
}

int get_adc_reading(){   return (ADCL + ADCH* 256);  }

void init_spi(void){
        DDRB |= (1 << PB3) | (1 << PB5);  
    DDRB &= ~(1 << PB4);              
    DDRB |= (1 << PB2);             
    PORTB |= (1 << PB2);         

    SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
        PORTB &= ~(0X04);

}

void spiTransfer_nonBlocking(unsigned char sData) {
    SPDR = sData; 
}

unsigned char check_spiCompletion() {
    unsigned char xData = SPDR;
    if (SPSR & 0x80) {
    PORTB |= 0X04;
    }
    return(xData);

}

volatile int32_t encoder_pulse_count = 0;

void ext_int_init()
{
    DDRD &= ~((1 << PD2) | (1 << PD3));  
    // Configure INT0 (PD2) to trigger on a rising edge
    EICRA |= (1 << ISC00) | (1 << ISC01);  // Rising edge on INT0
    // Configure INT1 (PD3) to trigger on a rising edge
     EICRA |= (1 << ISC10) | (1 << ISC11);  // Rising edge on INT1
    // Enable INT0 and  INT1 interrupts
    EIMSK |= (1 << INT0);  
    EIMSK |= (1 << INT1); 
    // Enable global interrupts
    sei();
}

//INT0 CHANNEL A
ISR(INT0_vect)
{
    encoder_pulse_count++;
}
// INT1 for direction detection
ISR(INT1_vect)
{
    encoder_pulse_count--;
}

volatile uint32_t rpm = 0;

// Function to calculate RPM
int calculate_rpm()
{
    rpm = (encoder_pulse_count * 60) / ENCODER_PULSES_PER_REVOLUTION;
    encoder_pulse_count = 0;  // Reset pulse count after calculation
    
    return rpm;
}

void main(void) {

    ext_int_init();
    init_spi();
    init_PWM();
    settingAdcPin();
    
    int adc_reading ;

    while(1){
         spiTransfer_nonBlocking(rpm);
         check_spiCompletion();
        
        set_predefined_bit(ADCSRA, ADATE); // keeps toggeling the ADATE bit to keep reading the input analog value and keep updating the data register
        adc_reading = get_adc_reading();
        update_pwm(adc_reading);

    }
    return;
}
