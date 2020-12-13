#ifndef _LCD_H_
#define _LCD_H_
#include "stm32f10x.h"
typedef struct
{
	u16 LCD_REG;
	u16 LCD_RAM;
} LCD_TypeDef;
//ʹ��NOR/SRAM�� Bank1.sector4,��ַλHADDR[27,26]=11 A10��Ϊ�������������� 
//ע������ʱSTM32�ڲ�������һλ����! 111110=0X3E			    
#define LCD_BASE        ((u32)(0x6C000000 | 0x000007FE))
#define TFTLCD             ((LCD_TypeDef *) LCD_BASE)

#define LCD_LED_ON 	GPIO_SetBits(GPIOB,GPIO_Pin_0)
#define LCD_LED_OFF GPIO_ResetBits(GPIOB,GPIO_Pin_0)

extern u8 font_lib[];
extern u8 font_data[];
extern uint8_t zf_32[];
extern uint8_t AscII_32_32_data[][16];
void Init_LCD(void);//��ʼ��LCD����

void Draw_xline(void);
void Wirte_ping_font(void);
void Wirte_32_font(u16 x,u16 y,u16 backclock,u16 fontcolock,u8 * font);
void show_H(u16 x,u16 y,u16 backclock,u16 fontcolock);
void show_16_one_font(u16 x,u16 y,u16 backclock,u16 fontcolock,u8 font[2]);
void Show_font_16(u16 x,u16 y,u16 backclock,u16 fontcolock,u8 * font);
void Show_ASCII_32(uint16_t x, uint16_t y,uint16_t font_color,uint16_t bk_color,uint8_t * font);
void Show_Sting(u16 x,u16 y,u16 backclock,u16 fontcolock,u8 * font);



void My_self_Draw_Piont(u16 x,u16 y,u16 color);
void Draw_Line(u16 x , u16 y,u8 w,u16 color);
void Draw_Pic(u16 x,u16 y,u16 * pic);
#endif


