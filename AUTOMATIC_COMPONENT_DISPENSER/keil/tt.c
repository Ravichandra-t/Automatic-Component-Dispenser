#include<reg51.h>
#include<i2c.h>
#include<lcd.h>
unsigned char bh=0x00,bl=0xff;
void main()
{
	unsigned char rr;
	init_lcd();
	clr_lcd();
	set_cur(1,0);
	lstrng("Writing 0");
	while(!(bl==0x00))
	{
		eeprom_write(bh,bl,0);
		bl=bl-0x01;
		delay(10);
	}
	delay(200);
	clr_lcd();
	bl=0xff;
	while(!(bl==0x00))
	{
	rr=eeprom_read(bh,bl);
	lvar(rr);
		delay(10);
	}
	while(1);
}