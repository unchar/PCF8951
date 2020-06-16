#include<DA.h>
#include<lcd12864.h>
#include<I2C.h>
#include<delay_ms.h>
unsigned char dat;

 //*****���ڳ�ʼ������***********
void Initial_com(void)
{
 EA=1;        //�����ж�
 ES=1;        //�������ж�
 ET1=1;        //����ʱ��T1���ж�
 TMOD=0x20;   //��ʱ��T1���ڷ�ʽ2�жϲ���������
 PCON=0x00;   //SMOD=0
 SCON=0x50;   // ��ʽ1 �ɶ�ʱ������
 TH1=0xfd;    //����������Ϊ9600
 TL1=0xfd;
 TR1=1;       //����ʱ��T1���п���λ

}
void main()
{  
		LCD12864_init();  							 // LCD12864��ʼ��	
		Initial_com();										//��ʼ��PCF8591
	
		
		while(1)
			{	
					int temp,value;
				
				ISendByte(PCF8591,0x03);  // 0x00-ch0 0x01-ch1 0x02-ch2 
				temp =IRcvByte(PCF8591);  //ADC3   	   �ɵ�0-5v
				
				//P0=temp;
			
				value=temp*1.012/255*5000;
				disp[0]=value%10 +'0';
				disp[1]=value/10%10+'0';
				disp[2]=value/100%10+'0';
				disp[3]=value/1000+'0';  //+'0'

				display();
						if(RI)    //���RI=1����������
					{
						RI=0;    //�������
						dat=SBUF;
					 
						if(dat=='V')  //��ѯ����
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
