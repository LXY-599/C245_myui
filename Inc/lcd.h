#ifndef __LCD_H
#define __LCD_H
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
void LCD_Clean(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color_p);
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color);
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color);
void Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color);

HAL_StatusTypeDef LCD_SPI_Transmit(SPI_HandleTypeDef *hspi, uint16_t pData, uint32_t Size);
HAL_StatusTypeDef LCD_SPI_WaitFifoStateUntilTimeout(SPI_HandleTypeDef *hspi, uint32_t Fifo, uint32_t State,
                                                    uint32_t Timeout, uint32_t Tickstart);

// 画笔颜色
#define WHITE 0xFFFF
#define BLACK 0x0000
#define BLUE 0x001F
#define BRED 0XF81F
#define GRED 0XFFE0
#define GBLUE 0X07FF
#define RED 0xF800
#define MAGENTA 0xF81F
#define GREEN 0x07E0
#define CYAN 0x7FFF
#define YELLOW 0xFFE0
#define BROWN 0XBC40    // 棕色
#define BRRED 0XFC07    // 棕红色
#define GRAY 0X8430     // 灰色
#define DARKGRAY 0x0821 // 深灰色
// GUI颜色

#define DARKBLUE 0X01CF  // 深蓝色
#define LIGHTBLUE 0X7D7C // 浅蓝色
#define GRAYBLUE 0X5458  // 灰蓝色
// 以上三色为PANEL的颜色

#define LIGHTGREEN 0X841F // 浅绿色
#define LGRAY 0XC618      // 浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE 0XA651 // 浅灰蓝色(中间层颜色)
#define LBBLUE 0X2B12    // 浅棕蓝色(选择条目的反色)

#endif
