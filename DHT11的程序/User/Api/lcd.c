#include "lcd.h"
#include "delay.h"
#include "stdio.h"

void LCD_WR_REG(volatile uint16_t regval)
{
  regval=regval;		//ʹ��-O2�Ż���ʱ��,����������ʱ
  TFTLCD->LCD_REG=regval;//д��Ҫд�ļĴ������
}
//дLCD����
//data:Ҫд���ֵ
void LCD_WR_DATA(volatile uint16_t data)
{
  data=data;			//ʹ��-O2�Ż���ʱ��,����������ʱ
  TFTLCD->LCD_RAM=data;
}
//��LCD����
//����ֵ:������ֵ
uint16_t LCD_RD_DATA(void)
{
  volatile uint16_t ram;			//��ֹ���Ż�
  ram=TFTLCD->LCD_RAM;
  return ram;
}
//д�Ĵ���
//LCD_Reg:�Ĵ�����ַ
//LCD_RegValue:Ҫд�������
void LCD_WriteReg(uint16_t LCD_Reg,uint16_t LCD_RegValue)
{
  TFTLCD->LCD_REG = LCD_Reg;		//д��Ҫд�ļĴ������
  TFTLCD->LCD_RAM = LCD_RegValue;//д������
}
//���Ĵ���
//LCD_Reg:�Ĵ�����ַ
//����ֵ:����������
uint16_t LCD_ReadReg(uint16_t LCD_Reg)
{
  LCD_WR_REG(LCD_Reg);		//д��Ҫ���ļĴ������
  Delay_us(5);
  return LCD_RD_DATA();		//���ض�����ֵ
}

//LCDдGRAM
//RGB_Code:��ɫֵ
void LCD_WriteRAM(uint16_t RGB_Code)
{
  TFTLCD->LCD_RAM = RGB_Code;//дʮ��λGRAM
}



void Init_LCD(void)
{
	u32 i=0;
	//1����ʱ��
	//2������LCD����IO�ڣ��������죩
	FSMC_NORSRAMInitTypeDef FSMC_NORSRAMInitStruct;
	FSMC_NORSRAMTimingInitTypeDef FSMC_NORSRAMTimingInitWirte;
	FSMC_NORSRAMTimingInitTypeDef FSMC_NORSRAMTimingInitRead;
	
	GPIO_InitTypeDef GPIO_InitStructure;
	

	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_FSMC,ENABLE);	//ʹ��FSMCʱ��
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOD|RCC_APB2Periph_GPIOE|RCC_APB2Periph_GPIOG|RCC_APB2Periph_AFIO,ENABLE);//ʹ��PORTB,D,E,G�Լ�AFIO���ù���ʱ��

 	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;				 //PB0 ������� ����
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOB, &GPIO_InitStructure);

 	//PORTD�����������  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_14|GPIO_Pin_15;				 //	//PORTD�����������  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOD, &GPIO_InitStructure); 
	  
	//PORTE�����������  
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;				 //	//PORTD�����������  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOE, &GPIO_InitStructure); 
	  
   	//	//PORTG12����������� A10	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_12;	 //	//PORTD�����������  
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 		 //�����������   
 	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 	GPIO_Init(GPIOG, &GPIO_InitStructure);


	FSMC_NORSRAMTimingInitRead.FSMC_AddressSetupTime = 0x01;	 //��ַ����ʱ�䣨ADDSET��Ϊ2��HCLK 1/36M=27ns
	FSMC_NORSRAMTimingInitRead.FSMC_AddressHoldTime = 0x00;	 //��ַ����ʱ�䣨ADDHLD��ģʽAδ�õ�	
	FSMC_NORSRAMTimingInitRead.FSMC_DataSetupTime = 0x0f;		 // ���ݱ���ʱ��Ϊ16��HCLK,��ΪҺ������IC�Ķ����ݵ�ʱ���ٶȲ���̫�죬�����1289���IC��
	FSMC_NORSRAMTimingInitRead.FSMC_BusTurnAroundDuration = 0x00;
	FSMC_NORSRAMTimingInitRead.FSMC_CLKDivision = 0x00;
	FSMC_NORSRAMTimingInitRead.FSMC_DataLatency = 0x00;
	FSMC_NORSRAMTimingInitRead.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 
    

	FSMC_NORSRAMTimingInitWirte.FSMC_AddressSetupTime = 0x00;	 //��ַ����ʱ�䣨ADDSET��Ϊ1��HCLK  
	FSMC_NORSRAMTimingInitWirte.FSMC_AddressHoldTime = 0x00;	 //��ַ����ʱ�䣨A		
	FSMC_NORSRAMTimingInitWirte.FSMC_DataSetupTime = 0x03;		 ////���ݱ���ʱ��Ϊ4��HCLK	
	FSMC_NORSRAMTimingInitWirte.FSMC_BusTurnAroundDuration = 0x00;
	FSMC_NORSRAMTimingInitWirte.FSMC_CLKDivision = 0x00;
	FSMC_NORSRAMTimingInitWirte.FSMC_DataLatency = 0x00;
	FSMC_NORSRAMTimingInitWirte.FSMC_AccessMode = FSMC_AccessMode_A;	 //ģʽA 
