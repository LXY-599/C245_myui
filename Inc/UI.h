#ifndef __UI_H
#define __UI_H

#include "lcd.h"

void UI_Background_olor(uint16_t color);
uint16_t UI_pow(uint8_t m, uint8_t n);
void UI_ShowChar_font24(uint16_t x, uint16_t y, uint8_t num, uint16_t color);
void UI_ShowChar_font68x104(uint16_t x, uint16_t y, uint8_t num, uint16_t color);
void UI_ShowChar_font28x48(uint16_t x, uint16_t y, uint8_t num, uint16_t color);
void UI_ShowChinese_font24(uint16_t x, uint16_t y, uint8_t index, uint16_t color);
void UI_ShowNum_font24(uint16_t x, uint16_t y, uint16_t num, uint8_t len, uint16_t mulriple, uint8_t mode, uint16_t color);
void UI_ShowTemperature(uint16_t x, uint16_t y, uint16_t num, uint16_t color);
void UI_ShowTargetTemperature(uint16_t x, uint16_t y, uint16_t num, uint16_t color);
void UI_ShowSoundFlag(uint16_t x, uint16_t y, uint16_t num, uint16_t color);
void UI_SetBarValue(uint8_t num);
void Main_Page_Init(void);

#endif
