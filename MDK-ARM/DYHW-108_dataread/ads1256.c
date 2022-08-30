#include <stdio.h>
#include "stm32f1xx_hal.h"
#include "ads1256.h"
#include "spi.h"

#define N 21          //中值滤波次数

void delay_us(uint32_t udelay)
{
  uint32_t startval,tickn,delays,wait;
 
  startval = SysTick->VAL;
  tickn = HAL_GetTick();
  //sysc = 72000;  //SystemCoreClock / (1000U / uwTickFreq);
  delays =udelay * 72; //sysc / 1000 * udelay;
  if(delays > startval)
    {
      while(HAL_GetTick() == tickn)
        {
 
        }
      wait = 72000 + startval - delays;
      while(wait < SysTick->VAL)
        {
 
        }
    }
  else
    {
      wait = startval - delays;
      while(wait < SysTick->VAL && HAL_GetTick() == tickn)
        {
 
        }
    }
}

//***************************
//		Pin assign	   	
//	  STM32			           ADS1256_1		
//		GPIOB_Pin_11 		<--- DRDY
//		GPIOB_Pin_12 		---> CS
//		GPIOB_Pin_13 		---> SCK
//		GPIOB_Pin_14(MISO)  <--- DOUT
//		GPIOB_Pin_15(MOSI)  ---> DIN

//	  STM32			           ADS1256_2		
//		GPIOC_Pin_4 		<--- DRDY
//		GPIOC_Pin_5 		---> CS
//		GPIOA_Pin_5 		---> SCK
//		GPIOA_Pin_6(MISO)  <--- DOUT
//		GPIOA_Pin_7(MOSI)  ---> DIN

//***************************	

//#define RCC_DRDY_1		  ((uint32_t)0x00000008)
#define PORT_DRDY_2			GPIOB
#define PIN_DRDY_2			GPIO_PIN_11

#define PORT_CS_2				GPIOB
#define PIN_CS_2			  GPIO_PIN_12

#define CS_2_0()				HAL_GPIO_WritePin(PORT_CS_2,PIN_CS_2,GPIO_PIN_RESET);
#define CS_2_1()				HAL_GPIO_WritePin(PORT_CS_2,PIN_CS_2,GPIO_PIN_SET);
#define ADS1256_DRDY_2  		(PORT_DRDY_2->IDR & PIN_DRDY_2)



#define PORT_DRDY_1		  GPIOC
#define PIN_DRDY_1			GPIO_PIN_4

#define PORT_CS_1			  GPIOC
#define PIN_CS_1				GPIO_PIN_5

#define CS_1_0()				HAL_GPIO_WritePin(PORT_CS_1,PIN_CS_1,GPIO_PIN_RESET);
#define CS_1_1()				HAL_GPIO_WritePin(PORT_CS_1,PIN_CS_1,GPIO_PIN_SET);
#define ADS1256_DRDY_1  		(PORT_DRDY_1->IDR & PIN_DRDY_1)

////ADS1256 写数据,向ADS1256中地址为regaddr的寄存器写入一个字节databyte
//void ADS1256WREG_2(unsigned char regaddr,unsigned char databyte)
//{
//  CS_1_1();  
//	CS_2_0();
//	while(ADS1256_DRDY_2);//当ADS1256_DRDY为低时才能写寄存器
//	SPI2_ReadWriteByte(ADS1256_CMD_WREG | (regaddr & 0x0F));
//	SPI2_ReadWriteByte(0x00);
//	SPI2_ReadWriteByte(databyte);
//	CS_2_1();
//}

////初始化ADS1256
//void ADS1256_Init(void)
//{
//	CS_1_1();
//	//*************自校准****************
//  while(ADS1256_DRDY_2);
//	CS_2_0();
//	SPI2_ReadWriteByte(ADS1256_CMD_SELFCAL);
//	while(ADS1256_DRDY_2);
//	CS_2_1();
//	//**********************************

//	ADS1256WREG_2(ADS1256_STATUS,0x06);               
////	ADS1256WREG(ADS1256_STATUS,0x04);           

////	ADS1256WREG(ADS1256_MUX,0x08);                  
//	ADS1256WREG_2(ADS1256_ADCON,ADS1256_GAIN_1);      // 放大倍数64
//	ADS1256WREG_2(ADS1256_DRATE,ADS1256_DRATE_10SPS);  // 数据10sps
//	ADS1256WREG_2(ADS1256_IO,0x00);               

//	//*************自校准****************
//	while(ADS1256_DRDY_2);
//	CS_2_0();
//	SPI2_ReadWriteByte(ADS1256_CMD_SELFCAL);
//	while(ADS1256_DRDY_2);
//	CS_2_1(); 
//	//**********************************
//}

