#include "attitude.h"
#include <iostream>
#include <stdio.h>

int main(void){
	double var1,var2,var3,var4;
	

	var1 = radiance_ads.ads_read(1);
	var2 = radiance_ads.ads_read(2);
	var3 = radiance_ads.ads_read(3);
	var4 = radiance_ads.ads_read(4);

	std::cout << "results: " << var1 << " " << var2 << " " << var3 << " " << var4 << "\n";

	return 0;

}