#include "dht11.h"
#include "delay.h"//��ʱ����
#include "stdio.h"
#define DATA(x) x?(GPIO_SetBits(GPIOG,GPIO_Pin_11)):(GPIO_ResetBits(GPIOG,GPIO_Pin_11))
#define DATA_STA() (GPIO_ReadInputDataBit(GPIOG,GPIO_Pin_11))
//PG11
void Init_DHT11_GPIO(void)
{
	//1����ʱ��
	RCC->APB2ENR |=(0x01<<8);
}
//��IO�����ó��������
void OUT_MODE(void)
{

	GPIOG->CRH &=~(0x0F<<12);
	GPIOG->CRH |=(0x01<<12);

}
//��IO�����ó�����
void IN_MODE(void)
{
	GPIOG->CRH &=~(0x0F<<12);
	GPIOG->CRH |=(0x01<<14);

}
//���DHT11������
u8 dht11_buf[5];
void Get_DHT11_Value(void)
{
	u8 i ,j ;
	//1:��ʼ�ź�
	OUT_MODE();//���
	DATA(1);
	DATA(0);
	Delay_ms(20);
	DATA(1);
	//2:��Ӧ�ź�
	IN_MODE();
	while(DATA_STA()==1);//�ȴ�����
	while(DATA_STA()==0);//�ȴ�����
	//3����ʼ����DHT11������
	for(i=0;i<5;i++)
	{
		for(j=0;j<8;j++)
		{
				while(DATA_STA()==1);//�ȴ���������
				while(DATA_STA()==0);//�ȴ���������
				Delay_us(35);
				if(DATA_STA() == 1)
				{
					//����1
					dht11_buf[i]<<=1;
					dht11_buf[i]+=1;
				}else
				{
					//����0
					dht11_buf[i]<<=1;
				}
		}
	}
	if(dht11_buf[4]==(dht11_buf[0]+dht11_buf[1]+dht11_buf[2]+dht11_buf[3]))
	{
		printf("�������û������\r\n");
		printf("ʪ��==%d\r\n",dht11_buf[0]);
		printf("�¶�==%d\r\n",dht11_buf[2]);
	}else
	{
		printf("����ܵ����ݳ��ִ���\r\n");
	}

}



