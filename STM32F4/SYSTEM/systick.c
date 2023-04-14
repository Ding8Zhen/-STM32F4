#include "systick.h"

void systick_cfg(uint32_t clk_cnt)
{
	rSysTickCtrl =0;
	rSysTickCtrl |=(1<<0)|(1<<1)|(1<<2);
	rSysTickLoad =clk_cnt;//赋初值 167999，每1/168ns减一，减完就是1ms,然后发生中断
	rSysTickVal =0;
}

static uint32_t systick_num;
void SysTick_Handler(void)//一毫秒中断一次，中断2000次就是2秒
{
	if(systick_num!=0x00)
	{
		systick_num--;
	}
}
void Delay_ms(uint32_t num)
{	

	systick_cfg(167999);//初始化时钟
	systick_num = num;//设置延长多少ms
	while (systick_num!=0x00);
	rSysTickCtrl &=~(1<<0);//时间未到摸鱼

}


