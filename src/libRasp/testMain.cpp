#include <stdio.h>
#include "raspSPI.h"

int main(){
	
	gpio_init();
	gpio_configure(22, GPIO_OUTPUT);
	
	while (1) {
		
		gpio_set(22);
		printf("off\n");
		sleep(100);
		
		gpio_clear(22);
		printf("on\n");
		
	}
	
	return 0;
}