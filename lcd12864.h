#define DataPort P2  //单片机P2口与液晶DB0～DB7相接
sbit RS = P0^5;
sbit RW = P0^6;
sbit E  = P0^7;
sbit PSB = P0^2;

extern unsigned char disp[4];
void display();
void LCD12864_init();
void Check_Busy();
void Write_Cmd(unsigned char Cmd);
void Write_Data(unsigned char Data);