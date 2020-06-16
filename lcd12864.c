#include<reg52.h>
#include<delay_ms.h>
#include<lcd12864.h>
#define uchar unsigned char
#define uint unsigned int

unsigned char disp[4];
uchar code tab0[]={"电压测量系统"};
uchar code tab1[]={"U ="};
void Check_Busy() //检测忙位
{  
    RS=0;   // RS=0、RW=1读出忙标志（BF）的状态
    RW=1;
    E=1;     //E的下降沿有效
    DataPort=0xff;  //如果想读取端口的数据，需要先把端口置位
    while((DataPort&0x80)==0x80); //忙则等待
    E=0;
}
//*******************************************************************************************
void Write_Cmd(unsigned char Cmd) //写命令
{
	Check_Busy();
	RS=0;   // RS=0、RW=0写命令
	RW=0;
	E=1;   //E的下降沿有效
	DataPort=Cmd;  //写命令到端口
	E=0;
}
//*******************************************************************************************
void Write_Data(unsigned char Data)//写数据
{
	Check_Busy();
	RS=1;   // RS=1、RW=0写数据
	RW=0;
	E=1;   //E的下降沿有效
	DataPort=Data; //写数据到端口
	E=0;
}
//*******************************************************************************************
void LCD12864_init() // 液晶屏初始化
{  
   PSB=1;            //设置为8BIT并口工作模式
   Write_Cmd(0x01);  //清除显示，并且设定地址指针为00H
   delay_ms(1); 
   Write_Cmd(0x30);  //选择基本指令集、8bit数据流
   delay_ms(1);         
   Write_Cmd(0x06);  //读/写时，设定游标的移动方向及指定显示的移位
   delay_ms(1); 
   Write_Cmd(0x0c);  //开显示(无游标、不反白)
   delay_ms(1);                          
}

void display()  //显示
{
			

	unsigned char i;

	Write_Cmd(0x81);								//设置显示地址位置，即在第一行显示
			 			i=0; 				//初始化变量，防止显示乱码
				while(tab0[i]!='\0')
				{
					Write_Data(tab0[i]); //显示变量i对应的数组元素
					delay_ms(2);
					i++;	//为显示下一个字符变量自增
				}



	Write_Cmd(0x90); 	//设置显示地址位置，即在第二行显示
				i=0; 				//初始化变量，防止显示乱码
				while(tab1[i]!='\0')
				{
					Write_Data(tab1[i]); //显示变量i对应的数组元素
					delay_ms(2);
					i++;	//为显示下一个字符变量自增
				}



		Write_Cmd(0x92); 	//设置显示地址位置，即在第二行第四个显示
		Write_Data(disp[3]); //显示千位
		
		Write_Cmd(0x93); 	
		Write_Data('.'); //显示.
	
		Write_Cmd(0x94); 	
		Write_Data(disp[2]); //显示百位
		
		Write_Cmd(0x95); 	
		Write_Data(disp[1]); //显示十位
		
		Write_Cmd(0x96); 	
		Write_Data(disp[0]); //显示个位
		
		Write_Cmd(0x97); 	
		Write_Data('V'); //显示
	}