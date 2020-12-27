
#include"reg52.h"
#include"string.h"
#include"stdio.h"
#include"lcd4.h"

sbit L1  = P0^0;
sbit L2  = P0^1;
sbit L3  = P0^2;

void delay(unsigned int);
void send_com(unsigned char *);
void new_line(void );
void longdelay(void);
void send_char(unsigned char );

unsigned int i;
int count=0,prev=-1;
unsigned char buffer[45];
unsigned int loop1;

int a,b,c,d;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void send_com(unsigned char *arr)
{
	unsigned char i;
	for(i=0;arr[i]!='0';i++)
	{
		send_char(arr[i]);
		delay(10);
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void main()
{
	LCD_init();

	TMOD =0X21;
	TH1  =0X0FD; 
	SCON =0X50;
	TR1  =1;

	delay(10);

	LCD_puts(0x80,"Initializing    ");
	LCD_puts(0xc0," . ");
	send_com("AT\n");
	buz1=0;
	delay(100);
	buz1=1;
	delay(200);

	LCD_puts(0xc0," .  . ");
	buz1=0;
	delay(100);
	buz1=1;
	delay(200);

	send_com("AT+CWSAP=\"channels/121585\",\"12345678\",2,3\n");
	LCD_puts(0xc0," .  .  . ");
	buz1=0;
	delay(100);
	buz1=1;
	delay(200);
	delay(200);

	send_com("AT+CWJAP=\"IOT\",\"carvingnotions\"\n");
	LCD_puts(0xc0," .  .  .  . ");
	buz1=0;
	delay(200);
	buz1=1;
	delay(200);
	delay(200);

	LCD_command(0x01);
	while(1)
	{
		LCD_puts(0x80,"WaterGrid Status");

		if(L1==1)
		{
			LCD_puts(0xc2,"O");
			a=1;
			led1=0;
		}
		else
		{
			LCD_puts(0xc2,"X"); 
			a=0;  
			led1=1;
		}

		if(L2==1)
		{
			LCD_puts(0xc4,"O");
			b=1;
			led2=0;
		}
		else
		{
			LCD_puts(0xc4,"X");  
			b=0; 
			led2=1;
		}

		if(L3==1)
		{
			LCD_puts(0xc6,"O");
			c=1;
			led3=0;
		}
		else
		{
			LCD_puts(0xc6,"X"); 
			c=0; 
			led3=1; 
		}

		loop1++;
		
		if(loop1>20)
		{
			loop1=0;
			prev=count;
			send_com("AT\n");
			delay(200);
			delay(200);

			send_com("AT+CIPSTART=\"TCP\",\"184.106.153.149\"\n");
			delay(200);
			delay(200);

			send_com("AT+CIPSEND=80\n");
			delay(200);
			delay(200);

			send_com("GET /update?api_key=JODGOKBUMTY38HYQ&field1=");
			sprintf(buffer,"%d&field2=%d&field3=%d&field4=%d",a,b,c,d);
			send_com(buffer);
			send_com("\n\n");
			delay(200);
			delay(200);
		}
	}			 
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void delay(unsigned int r)
{ 
	unsigned int p,q;
	for(p=0;p<r;p++)
		for(q=0;q<=200;q++)
		{
		}
}    

/////////////////////////////////////////////////////////////////////////////////////////////////////////

void send_char(unsigned char arr_ch)
{
	SBUF=arr_ch;
	while(TI==0);
	TI=0;
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////