/*
	FSMC_NORSRAMInitStruct.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable;
	FSMC_NORSRAMInitStruct.FSMC_Bank=FSMC_Bank1_NORSRAM4;
	FSMC_NORSRAMInitStruct.FSMC_BurstAccessMode=FSMC_BurstAccessMode_Disable;
	FSMC_NORSRAMInitStruct.FSMC_DataAddressMux=FSMC_DataAddressMux_Disable;
	FSMC_NORSRAMInitStruct.FSMC_ExtendedMode=FSMC_ExtendedMode_Enable;
	FSMC_NORSRAMInitStruct.FSMC_MemoryDataWidth=FSMC_MemoryDataWidth_16b;
	FSMC_NORSRAMInitStruct.FSMC_MemoryType=FSMC_MemoryType_SRAM;
	FSMC_NORSRAMInitStruct.FSMC_WriteOperation =FSMC_WriteOperation_Enable;
*/	
	FSMC_NORSRAMInitStruct.FSMC_Bank = FSMC_Bank1_NORSRAM4;//  ��������ʹ��NE4 ��Ҳ�Ͷ�ӦBTCR[6],[7]��
	FSMC_NORSRAMInitStruct.FSMC_DataAddressMux = FSMC_DataAddressMux_Disable; // ���������ݵ�ַ
	FSMC_NORSRAMInitStruct.FSMC_MemoryType =FSMC_MemoryType_SRAM;// FSMC_MemoryType_SRAM;  //SRAM   
	FSMC_NORSRAMInitStruct.FSMC_MemoryDataWidth = FSMC_MemoryDataWidth_16b;//�洢�����ݿ��Ϊ16bit   
	FSMC_NORSRAMInitStruct.FSMC_BurstAccessMode =FSMC_BurstAccessMode_Disable;// FSMC_BurstAccessMode_Disable; 
	FSMC_NORSRAMInitStruct.FSMC_WaitSignalPolarity = FSMC_WaitSignalPolarity_Low;
	FSMC_NORSRAMInitStruct.FSMC_AsynchronousWait=FSMC_AsynchronousWait_Disable; 
	FSMC_NORSRAMInitStruct.FSMC_WrapMode = FSMC_WrapMode_Disable;   
	FSMC_NORSRAMInitStruct.FSMC_WaitSignalActive = FSMC_WaitSignalActive_BeforeWaitState;  
	FSMC_NORSRAMInitStruct.FSMC_WriteOperation = FSMC_WriteOperation_Enable;	//  �洢��дʹ��
	FSMC_NORSRAMInitStruct.FSMC_WaitSignal = FSMC_WaitSignal_Disable;   
	FSMC_NORSRAMInitStruct.FSMC_ExtendedMode = FSMC_ExtendedMode_Enable; // ��дʹ�ò�ͬ��ʱ��
	FSMC_NORSRAMInitStruct.FSMC_WriteBurst = FSMC_WriteBurst_Disable; 
	
	
	FSMC_NORSRAMInitStruct.FSMC_ReadWriteTimingStruct=&FSMC_NORSRAMTimingInitRead;
	FSMC_NORSRAMInitStruct.FSMC_WriteTimingStruct=&FSMC_NORSRAMTimingInitWirte;
	FSMC_NORSRAMInit(&FSMC_NORSRAMInitStruct);
	FSMC_NORSRAMCmd(FSMC_Bank1_NORSRAM4,ENABLE);
	Delay_ms(100);
	LCD_WR_REG(0xCF);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0xC1);
    LCD_WR_DATA(0X30);
    LCD_WR_REG(0xED);
    LCD_WR_DATA(0x64);
    LCD_WR_DATA(0x03);
    LCD_WR_DATA(0X12);
    LCD_WR_DATA(0X81);
    LCD_WR_REG(0xE8);
    LCD_WR_DATA(0x85);
    LCD_WR_DATA(0x10);
    LCD_WR_DATA(0x7A);
    LCD_WR_REG(0xCB);
    LCD_WR_DATA(0x39);
    LCD_WR_DATA(0x2C);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x34);
    LCD_WR_DATA(0x02);
    LCD_WR_REG(0xF7);
    LCD_WR_DATA(0x20);
    LCD_WR_REG(0xEA);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_REG(0xC0);    //Power control
    LCD_WR_DATA(0x1B);   //VRH[5:0]
    LCD_WR_REG(0xC1);    //Power control
    LCD_WR_DATA(0x01);   //SAP[2:0];BT[3:0]
    LCD_WR_REG(0xC5);    //VCM control
    LCD_WR_DATA(0x30); 	 //3F
    LCD_WR_DATA(0x30); 	 //3C
    LCD_WR_REG(0xC7);    //VCM control2
    LCD_WR_DATA(0XB7);
    LCD_WR_REG(0x36);    // Memory Access Control
    LCD_WR_DATA(0x48);
    LCD_WR_REG(0x3A);
    LCD_WR_DATA(0x55);
    LCD_WR_REG(0xB1);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x1A);
    LCD_WR_REG(0xB6);    // Display Function Control
    LCD_WR_DATA(0x0A);
    LCD_WR_DATA(0xA2);
    LCD_WR_REG(0xF2);    // 3Gamma Function Disable
    LCD_WR_DATA(0x00);
    LCD_WR_REG(0x26);    //Gamma curve selected
    LCD_WR_DATA(0x01);
    LCD_WR_REG(0xE0);    //Set Gamma
    LCD_WR_DATA(0x0F);
    LCD_WR_DATA(0x2A);
    LCD_WR_DATA(0x28);
    LCD_WR_DATA(0x08);
    LCD_WR_DATA(0x0E);
    LCD_WR_DATA(0x08);
    LCD_WR_DATA(0x54);
    LCD_WR_DATA(0XA9);
    LCD_WR_DATA(0x43);
    LCD_WR_DATA(0x0A);
    LCD_WR_DATA(0x0F);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_REG(0XE1);    //Set Gamma
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x15);
    LCD_WR_DATA(0x17);
    LCD_WR_DATA(0x07);
    LCD_WR_DATA(0x11);
    LCD_WR_DATA(0x06);
    LCD_WR_DATA(0x2B);
    LCD_WR_DATA(0x56);
    LCD_WR_DATA(0x3C);
    LCD_WR_DATA(0x05);
    LCD_WR_DATA(0x10);
    LCD_WR_DATA(0x0F);
    LCD_WR_DATA(0x3F);
    LCD_WR_DATA(0x3F);
    LCD_WR_DATA(0x0F);
    LCD_WR_REG(0x2B);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x01);
    LCD_WR_DATA(0x3f);
    LCD_WR_REG(0x2A);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0x00);
    LCD_WR_DATA(0xef);
    LCD_WR_REG(0x11); //Exit Sleep
    Delay_ms(120);
    LCD_WR_REG(0x29); //display on
	
	
	LCD_WR_REG(0x36);
	LCD_WR_DATA(0x08);//II9341��������
	
	//����LCD�ͳ�ʼ�����
	//lCD�и������
	LCD_LED_ON;//��LCD��Ļ�����
	//REG :д����
	//DATA:д����
	LCD_WR_REG(0x2A);
	LCD_WR_DATA(0);
	LCD_WR_DATA(0);  //
	LCD_WR_DATA(0);
	LCD_WR_DATA((240-1));
