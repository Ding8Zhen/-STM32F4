#include "motor.h"



void motor_init(int n)
{
	//0.clk enable GPIOC
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE);
	//RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	//1.GPIO口的配置
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode		=GPIO_Mode_OUT;
	GPIO_InitStruct.GPIO_OType		=GPIO_OType_PP;
	GPIO_InitStruct.GPIO_Pin		=GPIO_Pin_6|GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9;
	GPIO_InitStruct.GPIO_PuPd		=GPIO_PuPd_NOPULL;
	GPIO_InitStruct.GPIO_Speed		=GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStruct);


}

static void Set_La(uint8_t value)//使用推挽输出的模式
{
	if(value==0)
		GPIO_ResetBits(GPIOC,GPIO_Pin_6);//设置PC6引脚为低电平
	else
		GPIO_SetBits(GPIOC, GPIO_Pin_6);//设置PC6引脚为高电平
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
	Set_La(1);//左电动机正向电压
	Set_Lb(0);
	Set_Ra(1);//右电动机正向电压
	Set_Rb(0);
}

void Go_Right(void)
	{
	Set_La(0);//这里经过之前小车的测试,最终决定还是不反向转动了
	Set_Lb(0);
	Set_Ra(1);//右电动机正向电压
	Set_Rb(0);
}

void Go_Down(void)
{
	Set_La(0);
	Set_Lb(1);//左电动机反向电压
	Set_Ra(0);
	Set_Rb(1);//右电动机反向电压
}

void Go_Left(void)
{
	Set_La(1);//左电动机正向电压
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
//6 左后 7 左前  8右前 9右后
void motor_init(void)
{
	//0.clk enable GPIOF-AHB1 时钟使能
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC ,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	//1.GPIOF8 MODE-AF--TIM13
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;//复用模式
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
	

	GPIO_PinAFConfig(GPIOC,GPIO_PinSource6,GPIO_AF_TIM3);//复用功能对应引脚
	GPIO_PinAFConfig(GPIOC,GPIO_PinSource9,GPIO_AF_TIM3);//复用功能对应引脚
	
	//2.TIM13-TIMEBASE 定时器时基单元
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_Prescaler		=8399;// 84M---10K 指定定时器的预分频
	TIM_TimeBaseInitStruct.TIM_CounterMode		=TIM_CounterMode_Down;//指定计数器模式递减
	TIM_TimeBaseInitStruct.TIM_Period			=500;//指定自动加载的起始值
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseInitStruct);

	//3.TIM13 OUT CH---1 定时器输出通道/输入通道配置
	TIM_OCInitTypeDef  TIM_OCInitStruct;
	TIM_OCInitStruct.TIM_OCMode		=TIM_OCMode_PWM1;//当TIMx_CNT < TIMx_CCRn时，　输出高电平否则，输出低电平
	TIM_OCInitStruct.TIM_OutputState=TIM_OutputState_Enable;//输出信号 状态
	TIM_OCInitStruct.TIM_OCPolarity	=TIM_OCPolarity_High;//指定输出极性：高电平为有效电平
	TIM_OCInitStruct.TIM_Pulse		=0.2*500 ;   	//指定要比较的值TIMx_CCRn
	TIM_OC1Init(TIM3, &TIM_OCInitStruct);
	//使能/禁止预装载 
	TIM_OC1PreloadConfig(TIM3, TIM_OCPreload_Enable);//每次自动加载比较寄存器的值
 
 	//4.TIM13-ENABLE  定时器使能
	TIM_ARRPreloadConfig(TIM3, ENABLE);//使能自动加载 ARR,计数值
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


void Set_la(uint8_t m)  //左前
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


void Set_lb(uint8_t m)  //左后
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
void Set_ra(uint8_t m)		//右前
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

void Set_rb(uint8_t m)		//右后
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

void go_up(void)//前进
{
	Set_la(0);
	Set_ra(0);
	Set_lb(0);
	Set_rb(0);
}

void go_down(void)//后退
{
	Set_la(0);
	Set_ra(1);
	Set_lb(1);
	Set_rb(0);
}
void go_right(void)//右转
{
	Set_la(1);
	Set_lb(0);
	Set_ra(0);//左轮正常移动，右轮0.8倍速倒转
	Set_rb(1);
	Delay_ms(80);
	Set_rb(0);
	Delay_ms(20);
}
void go_left(void)//左转
{
	Set_ra(1);
	Set_rb(0);
	Set_la(0);
	Set_lb(1);
	Delay_ms(80);
	Set_lb(0);
	Delay_ms(20);
	
	
}
void car_stop(void)//暂停
{
	Set_la(0);
	Set_ra(0);
	Set_lb(0);
	Set_rb(0);
}
*/
