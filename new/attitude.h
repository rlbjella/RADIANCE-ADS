#ifndef ADS_H
#define ADS_H

#include <pigpio.h>
#include <iostream>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
#include <unistd.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>


// Class for entire attitude system. Simplified from original work to avoid
// "Bad file descriptor" error in ioctl calls

class attitude{

public:

	// Initialize function
	attitude();
	// Destructor
	~attitude();

	// User functions
	double ads_read(int pdiode);
	double ads_compute(double p1, double p2, double p3, double p4);


private:

	// SPI settings
	const unsigned char mode = SPI_MODE_0;
	const unsigned char bitsPerWord = 8;
	const unsigned int speed = 1000000;

	// Feedback resistances (ohms)
	const double rf1=1000;
	const double rf2=1000;
	const double rf3=1000;
	const double rf4=1000;

	// Open and close functions
	int spiOpen(); 	// returns spifd
	int spiClose(int spifd);


}