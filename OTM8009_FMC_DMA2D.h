#ifndef __OTM8009_FMC_DMA2D_H
#define __OTM8009_FMC_DMA2D_H
#endif

#include "stm32f4xx_hal.h"

//LCD Size
#define LCD_WIDTH 800
#define LCD_HEIGHT 480

//LCD Direction
#define LCD_DIR 0 //0:Horizontal 1:Vectrial

//Handler Definition
//#define LCD_FMC_HANDLER hsram1 :unused
#define LCD_DMA2D_HANDLER hdma2d

//Pin Definition
#define LCD_RST_PORT GPIOG	
#define LCD_BL_PORT GPIOG
#define LCD_RST GPIO_PIN_3
#define LCD_BL GPIO_PIN_4

//LCD FMC Address
#define LCD_FMC_DAT_ADDR 0x62000000 //RS# is connected to A24
#define LCD_FMC_CMD_ADDR 0x60000000 

//LCD Config structure
typedef struct
{
	uint16_t height;
	uint16_t width;
	uint8_t direction;
}LCD_Conf;

//Function declaration
void LCD_Reset(void);
void LCD_Init(void);
void LCD_Fill(uint16_t color);
void LCD_WriteData(uint16_t data);
void LCD_WriteCommand(uint16_t data);
void LCD_SetConfig(void);
void LCD_PrepareWriteDisplayData(void);
void LCD_SetWindowSize(uint16_t start_x, uint16_t start_y, uint16_t end_x,uint16_t end_y);
void LCD_SetCursorPos(uint16_t pos_x, uint16_t pos_y);
void LCD_SetBacklight(uint8_t stat);




