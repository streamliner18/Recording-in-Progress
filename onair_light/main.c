#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <avr/sleep.h>


#define led_ind PB4
#define led_pwr PB3
#define main_p PB2
#define buzzer PB0
#define main_switch PB1

uint8_t led_on = 0;

void initIO(void) {
    DDRB = 0b00011101;
    PORTB |= (1 << main_switch);
    GIMSK |= (1 << INT0);
    MCUCR &= ~(1 << ISC00);
    MCUCR &= ~(1 << ISC01);//enable interrupt
    sei();
    //MCUCR |= (1 << SM0);
    //MCUCR &= (1 << SM1); //deep sleep mode
    MCUCR |= (1 << SE);
    SLEEP_MODE_PWR_DOWN;
    sleep_cpu();
}

int main(void) {
	initIO();
    while (1) {
        /*if (!(PINB & _BV(main_switch))) {
            
            }
        }*/
	}
	return 0; // never reached
}

ISR(INT0_vect){
    cli();
    led_on = 1 - led_on;
    if (led_on) {
        PORTB |= 1 << main_p;
        PORTB |= 1 << led_ind;
        PORTB |= 1 << buzzer;
        _delay_ms(400);
        PORTB &= ~(1 << buzzer);
    } else {
        PORTB &= ~(1 << main_p);
        PORTB &= ~(1 << led_ind);
        PORTB |= 1 << buzzer;
        _delay_ms(200);
        PORTB &= ~(1 << buzzer);
    }
    sei();
    sleep_enable();
    sleep_cpu();
}