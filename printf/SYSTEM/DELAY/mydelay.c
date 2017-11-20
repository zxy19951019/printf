#include "mydelay.h"
#include "stm32f4xx.h" 

static int fac_ms=0;							

void delay_init(char sysclock)
{
	SysTick ->CTRL |= 1<<2;
	fac_ms =sysclock*1000 ;
}

void delay(float nms)
{
	int temp;
	long sum = nms*fac_ms;
	while( sum > 0xFFFFFF){
		SysTick ->LOAD = 0xFFFFFF;
		SysTick->VAL =0x00;
		SysTick ->CTRL |= 1;
		do
		{
			temp=SysTick->CTRL;
		}while((temp&0x01)&&!(temp&(1<<16)));	     
		sum -= 0xFFFFFF;
	}	
	SysTick ->LOAD = sum;
	SysTick->VAL =0x00;
	SysTick ->CTRL |= 1;
	do
	{
		temp=SysTick->CTRL;
	}while((temp&0x01)&&!(temp&(1<<16)));	 
	SysTick->CTRL&=~0x01;
	SysTick->VAL =0X00;  
}


