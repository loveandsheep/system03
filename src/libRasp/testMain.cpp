#include <stdio.h>
#include "raspGPIO.h"

int main(){
	
	gpio_init();
	gpio_configure(17, GPIO_OUTPUT);
	
	while (1) {
		
		gpio_set(2);
		printf("off\n");
		sleep(1);
		
		gpio_clear(2);
		printf("on\n");
		sleep(1);
	}
	
	return 0;
}
