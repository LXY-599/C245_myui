#include "lcd.h"
#include "spi.h"
#include "usart.h"

#define LCD_SPI hspi1 // SPI�ֲ��꣬�����޸ĺ���ֲ
#define SPI_DMA_ENABLE 0

/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_DATA8(uint8_t lcd_data)
{
    LCD_CS_Clr();
#if SPI_DMA_ENABLE
    HAL_SPI_Transmit_DMA(&LCD_SPI, &lcd_data, 1);
#else
    HAL_SPI_Transmit(&LCD_SPI, &lcd_data, 1, 1000);                                            // ����SPI����
#endif
    LCD_CS_Set();
}

/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_DATA(uint16_t lcd_data)
{
    LCD_CS_Clr();
    uint8_t lcd_data_buff[2]; // ���ݷ�����

    lcd_data_buff[0] = lcd_data >> 8; // �����ݲ��
    lcd_data_buff[1] = lcd_data;

#if SPI_DMA_ENABLE
    HAL_SPI_Transmit_DMA(&LCD_SPI, lcd_data_buff, 2);
#else
    HAL_SPI_Transmit(&LCD_SPI, lcd_data_buff, 2, 1000);                                        // ����SPI����
#endif
    LCD_CS_Set();
}

/******************************************************************************
      ����˵����LCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void LCD_WR_REG(uint8_t lcd_data)
{
    LCD_CS_Clr();
    LCD_DC_Clr(); // д����
#if SPI_DMA_ENABLE
    HAL_SPI_Transmit_DMA(&LCD_SPI, &lcd_data, 1);
#else
    HAL_SPI_Transmit(&LCD_SPI, &lcd_data, 1, 1000);                                            // ����SPI����
#endif
    LCD_DC_Set(); // д����
    LCD_CS_Set();
}

/******************************************************************************
      ����˵����������ʼ�ͽ�����ַ
      ������ݣ�x1,x2 �����е���ʼ�ͽ�����ַ
                y1,y2 �����е���ʼ�ͽ�����ַ
      ����ֵ��  ��
**************************************************************************/
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    if (USE_HORIZONTAL == 0)
    {
        LCD_WR_REG(0x2a); // �е�ַ����
        LCD_WR_DATA(x1);
        LCD_WR_DATA(x2);
        LCD_WR_REG(0x2b); // �е�ַ����
        LCD_WR_DATA(y1);
        LCD_WR_DATA(y2);
        LCD_WR_REG(0x2c); // ������д
    }
    else if (USE_HORIZONTAL == 1)
    {
        LCD_WR_REG(0x2a); // �е�ַ����
        LCD_WR_DATA(x1);
        LCD_WR_DATA(x2);
        LCD_WR_REG(0x2b); // �е�ַ����
        LCD_WR_DATA(y1 + 80);
        LCD_WR_DATA(y2 + 80);
        LCD_WR_REG(0x2c); // ������д
    }
    else if (USE_HORIZONTAL == 2)
    {
        LCD_WR_REG(0x2a); // �е�ַ����
        LCD_WR_DATA(x1);
        LCD_WR_DATA(x2);
        LCD_WR_REG(0x2b); // �е�ַ����
        LCD_WR_DATA(y1);
        LCD_WR_DATA(y2);
        LCD_WR_REG(0x2c); // ������д
    }
    else
    {
        LCD_WR_REG(0x2a); // �е�ַ����
        LCD_WR_DATA(x1 + 80);
        LCD_WR_DATA(x2 + 80);
        LCD_WR_REG(0x2b); // �е�ַ����
        LCD_WR_DATA(y1);
        LCD_WR_DATA(y2);
        LCD_WR_REG(0x2c); // ������д
    }
}

