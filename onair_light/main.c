#include <stdio.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>


#define led_ind PB4
#define led_pwr PB3
#define main_p PB2
#define buzzer PB0
#define main_switch PB1

uint8_t led_on = 0;

void initIO(void) {
    DDRB = 0b00011101;
    PORTB |= (1 << main_switch);
}

int main(void) {
	initIO();
    while (1) {
        if (!(PINB & _BV(main_switch))) {
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
        }
	}
	return 0; // never reached
}
