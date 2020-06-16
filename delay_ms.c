void delay_ms(unsigned char t)
{    
	unsigned char i,j=0;
	for(i=0;i<t;i++)
		for(j=0;j<125;j++);
}