void LCD_Init(void)
{
    HAL_Delay(10); // ��Ļ����ɸ�λʱ�������ϵ縴λ������Ҫ�ȴ�����5ms���ܷ���ָ��

    LCD_RES_Clr(); // ��λ
    HAL_Delay(100);
    LCD_RES_Set();
    HAL_Delay(100);

    //	LCD_BLK_Set();
    //************* Start Initial Sequence **********//
    LCD_WR_REG(0x11); // Sleep out
    HAL_Delay(120);   // Delay 120ms
    //************* Start Initial Sequence **********//
    LCD_WR_REG(0x36);
    if (USE_HORIZONTAL == 0)
        LCD_WR_DATA8(0x00);
    else if (USE_HORIZONTAL == 1)
        LCD_WR_DATA8(0xC0);
    else if (USE_HORIZONTAL == 2)
        LCD_WR_DATA8(0x70);
    else
        LCD_WR_DATA8(0xA0);

    LCD_WR_REG(0x3A);
    LCD_WR_DATA8(0x05);

    LCD_WR_REG(0xB2);
    LCD_WR_DATA8(0x1F);
    LCD_WR_DATA8(0x1F);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x33);
    LCD_WR_DATA8(0x33);

    LCD_WR_REG(0xB7);
    LCD_WR_DATA8(0x00); // VGH=12.2V,VGL=-7.16V

    LCD_WR_REG(0xBB);
    LCD_WR_DATA8(0x3F);

    LCD_WR_REG(0xC0);
    LCD_WR_DATA8(0x2C);

    LCD_WR_REG(0xC2);
    LCD_WR_DATA8(0x01);

    LCD_WR_REG(0xC3);
    LCD_WR_DATA8(0x0F); // 4.3V

    LCD_WR_REG(0xC4);
    LCD_WR_DATA8(0x20); // VDV, 0x20:0v

    LCD_WR_REG(0xC6);
    LCD_WR_DATA8(0x13);

    LCD_WR_REG(0xD0);
    LCD_WR_DATA8(0xA4);
    LCD_WR_DATA8(0xA1);

    LCD_WR_REG(0xD6);
    LCD_WR_DATA8(0xA1); // sleep in��gate���ΪGND

    LCD_WR_REG(0xE0);
    LCD_WR_DATA8(0xF0);
    LCD_WR_DATA8(0x06);
    LCD_WR_DATA8(0x0D);
    LCD_WR_DATA8(0x0B);
    LCD_WR_DATA8(0x0A);
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x2E);
    LCD_WR_DATA8(0x43);
    LCD_WR_DATA8(0x45);
    LCD_WR_DATA8(0x38);
    LCD_WR_DATA8(0x14);
    LCD_WR_DATA8(0x13);
    LCD_WR_DATA8(0x25);
    LCD_WR_DATA8(0x29);

    LCD_WR_REG(0xE1);
    LCD_WR_DATA8(0xF0);
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x0A);
    LCD_WR_DATA8(0x08);
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x23);
    LCD_WR_DATA8(0x2E);
    LCD_WR_DATA8(0x33);
    LCD_WR_DATA8(0x44);
    LCD_WR_DATA8(0x3A);
    LCD_WR_DATA8(0x16);
    LCD_WR_DATA8(0x17);
    LCD_WR_DATA8(0x26);
    LCD_WR_DATA8(0x2C);

    LCD_WR_REG(0xE4);
    LCD_WR_DATA8(0x1D); // ʹ��240��gate  (N+1)*8
    LCD_WR_DATA8(0x00); // �趨gate���λ��
    LCD_WR_DATA8(0x00); // ��gateû������ʱ��bit4(TMG)��Ϊ0

    LCD_WR_REG(0x21);
    LCD_WR_REG(0x29);
}

