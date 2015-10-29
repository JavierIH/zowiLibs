/******************************************************************************
* Zowi LED Matrix Library
*
* @version 20150710
* @author Raul de Pablos Martin
*         José Alberca Pita-Romero (Mouth's definitions)
******************************************************************************/

#include "LedMatrix.h"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

LedMatrix::LedMatrix(char ser_pin, char clk_pin, char rck_pin) {
  memory = 0x00000000;
	_ser = ser_pin;
	_clk = clk_pin;
	_rck = rck_pin;
	pinMode(_ser, OUTPUT);
	pinMode(_clk, OUTPUT);
	pinMode(_rck, OUTPUT);
	digitalWrite(_ser, LOW);
	digitalWrite(_clk, LOW);
	digitalWrite(_rck, LOW);
	sendMemory();
}

void LedMatrix::writeFull(unsigned long value) {
	memory = value;
	sendMemory();
}

unsigned long LedMatrix::readFull(void) {
	return memory;
}

void LedMatrix::setLed(char row, char column) {
	if(row >= 1 && row <= ROWS && column >= 1 && column <= COLUMNS) {
		memory |= (1L << (MATRIX_LENGTH - (row-1)*COLUMNS - (column)));
		sendMemory();
	}
}

void LedMatrix::unsetLed(char row, char column) {
	if(row >= 1 && row <= ROWS && column >= 1 && column <= COLUMNS) {
		memory &= ~(1L << (MATRIX_LENGTH - (row-1)*COLUMNS - (column)));
		sendMemory();
	}
}

void LedMatrix::clearMatrix(void) {
	memory = 0x00000000;
	sendMemory();
}

void LedMatrix::setEntireMatrix(void) {
	memory = 0x3FFFFFFF;
	sendMemory();
}

void LedMatrix::sendMemory(void) {
	int i;

	for(i = 0; i < MATRIX_LENGTH; i++) {
		digitalWrite(_ser, 1L & (memory >> i));
		// ## adjust this delay to match with 74HC595 timing
		asm volatile ("nop");
		asm volatile ("nop");
		asm volatile ("nop");
		digitalWrite(_clk, 1);
		// ## adjust this delay to match with 74HC595 timing
		asm volatile ("nop");
		asm volatile ("nop");
		asm volatile ("nop");
		digitalWrite(_clk, 0);
	}

	digitalWrite(_rck, 1);
	// ## adjust this delay to match with 74HC595 timing
	asm volatile ("nop");
	asm volatile ("nop");
	asm volatile ("nop");
	digitalWrite(_rck, 0);
}
