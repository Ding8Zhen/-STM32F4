#include "systick.h"

void systick_cfg(uint32_t clk_cnt)
{
	rSysTickCtrl =0;
	rSysTickCtrl |=(1<<0)|(1<<1)|(1<<2);
	rSysTickLoad =clk_cnt;//����ֵ 167999��ÿ1/168ns��һ���������1ms,Ȼ�����ж�
	rSysTickVal =0;
}

static uint32_t systick_num;
void SysTick_Handler(void)//һ�����ж�һ�Σ��ж�2000�ξ���2��
{
	if(systick_num!=0x00)
	{
		systick_num--;
	}
}
void Delay_ms(uint32_t num)
{	

	systick_cfg(167999);//��ʼ��ʱ��
	systick_num = num;//�����ӳ�����ms
	while (systick_num!=0x00);
	rSysTickCtrl &=~(1<<0);//ʱ��δ������

}