/******************************************************************************
      ����˵������ָ�����������ɫ
      ������ݣ�xsta,ysta   ��ʼ����
                xend,yend   ��ֹ����
                                color       Ҫ������ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_Fill(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t *color_p)
{
    LCD_Address_Set(xsta, ysta, xend, yend); // ��������
    LCD_CS_Clr();
    LCD_DC_Set(); // д����;

    // �޸�Ϊ16λ���ݿ�ȣ�д�����ݸ���Ч�ʣ�����Ҫ���
    LCD_SPI.Init.DataSize = SPI_DATASIZE_16BIT; //	16λ���ݿ��
    HAL_SPI_Init(&LCD_SPI);
    // LCD_SPI_Transmit(&LCD_SPI, color_p, (xend - xsta) * (yend - ysta));
#if SPI_DMA_ENABLE
    HAL_SPI_Transmit_DMA(&LCD_SPI, (uint8_t *)&color_p->full, (xend - xsta) * (yend - ysta));
#else
    HAL_SPI_Transmit(&LCD_SPI, (uint8_t *)color_p, (xend - xsta + 1) * (yend - ysta + 1), 10); // ����SPI����
#endif
    // �Ļ�8λ���ݿ�ȣ���Ϊָ��Ͳ������ݶ��ǰ���8λ�����
    LCD_SPI.Init.DataSize = SPI_DATASIZE_8BIT; //	8λ���ݿ��
    HAL_SPI_Init(&LCD_SPI);
    LCD_CS_Set();
}

/******************************************************************************
      ����˵�����ֲ���������
      ������ݣ�xsta,ysta   ��ʼ����
                xend,yend   ��ֹ����
                                color       Ҫ������ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_Clean(uint16_t xsta, uint16_t ysta, uint16_t xend, uint16_t yend, uint16_t color_p)
{
    LCD_Address_Set(xsta, ysta, xend, yend); // ��������
    LCD_CS_Clr();
    LCD_DC_Set(); // д����;

    // �޸�Ϊ16λ���ݿ�ȣ�д�����ݸ���Ч�ʣ�����Ҫ���
    LCD_SPI.Init.DataSize = SPI_DATASIZE_16BIT; //	16λ���ݿ��
    HAL_SPI_Init(&LCD_SPI);

    LCD_SPI_Transmit(&LCD_SPI, color_p, (xend - xsta + 1) * (yend - ysta + 1));

    // �Ļ�8λ���ݿ�ȣ���Ϊָ��Ͳ������ݶ��ǰ���8λ�����
    LCD_SPI.Init.DataSize = SPI_DATASIZE_8BIT; //	8λ���ݿ��
    HAL_SPI_Init(&LCD_SPI);
    LCD_CS_Set();
}

/******************************************************************************
      ����˵������ָ��λ�û���
      ������ݣ�x,y ��������
                color �����ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
    LCD_Address_Set(x, y, x, y); // ���ù��λ��
    LCD_WR_DATA(color);
}

/******************************************************************************
      ����˵��������
      ������ݣ�x1,y1   ��ʼ����
                x2,y2   ��ֹ����
                color   �ߵ���ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawLine(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
    uint16_t t;
    int xerr = 0, yerr = 0, delta_x, delta_y, distance;
    int incx, incy, uRow, uCol;
    delta_x = x2 - x1; // ������������
    delta_y = y2 - y1;
    uRow = x1; // �����������
    uCol = y1;
    if (delta_x > 0)
        incx = 1; // ���õ�������
    else if (delta_x == 0)
        incx = 0; // ��ֱ��
    else
    {
        incx = -1;
        delta_x = -delta_x;
    }
    if (delta_y > 0)
        incy = 1;
    else if (delta_y == 0)
        incy = 0; // ˮƽ��
    else
    {
        incy = -1;
        delta_y = -delta_y;
    }
    if (delta_x > delta_y)
        distance = delta_x; // ѡȡ��������������
    else
        distance = delta_y;
    for (t = 0; t < distance + 1; t++)
    {
        LCD_DrawPoint(uRow, uCol, color); // ����
        xerr += delta_x;
        yerr += delta_y;
        if (xerr > distance)
        {
            xerr -= distance;
            uRow += incx;
        }
        if (yerr > distance)
        {
            yerr -= distance;
            uCol += incy;
        }
    }
}

/******************************************************************************
      ����˵����������
      ������ݣ�x1,y1   ��ʼ����
                x2,y2   ��ֹ����
                color   ���ε���ɫ
      ����ֵ��  ��
******************************************************************************/
void LCD_DrawRectangle(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2, uint16_t color)
{
#if UNUSED_Fill
    LCD_DrawLine(x1, y1, x2, y1, color);
    LCD_DrawLine(x1, y1, x1, y2, color);
    LCD_DrawLine(x1, y2, x2, y2, color);
    LCD_DrawLine(x2, y1, x2, y2, color);
#else
    LCD_Clean(x1, y1, x2, y1, color);
    LCD_Clean(x1, y1, x1, y2, color);
    LCD_Clean(x1, y2, x2, y2, color);
    LCD_Clean(x2, y1, x2, y2, color);
#endif
}