//X���Ǵ� 0��ʼ   ��240����
	LCD_WR_REG(0x2B);
	LCD_WR_DATA(0);
	LCD_WR_DATA(0);
	LCD_WR_DATA((320-1)>>8);
	LCD_WR_DATA((320-1)&0xFF);
//y�����ʼ 0
//y��Ľ��� 320
	LCD_WR_REG(0x2C);
	for(i=0;i<240*320;i++)
	{
		LCD_WR_DATA(0x1F);//��ɫ
		
	}
		
}



void My_self_Draw_Piont(u16 x,u16 y,u16 color)
{
	
	LCD_WR_REG(0x2A);
	LCD_WR_DATA(x>>8);
	LCD_WR_DATA(x&0xFF);
	
	LCD_WR_REG(0x2B);
	LCD_WR_DATA(y>>8);
	LCD_WR_DATA(y&0xFF);
	
	LCD_WR_REG(0x2C);
	LCD_WriteRAM(color);
}


void Draw_Line(u16 x , u16 y,u8 w,u16 color)
{
	u16 i =0;
	LCD_WR_REG(0x2A);
	LCD_WR_DATA(x>>8);
	LCD_WR_DATA(x&0xFF);
	
	LCD_WR_REG(0x2B);
	LCD_WR_DATA(y>>8);
	LCD_WR_DATA(y&0xFF);
	
	LCD_WR_REG(0x2C);
	for(i=0;i<240*w;i++)
	{
		LCD_WriteRAM(color);
	}
	
}

