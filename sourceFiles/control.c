#include <xc.h>
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

int get_adc_reading(){   return (ADCL + ADCH* 256);  }

void main(void) {

    init_PWM();
    settingAdcPin();
    int adc_reading ;
    
    while(1){
      set_predefined_bit(ADCSRA, ADATE); // keeps toggeling the ADATE bit to keep reading the input analog value and keep updating the data register
        adc_reading = get_adc_reading();
        update_pwm(adc_reading);
    }
    return;
}
