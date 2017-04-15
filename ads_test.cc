#include "ads.h"
#include "ltc2470.h"
#include <iostream>
#include <stdio.h>
#include <ctime>

int main(void){
	float var1,var2,var3,var4,angle;
	// Initialize ADS
	ads radiance_ads;
	// Initialize ADC
	ltc2470 adc("/dev/spidev0.0", SPI_MODE_0, 1000000, 8);
	std::cout << "ADC initialized\n";

	// Begin timer
	clock_t begin = clock();

	// Read current from photodiodes
	std::cout << "Reading photodiode 1...\n";
	var1 = radiance_ads.ads_read(1, adc);
	usleep(10000);	// 10 ms
	std::cout << "Reading photodiode 2...\n";
	var2 = radiance_ads.ads_read(2, adc);
//	var2 = 1;
	usleep(10000);
	std::cout << "Reading photodiode 3...\n";
	var3 = radiance_ads.ads_read(3, adc);
//	var3 = 1;
	usleep(10000);
	std::cout << "Reading photodiode 4...\n";
	var4 = radiance_ads.ads_read(4, adc);
//	var4 = 1;

	// Compute angle
	std::cout << "Computing angle...\n";
	angle = radiance_ads.ads_compute(var1, var2, var3, var4);

	// Stop timer
	clock_t end = clock();
	double time = double(end-begin) / CLOCKS_PER_SEC;
	std::cout << "Time to read diodes and compute angle: " << time << "\n";

	std::cout << "result is: " << angle << "\n";
	std::cout << "adc reading: " << var1 << "\n";
	std::cout << "adc reading: " << var2 << "\n";
	std::cout << "adc reading: " << var3 << "\n";
	std::cout << "adc reading: " << var4 << "\n";

	adc.~ltc2470();
	return 0;

}
