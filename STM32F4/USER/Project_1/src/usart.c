#include "usart.h"

void usart_init(void)
{
	//1. GPIO口的配置
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

		GPIO_InitTypeDef GPIO_InitStruct;
		GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_9 | GPIO_Pin_10;
		GPIO_InitStruct.GPIO_PuPd = GPIO_PuPd_NOPULL;
		GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA,  &GPIO_InitStruct);//初始化USART1
		GPIO_InitStruct.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;//USART3对应引脚
		GPIO_Init(GPIOB,  &GPIO_InitStruct);//初始化USART3

		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);
	
	//2.初始化usart结构体

		USART_InitTypeDef USART_InitStruct;
		USART_InitStruct.USART_BaudRate = 115200;
		USART_InitStruct.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStruct.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
		USART_InitStruct.USART_Parity = USART_Parity_No;
		USART_InitStruct.USART_StopBits = USART_StopBits_1;
		USART_InitStruct.USART_WordLength = USART_WordLength_8b;
		USART_Init(USART1, &USART_InitStruct);
		USART_InitStruct.USART_BaudRate = 9600;
		USART_Init(USART3, &USART_InitStruct);
		
	//3.配置串口中断
		USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
		USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);

	//4.配置NVIC
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	
		NVIC_InitTypeDef n;
		n.NVIC_IRQChannel = USART1_IRQn; ////串口1中断通道
		n.NVIC_IRQChannelCmd = ENABLE;
		n.NVIC_IRQChannelPreemptionPriority = 2;//抢占优先级2
		n.NVIC_IRQChannelSubPriority = 2;//子优先级2
		NVIC_Init(&n);
		n.NVIC_IRQChannel = USART3_IRQn; // PPP_IRQn
		NVIC_Init(&n);
	//5.使能串口1和3
		USART_Cmd(USART1, ENABLE);
		USART_Cmd(USART3, ENABLE);
}

uint8_t recv_byte=0;

void USART1_IRQHandler(void)//串口1中断服务程序
		{
			//USART_GetITStatus 用来获取串口中断状态			
			if (USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
			{
				//RXNE事件产生，接收数据的寄存器非空
				
				//读取接收到的数据
				recv_byte = USART_ReceiveData(USART1);
				
				//清除中断标志,之后可以重新接收
				USART_ClearITPendingBit(USART1, USART_IT_RXNE  );
				
			}
}

void USART3_IRQHandler(void)
		{			
			if (USART_GetITStatus(USART3, USART_IT_RXNE) == SET)
			{
				recv_byte = USART_ReceiveData(USART3);
				USART_ClearITPendingBit(USART3, USART_IT_RXNE );
				
			}
}
int fputc(int c, FILE *stream)
{
	USART3->SR;	
	USART_SendData(USART3, c & 0xff);
	while( USART_GetFlagStatus(USART3, USART_FLAG_TC) == RESET){};	
  return(c);
}