/******************************************************************************
      ����˵������Բ
      ������ݣ�x0,y0   Բ������
                r       �뾶
                color   Բ����ɫ
      ����ֵ��  ��
******************************************************************************/
void Draw_Circle(uint16_t x0, uint16_t y0, uint8_t r, uint16_t color)
{
    int a, b;
    a = 0;
    b = r;
    while (a <= b)
    {
        LCD_DrawPoint(x0 - b, y0 - a, color); // 3
        LCD_DrawPoint(x0 + b, y0 - a, color); // 0
        LCD_DrawPoint(x0 - a, y0 + b, color); // 1
        LCD_DrawPoint(x0 - a, y0 - b, color); // 2
        LCD_DrawPoint(x0 + b, y0 + a, color); // 4
        LCD_DrawPoint(x0 + a, y0 - b, color); // 5
        LCD_DrawPoint(x0 + a, y0 + b, color); // 6
        LCD_DrawPoint(x0 - b, y0 + a, color); // 7
        a++;
        if ((a * a + b * b) > (r * r)) // �ж�Ҫ���ĵ��Ƿ��Զ
        {
            b--;
        }
    }
}

/**********************************************************************************************************************************
 *
 * ���¼��������޸���HAL�Ŀ⺯����Ŀ����Ϊ��SPI�������ݲ������ݳ��ȵ�д�룬��������������ٶ�
 *
 *****************************************************************************************************************FANKE************/

/**
 * @brief  �ȴ�fifo��������ɣ�LCD_SPI_Transmit() �ﱻ����
 * @param  hspi pointer to a SPI_HandleTypeDef structure that contains
 *              the configuration information for SPI module.
 * @param  Fifo Fifo to check
 * @param  State Fifo state to check
 * @param  Timeout Timeout duration
 * @param  Tickstart tick start value
 * @retval HAL status
 * fanke
 */
HAL_StatusTypeDef LCD_SPI_WaitFifoStateUntilTimeout(SPI_HandleTypeDef *hspi, uint32_t Fifo, uint32_t State,
                                                    uint32_t Timeout, uint32_t Tickstart)
{
    __IO uint32_t count;
    uint32_t tmp_timeout;
    uint32_t tmp_tickstart;
    __IO uint8_t *ptmpreg8;
    __IO uint8_t tmpreg8 = 0;

    /* Adjust Timeout value  in case of end of transfer */
    tmp_timeout = Timeout - (HAL_GetTick() - Tickstart);
    tmp_tickstart = HAL_GetTick();
    /* Initialize the 8bit temporary pointer */
    ptmpreg8 = (__IO uint8_t *)&hspi->Instance->DR;
    /* Calculate Timeout based on a software loop to avoid blocking issue if Systick is disabled */
    count = tmp_timeout * ((SystemCoreClock * 35U) >> 20U);

    while ((hspi->Instance->SR & Fifo) != State)
    {
        if ((Fifo == SPI_SR_FRLVL) && (State == SPI_FRLVL_EMPTY))
        {
            /* Flush Data Register by a blank read */
            tmpreg8 = *ptmpreg8;
            /* To avoid GCC warning */
            UNUSED(tmpreg8);
        }

        if (Timeout != HAL_MAX_DELAY)
        {
            if (((HAL_GetTick() - tmp_tickstart) >= tmp_timeout) || (tmp_timeout == 0U))
            {
                /* Disable the SPI and reset the CRC: the CRC value should be cleared
                on both master and slave sides in order to resynchronize the master
                and slave for their respective CRC calculation */

                /* Disable TXE, RXNE and ERR interrupts for the interrupt process */
                __HAL_SPI_DISABLE_IT(hspi, (SPI_IT_TXE | SPI_IT_RXNE | SPI_IT_ERR));

                if ((hspi->Init.Mode == SPI_MODE_MASTER) && ((hspi->Init.Direction == SPI_DIRECTION_1LINE) || (hspi->Init.Direction == SPI_DIRECTION_2LINES_RXONLY)))
                {
                    /* Disable SPI peripheral */
                    __HAL_SPI_DISABLE(hspi);
                }
                /* Reset CRC Calculation */
                if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
                {
                    SPI_RESET_CRC(hspi);
                }
                hspi->State = HAL_SPI_STATE_READY;
                /* Process Unlocked */
                __HAL_UNLOCK(hspi);
                return HAL_TIMEOUT;
            }
            /* If Systick is disabled or not incremented, deactivate timeout to go in disable loop procedure */
            if (count == 0U)
            {
                Timeout = 0U;
            }
            count--;
        }
    }

    return HAL_OK;
}

