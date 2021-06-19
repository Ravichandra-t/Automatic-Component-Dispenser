/***************** Pin Details ********************/
sbit scl=P3^6;/* Serial Clock - I2C */
sbit sda=P3^7;/* Serial Data - I2C */
sbit m1= P2^2;/* Motor Driver - IN1 */
sbit m2= P2^3;/* Motor Driver - IN2 */
sbit m3= P2^4;/* Motor Driver - IN3 */
sbit m4= P2^5;/* Motor Driver - IN4 */
sbit en1=P2^6;/* Enable Pin for Motor Driver */
sbit en2=P2^7;/* Enable Pin for Motor Driver */
sbit IR=P3^5;//IR sensor pin for calibration
/**************************************************/

/***************Variable Declarations**************/
short int I1[8],flag=0;   //To store details
unsigned char R[8];//To get the details from EEPROM
short int a,b,c,d,e,f,Da;
unsigned char ID[12];
code unsigned char CARD1[12]="5A001DFB19A5";
code unsigned char CARD2[12]="5A001E17A4F7";
code unsigned char CARD3[12]="5A001DC34ACE";
code unsigned char CARD4[12]="5A001E1EC09A";
code unsigned char CARD5[12]="5A001E02682E";
code unsigned char USER[12]="5A001E326412";
/**************************************************/

/***************** I2C*****************************/
void start(void)/*   Start condition for I2C   */
	{
		sda=1;
		scl=1;         
		sda=0;
	}

void stop()/*   Stop condition for I2C   */
	{
		sda=0;
		scl=1; 
		sda=1;
	}

void write(unsigned char dat)/* I2C Byte Write */
	{
		unsigned char i;
		for(i=0;i<8;i++)
			{
				scl=0;
				sda=(dat&0x80>>i)?1:0;
				scl=1;
			}
	}	

void ack(void) /* I2C Acknowledgement  */
	{
		scl=0;
		sda=1;
		scl=1;
		scl=0;
	}

void noack(void) /* No Acknowledgement  */
	{
		scl=0;
		sda=1;
		scl=1;
	}

unsigned char read() /* I2C Byte Read */
	{
		unsigned char i,buff=0;
		sda=1;
		for(i=0;i<8;i++)
			{
				scl=1;
				if(sda)
					buff|=(0x80>>i);
				scl=0;
			}

		return buff;
	}
/*********************************************************/

/*************** Serial EEPROM (I2C)**********************/	
void eeprom_write(char addr,char ch)/* Byte write to EEPROM*/
	{
		start();
		write(0xa0);
		ack();
		write(addr);
		ack();
		write(ch);
		ack();
		stop();
		delay(8);
	}


char eeprom_read(char addr)/* Byte read from EEPROM*/
	{
		unsigned char buff;
		start();
		write(0xa0);
		ack();
		write(addr);
		ack();
		start();
		write(0xa0|1);
		ack();
		buff=read();
		noack();
		stop();
		return buff;
	}

void EEPROM_update(int t)/* Storing details to EEPROM  */
	{
		int i;
		for(i=0;i<8;i++)
			if(I1[i]<0)
				I1[i]=0;
		switch(t)
			{
				case 1:for(i=0;i<8;i++)eeprom_write((t*10)+i,I1[i]);break;
				case 2:for(i=0;i<8;i++)eeprom_write((t*10)+i,I1[i]);break;
				case 3:for(i=0;i<8;i++)eeprom_write((t*10)+i,I1[i]);break;
				case 4:for(i=0;i<8;i++)eeprom_write((t*10)+i,I1[i]);break;
				case 5:for(i=0;i<8;i++)eeprom_write((t*10)+i,I1[i]);break;
				case 6:for(i=0;i<8;i++)eeprom_write((t*10)+i,I1[i]);break;
				case 7:for(i=0;i<8;i++)eeprom_write((t*10)+i,I1[i]);break;
				case 8:for(i=0;i<8;i++)eeprom_write((t*10)+i,I1[i]);break;
				case 9:for(i=0;i<8;i++)eeprom_write((t*10)+i,I1[i]);break;
				case 10:for(i=0;i<8;i++)eeprom_write((t*10)+i,I1[i]);break;
			}
	}
