#include "motor.h"



void motor_init(int n)
{
	//0.clk enable GPIOC
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	//1.GPIO�ڵ�����
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode		=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType		=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin		=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStruct.GPIO_PuPd		=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed		=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);


}

static void Set_La(uint8_t value)//ʹ�����������ģʽ
{
	if(value==0)
		GPIO_ResetBits(GPIOC,GPIO_Pin_6);//����PC6����Ϊ�͵�ƽ
	else
		GPIO_SetBits(GPIOC, GPIO_Pin_6);//����PC6����Ϊ�ߵ�ƽ
}

static void Set_Lb(uint8_t value)
{
	if(value==0)
		GPIO_ResetBits(GPIOC,GPIO_Pin_7);
	else
		GPIO_SetBits(GPIOC, GPIO_Pin_7);
}

static void Set_Ra(uint8_t value)
{
	if(value==0)
		GPIO_ResetBits(GPIOC,GPIO_Pin_8);
	else
		GPIO_SetBits(GPIOC, GPIO_Pin_8);
}

static void Set_Rb(uint8_t value)
{
	if(value==0)
		GPIO_ResetBits(GPIOC,GPIO_Pin_9);
	else
		GPIO_SetBits(GPIOC, GPIO_Pin_9);
}

void Go_Up(void)
{
	Set_La(1);//��綯�������ѹ
	Set_Lb(0);
	Set_Ra(1);//�ҵ綯�������ѹ
	Set_Rb(0);
}

void Go_Right(void)
	{
	Set_La(0);//���ﾭ��֮ǰС���Ĳ���,���վ������ǲ�����ת����
	Set_Lb(0);
	Set_Ra(1);//�ҵ綯�������ѹ
	Set_Rb(0);
}

void Go_Down(void)
{
	Set_La(0);
	Set_Lb(1);//��綯�������ѹ
	Set_Ra(0);
	Set_Rb(1);//�ҵ綯�������ѹ
}

void Go_Left(void)
{
	Set_La(1);//��綯�������ѹ
	Set_Lb(0);
	Set_Ra(0);
	Set_Rb(0);
}

void Stop(void){
	Set_La(0);
	Set_Lb(0);
	Set_Ra(0);
	Set_Rb(0);
}







/*
//6 ��� 7 ��ǰ  8��ǰ 9�Һ�
void motor_init(void)
{
	//0.clk enable GPIOF-AHB1 ʱ��ʹ��
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC ,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	//1.GPIOF8 MODE-AF--TIM13
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;//����ģʽ
	GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_6;
	GPIO_InitStruct.GPIO_PuPd=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_7;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_8;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin=GPIO_Pin_9;
	GPIO_Init(GPIOC, &GPIO_InitStruct);
	

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);//���ù��ܶ�Ӧ����
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM3);//���ù��ܶ�Ӧ����
	
	//2.TIM13-TIMEBASE ��ʱ��ʱ����Ԫ
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_Prescaler		=8399;// 84M---10K ָ����ʱ����Ԥ��Ƶ
	TIM_TimeBaseInitStruct.TIM_CounterMode		=TIM_CounterMode_Down;//ָ��������ģʽ�ݼ�
	TIM_TimeBaseInitStruct.TIM_Period			=500;//ָ���Զ����ص���ʼֵ
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);

	//3.TIM13 OUT CH---1 ��ʱ�����ͨ��/����ͨ������
	TIM_OCInitTypeDef  TIM_OCInitStruct;
	TIM_OCInitStruct.TIM_OCMode		=TIM_OCMode_PWM1;//��TIMx_CNT < TIMx_CCRnʱ��������ߵ�ƽ��������͵�ƽ
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;//����ź� ״̬
	TIM_OCInitStruct.TIM_OCPolarity	=TIM_OCPolarity_High;//ָ��������ԣ��ߵ�ƽΪ��Ч��ƽ
	TIM_OCInitStruct.TIM_Pulse		=0.2*500 ;   	//ָ��Ҫ�Ƚϵ�ֵTIMx_CCRn
	TIM_OC1Init(TIM3, &TIM_OCInitStruct);
	//ʹ��/��ֹԤװ�� 
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);//ÿ���Զ����رȽϼĴ�����ֵ
 
 	//4.TIM13-ENABLE  ��ʱ��ʹ��
	TIM_ARRPreloadConfig(TIM3, ENABLE);//ʹ���Զ����� ARR,����ֵ
	TIM_Cmd(TIM3, ENABLE);
	
	//go_up();

}

void control(uint8_t recv_byte)
{
	if(recv_byte=='1')
		{
			go_up();
		}
		else if(recv_byte=='0')
		{
			go_down();
		}
		else if(recv_byte=='2')
		{
			go_left();
		}
		else if(recv_byte=='3')
		{
			go_right();
		}
		else if(recv_byte=='4')
		{
			car_stop();
		}
}


void Set_la(uint8_t m)  //��ǰ
{
	if(m==1)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_6);
	}
	else if(m==0)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_6);
	}
}


void Set_lb(uint8_t m)  //���
{
	if(m==1)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_7);
	}
	else if(m==0)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_7);
	}
}
void Set_ra(uint8_t m)		//��ǰ
{
	if(m==1)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_8);
	}
	else if(m==0)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_8);
	}
}

void Set_rb(uint8_t m)		//�Һ�
{
	if(m==1)
	{
		GPIO_SetBits(GPIOC, GPIO_Pin_9);
	}
	else if(m==0)
	{
		GPIO_ResetBits(GPIOC, GPIO_Pin_9);
	}
}

void go_up(void)//ǰ��
{
	Set_la(0);
	Set_ra(0);
	Set_lb(0);
	Set_rb(0);
}

void go_down(void)//����
{
	Set_la(0);
	Set_ra(1);
	Set_lb(1);
	Set_rb(0);
}
void go_right(void)//��ת
{
	Set_la(1);
	Set_lb(0);
	Set_ra(0);//���������ƶ�������0.8���ٵ�ת
	Set_rb(1);
	Delay_ms(80);
	Set_rb(0);
	Delay_ms(20);
}
void go_left(void)//��ת
{
	Set_ra(1);
	Set_rb(0);
	Set_la(0);
	Set_lb(1);
	Delay_ms(80);
	Set_lb(0);
	Delay_ms(20);
	
	
}
void car_stop(void)//��ͣ
{
	Set_la(0);
	Set_ra(0);
	Set_lb(0);
	Set_rb(0);
}
*/