////读取AD值
//signed int ADS1256ReadData_2(unsigned char channel)  
//{
//  CS_1_1();
//  unsigned int sum=0;
//	while(ADS1256_DRDY_2);//当ADS1256_DRDY为低时才能写寄存器 
//	ADS1256WREG_2(ADS1256_MUX,channel);		//设置通道
//	CS_2_0();
//	SPI2_ReadWriteByte(ADS1256_CMD_SYNC);
//	SPI2_ReadWriteByte(ADS1256_CMD_WAKEUP);
//	SPI2_ReadWriteByte(ADS1256_CMD_RDATA);
//  sum |= (SPI2_ReadWriteByte(0xff) << 16);
//	sum |= (SPI2_ReadWriteByte(0xff) << 8);
//	sum |= SPI2_ReadWriteByte(0xff);
//	CS_2_1();

//	if (sum>0x7FFFFF)          
//	{
//		sum -= 0x1000000;       

//	};
//    return sum;
//}


////**********************************//**********************************//**********************************

////ADS1256 写数据,向ADS1256中地址为regaddr的寄存器写入一个字节databyte
//void ADS1256WREG_1(unsigned char regaddr,unsigned char databyte)
//{
//  CS_2_1();  
//	CS_1_0();
//	while(ADS1256_DRDY_1);//当ADS1256_DRDY为低时才能写寄存器
//	SPI1_ReadWriteByte(ADS1256_CMD_WREG | (regaddr & 0x0F));
//	SPI1_ReadWriteByte(0x00);
//	SPI1_ReadWriteByte(databyte);
//	CS_1_1();
//}

////初始化ADS1256
//void ADS1256_Init_1(void)
//{
//	CS_2_1();
//	//*************自校准****************
//  while(ADS1256_DRDY_1);
//	CS_1_0();
//	SPI1_ReadWriteByte(ADS1256_CMD_SELFCAL);
//	while(ADS1256_DRDY_1);
//	CS_1_1();
//	//**********************************

//	ADS1256WREG_1(ADS1256_STATUS,0x06);               
////	ADS1256WREG(ADS1256_STATUS,0x04);           

////	ADS1256WREG(ADS1256_MUX,0x08);                  
//	ADS1256WREG_1(ADS1256_ADCON,ADS1256_GAIN_1);      // 放大倍数64
//	ADS1256WREG_1(ADS1256_DRATE,ADS1256_DRATE_10SPS);  // 数据10sps
//	ADS1256WREG_1(ADS1256_IO,0x00);               

//	//*************自校准****************
//	while(ADS1256_DRDY_1);
//	CS_1_0();
//	SPI1_ReadWriteByte(ADS1256_CMD_SELFCAL);
//	while(ADS1256_DRDY_1);
//	CS_1_1(); 
//	//**********************************
//}

////读取AD值
//signed int ADS1256ReadData_1(unsigned char channel)  
//{
//  CS_2_1();
//  unsigned int sum=0;
//	while(ADS1256_DRDY_1);//当ADS1256_DRDY为低时才能写寄存器 
//	ADS1256WREG_1(ADS1256_MUX,channel);		//设置通道
//	CS_1_0();
//	SPI1_ReadWriteByte(ADS1256_CMD_SYNC);
//	SPI1_ReadWriteByte(ADS1256_CMD_WAKEUP);
//	SPI1_ReadWriteByte(ADS1256_CMD_RDATA);
//  sum |= (SPI1_ReadWriteByte(0xff) << 16);
//	sum |= (SPI1_ReadWriteByte(0xff) << 8);
//	sum |= SPI1_ReadWriteByte(0xff);
//	CS_1_1();

//	if (sum>0x7FFFFF)          
//	{
//		sum -= 0x1000000;       

//	};
//    return sum;
//}

//ADS1256 写数据,向ADS1256中地址为regaddr的寄存器写入一个字节databyte
void ADS1256WREG_1(unsigned char regaddr,unsigned char databyte)
{
  CS_2_1();
	CS_1_0();
	while(ADS1256_DRDY_1);//当ADS1256_DRDY为低时才能写寄存器
	SPI1_ReadWriteByte(ADS1256_CMD_WREG | (regaddr & 0x0F));
	SPI1_ReadWriteByte(0x00);
	SPI1_ReadWriteByte(databyte);
	CS_1_1();
}

//初始化ADS1256
void ADS1256_Init_1(void)
{
	CS_2_1();
	//*************自校准****************
  while(ADS1256_DRDY_1);
	CS_1_0();
	SPI1_ReadWriteByte(ADS1256_CMD_SELFCAL);
	while(ADS1256_DRDY_1);
	CS_1_1();
	//**********************************

	ADS1256WREG_1(ADS1256_STATUS,0x06);               
//	ADS1256WREG(ADS1256_STATUS,0x04);           

//	ADS1256WREG(ADS1256_MUX,0x08);                  
	ADS1256WREG_1(ADS1256_ADCON,ADS1256_GAIN_1);      // 放大倍数
	ADS1256WREG_1(ADS1256_DRATE,ADS1256_DRATE_10SPS);  // 数据10sps
	ADS1256WREG_1(ADS1256_IO,0x00);               

	//*************自校准****************
	while(ADS1256_DRDY_1);
	CS_1_0();
	SPI1_ReadWriteByte(ADS1256_CMD_SELFCAL);
	while(ADS1256_DRDY_1);
	CS_1_1(); 
	//**********************************
}

