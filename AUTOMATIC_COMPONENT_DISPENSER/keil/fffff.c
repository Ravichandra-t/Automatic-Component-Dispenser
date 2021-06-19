#include<reg51.h>
#include<lcd.h>
#include<i2c.h>
#include<intrins.h>
sbit IR=P3^5;
short int I1[8];
unsigned char R[8];
short int a,b,c,d,e,f;
void disp_menu();
void c_issue();	
	
void EEPROM_update(int t)
{
	int i;
	switch(t)
	{
		case 1:for(i=0;i<8;i++)eeprom_write((t*10)+i,I1[i]);break;
		case 2:for(i=0;i<8;i++)	eeprom_write((t*10)+i,I1[i]);break;
		case 3:for(i=0;i<8;i++)	eeprom_write((t*10)+i,I1[i]);break;
		case 4:for(i=0;i<8;i++)	eeprom_write((t*10)+i,I1[i]);break;
		case 5:for(i=0;i<8;i++)	eeprom_write((t*10)+i,I1[i]);break;
	}
}
void EEPROM_red(int t)
{
	int i;
	switch(t)
	{
		case 1:for(i=0;i<8;i++) R[i]=eeprom_read((t*10)+i);break;
		case 2:for(i=0;i<8;i++) R[i]=eeprom_read((t*10)+i);break;
		case 3:for(i=0;i<8;i++) R[i]=eeprom_read((t*10)+i);break;
		case 4:for(i=0;i<8;i++) R[i]=eeprom_read((t*10)+i);break;
		case 5:for(i=0;i<8;i++) R[i]=eeprom_read((t*10)+i);break;
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
		lvar(t2);
		delay(200);
		anticlockwise(t2);
		while(key()!='C');
		clockwise(t2);
		clr_lcd();
		delay(200);
		return;
	}
	else if(t1<0)
	{
		t1=t1*-1;
		t2=5*t1;
		lvar(t2);
		delay(200);
		clockwise(t2);
		while(key()!='C');
		anticlockwise(t2);
		clr_lcd();
		delay(200);
		return;
		}	
		
}
	
	
int strc(unsigned char card[])
{
	unsigned char i;
	for(i=0;i<12;i++)
	{
		if(ID[i]!=card[i])
			return 1;
	}
	return 0;
}
int valid()
{
	a=(strc(CARD1));
	b=(strc(CARD2));
	c=(strc(CARD3));
	d=(strc(CARD4));
	e=(strc(CARD5));
	f=(strc(USER));
	if((a==0)||(b==0)||(c==0)||(d==0)||(e==0))
		return 1;
	else if(f==0)
		return 2;
	else
		return 0;
}

