/*****************************************
��������־ǿ
ʱ�䣺2010.6.12
���ܣ�NRF24L01��Ƶģ��C�ļ�(���䲿��)
*****************************************/
#include"reg52.h"
#include"Allhead.h"
/*********************������***************************/
sbit KEY=P3^7;
void main()
{
 //  unint ReadTempDate;//��ȡ�¶�
   char TxDate[4];
   NRF24L01Int();
   while(1)
    {
		 TxDate[0]=(char)KEY;
		 NRFSetTxMode(TxDate);//�����¶�
		 while(CheckACK());	//����Ƿ������
	}

}