/*****************************************
创建：陈志强
时间：2010.6.12
功能：NRF24L01射频模块C文件(发射部分)
*****************************************/
#include"reg52.h"
#include"Allhead.h"
/*********************主函数***************************/
sbit KEY=P3^7;
void main()
{
 //  unint ReadTempDate;//读取温度
   char TxDate[4];
   NRF24L01Int();
   while(1)
    {
		 TxDate[0]=(char)KEY;
		 NRFSetTxMode(TxDate);//发送温度
		 while(CheckACK());	//检测是否发送完毕
	}

}