void c_issue(int t)
{
	char ky,kn;
	int kj;

	switch(t)
	{
		case 1:	clr_lcd();
						disp_menu();
						ky=key();
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
						delay(200);
						rot(ky);
						return;
						break;
	case 2:	clr_lcd();
						disp_menu();
						ky=key();
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
						delay(200);
						rot(ky);
						break;
			case 3:	clr_lcd();
						disp_menu();
						ky=key();
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
						delay(200);
						rot(ky);
						break;
		case 4:	clr_lcd();
						disp_menu();
						ky=key();
						clr_lcd();
						lstrng("No of Components:");
						kn=key();
						kj=kn-48;
						ldata(kn);
						delay(200);
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
						delay(200);
						rot(ky);
						break;
	case 5:	clr_lcd();
						disp_menu();
						ky=key();
						clr_lcd();
						lstrng("No of Components:");
						kn=key();
						kj=kn-48;
						ldata(kn);
						delay(200);
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
						}delay(200);
						rot(ky);
						break;
						

	}
}
void c_return(int t)
{
	char ky,kn;
	int kj;
	switch(t)
	{
		case 1:	clr_lcd();
						disp_menu();
						ky=key();
						clr_lcd();
						lstrng("No of Components:");
						kn=key();
						kj=kn-48;
						ldata(kn);
						delay(100);
						switch(ky)
						{
							case '1':I1[0]=I1[0]-kj;break;
							case '2':I1[1]=I1[1]-kj;break;
							case '3':I1[2]=I1[2]-kj;break;
							case '4':I1[3]=I1[3]-kj;break;
							case '5':I1[4]=I1[4]-kj;break;
							case '6':I1[5]=I1[5]-kj;break;
							case '7':I1[6]=I1[6]-kj;break;
							case '8':I1[7]=I1[7]-kj;break;
						}
						delay(200);
						rot(ky);
						break;
	case 2:	clr_lcd();
						disp_menu();
						ky=key();
						clr_lcd();
						lstrng("No of Components:");
						kn=key();
						kj=kn-48;
						ldata(kn);
						delay(100);
												switch(ky)
						{
							case '1':I1[0]=I1[0]-kj;break;
							case '2':I1[1]=I1[1]-kj;break;
							case '3':I1[2]=I1[2]-kj;break;
							case '4':I1[3]=I1[3]-kj;break;
							case '5':I1[4]=I1[4]-kj;break;
							case '6':I1[5]=I1[5]-kj;break;
							case '7':I1[6]=I1[6]-kj;break;
							case '8':I1[7]=I1[7]-kj;break;
						}
						delay(200);
						rot(ky);
						break;
					
	case 4:	clr_lcd();
						disp_menu();
						ky=key();
						clr_lcd();
						lstrng("No of Components:");
						kn=key();
						kj=kn-48;
						ldata(kn);
						delay(100);
												switch(ky)
						{
							case '1':I1[0]=I1[0]-kj;break;
							case '2':I1[1]=I1[1]-kj;break;
							case '3':I1[2]=I1[2]-kj;break;
							case '4':I1[3]=I1[3]-kj;break;
							case '5':I1[4]=I1[4]-kj;break;
							case '6':I1[5]=I1[5]-kj;break;
							case '7':I1[6]=I1[6]-kj;break;
							case '8':I1[7]=I1[7]-kj;break;
						}
						delay(200);
						rot(ky);
						break;
					

case 5:	clr_lcd();
						disp_menu();
						ky=key();
						clr_lcd();
						lstrng("No of Components:");
						kn=key();
						kj=kn-48;
						ldata(kn);
						delay(100);
												switch(ky)
						{
							case '1':I1[0]=I1[0]-kj;break;
							case '2':I1[1]=I1[1]-kj;break;
							case '3':I1[2]=I1[2]-kj;break;
							case '4':I1[3]=I1[3]-kj;break;
							case '5':I1[4]=I1[4]-kj;break;
							case '6':I1[5]=I1[5]-kj;break;
							case '7':I1[6]=I1[6]-kj;break;
							case '8':I1[7]=I1[7]-kj;break;
						}
						delay(200);
						rot(ky);
						break;
}

					}
				

void disp_menu()
{
	clr_lcd();
	lstrng("Components List");
	set_cur(2,0);
	lstrng("1:7400 2:7402 3:MUX");
	set_cur(3,0);
	lstrng("4:7404 5:7486 6:741");
	set_cur(4,0);
	lstrng("7:7483 8:4051 9:DAM");
}

