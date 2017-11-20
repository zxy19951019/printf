#include "myprint.h"
#include "stdio.h"	
#include "stdarg.h"
#include "usart.h"

char arr[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
void printData(int);
void printString(char*);
void printHex(int);
void printFloat(double);
void printFraction(double);
void USART_Print_Send(char);

int myprintf(const char* format,...)
{
	char c,ch,str[30];
	va_list ap;
	int n;
	va_start(ap,format);
	while((c = *format))
	{
		switch(c)
		{
			case '%':
				ch = *++format;
				switch(ch)
				{
					case 'd':
						n = va_arg(ap,int);
						if(n>=0)
						{
							printData(n);
						} else {
							USART_Print_Send('-');
							printData(~(n-1));
						}
						break;
					case 'x':
						n = va_arg(ap,int);
						printHex(n);
						break;
//					case 'f':
//						printFloat(va_arg(ap,double));
//						break;
					case 'c':
						USART_Print_Send((char)(va_arg(ap,char*)));
						break;
					case 's':
						printString(va_arg(ap,char*));
						break;
					case '%':
						USART_Print_Send('%');
						break;
				}
				break;
			case '\n':
				USART_Print_Send('\n');
				break;
			case '\r':
				USART_Print_Send('\r');
				break;
			default :
				USART_Print_Send(c);
				break;
		}
		format++;
	}
	va_end(ap);
}

void printData(int data)
{
	char bufferD[10],x = 9,y;
	while(data != 0)
	{
		bufferD[x] = arr[data%10];
		data /= 10;
		x--;
	}
	for(y = x+1;y <10;y++)
	{
		USART_Print_Send(bufferD[y]);
	}
}


//向串口传输字符串
void printString(char* string)
{
	while(*string != '\0')
	{
		USART_Print_Send(*string);
		string++;
	}
}

//以16进制打印
void printHex(int number)
{
	char bufferHex[8],x = 7,y;
	while(number != 0)
	{
		bufferHex[x] = arr[number&15];
		number = number >>4;
		x--;
		if(x ==(char)-1)
		{
			break;
		}
	}
	for(y = x+1;y <8;y++)
	{
		USART_Print_Send(bufferHex[y]);
	}
}

//void printFloat(double fraction)
//{
//	char bufferF[20],x = 19,y;
//	long long maintissa = fraction;
//	fraction -= maintissa;
//	while(maintissa != 0)
//	{
//		bufferF[x] = arr[maintissa%10];
//		maintissa /= 10;
//		x--;
//	}
//	for(y = x+1;y <20;y++)
//	{
//		USART_Print_Send(bufferF[y]);
//	}
//	USART_Print_Send('.');
//	printFraction(fraction);
//}

//void printFraction(double decimal)
//{
//	char floatArr[30],x = 29,y;
//	char integerPart;
//		while(decimal != 0)
//	{
//		integerPart = decimal*10 ;
//		decimal =decimal*10 - integerPart ;
//		floatArr[x] = arr[integerPart];
//		x--;
//		if(x ==(char)-1)
//		{
//			break;
//		}
//	}
//	for(y = x+1;y <30;y++)
//	{
//		USART_Print_Send(floatArr[y]);
//	}
//}

void USART_Print_Send(char ch)
{
	while((USART_PRINT->SR&0X40)==0);
	USART_PRINT->DR = ch;
}

