#include "usart.h"
#include "myprint.h"
#include "mydelay.h"

int main(void){
	usart_init(9600);
	delay_init(84);
	while(1){
		myprintf("%s\r\n","hello world");
		delay(1000);
	}
}