int c_clockwise(int t)
{
	int i;
	for(i=0;i<t;i++){
	en1=1;en2=1;
	m1=1;m2=1;m3=0;m4=0;delay(4);
		if(IR==1)
			return 1;
	m1=0;m2=1;m3=1;m4=0;delay(4);
			if(IR==1)
			return 1;
	m1=0;m2=0;m3=1;m4=1;delay(4);
				if(IR==1)
			return 1;
	m1=1;m2=0;m3=0;m4=1;delay(4);
	if(IR==1)
			return 1;				
}}
void main()
{		
		
		int x;
		unsigned char i,ky,kk,ku;
		IR=1;
		init_lcd();
		clr_lcd();
		set_cur(1,0);
		lstrng("A  C  D");
		delay(300);
		clr_lcd();
		while(1)
		{
			clr_lcd();
			while(!c_clockwise(100));
			lstrng("Scan the card!");
			init_rfid();
			get_id();
			set_cur(2,0);
			for(i=0;i<12;i++)
				ldata(ID[i]);
			delay(300);
			x=valid();
			if(x==1)
			{
				clr_lcd();
				set_cur(1,3);
				lstrng("Card detected!");
				set_cur(2,5);
				switch(ID[10])
				{
					case 'A': while(1){
										lstrng("Table no 1");
										set_cur(3,1);
										lstrng("1--> ISSUE");
										set_cur(4,1);
										lstrng("2--> RETURN  D:EXIT");
										ky=key();
										if(ky=='1')
											c_issue(1);
										else if (ky=='2')
											c_return(1);
										else{
											clr_lcd();
											lstrng("Thank you..");
											delay(100);
											break;
										}
										clr_lcd();
										EEPROM_update(1);
					
					}
										break;
					case 'F': while(1){
										ky=key();
										lstrng("Table no 2");
										set_cur(3,1);
										lstrng("1--> ISSUE");
										set_cur(4,1);
										lstrng("2--> RETURN  D:EXIT");
								
										if(ky=='1')
											c_issue(2);
										else if (ky=='2')
											c_return(2);
										else{
											clr_lcd();
											lstrng("Thank you..");
											delay(100);
											break;
											
										}
										clr_lcd();
										EEPROM_update(2);
												
										}
										break;
										
					case 'C': while(1){
										lstrng("Table no 3");
										set_cur(3,1);
										lstrng("1--> ISSUE");
										set_cur(4,1);
										lstrng("2--> RETURN  D:EXIT");
										ky=key();
										if(ky=='1')
											c_issue(3);
										else if (ky=='2')
											c_return(3);
										else{
											clr_lcd();
											lstrng("Thank you..");
											delay(100);
											break;
										}
										clr_lcd();
										EEPROM_update(3);
										}
										break;
					case '9':while(1){
					lstrng("Table no 4");
										set_cur(3,1);
										lstrng("1--> ISSUE");
										set_cur(4,1);
										lstrng("2--> RETURN  D:EXIT");
										ky=key();
										if(ky=='1')
											c_issue(4);
										else if (ky=='2')
											c_return(4);
										else{
											clr_lcd();
											lstrng("Thank you..");
											delay(100);
											break;
										}
										clr_lcd();
										EEPROM_update(4);
										}break;
										
					case '2': while(1){
										lstrng("Table no 5");
										set_cur(3,1);
										lstrng("1--> ISSUE");
										set_cur(4,1);
										lstrng("2--> RETURN  D:EXIT");
										ky=key();
										if(ky=='1')
											c_issue(5);
										else if (ky=='2')
											c_return(5);
										else{
											clr_lcd();
											lstrng("Thank you..");
											delay(100);
											break;
										}
										clr_lcd();
										EEPROM_update(5);
										}break;
									
									}
								}
			else if(x==2)
			{
				clr_lcd();
				lstrng("LAB USER");
				set_cur(2,0);
				lstrng("1-->Details");
				set_cur(3,0);
				lstrng("2-->CLEAR");
				kk=key();
				if(kk=='1')
				{
				  clr_lcd();
					lstrng("Enter table no:");
					ku=key();
					switch(ku)
					{
						case '1':EEPROM_red(1);break;
						case '2':EEPROM_red(2);break;
						case '3':EEPROM_red(3);break;
						case '4':EEPROM_red(4);break;
						case '5':EEPROM_red(5);break;
					}
					clr_lcd();
					set_cur(1,0);
					lstrng("7400:");ldata(R[0]+48);
					set_cur(1,9);
					lstrng("7402:");ldata(R[1]+48);
					set_cur(2,0);
					lstrng("MUX:");ldata(R[2]+48);
					set_cur(2,9);
					lstrng("7404:");ldata(R[3]+48);
					set_cur(3,0);
					lstrng("7486:");ldata(R[4]+48);
					set_cur(3,9);
					lstrng("741:");ldata(R[5]+48);
					set_cur(4,0);
					lstrng("7483:");ldata(R[6]+48);
					set_cur(4,9);
					lstrng("4051:");ldata(R[7]+48);
					delay(600);
				}
			}
		else 
				{
					clr_lcd();
					lstrng("Invalid Card!");
				}
										
				
			

		}

}