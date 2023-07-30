#include "UI.h"
#include "font.h"
#include "usart.h"

static uint16_t UI_bgcolor = BLACK;

/******************************************************************************
      函数说明：背景颜色修改
      入口数据： color           要填充的颜色
      返回值：  无
******************************************************************************/
void UI_Background_olor(uint16_t color)
{
    UI_bgcolor = color;
}

/******************************************************************************
      函数说明：显示数字
      入口数据：m底数，n指数
      返回值：  无
******************************************************************************/
uint16_t UI_pow(uint8_t m, uint8_t n)
{
    uint16_t result = 1;
    while (n--)
        result *= m;
    return result;
}

/******************************************************************************
      函数说明：字符显示
      入口数据： x,y             起始坐标
                color           要填充的颜色
                num             显示的字符
      返回值：  无
******************************************************************************/
void UI_ShowChar_font24(uint16_t x, uint16_t y, uint8_t num, uint16_t color)
{
    uint16_t char_buff[288] = {0};
    uint8_t i, j, k;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 12; j++)
        {
            for (k = 0; k < 8; k++)
            {
                char_buff[i * 96 + j + k * 12] =
                    (char_font24[num * 36 + i + j * 3] & (0x01 << k)) ? color : UI_bgcolor;
            }
        }
    }
#if 0
    if (y + 23 >= 240)
        LCD_Fill(x, y, x + 11, 239, char_buff); // 设置坐标
    else
#endif
    LCD_Fill(x, y, x + 11, y + 23, char_buff); // 设置坐标
}

/******************************************************************************
      函数说明：字符显示
      入口数据： x,y             起始坐标
                color           要填充的颜色
                num             显示的字符
      返回值：  无
******************************************************************************/
void UI_ShowChar_font68x104(uint16_t x, uint16_t y, uint8_t num, uint16_t color)
{
    uint16_t char_buff[68 * 8] = {0};
    uint8_t i, j, k;

    for (i = 0; i < 13; i++)
    {
        for (j = 0; j < 68; j++)
        {
            for (k = 0; k < 8; k++)
            {
                char_buff[j + k * 68] =
                    (temp_font68x104[num * 884 + i + j * 13] & (0x01 << k)) ? color : UI_bgcolor;
            }
        }
        LCD_Fill(x, y + i * 8, x + 67, y + i * 8 + 7, char_buff); // 设置坐标
    }
}

/******************************************************************************
      函数说明：字符显示
      入口数据： x,y             起始坐标
                color           要填充的颜色
                num             显示的字符
      返回值：  无
******************************************************************************/
void UI_ShowChar_font28x48(uint16_t x, uint16_t y, uint8_t num, uint16_t color)
{
    uint16_t char_buff[28 * 16] = {0};
    uint8_t i, j, k, l;
    for (l = 0; l < 3; l++)
    {
        for (i = 0; i < 2; i++)
        {
            for (j = 0; j < 28; j++)
            {
                for (k = 0; k < 8; k++)
                {
                    char_buff[i * 224 + j + k * 28] =
                        (temp_font28x48[num * 168 + i + j * 6 + l * 2] & (0x01 << k)) ? color : UI_bgcolor;
                }
            }
        }
        LCD_Fill(x, y + l * 16, x + 27, y + l * 16 + 15, char_buff); // 设置坐标
    }
}

/******************************************************************************
      函数说明：汉字显示
      入口数据： x,y             起始坐标
                color           要填充的颜色
                index           显示的汉字序号
      返回值：  无
******************************************************************************/
void UI_ShowChinese_font24(uint16_t x, uint16_t y, uint8_t index, uint16_t color)
{
    uint16_t chinese_buff[24 * 24] = {0};
    uint8_t i, j, k;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 24; j++)
        {
            for (k = 0; k < 8; k++)
            {
                chinese_buff[i * 192 + j + k * 24] =
                    (chinese_font24[index * 72 + i + j * 3] & (0x01 << k)) ? color : UI_bgcolor;
            }
        }
    }

    LCD_Fill(x, y, x + 23, y + 23, chinese_buff); // 设置坐标
}

