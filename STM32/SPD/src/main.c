#include"stm32f10x.h"
#include"stdlib.h"
#include"stm32f10x_exti.h"
void delay(int d);
void UsendC(char d);
void EXTI15_10_IRQ_Handler(void);
void Run_Relay(int Flag);
float Read_Pressure();
void Print_Lcd(float D,int F);
int Flag=0;

int main(void)
{
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOC|RCC_APB2Periph_AFIO,ENABLE);

	GPIO_InitTypeDef GPIOI;
	GPIOI.GPIO_Pin=GPIO_Pin_2;
	GPIOI.GPIO_Speed=GPIO_Speed_50MHz;
	GPIOI.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA,&GPIOI);
	GPIOI.GPIO_Pin=GPIO_Pin_3;
	GPIOI.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA,&GPIOI);
	GPIOI.GPIO_Pin=GPIO_Pin_11;
	GPIOI.GPIO_Mode=GPIO_Mode_IPD;
	GPIO_Init(GPIOC,&GPIOI);


	USART_InitTypeDef UARTI;
	UARTI.USART_BaudRate=9600;
	UARTI.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	UARTI.USART_Parity=USART_Parity_No;
	UARTI.USART_StopBits=USART_StopBits_1;
	UARTI.USART_WordLength=USART_WordLength_8b;
	UARTI.USART_Mode=USART_Mode_Rx|USART_Mode_Tx;
	USART_Init(USART2,&UARTI);

	USART_ClockInitTypeDef UCLK;
	UCLK.USART_CPHA=USART_CPHA_2Edge;
	UCLK.USART_CPOL=USART_CPOL_Low;
	UCLK.USART_Clock=USART_Clock_Disable;
	UCLK.USART_LastBit=USART_LastBit_Disable;
	USART_ClockInit(USART2,&UCLK);
	USART_Cmd(USART2,ENABLE);

	EXTI_InitTypeDef EXTD;
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOC,GPIO_PinSource11);
	EXTD.EXTI_Line=EXTI_Line11;
	EXTD.EXTI_Mode=EXTI_Mode_Interrupt;
	EXTD.EXTI_Trigger=EXTI_Trigger_Rising;
	EXTD.EXTI_LineCmd=ENABLE;
	EXTI_Init(&EXTD);

	NVIC_InitTypeDef NVICI;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	NVICI.NVIC_IRQChannel=EXTI15_10_IRQn;
	NVICI.NVIC_IRQChannelPreemptionPriority=1;
	NVICI.NVIC_IRQChannelSubPriority=1;
	NVICI.NVIC_IRQChannelCmd=ENABLE;
	NVIC_Init(&NVICI);




	float PV;
  while (1)
  {
	  PV=Read_Pressure();

	  if(PV<=6)
	  {
		 Flag=0;
		 Run_Relay(Flag);
	  }
	  Print_Lcd(PV,Flag);

	  delay(1000);
  }
}
void delay(int d)
{

	for(int i=0;i<=6600*d;++i);
}
void UsendC(char d)
{
	USART_SendData(USART2,d);
	while(USART_GetFlagStatus(USART2,USART_FLAG_TXE)==RESET);

}

void EXTI15_10_IRQHandler(void)
{
	if(Flag==1)
	{
		Flag=0;
	}
	else if(Flag==0)
	{
		Flag=1;
	}
	Run_Relay(Flag);
	EXTI_ClearITPendingBit(EXTI_Line11);

}
void Run_Relay(int Flag)
{
	if(Flag==1)
		{
			UsendC('O');
		}
		else if(Flag==0)
		{
			UsendC('C');
		}


}
float Read_Pressure()
{
	float NUM;

	NUM=rand()%10;

	return NUM;
}

void Print_Lcd(float D,int F)
{

	UsendC(D+48); UsendC(F+68);

}