//读取AD值
int32_t ADS1256ReadData_1(unsigned char channel)  
{
  CS_2_1();
  unsigned int sum=0;
	while(ADS1256_DRDY_1);//当ADS1256_DRDY为低时才能写寄存器 
	ADS1256WREG_1(ADS1256_MUX,channel);		//设置通道

	CS_1_0();
	SPI1_ReadWriteByte(ADS1256_CMD_SYNC);
	SPI1_ReadWriteByte(ADS1256_CMD_WAKEUP);
	SPI1_ReadWriteByte(ADS1256_CMD_RDATA);
	delay_us(2);
  sum |= (SPI1_ReadWriteByte(0xff) << 16);
	sum |= (SPI1_ReadWriteByte(0xff) << 8);
	sum |= SPI1_ReadWriteByte(0xff);
	delay_us(2);
	CS_1_1();

	if (sum>0x7FFFFF)          
	{
		sum -= 0x1000000;       

	};
    return sum;
}

//ADS1256 写数据,向ADS1256中地址为regaddr的寄存器写入一个字节databyte
void ADS1256WREG_2(unsigned char regaddr,unsigned char databyte)
{
  CS_1_1();  
	CS_2_0();
	while(ADS1256_DRDY_2);//当ADS1256_DRDY为低时才能写寄存器
	SPI2_ReadWriteByte(ADS1256_CMD_WREG | (regaddr & 0x0F));
	SPI2_ReadWriteByte(0x00);
	SPI2_ReadWriteByte(databyte);
	CS_2_1();
}

//初始化ADS1256
void ADS1256_Init_2(void)
{
	CS_1_1();
	//*************自校准****************
  while(ADS1256_DRDY_2);
	CS_2_0();
	SPI2_ReadWriteByte(ADS1256_CMD_SELFCAL);
	while(ADS1256_DRDY_2);
	CS_2_1();
	//**********************************

	ADS1256WREG_2(ADS1256_STATUS,0x06);               
//	ADS1256WREG(ADS1256_STATUS,0x04);           

//	ADS1256WREG(ADS1256_MUX,0x08);                  
	ADS1256WREG_2(ADS1256_ADCON,ADS1256_GAIN_1);      // 放大倍数1
	ADS1256WREG_2(ADS1256_DRATE,ADS1256_DRATE_10SPS);  // 数据10sps
	ADS1256WREG_2(ADS1256_IO,0x00);                    //不使用IO口相关功能

	//*************自校准****************
	while(ADS1256_DRDY_2);
	CS_2_0();
	SPI2_ReadWriteByte(ADS1256_CMD_SELFCAL);
	while(ADS1256_DRDY_2);
	CS_2_1(); 
	//**********************************
}

//读取AD值
int32_t ADS1256ReadData_2(unsigned char channel)  
{
  CS_1_1();
  unsigned int sum=0;
	while(ADS1256_DRDY_2);//当ADS1256_DRDY为低时才能写寄存器 
	ADS1256WREG_2(ADS1256_MUX,channel);		//设置通道
	CS_2_0();
	SPI2_ReadWriteByte(ADS1256_CMD_SYNC);
	SPI2_ReadWriteByte(ADS1256_CMD_WAKEUP);
	SPI2_ReadWriteByte(ADS1256_CMD_RDATA);
	delay_us(2);//指令后的等待时间
  sum |= (SPI2_ReadWriteByte(0xff) << 16);
	sum |= (SPI2_ReadWriteByte(0xff) << 8);
	sum |= SPI2_ReadWriteByte(0xff);
	delay_us(2);//读取后等待DRDY管脚恢复时间
	CS_2_1();

	if (sum>0x7FFFFF)          
	{
		sum -= 0x1000000;       

	};
    return sum;
}


//中位值平均滤波
int32_t filter_1(unsigned char channel)
{
 int count,i,j;
 int32_t Value_buf[N], temp;
 int sum=0;
 for(count=0;count<N;count++)
  Value_buf[count]= ADS1256ReadData_1(channel);
 for(j=0;j<(N-1);j++)
  for(i=0;i<(N-j);i++)
   if(Value_buf[i]>Value_buf[i+1])
   {
     temp = Value_buf[i];
     Value_buf[i]= Value_buf[i+1];
     Value_buf[i+1]=temp;
   }
   for(count =1;count<N-1;count++)
    sum += Value_buf[count];
   return (int32_t)(sum/(N-2));
}


int32_t filter_2(unsigned char channel)
{
 int count,i,j;
 int32_t Value_buf[N], temp;
 int sum=0;
 for(count=0;count<N;count++)
  Value_buf[count]= ADS1256ReadData_2(channel);
 for(j=0;j<(N-1);j++)
  for(i=0;i<(N-j);i++)
   if(Value_buf[i]>Value_buf[i+1])
   {
     temp = Value_buf[i];
     Value_buf[i]= Value_buf[i+1];
     Value_buf[i+1]=temp;
   }
   for(count =1;count<N-1;count++)
    sum += Value_buf[count];
   return (int32_t)(sum/(N-2));
}

