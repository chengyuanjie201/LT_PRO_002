/*****************************************
创建：陈志强
时间：2010.6.12
功能：工程主函数(主机接收部分)
*****************************************/
#include"reg52.h"
#include"Allhead.h"
sbit RELAY=P3^7;
/************************主函数********************/
void main()
{
  //LCD1602Int();
//   *(RevTempDate+4)='\0';
   NRF24L01Int();
	 Max232Int();//串口初始化
   while(1)
    {
		NRFSetRXMode();//设置为接收模式
		GetDate();//开始接受�
		if(RevTempDate[0]==0)
			RELAY=0;
		else
			RELAY=1;
	}
}