/******************************************************************************
      函数说明：数值显示
      入口数据： x,y             起始坐标
                len             数字位数
                color           要填充的颜色
                mode            前面补0显示开关
                num/mulriple    显示的数值
      返回值：  无
******************************************************************************/
void UI_ShowNum_font24(uint16_t x, uint16_t y, uint16_t num, uint8_t len, uint16_t mulriple, uint8_t mode, uint16_t color)
{
    uint8_t i = 0;
    uint8_t truelen = 1;
    uint8_t pos = 0;
    uint16_t tmp = 0;

    if (num > 9999)
        return;
    while (mulriple /= 10)
    {
        pos++;
    }
    pos = len - pos;

    while (num / UI_pow(10, truelen))
    {
        truelen++;
    }
    for (i = 0; i < len; i++)
    {
        if (i < len - truelen)
        {
            if (mode)
            {
                UI_ShowChar_font24(x + 12 * i, y, 0, color);
            }
            else
            {
                LCD_Clean(x + 12 * i, y, x + 12 * i + 11, y + 23, UI_bgcolor);
            }
            continue;
        }
        else if (i == pos)
        {
            UI_ShowChar_font24(x + 12 * i, y, 10, color);
            i++;
            len++;
        }
        tmp = UI_pow(10, len - i - 1);
        UI_ShowChar_font24(x + 12 * i, y, num / tmp, color);
        num %= tmp;
    }
}

/******************************************************************************
      函数说明： 实际温度显示
      入口数据： x,y             起始坐标
                color           要填充的颜色
                num             显示的数值
      返回值：  无
******************************************************************************/
void UI_ShowTemperature(uint16_t x, uint16_t y, uint16_t num, uint16_t color)
{
    uint8_t i = 0;
    uint8_t tmp = 0;

    for (i = 0; i < 3; i++)
    {
        tmp = UI_pow(10, 2 - i);
        UI_ShowChar_font68x104(x + 70 * i, y, num / tmp, color);
        num %= tmp;
    }
}

/******************************************************************************
      函数说明： 目标温度显示
      入口数据： x,y             起始坐标
                color           要填充的颜色
                num             显示的数值
      返回值：  无
******************************************************************************/
void UI_ShowTargetTemperature(uint16_t x, uint16_t y, uint16_t num, uint16_t color)
{
    uint8_t i = 0;
    uint8_t tmp = 0;

    for (i = 0; i < 3; i++)
    {
        tmp = UI_pow(10, 2 - i);
        UI_ShowChar_font28x48(x + 30 * i, y, num / tmp, color);
        num %= tmp;
    }
}

/******************************************************************************
      函数说明： 声音打开/关闭显示
      入口数据： x,y             起始坐标
                color           要填充的颜色
                num             0 off, 1 on
      返回值：  无
******************************************************************************/
void UI_ShowSoundFlag(uint16_t x, uint16_t y, uint16_t num, uint16_t color)
{
    uint16_t pic_buff[24 * 24] = {0};
    uint8_t *pic;
    uint8_t i, j, k;

    if (num)
        pic = (uint8_t *)pic_sound_on;
    else
        pic = (uint8_t *)pic_sound_off;
    for (i = 0; i < 24; i++)
    {
        for (j = 0; j < 3; j++)
        {
            for (k = 0; k < 8; k++)
            {
                pic_buff[i * 24 + j * 8 + k] =
                    (pic[i * 3 + j] & (0x01 << k)) ? color : UI_bgcolor;
            }
        }
    }

    LCD_Fill(x, y, x + 23, y + 23, pic_buff); // 设置坐标
}

/******************************************************************************
      函数说明： 进度条外框显示
      入口数据： x,y             起始坐标
                color           要填充的颜色
      返回值：  无
******************************************************************************/
void UI_ShowBar(uint16_t x, uint16_t y, uint16_t color)
{
    uint16_t L_buff[12 * 24] = {0};
    uint16_t R_buff[12 * 24] = {0};
    uint8_t i, j, k;

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 12; j++)
        {
            for (k = 0; k < 8; k++)
            {
                L_buff[i * 96 + j + k * 12] =
                    (pic_route_L[i + j * 3] & (0x01 << k)) ? color : UI_bgcolor;
                R_buff[i * 96 + j + k * 12] =
                    (pic_route_R[i + j * 3] & (0x01 << k)) ? color : UI_bgcolor;
            }
        }
    }
    LCD_Fill(x, y, x + 11, y + 23, L_buff);
    LCD_Fill(x + 188, y, x + 199, y + 23, R_buff);
    LCD_Clean(x + 12, y, x + 188, y + 2, color);
    LCD_Clean(x + 12, y + 21, x + 188, y + 23, color);
}

