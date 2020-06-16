#ifndef  _DA_H 			//理解为	if not define led.h
#define _DA_H 
#include<reg52.h>    //包含单片机寄存器的头文件
#include<stdio.h>
#include<math.h>
#define  PCF8591 0x90    //PCF8591 地址

bit DACconversion(unsigned char sla,unsigned char c,  unsigned char Val);
bit ISendByte(unsigned char sla,unsigned char c);
unsigned char IRcvByte(unsigned char sla);
#endif	// 定义结束