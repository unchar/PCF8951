#include<DA.h>
#include<lcd12864.h>
#include<I2C.h>
#include<delay_ms.h>
unsigned char dat;

 //*****串口初始化函数***********
void Initial_com(void)
{
 EA=1;        //开总中断
 ES=1;        //允许串口中断
 ET1=1;        //允许定时器T1的中断
 TMOD=0x20;   //定时器T1，在方式2中断产生波特率
 PCON=0x00;   //SMOD=0
 SCON=0x50;   // 方式1 由定时器控制
 TH1=0xfd;    //波特率设置为9600
 TL1=0xfd;
 TR1=1;       //开定时器T1运行控制位

}
void main()
{  
		LCD12864_init();  							 // LCD12864初始化	
		Initial_com();										//初始化PCF8591
	
		
		while(1)
			{	
					int temp,value;
				
				ISendByte(PCF8591,0x03);  // 0x00-ch0 0x01-ch1 0x02-ch2 
				temp =IRcvByte(PCF8591);  //ADC3   	   可调0-5v
				
				//P0=temp;
			
				value=temp*1.012/255*5000;
				disp[0]=value%10 +'0';
				disp[1]=value/10%10+'0';
				disp[2]=value/100%10+'0';
				disp[3]=value/1000+'0';  //+'0'

				display();
						if(RI)    //如果RI=1，则接收完毕
					{
						RI=0;    //软件清零
						dat=SBUF;
					 
						if(dat=='V')  //查询电量
						{
							SBUF=disp[3];
							delay_ms(1);
							
							SBUF='.';
							delay_ms(1);
							SBUF=disp[2];
							delay_ms(1);
							
							SBUF=disp[1];
							delay_ms(1);
							
							SBUF=disp[0];
							delay_ms(1);
							
							SBUF='V';
							
						}
				
					}
		}

}
