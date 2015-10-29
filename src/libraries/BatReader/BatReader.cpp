/******************************************************************************
* Zowi Battery Reader Library
*
* @version 20150831
* @author Raul de Pablos Martin
*
******************************************************************************/

#include "BatReader.h"

#if defined(ARDUINO) && ARDUINO >= 100
  #include "Arduino.h"
#else
  #include "WProgram.h"
#endif

BatReader::BatReader() {
}

double BatReader::readBatVoltage(void) {
	double data = (analogRead(BAT_PIN)*AN_REF)/1024;
	if(data > BAT_MAX) return BAT_MAX;
	else return data;
}

double BatReader::readBatPercent(void) {
	double data = (_slope*readBatVoltage()) - _offset;
	if(data < 0) return 0;
	else return data;
}