void Draw_point(u16 x,u16 y,u16 color)
{
	LCD_WR_REG(0x2A);
	LCD_WR_DATA(x>>8);//320�߰�λ
	LCD_WR_DATA(x&0xFF); //320�ĵͰ�λ
	
	LCD_WR_REG(0x2B);
	LCD_WR_DATA(y>>8);
	LCD_WR_DATA(y&0xFF); 
	LCD_WR_REG(0x2C);
	LCD_WR_DATA(color);
}


void Draw_Pic(u16 x,u16 y,u16 * pic)
{
	u32 i = 0;
	LCD_WR_REG(0x2A);
	LCD_WR_DATA(0);
	LCD_WR_DATA(0); 
	LCD_WR_DATA((x-1)>>8);
	LCD_WR_DATA((x-1)&0xFF); 
	
	LCD_WR_REG(0x2B);
	LCD_WR_DATA(0);
	LCD_WR_DATA(0); 
	LCD_WR_DATA((y-1)>>8);
	LCD_WR_DATA((y-1)&0xFF); 
	LCD_WR_REG(0x2C);
	
	for(i=0;i<x*y;i++)
	{
		LCD_WriteRAM(* pic);
		pic ++;
	}
	
}

void Draw_xline(void)
{
	u16 i=0;
	for(i=0;i<240;i++)
	{
		Draw_point(i,160,0xF800);
	}
	for(i=0;i<240;i++)
	{
		Draw_point(i,161,0xF800);
	}
	for(i=0;i<240;i++)
	{
		Draw_point(i,162,0xF800);
	}for(i=0;i<240;i++)
	{
		Draw_point(i,163,0xF800);
	}
}

