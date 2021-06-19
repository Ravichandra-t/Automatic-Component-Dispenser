sbit scl=P3^6;
sbit sda=P3^7;
sbit m1= P2^2;
sbit m2= P2^3;
sbit m3= P2^4;
sbit m4= P2^5;
sbit en1=P2^6;
sbit en2=P2^7;

unsigned char ID[12];
code unsigned char CARD1[12]="5A001DFB19A5";
code unsigned char CARD2[12]="5A001E17A4F7";
code unsigned char CARD3[12]="5A001DC34ACE";
code unsigned char CARD4[12]="5A001E1EC09A";
code unsigned char CARD5[12]="5A001E02682E";
code unsigned char USER[12]="5A001E326412";
//////////////////////////////////////////////////////////
void del(int i)
{
int j;
while(i--)
for(j=0;j<1223;j++);
}


void start(void)
{
/*to start make
high to low of sda with a clock is high
*/
sda=1;
scl=1; 
sda=0;
//scl=0;
}

void stop()
{
/* to stop the i2c
make an low to high of sda with scl =1*/
// scl=0;
sda=0;
scl=1; 
sda=1;
//scl=0;
}


void write(unsigned char dat)
{
unsigned char i;
for(i=0;i<8;i++)
{
scl=0;
sda=(dat&0x80>>i)?1:0;
scl=1;
}
}

void ack(void)
{
scl=0;
sda=1;
scl=1;
scl=0;
}

void noack(void)
{
scl=0;
sda=1;
scl=1;
}

unsigned char read()
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


void eeprom_write(char addr,char ch)
{
start();

write(0xa0);
ack();

write(addr);
ack();

write(ch);
ack();

stop();
del(10);
}


char eeprom_read(char addr)
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

//////////////////////////////////////////////////////////////////////////////////////
void init_rfid()     
{
		TMOD=0x20;  
		TH1=0XFD; 
		SCON=0x50;
		TR1=1;
}

void clockwise(int t)
{
	int i;
	en1=1;en2=1;
	for(i=0;i<t;i++){
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
	for(i=0;i<t;i++){
	m1=1;m2=0;m3=0;m4=0;delay(4);
	m1=0;m2=1;m3=0;m4=0;delay(4);
	m1=0;m2=0;m3=1;m4=0;delay(4);
	m1=0;m2=0;m3=0;m4=1;delay(4);
	/*m1=0;m2=0;m3=1;m4=0;delay(4);
	m1=0;m2=1;m3=1;m4=0;delay(4);
	m1=0;m2=1;m3=0;m4=0;delay(4);
	m1=1;m2=1;m3=0;m4=0;delay(4);*/
	}}

	
void get_id() 
{
    unsigned char i;
    for(i=0;i<12;i++)
     { 
         while(RI==0); 
					ID[i]=SBUF;
          RI=0;
		 }
}

	/*m1=1;m2=0;m3=0;m4=0;delay(4);
	m1=1;m2=0;m3=0;m4=1;delay(4);
	m1=0;m2=0;m3=0;m4=1;delay(4);
	m1=0;m2=0;m3=1;m4=1;delay(4);
	m1=0;m2=0;m3=1;m4=0;delay(4);
	m1=0;m2=1;m3=1;m4=0;delay(4);
	m1=0;m2=1;m3=0;m4=0;delay(4);*/
