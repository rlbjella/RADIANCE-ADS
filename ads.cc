#include "ads.h"
#include <array>
#include <math.h>

// Initialization function. Configure GPIO pins for CS and set high,
// open SPI device. Set feedback resistances and ADC resolution
ads::ads(){
	// Configure gpio MIGHT BE DONE ALREADY
	gpioInitialise();
	// Configure pins as output
	gpioSetMode(12, PI_OUTPUT);
	gpioSetMode(16, PI_OUTPUT);
	gpioSetMode(20, PI_OUTPUT);
	gpioSetMode(21, PI_OUTPUT);

	// Set CS pins high
	gpioWrite(12, 1);
	gpioWrite(16, 1);
	gpioWrite(20, 1);
	gpioWrite(21, 1);

	// Construct SPI device for 1MHz and 8 bit words
//	ltc2470 spiadc("/dev/spidev0.0", SPI_MODE_0, 10000000, 8);
}


// Function to read current from a specified photodiode
float ads::ads_read(unsigned char pdiode, ltc2470 adc){

	std::array<unsigned char,3> data;
	data[0] = 0;	// start bit
	data[1] = 0;	// single-ended mode, channel 0
	data[2] = 0;	// doesn't matter what this byte is

	unsigned int dn = 0;
	float current = 0;
	unsigned int rf;	// Feedback resistance

	// Set necessary CS pin low to make corresponding ADC listen
	if(pdiode == 1){
		gpioWrite(12, 0);
		rf = rf1;
	}
	else if(pdiode == 2){
		gpioWrite(16, 0);
		rf = rf2;
	}
	else if(pdiode == 3){
		gpioWrite(20, 0);
		rf = rf3;
	}
	else if(pdiode == 4){
		gpioWrite(21, 0);
		rf = rf4;
	}


	// Call the read/write function of SPI object to get AD conversion
	adc.spiWriteRead(data.data(),data.size());

	// Get result from data registers
	dn = (data[1] << 8) & 0b1100000000;
	dn |= (data[2] & 0xff);

	// Convert DN to current
	current = (dn * ref_voltage / ((resolution))) / ((float)(rf));

	// Set necessary CS pin high again
	if(pdiode == 1){
		gpioWrite(12, 1);
	}
	else if(pdiode == 2){
		gpioWrite(16, 1);
	}
	else if(pdiode == 3){
		gpioWrite(20, 1);
	}
	else if(pdiode == 4){
		gpioWrite(21, 1);
	}
	return current;

}

// Function to compute angle from photodiode measurements
float ads::ads_compute(float I1, float I2, float I3, float I4){
	double x,y;	// x and y positions of sun
	float theta;	// off sun angle

	// Calibration factor and weights
	double f = 1; // placeholder
	float w1 = 1, w2 = 1, w3 = 1, w4 = 1; // placeholder

	// Compute x and y components from relative current
	x = f*((w2*I2+w3*I3)-(w1*I1+w4*I4)) / (I1 + I2 + I3 + I4);
	y = f*((w1*I1+w2*I2)-(w3*I3+w4*I4)) / (I1 + I2 + I3 + I4);

	// Compute off sun angle
	theta = (float) (sqrt(pow((float)x,2)+pow(y,2)));

	return theta;

}
