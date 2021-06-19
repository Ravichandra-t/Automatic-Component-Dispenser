sbit rs=P2^0;
sbit en=P2^1;
sbit R1=P0^0;
sbit R2=P0^1;
sbit R3=P0^2;
sbit R4=P0^3;
sbit C1=P0^4;
sbit C2=P0^5;
sbit C3=P0^6;
sbit C4=P0^7;
char read_key();
void delay(unsigned int ms);
void init_lcd();
void lcmd( char cmd);
void ldata( char msg);
void lstrng( char *msg);
void set_cur(char line, char position);
void lvar(unsigned char val);
void delay(unsigned int ms)
	{
		int i,j;
		for(i=0;i<ms;i++)
			for(j=0;j<1275;j++);
	}
void lvar(unsigned char val)
{
	unsigned char temp;
	temp = val/100;				 				// 123 / 100 = 1
	if(temp!=0)
	{
		ldata(temp+0x30);
	}
	temp = val/10;	   							// 123 / 10 = 12
	temp = temp%10;								// 12 % 10 = 2
	ldata(temp+0x30);
	temp = val%10;								// 123 % 10 = 3
	ldata(temp+0x30);
}



void init_lcd()
	{
		lcmd(0x38);
		delay(20);
		lcmd(0x0c);
		delay(20);
		lcmd(0x80);
		delay(20);
	}
void lcmd( char cmd)
	{
		P1=cmd;
		en=1;
		rs=0;
		delay(4);
		en=0;
	}
void ldata( char msg)
	{
		P1=msg;
		en=1;
		rs=1;
		delay(4);
		en=0;
	}
void lstrng( char *msg)
	{
		int k;
		for(k=0;msg[k]!=0;msg++)
			{
				ldata(msg[k]);
			}
	}
void set_cur(char line, char position)
	{
		if(line==1)
			lcmd(0x80+position);
		if(line==2)
			lcmd(0xC0+position);
		if(line==3)
			lcmd(0x94+position);
		if(line==4)
			lcmd(0xD4+position);
	}
void clr_lcd()
	{
		lcmd(0x01);
		lcmd(0x80);
	}																														   
char read_key()
	{
    	char t;
		C1=1;C2=1;C3=1;
		R1=0;R2=1;R3=1;R4=1;	//first row //
		if(C1==0){delay(1);while(C1==0);t='1';return t;}  //first column //
		if(C2==0){delay(1);while(C2==0);t='2';return t;}  //second column //
		if(C3==0){delay(1);while(C3==0);t='3';return t;}  //third column //
		if(C4==0){delay(1);while(C4==0);t='A';return t;}  //third column //
		R1=1;R2=0;R3=1;R4=1;	//second row //
		if(C1==0){delay(1);while(C1==0);t='4';return t;}  //first column //
		if(C2==0){delay(1);while(C2==0);t='5';return t;}  //second column //
		if(C3==0){delay(1);while(C3==0);t='6';return t;}  //third column //
		if(C4==0){delay(1);while(C4==0);t='B';return t;}  //third column //
		R1=1;R2=1;R3=0;R4=1;	 //third row //
		if(C1==0){delay(1);while(C1==0);t='7';return t;}  //first column //
		if(C2==0){delay(1);while(C2==0);t='8';return t;}  //second column //
		if(C3==0){delay(1);while(C3==0);t='9';return t;}  //third column //
		if(C4==0){delay(1);while(C4==0);t='C';return t;}  //third column //
		R1=1;R2=1;R3=1;R4=0;	//fourth row //
		if(C1==0){delay(1);while(C1==0);t='*';return t;}  //first column //
		if(C2==0){delay(1);while(C2==0);t='0';return t;}  //second column //
		if(C3==0){delay(1);while(C3==0);t='#';return t;}  //third column //
		if(C4==0){delay(1);while(C4==0);t='D';return t;}  //third column //
		return 'n';
	}
char key(void)
	{
		char ch;
		while((ch=read_key())=='n');
		return ch;
	}
////////////////////////////RFID//////////////////////////////////////
	void reset (void)
{
((void (code *)(void)) 0) ();
}


	
