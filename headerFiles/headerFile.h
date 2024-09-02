#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <avr/io.h>

#define PORT_0 0x01
#define PORT_1 0x02
#define PORT_2 0x04
#define PORT_3 0x08
#define PORT_4 0x10
#define PORT_5 0x20
#define PORT_6 0x40
#define PORT_7 0x80
#define ENCODER_PULSES_PER_REVOLUTION 24  

#define set_bit(REGISTER, PORT) REGISTER |= PORT 
#define set_predefined_bit(REGISTER, PREDEF_PORT) REGISTER |=(1 << PREDEF_PORT)
#define clear_bit(REGISTER, PORT) REGISTER &= ~(PORT)

#include <avr/io.h>
#include <avr/interrupt.h>
#define PORT_D4 0x10
#define PORT_D5 0x20
#define PORT_D6 0x40
#define PORT_D7 0x80


#define SET_BIT_BOS(REGESTER, BOS)  (REGESTER |= (1<<BOS))
#define SET_BIT(REGESTER, MASK)     (REGESTER |= MASK)
#define CLEAR_BIT(REGESTER, MASK)    ~(REGESTER &= MASK)


void init_PWM(void);
void update_pwm(int duty_cycle);
void settingAdcPin(void);
int get_adc_reading();


#endif	/* XC_HEADER_TEMPLATE_H */

