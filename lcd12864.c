#include<reg52.h>
#include<delay_ms.h>
#include<lcd12864.h>
#define uchar unsigned char
#define uint unsigned int

unsigned char disp[4];
uchar code tab0[]={"��ѹ����ϵͳ"};
uchar code tab1[]={"U ="};
void Check_Busy() //���æλ
{  
    RS=0;   // RS=0��RW=1����æ��־��BF����״̬
    RW=1;
    E=1;     //E���½�����Ч
    DataPort=0xff;  //������ȡ�˿ڵ����ݣ���Ҫ�ȰѶ˿���λ
    while((DataPort&0x80)==0x80); //æ��ȴ�
    E=0;
}
//*******************************************************************************************
void Write_Cmd(unsigned char Cmd) //д����
{
	Check_Busy();
	RS=0;   // RS=0��RW=0д����
	RW=0;
	E=1;   //E���½�����Ч
	DataPort=Cmd;  //д����˿�
	E=0;
}
//*******************************************************************************************
void Write_Data(unsigned char Data)//д����
{
	Check_Busy();
	RS=1;   // RS=1��RW=0д����
	RW=0;
	E=1;   //E���½�����Ч
	DataPort=Data; //д���ݵ��˿�
	E=0;
}
//*******************************************************************************************
void LCD12864_init() // Һ������ʼ��
{  
   PSB=1;            //����Ϊ8BIT���ڹ���ģʽ
   Write_Cmd(0x01);  //�����ʾ�������趨��ַָ��Ϊ00H
   delay_ms(1); 
   Write_Cmd(0x30);  //ѡ�����ָ���8bit������
   delay_ms(1);         
   Write_Cmd(0x06);  //��/дʱ���趨�α���ƶ�����ָ����ʾ����λ
   delay_ms(1); 
   Write_Cmd(0x0c);  //����ʾ(���αꡢ������)
   delay_ms(1);                          
}

void display()  //��ʾ
{
			

	unsigned char i;

	Write_Cmd(0x81);								//������ʾ��ַλ�ã����ڵ�һ����ʾ
			 			i=0; 				//��ʼ����������ֹ��ʾ����
				while(tab0[i]!='\0')
				{
					Write_Data(tab0[i]); //��ʾ����i��Ӧ������Ԫ��
					delay_ms(2);
					i++;	//Ϊ��ʾ��һ���ַ���������
				}



	Write_Cmd(0x90); 	//������ʾ��ַλ�ã����ڵڶ�����ʾ
				i=0; 				//��ʼ����������ֹ��ʾ����
				while(tab1[i]!='\0')
				{
					Write_Data(tab1[i]); //��ʾ����i��Ӧ������Ԫ��
					delay_ms(2);
					i++;	//Ϊ��ʾ��һ���ַ���������
				}



		Write_Cmd(0x92); 	//������ʾ��ַλ�ã����ڵڶ��е��ĸ���ʾ
		Write_Data(disp[3]); //��ʾǧλ
		
		Write_Cmd(0x93); 	
		Write_Data('.'); //��ʾ.
	
		Write_Cmd(0x94); 	
		Write_Data(disp[2]); //��ʾ��λ
		
		Write_Cmd(0x95); 	
		Write_Data(disp[1]); //��ʾʮλ
		
		Write_Cmd(0x96); 	
		Write_Data(disp[0]); //��ʾ��λ
		
		Write_Cmd(0x97); 	
		Write_Data('V'); //��ʾ
	}