#include <xc.h>
#include "headerFile.h"

/*
   In the TCCR1A register ? Timer/Counter1 Control Register A
 * SETTING com1A1, clearing com1A0 so i can Clear OC1A/OC1B on Compare Match
      - COM1A1 refer to bit 7
      - COM1A0 refer to bit 6
 
 *  To use Fast PWM, 10-bit controle for better resolution than the 8 bit timer
 * 
 * set WGM12(bit 3) in  TCCR1B register
 * set WGM11(bit 1) , WGM10(bit 0) in TCCR1A register
 * 
 * 
 * setting CS10(bit 0) in the TCCR1B register to avoid pre-scailling
 */  

int com1A1 = PORT_7;  // register: TCCR1A
int com1A0 = PORT_6;  // register: TCCR1A
int wgm12 = PORT_3 ;  // register: TCCR1B
int wgm11 = PORT_1 ; // register: TCCR1A
int wgm10 = PORT_0 ; // register: TCCR1A
int cs10 = PORT_0;  // register: TCCR1B

void PWM(int duty_cycle){
    
    set_bit(DDRB, PORT_1);

    clear_bit(TCCR1A, com1A0);
    set_bit(TCCR1A, com1A1);

    set_bit(TCCR1B, wgm12);
    set_bit(TCCR1A, wgm10);
    set_bit(TCCR1A, wgm11);
    
    OCR1A = duty_cycle;
    
    set_bit(TCCR1B, cs10);
    
}


void main(void) {

    PWM(1000);
    
    while(1){
        
        
    }

    return;
}
