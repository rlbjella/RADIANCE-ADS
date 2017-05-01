#include "attitude.h"
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <sstream>
#include <time.h>
#include <math.h>
#include <ctime>
#include <string>
#include <cstdio>

using namespace std;

//#define LOGNAME_FORMAT "data_%Y/%m/%d_%H%M%S"
//#define LOGNAME_SIZE 20

int main(void){
	double var1,var2,var3,var4;

	attitude radiance_ads;

	gpioInitialise();

	var1 = radiance_ads.ads_read(1);
	var2 = radiance_ads.ads_read(2);
	var3 = radiance_ads.ads_read(3);
	var4 = radiance_ads.ads_read(4);

	std::cout << "results: " << var1 << " " << var2 << " " << var3 << " " << var4 << "\n";

	time_t rawtime;
	struct tm * timeinfo;
	char name[80];

	time(&rawtime);
	timeinfo = localtime(&rawtime);

	strftime(name,sizeof(name),"data_%d-%m-%Y_%I%M%S.csv",timeinfo);

	ofstream myfile;

	myfile.open(name);
	myfile << "STARTING TEST\n";

	int i = 0;

	clock_t time;
	double dt;
	clock_t t0 = clock();


	while(i < 1000) {

		i++;

		var1 = radiance_ads.ads_read(1);
        	var2 = radiance_ads.ads_read(2);
        	var3 = radiance_ads.ads_read(3);
        	var4 = radiance_ads.ads_read(4);

		std::cout << "results: " << var1 << " " << var2 << " " << var3 << " " << var4 << "\n";
		time = clock();
		dt = double(time - t0) / CLOCKS_PER_SEC;

		myfile << dt << "," << var1 << "," << var2 << "," << var3 << "," << var4 << "\n";

	}

	myfile.close();

	return 0;

}
