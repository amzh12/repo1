
#include "delay.h"

u32 sys_time =0;//记录系统时间
u16 rgb_run[2]={0,500};
//系统滴答产生的精准延时
void Delay_ms(u32 time)
{
	sys_time=0;
	while(time>sys_time);
}
//中断服务函数  1ms进入一次
void SysTick_Handler(void)
{
	sys_time++;
	rgb_run[0]++;
}
// 1us的延时
void Delay_1us(void)
{
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();__nop();
	__nop();__nop();
	
}

void Delay_us(uint32_t time)
{
	while(time--)
	{
			Delay_1us();
	}
}
