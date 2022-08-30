

//��Ƭ���ͺţ�STC15W408AS 
//	��ѹ	��5V 
//�ڲ�RC�񵴣�11.0592M



#include <stdio.h>
#include "STC15F2K60S2.H"
#include "ADS1256.H"
#include "uart.h"

sbit LED = P5^5;

/*
*********************************************************************************************************
*	�� �� ��: DelayMs
*	����˵��: ʱ����ʱ
*	��    ��: ms �Ժ���Ϊ��λ.
*	�� �� ֵ: ��
*********************************************************************************************************
*/
void DelayMs( unsigned int ms)
{
	unsigned int i,j;
	for (i = 0; i < ms; i++)
		for(j=0;j<1074;j++);
}

#define u8 unsigned char 
#define u16 unsigned short
							
//	sbit SCK  = P1^2;
//	sbit DIN  = P1^3;
//	sbit DOUT = P1^4; 
//	sbit DRDY = P1^5;	
//	sbit CS   = P1^6;	 
						  

void main()
{

	u16 ch=0;
	signed	long Adc;
	float  Volts;
	char str[20];

    InitCOM();  			//��ʼ������  ������ 9600
	Init_ADS1256_GPIO();  	// ����I/O��
	DelayMs(50);
    ADS1256_Init();			//ADS1256 ������ʼ��

	while(1)
	{


		for(ch = 0;ch < 8;ch++)
		{	
			//Adc = ADS1256ReadData((u8)( 0| ADS1256_MUXN_AINCOM));// �൱�� ( ADS1256_MUXP_AIN0 | ADS1256_MUXN_AINCOM);		
			Adc = ADS1256ReadData( ch<<4|ADS1256_MUXN_AINCOM);
				
			 /*��ֲɼ���ʽ*/
			 /*Adc = ADS1256ReadData( ADS1256_MUXP_AIN0|ADS1256_MUXN_AIN1); //P = AIN0 ,N = AIN1 ��ַ�ʽ*/
			
			Volts = Adc*.00000059453; // 0.00000059453 Ϊϵ����ADC����������һ����ƫ��ڴ�У׼��
			sprintf(str,"ͨ��%d:%fV ",(u16)ch,Volts);  // ��ðѴ��ڵ������ִ��ڷŵ�������ݻ��Զ��������룬����������Щ��	
			SendString(str);


		}
	 	 	SendString("\r\n");
			DelayMs(10);
		   	LED=!LED;
	}

	
}