/**
 * @brief  רΪ��Ļ�������޸ģ�����Ҫ��������ɫ��������
 * @param  hspi   : spi�ľ��
 * @param  pData  : Ҫд�������
 * @param  Size   : ���ݴ�С
 * @retval HAL status
 */
HAL_StatusTypeDef LCD_SPI_Transmit(SPI_HandleTypeDef *hspi, uint16_t pData, uint32_t Size)
{
    uint32_t tickstart;
    uint32_t Timeout = 1000;  // ��ʱ�ж�
    uint32_t LCD_TxDataCount; // �������
    HAL_StatusTypeDef errorcode = HAL_OK;

    /* Check Direction parameter */
    assert_param(IS_SPI_DIRECTION_2LINES_OR_1LINE_2LINES_TXONLY(hspi->Init.Direction));

    /* Process Locked */
    __HAL_LOCK(hspi);

    /* Init tickstart for timeout management*/
    tickstart = HAL_GetTick();

    if (hspi->State != HAL_SPI_STATE_READY)
    {
        errorcode = HAL_BUSY;
        __HAL_UNLOCK(hspi);
        return errorcode;
    }

    /* Set the transaction information */
    hspi->State = HAL_SPI_STATE_BUSY_TX;
    hspi->ErrorCode = HAL_SPI_ERROR_NONE;
    //   hspi->pTxBuffPtr  = (uint8_t *)pData;
    hspi->TxXferSize = Size;
    hspi->TxXferCount = Size;

    LCD_TxDataCount = Size; // ��������ݳ���

    /*Init field not used in handle to zero */
    hspi->pRxBuffPtr = NULL;
    hspi->RxXferSize = (uint16_t)0UL;
    hspi->RxXferCount = (uint16_t)0UL;
    hspi->TxISR = NULL;
    hspi->RxISR = NULL;
    // fanke
    /* Configure communication direction : 1Line */
    SPI_1LINE_TX(hspi); // ����SPI

    /* Check if the SPI is already enabled */
    if ((hspi->Instance->CR1 & SPI_CR1_SPE) != SPI_CR1_SPE)
    {
        /* Enable SPI peripheral */
        __HAL_SPI_ENABLE(hspi);
    }
    if ((hspi->Init.Mode == SPI_MODE_SLAVE) || (LCD_TxDataCount == 0x01U))
    {
        hspi->Instance->DR = (uint16_t)pData;
        LCD_TxDataCount--;
    }

    /* Transmit data in 16 Bit mode */
    /* Transmit data in 16 Bit mode */
    while (LCD_TxDataCount > 0UL)
    {
        /* Wait until TXE flag is set to send data */
        if (__HAL_SPI_GET_FLAG(hspi, SPI_FLAG_TXE))
        {
            hspi->Instance->DR = (uint16_t)pData;
            LCD_TxDataCount--;
        }
        else
        {
            /* Timeout management */
            if ((((HAL_GetTick() - tickstart) >= Timeout) && (Timeout != HAL_MAX_DELAY)) || (Timeout == 0U))
            {
                errorcode = HAL_TIMEOUT;
                return HAL_ERROR;
            }
        }
    }
#if (USE_SPI_CRC != 0U)
    /* Enable CRC Transmission */
    if (hspi->Init.CRCCalculation == SPI_CRCCALCULATION_ENABLE)
    {
        SET_BIT(hspi->Instance->CR1, SPI_CR1_CRCNEXT);
    }
#endif /* USE_SPI_CRC */

    /* Control if the TX fifo is empty */
    if (LCD_SPI_WaitFifoStateUntilTimeout(hspi, SPI_FLAG_FTLVL, SPI_FTLVL_EMPTY, Timeout, tickstart) != HAL_OK)
    {
        SET_BIT(hspi->ErrorCode, HAL_SPI_ERROR_FLAG);
        hspi->ErrorCode = HAL_SPI_ERROR_FLAG;

        return HAL_ERROR;
    }
    /* Process Unlocked */
    __HAL_UNLOCK(hspi);
    hspi->State = HAL_SPI_STATE_READY;
    if (hspi->ErrorCode != HAL_SPI_ERROR_NONE)
    {
        return HAL_ERROR;
    }
    return errorcode;
}
