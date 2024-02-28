#include<reg51.h>
#include "sim800l.h"
sbit firesensor=P3^2;
sbit alcoholsensor=P3^3;
sbit rs=P1^0;
sbit rw=P1^1;
sbit en=P1^2;
sbit buzzer=P2^4;
sbit motter=P2^5;


//char message_one[30] = "Your Son is Drunk";
//char message_two[30] = "Fire occured in Vehicle";

//unsigned char NUMBER[20] = "+9779865993612\"";        //Here insert your number where you want to send message
//void tx(unsigned char send);
//void tx_str(unsigned char *s);
//unsigned char rx();
void delay(unsigned int j)
{
    int a, b;
    for (a = 0; a < j; a++)
    {
        for (b = 0; b < 10; b++);
    }
}

void buzzer_play()
	{
	int i;
	for(i=0;i<5;i++){
	buzzer=1;
	delay(1000);
	buzzer=0;
	delay(1000);
	delay(1000);
	buzzer=1;
	delay(1000);
	delay(1000);
	buzzer=0;
	delay(1000);
	delay(1000);
	buzzer=1;
	delay(100);
	delay(1000);
	delay(1000);
	buzzer=0;
	delay(100);
	delay(1000);
	buzzer=1;
	delay(100);
	delay(1000);
	delay(1000);
	delay(1000);
	buzzer=0;
	delay(1000);
	delay(1000);
	buzzer=1;
	delay(1000);
	delay(1000);
	delay(1000);	
	delay(1000);
	delay(1000);
	buzzer=0;
	}
}	
void send_sms_alcohol()
{
	sendString("AT+CMGF=1\r\n");
  delay(100);
  sendString("AT+CMGS=\"+9779865993612\"\r\n");
  delay(100);
	sendString("The driver is drunk");
	sendChar(0x1A);
	delay(100);
	sendString("AT+CMGF=0\r\n");
	delay(100);
}
    void send_sms_fire()
{
	sendString("AT+CMGF=1\r\n");
  delay(100);
  sendString("AT+CMGS=\"+9779865993612\"\r\n");
  delay(100);
	sendString("Fire Occur");
	sendChar(0x1A);
	delay(100);
	sendString("AT+CMGF=0\r\n");
	delay(100);
}        




void lcddat(unsigned char); //pass dataa
void lcdcmd(unsigned char); // send command
void lcddis(unsigned char *);  //send character
//void gsm(unsigned int);
void main()
{
	delay(90000); //gsm initialized
	delay(90000); //gsm initialized
	delay(90000); //gsm initialized
	delay(90000); //gsm initialized
	delay(90000); //gsm initialized
	delay(90000); //gsm initialized
	delay(90000); //gsm initialized
	initSerial();
	lcdcmd(0x0F);
	lcdcmd(0x38); 
	lcdcmd(0x01);
	buzzer=1;
	motter=0;
  
		lcdcmd(0x80);
	  lcdcmd(0x01);
		lcddis("VEHICLE SAFETY");
		delay(1000);
		lcdcmd(0xc0);
		lcddis("  SYSTEM  ");
	delay(90000); 
	
	back:
	while(1)
	{
		
		if(firesensor == 0)
			
		{
			lcdcmd(0x80);
			lcdcmd(0x01);//clear
			
			lcddis(" FIRE OCCURRED");
			delay(1000);
			lcdcmd(0xc0);
			lcddis("WARNING!!!...");
			delay(10000);
			delay(10000);
			lcdcmd(0x01);
			motter=1;
			buzzer=0;
			lcdcmd(0x01);
		 // sim sms send
	
			send_sms_fire();
			lcddis("GET OUT");
			delay(1000);
			lcdcmd(0xc0);
			lcddis("FROM VEHICLE");
			delay(1000);
			buzzer_play();
			lcdcmd(0x01);
			delay(90000); 
			delay(90000); 
			back1:
			goto back1;
			
			
		}
		else if(alcoholsensor==0)
		{
			lcdcmd(0x80);
			lcdcmd(0x01);
			lcddis("ALCOHOL DETECTED");
			
      send_sms_alcohol();
			buzzer=0;
			
			delay(1000);
			lcdcmd(0xc0);
			lcddis("MESSAGE SEND...");
			motter=1;
			delay(100);
			buzzer_play();
			lcdcmd(0x01);
			delay(90000); 
			delay(90000); 
			back2:
			goto back2;
		

		}
		else
		{
			lcdcmd(0x01);
			goto back;
		}
		
	}
}

void lcdcmd(unsigned char v)
{
	P0=v;
	rs=0;
	rw=0;
	en=1;
	delay(1000);
	en=0;
}
void lcddat(unsigned char d)
{
	P0=d;
	rs=1;
	rw=0;
	en=1;
	delay(1000);
	en=0;
}
void lcddis(unsigned char *s)
{
	int w;
	for (w=0;s[w] !='\0';w++)
{
	lcddat(s[w]);
}
delay(1000);
}
//void delay()
//{
	//unsigned int i;
	//for(i=0;i10000;i+);
//}








