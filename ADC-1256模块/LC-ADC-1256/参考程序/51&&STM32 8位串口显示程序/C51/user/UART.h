//////////////////////////////////
//


#include "STC15F2K60S2.H"
#include <string.h>
#include <intrins.h>

#define FOSC 11059200L          //ϵͳƵ��
#define BAUD 9600             //���ڲ�����



typedef unsigned char BYTE;
typedef unsigned int WORD;

bit busy;



void InitCOM(void)
{


    SCON = 0x50;                //8λ�ɱ䲨����
    T2L = (65536 - (FOSC/4/BAUD));   //���ò�������װֵ
    T2H = (65536 - (FOSC/4/BAUD))>>8;
    AUXR = 0x14;                //T2Ϊ1Tģʽ, ��������ʱ��2
    AUXR |= 0x01;               //ѡ��ʱ��2Ϊ����1�Ĳ����ʷ�����
    ES = 1;                     //ʹ�ܴ���1�ж�
    EA = 1;

}

/*----------------------------
���ʹ�������
----------------------------*/
void SendData(BYTE dat)
{
    while (busy);               //�ȴ�ǰ������ݷ������
    ACC = dat;                  //��ȡУ��λP (PSW.0)
    busy = 1;
    SBUF = ACC;                 //д���ݵ�UART���ݼĴ���
}

/*----------------------------
�����ַ���
----------------------------*/
void SendString(char *s)
{
    while (*s)                  //����ַ���������־
    {
        SendData(*s++);         //���͵�ǰ�ַ�
    }
}



/** COM receive message interrupt function**/

void Uart(void) interrupt 4 using 1
{
    if (RI)
    {
        RI = 0;                 //���RIλ
        //P0 = SBUF;              //P0��ʾ��������
        //P22 = RB8;              //P2.2��ʾУ��λ
    }
    if (TI)
    {
        TI = 0;                 //���TIλ
        busy = 0;               //��æ��־
    }

}


