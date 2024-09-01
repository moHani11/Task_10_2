#include <xc.h>
#include "headerfile.h"

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

void main(void) {

settingAdcPin();

    
    while(1){
        set_predefined_bit(ADCSRA, ADATE); // keeps toggeling the ADATE bit to keep reading the input analog value and keep updating the data register
        
    }


    return;
}
