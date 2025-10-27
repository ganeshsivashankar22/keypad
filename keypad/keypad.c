#include<LPC21xx.h>
#define c0 (IOPIN0 &(1<<16))
#define c1 (IOPIN0 &(1<<17))
#define c2 (IOPIN0&(1<<18))
#define c3 (IOPIN0 &(1<<19))

#define r0 1<<20
#define r1 1<<21
#define r2 1<<22
#define r3 1<<23
#define LCD 0xff<<0
#define RS 1<<8
#define E 1<<9
void LCD_INIT(void);
void LCD_CMD(unsigned char);
void LCD_DATA(unsigned char);
 void delay_ms(int);
 void LCD_STRING(unsigned char *);
 void LCD_INTEGER(int);
 typedef unsigned char u8;
  unsigned int key_lut[4][4]={{1,2,3,4},{5,6,7,8},{9,10,11,12},{13,14,15,16}};
  unsigned int keyscan(void)
  {
  u8 row_val,col_val;
  PINSEL1|=0x00000000;
  IODIR0=r0|r1|r2|r3;
  while(1)
  {
  IOCLR0=r0;
  IOSET0=r1|r2|r3;
  while((c0&&c1&&c2&&c3)==1);
  IOCLR0=r0;
  IOSET0=r1|r2|r3;
  if((c0&&c1&&c2&&c3)==0)
  {
  row_val=1;
  break;
  }
  IOCLR0=r2;
  IOSET0=r0|r1|r3;
  if((c0&&c1&&c2&&c3)==0)
  {
  row_val=2;
  break;
  }
  		IOCLR0=r3;
		IOSET0=r0|r1|r2;
		if((c0&&c1&&c2&&c3)==0)
		{
		row_val=3;
		break;
		}

  
  }
  if(c0==0)
  col_val=0;
  else if(c1==0)
  col_val=1;
  else if(c2==0)
  col_val=2;
  else
  col_val=3;
  delay_ms(150);
  while((c0&&c1&&c2&&c3)==0);
  return key_lut[row_val][col_val];
  }
  int main()
  {
  int res;
  LCD_INIT();
  LCD_STRING("4x4 keypad");
  while(1)
  {
   LCD_CMD(0xc0);
   res=keyscan();
   LCD_INTEGER(res);
   delay_ms(500);
   LCD_CMD(0x01);
   }
   }
   void delay_ms(int ms)
   {
   int i;
   for(;ms>0;ms--)
   for(i=12000;i>0;i--);
   
   }

 void LCD_INIT(void)
{
IODIR0=0x000003ff;
LCD_CMD(0x01);
LCD_CMD(0x02);
LCD_CMD(0x0c);
LCD_CMD(0x38);
LCD_CMD(0x80);
}
void LCD_CMD(unsigned char cmd)
{
IOCLR0=LCD;
IOSET0=cmd;
IOCLR0=RS;
IOSET0=E;
delay_ms(2);
IOCLR0=E;
}

void LCD_DATA(unsigned char d)
{
IOCLR0=LCD;
IOSET0=d;
IOSET0=RS;
IOSET0=E;
delay_ms(2);
IOCLR0=E;
}
void LCD_STRING(unsigned char* s)
		{
		while(*s)
		{
		LCD_DATA(*s++);
		}
		}
	 void LCD_INTEGER(int n)

{

unsigned char a[5];

int i=0;

if(n==0)  

{


LCD_DATA('0');

}

else

{

if(n<0)

{

LCD_DATA('-');

n=-n;

}

while(n>0)

{

 a[i++]=n%10;

 n=n/10;

}

for(i=i-1;i>=0;i--)

LCD_DATA(a[i]+48);
}
}

			   