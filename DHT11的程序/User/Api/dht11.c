#include "dht11.h"
#include "delay.h"//延时函数
#include "stdio.h"
#define DATA(x) x?(GPIO_SetBits(GPIOG,GPIO_Pin_11)):(GPIO_ResetBits(GPIOG,GPIO_Pin_11))
#define DATA_STA() (GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_11))
//PG11
void Init_DHT11_GPIO(void)
{
	//1：开时钟
	RCC->APB2ENR |=(0x01<<8);
}
//把IO口配置成推挽输出
void OUT_MODE(void)
{

	GPIOG->CRH &=~(0x0F<<12);
	GPIOG->CRH |=(0x01<<12);

}
//把IO口配置成输入
void IN_MODE(void)
{
	GPIOG->CRH &=~(0x0F<<12);
	GPIOG->CRH |=(0x01<<14);

}
//获得DHT11的数据
u8 dht11_buf[5];
void Get_DHT11_Value(void)
{
	u8 i ,j ;
	//1:起始信号
	OUT_MODE();//输出
	DATA(1);
	DATA(0);
	Delay_ms(20);
	DATA(1);
	//2:响应信号
	IN_MODE();
	while(DATA_STA()==1);//等待拉低
	while(DATA_STA()==0);//等待拉高
	//3：开始接受DHT11的数据
	for(i=0;i<5;i++)
	{
		for(j=0;j<8;j++)
		{
				while(DATA_STA()==1);//等待引脚拉低
				while(DATA_STA()==0);//等待引脚拉高
				Delay_us(35);
				if(DATA_STA() == 1)
				{
					//就是1
					dht11_buf[i]<<=1;
					dht11_buf[i]+=1;
				}else
				{
					//就是0
					dht11_buf[i]<<=1;
				}
		}
	}
	if(dht11_buf[4]==(dht11_buf[0]+dht11_buf[1]+dht11_buf[2]+dht11_buf[3]))
	{
		printf("你的数据没有问题\r\n");
		printf("湿度==%d\r\n",dht11_buf[0]);
		printf("温度==%d\r\n",dht11_buf[2]);
	}else
	{
		printf("你接受的数据出现错误\r\n");
	}

}



