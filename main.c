/*
 * main.c
 *
 *  Created on: Aug 4, 2018
 *      Author: Mohamed Talaat Harb
 */

#include<avr/io.h>
#include<util/delay.h>

#define DELAY_PERIOD 500

#define ASSIGNMENT 3
#define NUM_BITS 8

typedef unsigned char u8;

static void original(void);
static void A1(void);
static void A2(void);
static void A3(void);

int main(void) {
	u8 assignment = ASSIGNMENT;

	switch (assignment) {
	case 0:
		original();
		break;
	case 1:
		A1();
		break;
	case 2:
		A2();
		break;
	case 3:
		A3();
		break;
	}

	return 0;
}

static void original(void) {

	// Set all port C as output
	DDRC = 0xff;

	// Run forever
	while (1) {

		// Put high voltage (5V) on all the pins of port C
		PORTC = 0xff;

		// Delay for 500ms
		_delay_ms(DELAY_PERIOD);

		// Put low voltage (0V) on all the pins of port C
		PORTC = 0x00;

		// Delay for 500ms
		_delay_ms(DELAY_PERIOD);
	}
}

static void A1(void) {
	/* Initialization */
	DDRC = 0xff;

	/* Super loop */
	while (1) {
		PORTC = 0b01010101;
		_delay_ms(DELAY_PERIOD);
		PORTC = 0b10101010;
		_delay_ms(DELAY_PERIOD);
	}
}

static void A2(void) {
	/* Initialization */
	DDRC = 0b00000001;
	PORTC = 0x00;
	u8 status = 0;

	/* Super loop */
	while (1) {
		if (!(PINC & 0b10000000) && !status) {
			PORTC ^= 1;
			status = 1;
		} else if ((PINC & 0b10000000)) {
			status = 0;
		}
	}
}

static void A3(void) {
	/* Initialization */
	DDRC = 0xff;
	PORTC = 0b10000000;
	u8 counter = 0;

	/* Super loop */
	while (1) {

		for (counter = 0; counter < NUM_BITS - 1; counter++) {
			PORTC = PORTC >> 1;
			_delay_ms(DELAY_PERIOD);
		}
		for (counter = 0; counter < NUM_BITS - 1; counter++) {
			PORTC = PORTC << 1;
			_delay_ms(DELAY_PERIOD);
		}
	}
}