/******************************************************************************
      函数说明： 进度条百分比显示
      入口数据： num 百分比
      返回值：  无
******************************************************************************/
void UI_SetBarValue(uint8_t num)
{
    const uint8_t arc_L_sta[5][2] = {219, 216, 214, 213, 213, 212, 211, 211, 211, 211};
    const uint8_t arc_L_end[5][2] = {220, 223, 225, 226, 226, 227, 228, 228, 228, 228};
    const uint8_t arc_R_sta[5][2] = {211, 211, 211, 211, 212, 213, 213, 214, 216, 219};
    const uint8_t arc_R_end[5][2] = {228, 228, 228, 228, 227, 226, 226, 225, 223, 220};
    static uint8_t last_num = 2;
    uint16_t *color_bar = (uint16_t *)pic_bar;
    uint8_t dir = 0;
    uint8_t i, j, k;

    if (num > 99)
    {
        num = 99;
    }
    else if (num < 2)
    {
        num = 2;
    }
    if (num == last_num)
    {
        return;
    }
    else if (num > last_num)
    {
        dir = 0;
    }
    else
    {
        i = last_num;
        last_num = num;
        num = i;
        dir = 1;
    }
    for (i = last_num; i <= num && i < 7; i++) // 6%(含)以下圆弧部分处理
    {
        j = i - 2;
        if (dir)
        {
            LCD_Clean(j * 2 + 2, arc_L_sta[j][0], j * 2 + 2, arc_L_end[j][0], UI_bgcolor);
            LCD_Clean(j * 2 + 3, arc_L_sta[j][1], j * 2 + 3, arc_L_end[j][1], UI_bgcolor);
        }
        else
        {
            LCD_Clean(j * 2 + 2, arc_L_sta[j][0], j * 2 + 2, arc_L_end[j][0], color_bar[j * 2]);
            LCD_Clean(j * 2 + 3, arc_L_sta[j][1], j * 2 + 3, arc_L_end[j][1], color_bar[j * 2 + 1]);
        }
    }
    for (i = last_num > 6 ? last_num : 7; i <= num && i < 95; i++) // 7%(含) ~ 94%(含)
    {
        j = i - 7;
        if (dir)
        {
            LCD_Clean(j * 2 + 12, 211, j * 2 + 12, 228, UI_bgcolor);
            LCD_Clean(j * 2 + 13, 211, j * 2 + 13, 228, UI_bgcolor);
        }
        else
        {
            LCD_Clean(j * 2 + 12, 211, j * 2 + 12, 228, color_bar[j * 2 + 10]);
            LCD_Clean(j * 2 + 13, 211, j * 2 + 13, 228, color_bar[j * 2 + 11]);
        }
    }
    for (i = last_num > 94 ? last_num : 95; i <= num && i > 94; i++) // 95%(含)以上圆弧部分处理
    {
        j = i - 95;
        if (dir)
        {
            LCD_Clean(j * 2 + 188, arc_R_sta[j][0], j * 2 + 188, arc_R_end[j][0], UI_bgcolor);
            LCD_Clean(j * 2 + 189, arc_R_sta[j][1], j * 2 + 189, arc_R_end[j][1], UI_bgcolor);
        }
        else
        {
            LCD_Clean(j * 2 + 188, arc_R_sta[j][0], j * 2 + 188, arc_R_end[j][0], color_bar[j * 2 + 184]);
            LCD_Clean(j * 2 + 189, arc_R_sta[j][1], j * 2 + 189, arc_R_end[j][1], color_bar[j * 2 + 185]);
        }
    }
    if (dir == 0)
    {
        last_num = num;
    }
    printf("last_num = %d, dir = %d\r\n", last_num, dir);
}

void Main_Page_Init(void)
{
    // UI_Background_olor(DARKGRAY);
    LCD_Clean(0, 0, 240, 240, UI_bgcolor);
    // LCD_Clean(0, 23, 240, 25, BLACK);

    // UI_ShowChinese_font24(0, 0, 0, WHITE);
    UI_ShowChinese_font24(0, 0, 1, BLUE);
    UI_ShowChinese_font24(24, 0, 2, BLUE);
    UI_ShowChinese_font24(72, 0, 3, BLUE);
    UI_ShowChinese_font24(120, 0, 4, BLUE);

    UI_ShowSoundFlag(156, 0, 1, WHITE);

    UI_ShowChinese_font24(192, 0, 5, BLUE);
    UI_ShowChinese_font24(216, 0, 6, BLUE);

    UI_ShowChinese_font24(0, 55, 9, GREEN);
    UI_ShowChinese_font24(0, 103, 10, GREEN);

    UI_ShowChinese_font24(0, 150, 7, YELLOW);
    UI_ShowChinese_font24(0, 175, 8, YELLOW);

    UI_ShowChinese_font24(132, 175, 11, RED);
    UI_ShowChinese_font24(156, 175, 12, RED);
    UI_ShowChar_font24(228, 175, 11, RED);

    UI_ShowChinese_font24(216, 199, 14, BROWN);
    UI_ShowChinese_font24(198, 199, 13, BROWN);

    UI_ShowBar(0, 208, BROWN);
}