void EEPROM_red(int t)/* Retreiving Data from EEPROM */
	{
		int i;
		switch(t)
			{
				case 1:for(i=0;i<8;i++) R[i]=eeprom_read((t*10)+i);break;
				case 2:for(i=0;i<8;i++) R[i]=eeprom_read((t*10)+i);break;
				case 3:for(i=0;i<8;i++) R[i]=eeprom_read((t*10)+i);break;
				case 4:for(i=0;i<8;i++) R[i]=eeprom_read((t*10)+i);break;
				case 5:for(i=0;i<8;i++) R[i]=eeprom_read((t*10)+i);break;
				case 6:for(i=0;i<8;i++) R[i]=eeprom_read((t*10)+i);break;
				case 7:for(i=0;i<8;i++) R[i]=eeprom_read((t*10)+i);break;
				case 8:for(i=0;i<8;i++) R[i]=eeprom_read((t*10)+i);break;
				case 9:for(i=0;i<8;i++) R[i]=eeprom_read((t*10)+i);break;
				case 10:for(i=0;i<8;i++) R[i]=eeprom_read((t*10)+i);break;
			}
	}

/*******************************************************************/
	
/***************************** EM18-RFID ***************************/
void init_rfid()/* Initializing serial port with Baudrate-9600 */   
	{
		TMOD=0x20;  
		TH1=0XFD; 
		SCON=0x50;
		TR1=1;
	}
void get_id() /* Reading Card ID From RFID reader */
	{
    unsigned char i;
    for(i=0;i<12;i++)
     { 
				while(RI==0); 
				ID[i]=SBUF;
        RI=0;
		 }
	}
int strc(unsigned char card[])/* String Compare Function */
	{
		unsigned char i;
		for(i=0;i<12;i++)
			{
				if(ID[i]!=card[i])
					return 1;
			}
		return 0;
	}
int valid() /* Validating the card read */
	{
		a=(strc(CARD1));
		b=(strc(CARD2));
		c=(strc(CARD3));
		d=(strc(CARD4));
		e=(strc(CARD5));
		f=(strc(USER));
		if((a==0)||(b==0)||(c==0)||(d==0)||(e==0))
			return 1;/* Student card */
		else if(f==0)
			return 2;/* Lab user card */
		else
			return 0;/* Invalid card */
	}

	
/************************************************************/

/**************** Stepper Motor *****************************/	

void clockwise(int t)
	{
		int i;
		en1=1;en2=1;
		for(i=0;i<t;i++)
			{
				m1=0;m2=0;m3=0;m4=1;delay(4);
				m1=0;m2=0;m3=1;m4=0;delay(4);
				m1=0;m2=1;m3=0;m4=0;delay(4);
				m1=1;m2=0;m3=0;m4=0;delay(4);
			}
	}	
void anticlockwise(int t)
	{
		int i;
		en1=1;en2=1;
		for(i=0;i<t;i++)
			{
				m1=1;m2=0;m3=0;m4=0;delay(4);
				m1=0;m2=1;m3=0;m4=0;delay(4);
				m1=0;m2=0;m3=1;m4=0;delay(4);
				m1=0;m2=0;m3=0;m4=1;delay(4);
			}		
	}

void rot(char ky)
	{
		int t,t1,t2;
		clr_lcd();	
		t=(int)ky-48;
		if(t>=5)
			t++;
		t1=5-t;
		if(t1>0)
			{
				t2=5*t1;
				lstrng("Moving to ");
				ldata(ky);
				delay(200);
				anticlockwise(t2);
				while(key()!='C');
				clockwise(t2);
				clr_lcd();
				return;
			}
		else if(t1<0)
			{
				t1=t1*-1;
				t2=5*t1;
				lstrng("Moving to ");
				ldata(ky);
				clockwise(t2);
				while(key()!='C');
				anticlockwise(t2);
				clr_lcd();
				return;
			}	
	}
