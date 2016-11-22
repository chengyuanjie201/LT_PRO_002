/********************************************************************
创建人：陈志强
时间：2010.5.17
功能：MAX232驱动
*********************************************************************/
#include"reg52.h"
#include"allhead.h"	
unchar RevFlags;

typedef bit BOOL;
typedef unsigned char BYTE;
typedef unsigned int WORD;
sfr AUXR=0x8e;
sbit RXB = P3^0; //??????
sbit TXB = P3^1;

//#define BAUD 0xF400 // 1200bps @ 11 .0592MHz
//#define BAUD 0xFA00 // 2400bps @ 11 .0592MHz
#define BAUD 0xFD00 // 4800bps @ 11 .0592MHz
//#define BAUD 0xFE80 // 9600bps @ 11 .0592MHz
//#define BAUD 0xFF40 //19200bps @ 11 .0592MHz
//#define BAUD 0xFFA0 //38400bps @ 11 .0592MHz
//#define BAUD 0xEC00 // 1200bps @ 18.432MHz
//#define BAUD 0xF600 // 2400bps @ 18.432MHz
//#define BAUD 0xFB00 // 4800bps @ 18.432MHz
//#define BAUD 0xFD80 // 9600bps @ 18.432MHz
//#define BAUD 0xFEC0 //19200bps @ 18.432MHz
//#define BAUD 0xFF60 //38400bps @ 18.432MHz
//#define BAUD 0xE800 // 1200bps @ 22.11 84MHz
//#define BAUD 0xF400 // 2400bps @ 22.11 84MHz
//#define BAUD 0xFA00 // 4800bps @ 22.11 84MHz
//#define BAUD 0xFD00 // 9600bps @ 22.11 84MHz
//#define BAUD 0xFE80 //19200bps @ 22.11 84MHz
//#define BAUD 0xFF40 //38400bps @ 22.11 84MHz
//#define BAUD 0xFF80 //57600bps @ 22.11 84MHz

BYTE TBUF,RBUF;
BYTE TDAT,RDAT;
BYTE TCNT,RCNT;
BYTE TBIT,RBIT;
BOOL TING,RING;
BOOL TEND,REND;
BOOL CT;
BYTE t, r;
BYTE buf[16]="1234567890qwerty";

void Max232Int()
{
    TMOD = 0x00; //???????1??????0??????16???????
    AUXR = 0x80; //AUXR?????7?6?---0??12???12T??51?IO?--1??????1T
    TL0 = BAUD;
    TH0 = BAUD>>8; //????????--????????
    TR0 = 1;    //?????0
    ET0 = 1;    //??T0????
    PT0 = 1;    //?????
    EA = 1;     //??????
    TING = 0;
    RING = 0;
    TEND = 1;
    REND = 0;
    TCNT = 0;
    RCNT = 0;
}
void Max232SendChar(unchar date)
{
		BYTE j=0;
    WORD i=0;
		TING = 1; 
    TBUF = date;
    i=6000;
    while(i--);  //??????--???????
    if (j>16)
			j=0;
}
void tm0() interrupt 1 using 1    
{
    if (RING)
    {
        if (--RCNT == 0)   //??---?????1
        {
            RCNT = 3;  
            if (--RBIT == 0)   //????????---????---??9?--8????---1????
            {
                RBUF = RDAT;   //?????
                RING = 0;   
                REND = 1;  
            }
            else//????9??????---????????--???
            {
                RDAT >>= 1; 
                if (RXB) 
                    RDAT |= 0x80; 
//????????????0??1
            }
        }
    }
    else if (!RXB) 
    {
        RING = 1;  
        RCNT = 4;  
        RBIT = 9;  
    }
    if (--TCNT == 0)  //??
    {
        TCNT = 3;  
        if (TING)  
        {
            if (TBIT == 0)//9???????
            {
                TXB = 0;   //?????
                TDAT = TBUF;  //??
                TBIT = 9;   //????????????8+1
                TEND = 0;  
            }
            else
            {
                TDAT >>= 1;   //??---??????
                if (--TBIT == 0)
                {
                    TXB = 1;
                    TING = 0;  
                    TEND = 1;  
                }
                else
                {
                    TXB = CY;  //CY????????7?
                }
            }
        }
    }
}
void MAX232SendDate()
{
		Max232SendChar(01);
}
