#include "track.h"

void track_init(void)
{
	//����?����1?��
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG|RCC_APB2Periph_EXTIT, ENABLE);
	
	//3?��??��gpio,pb8,pb9
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_IN;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,& GPIO_InitStruct);
	
}

void find_way(void)
{
	uint8_t left=GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_9);//��4������Ϊpb9
	uint8_t right=GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_8);//��1������Ϊpb8
	if(left==WHITE&&right==WHITE)
	{
		Go_Up();
		Delay_ms(100);//ʵ�ֵ��٣�ǰ��0.1s��ֹͣ0.4s
		Stop();
		Delay_ms(400);
	}
	else if(left==BLACK&&right==WHITE)
	{
		Go_Left();
		Delay_ms(100);
		Stop();
		Delay_ms(400);
	}
	else if(left==WHITE&&right==BLACK)
	{
		Go_Right();
		Delay_ms(100);
		Stop();
		Delay_ms(400);
		
	}
	else if(left==BLACK&&right==BLACK)
	{
		Stop();
	}
}