int c_clockwise(int t) /* To calibrate */
	{
		int i;
		for(i=0;i<t;i++)
		{
			en1=1;en2=1;
			m1=1;m2=1;m3=0;m4=0;delay(4);
			if(IR==1)	return 1;
			m1=0;m2=1;m3=1;m4=0;delay(4);
			if(IR==1)	return 1;
			m1=0;m2=0;m3=1;m4=1;delay(4);
			if(IR==1)	return 1;
			m1=1;m2=0;m3=0;m4=1;delay(4);
			if(IR==1)	return 1;				
		}

	}
	
	void damage()
		{
		char ky,kn;
		int kj;
			flag=1;
		clr_lcd();
		clockwise(25);
		while(1)
			{clr_lcd();
		lstrng("Components List");
		set_cur(2,0);
		lstrng("1:7400 2:7402 3:MUX");
		set_cur(3,0);
		lstrng("4:7404 5:7486 6:741");
		set_cur(4,0);
		lstrng("7:7483 8:4051 ");
		ky=key();
			if(ky=='D')
				break;
		clr_lcd();
		lstrng("No of Components:");
		kn=key();
		kj=kn-48;
		ldata(kn);
		delay(100);
		switch(ky)
			{
				case '1':I1[0]=I1[0]+kj;break;
				case '2':I1[1]=I1[1]+kj;break;
				case '3':I1[2]=I1[2]+kj;break;
				case '4':I1[3]=I1[3]+kj;break;
				case '5':I1[4]=I1[4]+kj;break;
				case '6':I1[5]=I1[5]+kj;break;
				case '7':I1[6]=I1[6]+kj;break;
				case '8':I1[7]=I1[7]+kj;break;
			}
		}
		return;
}
	
	

void c_issue() /* Menu function to issue */
	{
		char ky,kn;
		int kj;
		clr_lcd();
		lstrng("Components List");
		set_cur(2,0);
		lstrng("1:7400 2:7402 3:MUX");
		set_cur(3,0);
		lstrng("4:7404 5:7486 6:741");
		set_cur(4,0);
		lstrng("7:7483 8:4051 ");
		ky=key();
		clr_lcd();
		lstrng("No of Components:");
		kn=key();
		kj=kn-48;
		ldata(kn);
		delay(100);
		switch(ky)
			{
				case '1':I1[0]=R[0]+kj;break;
				case '2':I1[1]=R[1]+kj;break;
				case '3':I1[2]=R[2]+kj;break;
				case '4':I1[3]=R[3]+kj;break;
				case '5':I1[4]=R[4]+kj;break;
				case '6':I1[5]=R[5]+kj;break;
				case '7':I1[6]=R[6]+kj;break;
				case '8':I1[7]=R[7]+kj;break;
			}
		delay(200);
		rot(ky);
		return;
	}
void c_return()  /*Menu function to return */
	{
		char ky,kn;
		int kj;
		clr_lcd();
		lstrng("Components List");
		set_cur(2,0);
		lstrng("1:7400 2:7402 3:MUX");
		set_cur(3,0);
		lstrng("4:7404 5:7486 6:741");
		set_cur(4,0);
		lstrng("7:7483 8:4051 9:DAM");
		ky=key();
		if(ky=='9')
		{
			Damage();
			anticlockwise(25);return;
		}
		clr_lcd();
		lstrng("No of Components:");
		kn=key();
		kj=kn-48;
		ldata(kn);
		delay(100);
		switch(ky)
			{
				case '1':I1[0]=R[0]-kj;if(I1[0]<0)I1[0]=0;break;
				case '2':I1[1]=R[1]-kj;if(I1[1]<0)I1[1]=0;break;
				case '3':I1[2]=R[2]-kj;if(I1[2]<0)I1[2]=0;break;
				case '4':I1[3]=R[3]-kj;if(I1[3]<0)I1[3]=0;break;
				case '5':I1[4]=R[4]-kj;if(I1[4]<0)I1[4]=0;break;
				case '6':I1[5]=R[5]-kj;if(I1[5]<0)I1[5]=0;break;
				case '7':I1[6]=R[6]-kj;if(I1[6]<0)I1[6]=0;break;
				case '8':I1[7]=R[7]-kj;if(I1[7]<0)I1[7]=0;break;
			
			}
		
		delay(200);
		rot(ky);
		return;
	}

void init_disp()/*  Menu Function  */
	{
		char ky;
		set_cur(3,1);
		lstrng("1--> ISSUE");
		set_cur(4,1);
		lstrng("2--> RETURN  D:EXIT");
		ky=key();
		if(ky=='1')
			c_issue();
		else if (ky=='2')
			{
				c_return();
				/*else
				{
				clr_lcd();
				lstrng("invalid");
				delay(400);
				}*/
			}
		else
			{
				clr_lcd();
				lstrng("Thank you..");
				delay(100);
				reset();
			}
	}