char font_ping[]=
{
	0x00,0x00,0x7F,0xFC,0x01,0x00,0x01,0x00,0x11,0x10,0x09,0x10,0x09,0x20,0x01,0x00,
	0xFF,0xFE,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x01,0x00,/*"ƽ",0*/
};
//д�ֺ���
//16*16����ռ�����ֽ�
//16*16/8=32
void Wirte_ping_font(void)
{
	u8 i,j;
	u16 x0=0,y0=0;
	for(i=0;i<32;i++)
	{
		 for(j=0;j<8;j++)
		{
			
			if((font_ping[i]<<j)&0x80)
			{
				Draw_point(x0,y0,0xF800);
			}else
			{
				Draw_point(x0,y0,0x0000);
			}
			x0++;
		}
		if(i%2==1)
		{
			x0=0;
			y0++;
		}
	}
}
//��ʾ32*32�ĺ���
u8 font_32[128]={0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x80,0x00,0x00,0x01,0xE0,0x00,0x00,0x01,0xC0,0x00,0x30,0x01,0xC1,0xFF,0xF8,0x01,0xC0,0x00,0x78,0x01,0x80,0x00,0xE0,
0x03,0x8C,0x00,0xC0,0x3F,0xFE,0x01,0x80,0x03,0x8C,0x07,0x00,0x03,0x8C,0x07,0x00,0x03,0x1C,0x07,0x00,0x07,0x1C,0x07,0x00,0x07,0x1C,0x07,0x00,0x06,0x1C,0x07,0x1C,
0x06,0x1F,0xFF,0xFE,0x0E,0x38,0x07,0x00,0x0E,0x38,0x07,0x00,0x0C,0x38,0x07,0x00,0x0C,0x70,0x07,0x00,0x0F,0x70,0x07,0x00,0x01,0xE0,0x07,0x00,0x00,0xF8,0x07,0x00,
0x00,0xFE,0x07,0x00,0x01,0xCE,0x07,0x00,0x03,0x86,0x07,0x00,0x06,0x00,0x07,0x00,0x0C,0x00,0xFE,0x00,0x38,0x00,0x1E,0x00,0x00,0x00,0x0C,0x00,0x00,0x00,0x00,0x00,/*"��",0*/
/* (32 X 32 , ����, �Ӵ� )*/

}; 
// ���庯����һ��
// u8 * font ��������ĳ�ֱ�Ӵ��ֵ���ʽ��ʾ����
void Wirte_32_font(u16 x,u16 y,u16 backclock,u16 fontcolock,u8 * font)
{
	u8 i,j;
	u16 x0=x,y0=y;
	for(i=0;i<128;i++)
	{
		 for(j=0;j<8;j++)
		{
			
			if((font[i]<<j)&0x80)
			{
				Draw_point(x0,y0,fontcolock);
			}else
			{
				Draw_point(x0,y0,backclock);
			}
			x0++;
		}
		if(i%4==3)
		{
			x0=x;
			y0++;
		}
	}
}


u8 H_Font[]={
0x00,0x00,0x00,0xE7,0x42,0x42,0x42,0x42,0x7E,0x42,0x42,0x42,0x42,0xE7,0x00,0x00,/*"H",0*/
/* (8 X 16 , ���� )*/
};
void show_H(u16 x,u16 y,u16 backclock,u16 fontcolock)
{
	u8 i,j;
	u16 x0=x,y0=y;
//16*16 ����  16*16/8
//16*8  ASCII 16*8/8
	for(i=0;i<16;i++)
	{
		 for(j=0;j<8;j++)
		{
			
			if((H_Font[i]<<j)&0x80)
			{
				Draw_point(x0,y0,fontcolock);
			}else
			{
				Draw_point(x0,y0,backclock);
			}
			x0++;
		}
		x0=x;
		y0++;
	}
}



