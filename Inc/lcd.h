#ifndef __LCD_INIT_H
#define __LCD_INIT_H
#include "main.h"

typedef uint32_t u32;
typedef uint16_t u16;
typedef uint8_t u8;

#define USE_HORIZONTAL 2 // 屏幕方向
#define LCD_W 240
#define LCD_H 240

//-----------------LCD引脚初始化----------------
#define LCD_RES_Clr() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET) // RES
#define LCD_RES_Set() HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET)

#define LCD_DC_Clr() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_RESET) // DC
#define LCD_DC_Set() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_3, GPIO_PIN_SET)

#define LCD_CS_Clr() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_RESET) // CS
#define LCD_CS_Set() HAL_GPIO_WritePin(GPIOD, GPIO_PIN_2, GPIO_PIN_SET)

// #define LCD_BLK_Clr()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_RESET)//BLK
// #define LCD_BLK_Set()  HAL_GPIO_WritePin(GPIOB, GPIO_PIN_3, GPIO_PIN_SET)

void LCD_WR_DATA8(uint8_t dat);                                           // 写一个字节
void LCD_WR_DATA(uint16_t dat);                                           // 写两个字节
void LCD_WR_REG(uint8_t dat);                                             // 写命令
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2); // 设置坐标
void LCD_Init(void);                                                      // LCD初始化

void LCD_Fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t *color_p);
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void LCD_Draw_horizontal_Line(uint16_t x1, uint16_t x2, uint16_t y, uint16_t *color);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);
#endif
