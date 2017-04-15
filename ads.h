#ifndef ADS_H
#define ADS_H

#include "ltc2470.h"
#include <pigpio.h>
#include <math.h>
// Other includes in ltc2470.h

class ads{
public:
	// Initialization function. Configure GPIO pins for CS and set high,
	// open SPI device
	ads();

	// Function to read current from one of four photodiodes
	float ads_read(unsigned char pdiode, ltc2470 adc);

	// Float to compute off-sun angle from photodiode measurements
	float ads_compute(float diode1, float diode2, float diode3, float diode4);

private:
	// Feedback resistances, hard-coded into constructor
	const unsigned int rf1=1000;
	const unsigned int rf2=1000;
	const unsigned int rf3=1000;
	const unsigned int rf4=1000;

	// Resolution of ADC, equal to 2^(bits)-1
	const unsigned int resolution=pow(2,16)-1;

	// Reference voltage of ADC
	const float ref_voltage=1.25;

	// SPI device, defined in class ltc2470
	//ltc2470 spidev;

};

#endif