u8 * find_font(u8 font[2])
{
	u16 i=0;
	//u16 j=0;
	while(1)
	{
		if(font[0]==font_lib[i]&&font[1]==font_lib[i+1])
		{	
			return &(font_data[i*16]);
		}else
		{
			i+=2;
		}
	}
}
void show_16_one_font(u16 x,u16 y,u16 backclock,u16 fontcolock,u8 font[2])
{
	u8 i,j;
	u16 x0=x,y0=y;
	u8 * p=NULL;
	p=find_font(font);
//	for(i=0;i<32;i++)
//	{
//		printf("%x\r\n",p[i]);
//	}
	for(i=0;i<32;i++)
	{
		 for(j=0;j<8;j++)
		{
			
			if((p[i]<<j)&0x80)
			{
				Draw_point(x0,y0,fontcolock);
			}else
			{
				//Draw_point(x0,y0,backclock);
			}
			x0++;
		}
		if(i%2==1)
		{
			x0=x;
			y0++;
		}
	}
}



void Show_font_16(u16 x,u16 y,u16 backclock,u16 fontcolock,u8 * font)
{
	u16 x0,y0;
	x0=x;y0=y;
	u8 * font_tmp=font;
	while((*font_tmp)!='\0')
	{
		show_16_one_font(x0,y0,backclock,fontcolock,font_tmp);
		x0+=16;
		if(x0>=239)
		{
			y0+=16;
			x0=0;
		}
		font_tmp++;
		if((*font_tmp)==0)
		{
			return ;
		}
		font_tmp++;
	}
}


uint8_t Font_ZfFind(char ch)
{
	//uint32_t lenth = sizeof((uint8_t *)zf_32)-1;//����ַ����ĳ���
	uint32_t i = 0;//
	for(i=0;i<255;i++)
	{
		if(zf_32[i] == ch)
		return i;
	}
	return 0xff;
}

void Show_One_ASIIC(uint16_t x, uint16_t y,uint16_t font_color,uint16_t bk_color,uint8_t asc)
{
	uint8_t i,j;
	uint8_t x1=0,y1=0;//���ĸ�λ�ÿ�ʼ���
	x1 = x , y1=y;
	uint8_t offset=0;
	offset=Font_ZfFind(asc);//���������ַ������ֿ��λ��
//	printf("offset=====%d\r\n",offset);
	//offset+=2;
	for(i=0;i<16;i++)
	{
		for(j=0;j<8;j++)   
		{
			if((AscII_32_32_data[offset][i]<<j) & 0x80)//��������ж�����ֽڵ����λ�Ƿ�Ϊ1
			{
				Draw_point(x1,y1,font_color);//�����λ�ô���һ����ɫ��
			}else
			{
				//Draw_point(x1,y1,bk_color);//�����λ�ô���һ����ɫ��
			}
			x1++;
		}
		
		x1=x;
		y1+=1;
	}
}


void Show_ASCII_32(uint16_t x, uint16_t y,uint16_t font_color,uint16_t bk_color,uint8_t * font)
{
	while(* font!=0)
	{
		Show_One_ASIIC(x,y,bk_color,font_color,* font);
		x+=8;
		font+=1;
		if(x>=240)
		{
			x=0;
			y+=16;//
		}
	}
}
//ֱ������
void Show_Sting(u16 x,u16 y,u16 backclock,u16 fontcolock,u8 * font)
{
	while(* font!=0)
	{
		if(* font>=0xa1) //�����һ���ֽڴ���0xA0
		{
			show_16_one_font(x,y,backclock,fontcolock,font);
			x+=16;
			font+=2;//����ռ�����ֽ�
			if(x>=240)
			{
				x=0;
				y+=16;//
			}//����
		}else // �϶���ASCII
		{
			Show_One_ASIIC(x,y,fontcolock,backclock,* font);
			x+=8;
			font+=1; //ASCIIռһ���ֽ�
			if(x>=240)
			{
				x=0;
				y+=16;//
			}
		}
	}
}

