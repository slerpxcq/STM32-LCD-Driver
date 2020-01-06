#include "OTM8009_FMC_DMA2D.h"
#include "arm_math.h"

extern SRAM_HandleTypeDef LCD_FMC_HANDLER;		//Defined in main.c
extern DMA2D_HandleTypeDef LCD_DMA2D_HANDLER;

LCD_Conf lcdcfg;

//LCD Write Command
inline void LCD_WriteCommand(uint16_t com)
{
	//HAL_SRAM_Write_16b(sram_handler, (uint32_t *)LCD_FMC_CMD_ADDR, &data, 1);
	
	//__IO uint16_t * lcd_cmd_addr = (uint16_t *)LCD_FMC_CMD_ADDR;
	//*lcd_cmd_addr = com;
	
	*(__IO uint16_t *)LCD_FMC_CMD_ADDR = com;
}
//LCD Write Data
inline void LCD_WriteData(uint16_t data)
{
	//__IO uint16_t * lcd_data_addr = (uint16_t *)LCD_FMC_DAT_ADDR;
	//*lcd_data_addr = data;
	
	*(__IO uint16_t *)LCD_FMC_DAT_ADDR = data;
}
//LCD Reset
void LCD_Reset(void)
{
	HAL_GPIO_WritePin(LCD_RST_PORT,LCD_RST,GPIO_PIN_SET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(LCD_RST_PORT,LCD_RST,GPIO_PIN_RESET);
	HAL_Delay(100);
	HAL_GPIO_WritePin(LCD_RST_PORT,LCD_RST,GPIO_PIN_SET);
	HAL_Delay(100);
}
//LCD Initialization
void LCD_Init(void)
{
	LCD_Reset();
	LCD_WriteCommand(0xff00);   LCD_WriteData(0x80);		//enable access command2 0011 0100 1111 1111 00
	LCD_WriteCommand(0xff01);   LCD_WriteData(0x09);		//enable access command2
	LCD_WriteCommand(0xff02);   LCD_WriteData(0x01);		//enable access command2
	LCD_WriteCommand(0xff80);   LCD_WriteData(0x80);		//enable access command2
LCD_WriteCommand(0xff81);   LCD_WriteData(0x09);		//enable access command2
LCD_WriteCommand(0xff03);   LCD_WriteData(0x01);		//
LCD_WriteCommand(0xc5b1);   LCD_WriteData(0xA9);		//power control

LCD_WriteCommand(0xc591);   LCD_WriteData(0x0F);               //power control
LCD_WriteCommand(0xc0B4);   LCD_WriteData(0x50);
		
//panel driving mode : column inversion

//////	gamma
LCD_WriteCommand(0xE100);   LCD_WriteData(0x00);
LCD_WriteCommand(0xE101);   LCD_WriteData(0x09);
LCD_WriteCommand(0xE102);   LCD_WriteData(0x0F);
LCD_WriteCommand(0xE103);   LCD_WriteData(0x0E);
LCD_WriteCommand(0xE104);   LCD_WriteData(0x07);
LCD_WriteCommand(0xE105);   LCD_WriteData(0x10);
LCD_WriteCommand(0xE106);   LCD_WriteData(0x0B);
LCD_WriteCommand(0xE107);   LCD_WriteData(0x0A);
LCD_WriteCommand(0xE108);   LCD_WriteData(0x04);
LCD_WriteCommand(0xE109);   LCD_WriteData(0x07);
LCD_WriteCommand(0xE10A);   LCD_WriteData(0x0B);
LCD_WriteCommand(0xE10B);   LCD_WriteData(0x08);
LCD_WriteCommand(0xE10C);   LCD_WriteData(0x0F);
LCD_WriteCommand(0xE10D);   LCD_WriteData(0x10);
LCD_WriteCommand(0xE10E);   LCD_WriteData(0x0A);
LCD_WriteCommand(0xE10F);   LCD_WriteData(0x01);	
LCD_WriteCommand(0xE200);   LCD_WriteData(0x00);
LCD_WriteCommand(0xE201);   LCD_WriteData(0x09);
LCD_WriteCommand(0xE202);   LCD_WriteData(0x0F);
LCD_WriteCommand(0xE203);   LCD_WriteData(0x0E);
LCD_WriteCommand(0xE204);   LCD_WriteData(0x07);
LCD_WriteCommand(0xE205);   LCD_WriteData(0x10);
LCD_WriteCommand(0xE206);   LCD_WriteData(0x0B);
LCD_WriteCommand(0xE207);   LCD_WriteData(0x0A);
LCD_WriteCommand(0xE208);   LCD_WriteData(0x04);
LCD_WriteCommand(0xE209);   LCD_WriteData(0x07);
LCD_WriteCommand(0xE20A);   LCD_WriteData(0x0B);
LCD_WriteCommand(0xE20B);   LCD_WriteData(0x08);
LCD_WriteCommand(0xE20C);   LCD_WriteData(0x0F);
LCD_WriteCommand(0xE20D);   LCD_WriteData(0x10);
LCD_WriteCommand(0xE20E);   LCD_WriteData(0x0A);
LCD_WriteCommand(0xE20F);   LCD_WriteData(0x01);	
LCD_WriteCommand(0xD900);   LCD_WriteData(0x4E);		//vcom setting

LCD_WriteCommand(0xc181);   LCD_WriteData(0x66);		//osc=65HZ

LCD_WriteCommand(0xc1a1);   LCD_WriteData(0x08);		
LCD_WriteCommand(0xc592);   LCD_WriteData(0x01);		//power control

LCD_WriteCommand(0xc595);   LCD_WriteData(0x34);		//power control

LCD_WriteCommand(0xd800);   LCD_WriteData(0x79);		//GVDD / NGVDD setting

LCD_WriteCommand(0xd801);   LCD_WriteData(0x79);		//GVDD / NGVDD setting

LCD_WriteCommand(0xc594);   LCD_WriteData(0x33);		//power control

LCD_WriteCommand(0xc0a3);   LCD_WriteData(0x1B);       //panel timing setting
LCD_WriteCommand(0xc582);   LCD_WriteData(0x83);		//power control

LCD_WriteCommand(0xc481);   LCD_WriteData(0x83);		//source driver setting

LCD_WriteCommand(0xc1a1);   LCD_WriteData(0x0E);
LCD_WriteCommand(0xb3a6);   LCD_WriteData(0x20);
LCD_WriteCommand(0xb3a7);   LCD_WriteData(0x01);
LCD_WriteCommand(0xce80);   LCD_WriteData(0x85);		// GOA VST

LCD_WriteCommand(0xce81);   LCD_WriteData(0x01); 	// GOA VST

LCD_WriteCommand(0xce82);   LCD_WriteData(0x00);		// GOA VST	

LCD_WriteCommand(0xce83);   LCD_WriteData(0x84);		// GOA VST
LCD_WriteCommand(0xce84);   LCD_WriteData(0x01);		// GOA VST
LCD_WriteCommand(0xce85);   LCD_WriteData(0x00);		// GOA VST

LCD_WriteCommand(0xcea0);   LCD_WriteData(0x18);		// GOA CLK
LCD_WriteCommand(0xcea1);   LCD_WriteData(0x04);		// GOA CLK
LCD_WriteCommand(0xcea2);   LCD_WriteData(0x03);		// GOA CLK 
LCD_WriteCommand(0xcea3);   LCD_WriteData(0x39);		// GOA CLK 
LCD_WriteCommand(0xcea4);   LCD_WriteData(0x00);		// GOA CLK 
LCD_WriteCommand(0xcea5);   LCD_WriteData(0x00);		// GOA CLK 
LCD_WriteCommand(0xcea6);   LCD_WriteData(0x00);		// GOA CLK
LCD_WriteCommand(0xcea7);   LCD_WriteData(0x18);		// GOA CLK 
LCD_WriteCommand(0xcea8);   LCD_WriteData(0x03);		// GOA CLK
LCD_WriteCommand(0xcea9);   LCD_WriteData(0x03);		// GOA CLK 
LCD_WriteCommand(0xceaa);   LCD_WriteData(0x3a);		// GOA CLK
LCD_WriteCommand(0xceab);   LCD_WriteData(0x00);		// GOA CLK 
LCD_WriteCommand(0xceac);   LCD_WriteData(0x00);		// GOA CLK 
LCD_WriteCommand(0xcead);   LCD_WriteData(0x00);		// GOA CLK 
LCD_WriteCommand(0xceb0);   LCD_WriteData(0x18);		// GOA CLK
LCD_WriteCommand(0xceb1);   LCD_WriteData(0x02);		// GOA CLK 
LCD_WriteCommand(0xceb2);   LCD_WriteData(0x03); 		// GOA CLK
LCD_WriteCommand(0xceb3);   LCD_WriteData(0x3b);		// GOA CLK 
LCD_WriteCommand(0xceb4);   LCD_WriteData(0x00);		// GOA CLK 
LCD_WriteCommand(0xceb5);   LCD_WriteData(0x00);		// GOA CLK 
LCD_WriteCommand(0xceb6);   LCD_WriteData(0x00);		// GOA CLK
LCD_WriteCommand(0xceb7);   LCD_WriteData(0x18);		// GOA CLK
LCD_WriteCommand(0xceb8);   LCD_WriteData(0x01);		// GOA CLK 
LCD_WriteCommand(0xceb9);   LCD_WriteData(0x03);		// GOA CLK 
LCD_WriteCommand(0xceba);   LCD_WriteData(0x3c);		// GOA CLK 
LCD_WriteCommand(0xcebb);   LCD_WriteData(0x00);		// GOA CLK 
LCD_WriteCommand(0xcebc);   LCD_WriteData(0x00);		// GOA CLK 
LCD_WriteCommand(0xcebd);   LCD_WriteData(0x00);		// GOA CLK
LCD_WriteCommand(0xcfc0);   LCD_WriteData(0x01);		// GOA ECLK 
LCD_WriteCommand(0xcfc1);   LCD_WriteData(0x01);		// GOA ECLK
LCD_WriteCommand(0xcfc2);   LCD_WriteData(0x20); 		// GOA ECLK

LCD_WriteCommand(0xcfc3);   LCD_WriteData(0x20); 		// GOA ECLK

LCD_WriteCommand(0xcfc4);   LCD_WriteData(0x00); 		// GOA ECLK

LCD_WriteCommand(0xcfc5);   LCD_WriteData(0x00); 		// GOA ECLK

LCD_WriteCommand(0xcfc6);   LCD_WriteData(0x01); 		// GOA other options

LCD_WriteCommand(0xcfc7);   LCD_WriteData(0x00); 
   		
// GOA signal toggle option setting

LCD_WriteCommand(0xcfc8);   LCD_WriteData(0x00); 		//GOA signal toggle option setting
LCD_WriteCommand(0xcfc9);   LCD_WriteData(0x00); 
   
//GOA signal toggle option setting

LCD_WriteCommand(0xcfd0);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb80);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb81);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb82);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb83);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb84);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb85);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb86);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb87);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb88);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb89);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb90);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb91);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb92);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb93);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb94);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb95);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb96);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb97);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb98);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb99);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb9a);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb9b);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb9c);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb9d);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcb9e);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcba0);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcba1);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcba2);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcba3);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcba4);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcba5);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcba6);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcba7);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcba8);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcba9);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbaa);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbab);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbac);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbad);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbae);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbb0);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbb1);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbb2);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbb3);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbb4);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbb5);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbb6);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbb7);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbb8);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbb9);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbc0);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbc1);   LCD_WriteData(0x04);
LCD_WriteCommand(0xcbc2);   LCD_WriteData(0x04);
LCD_WriteCommand(0xcbc3);   LCD_WriteData(0x04);
LCD_WriteCommand(0xcbc4);   LCD_WriteData(0x04);
LCD_WriteCommand(0xcbc5);   LCD_WriteData(0x04);
LCD_WriteCommand(0xcbc6);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbc7);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbc8);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbc9);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbca);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbcb);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbcc);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbcd);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbce);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbd0);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbd1);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbd2);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbd3);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbd4);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbd5);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbd6);   LCD_WriteData(0x04);
LCD_WriteCommand(0xcbd7);   LCD_WriteData(0x04);
LCD_WriteCommand(0xcbd8);   LCD_WriteData(0x04);
LCD_WriteCommand(0xcbd9);   LCD_WriteData(0x04);
LCD_WriteCommand(0xcbda);   LCD_WriteData(0x04);
LCD_WriteCommand(0xcbdb);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbdc);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbdd);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbde);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbe0);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbe1);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbe2);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbe3);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbe4);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbe5);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbe6);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbe7);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbe8);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbe9);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcbf0);   LCD_WriteData(0xFF);
LCD_WriteCommand(0xcbf1);   LCD_WriteData(0xFF);
LCD_WriteCommand(0xcbf2);   LCD_WriteData(0xFF);
LCD_WriteCommand(0xcbf3);   LCD_WriteData(0xFF);
LCD_WriteCommand(0xcbf4);   LCD_WriteData(0xFF);
LCD_WriteCommand(0xcbf5);   LCD_WriteData(0xFF);
LCD_WriteCommand(0xcbf6);   LCD_WriteData(0xFF);
LCD_WriteCommand(0xcbf7);   LCD_WriteData(0xFF);
LCD_WriteCommand(0xcbf8);   LCD_WriteData(0xFF);
LCD_WriteCommand(0xcbf9);   LCD_WriteData(0xFF);
LCD_WriteCommand(0xcc80);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcc81);   LCD_WriteData(0x26);
LCD_WriteCommand(0xcc82);   LCD_WriteData(0x09);
LCD_WriteCommand(0xcc83);   LCD_WriteData(0x0B);
LCD_WriteCommand(0xcc84);   LCD_WriteData(0x01);
LCD_WriteCommand(0xcc85);   LCD_WriteData(0x25);
LCD_WriteCommand(0xcc86);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcc87);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcc88);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcc89);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcc90);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcc91);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcc92);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcc93);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcc94);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcc95);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcc96);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcc97);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcc98);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcc99);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcc9a);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcc9b);   LCD_WriteData(0x26);
LCD_WriteCommand(0xcc9c);   LCD_WriteData(0x0A);
LCD_WriteCommand(0xcc9d);   LCD_WriteData(0x0C);
LCD_WriteCommand(0xcc9e);   LCD_WriteData(0x02);
LCD_WriteCommand(0xcca0);   LCD_WriteData(0x25);
LCD_WriteCommand(0xcca1);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcca2);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcca3);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcca4);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcca5);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcca6);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcca7);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcca8);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcca9);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccaa);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccab);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccac);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccad);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccae);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccb0);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccb1);   LCD_WriteData(0x25);
LCD_WriteCommand(0xccb2);   LCD_WriteData(0x0C);
LCD_WriteCommand(0xccb3);   LCD_WriteData(0x0A);
LCD_WriteCommand(0xccb4);   LCD_WriteData(0x02);
LCD_WriteCommand(0xccb5);   LCD_WriteData(0x26);
LCD_WriteCommand(0xccb6);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccb7);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccb8);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccb9);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccc0);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccc1);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccc2);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccc3);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccc4);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccc5);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccc6);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccc7);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccc8);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccc9);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccca);   LCD_WriteData(0x00);
LCD_WriteCommand(0xcccb);   LCD_WriteData(0x25);
LCD_WriteCommand(0xcccc);   LCD_WriteData(0x0B);
LCD_WriteCommand(0xcccd);   LCD_WriteData(0x09);
LCD_WriteCommand(0xccce);   LCD_WriteData(0x01);
LCD_WriteCommand(0xccd0);   LCD_WriteData(0x26);
LCD_WriteCommand(0xccd1);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccd2);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccd3);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccd4);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccd5);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccd6);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccd7);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccd8);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccd9);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccda);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccdb);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccdc);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccdd);   LCD_WriteData(0x00);
LCD_WriteCommand(0xccde);   LCD_WriteData(0x00);
LCD_WriteCommand(0x3A00);   LCD_WriteData(0x55);

LCD_WriteCommand(0x1100);
   HAL_Delay(50);
LCD_WriteCommand(0x2900);
   HAL_Delay(50);
LCD_WriteCommand(0x2C00);
LCD_WriteCommand(0x2A00);  LCD_WriteData(0x00);
LCD_WriteCommand(0x2A01);  LCD_WriteData(0x00);
LCD_WriteCommand(0x2A02);  LCD_WriteData(0x01);
LCD_WriteCommand(0x2A03);  LCD_WriteData(0xe0);
LCD_WriteCommand(0x2B00);  LCD_WriteData(0x00);
LCD_WriteCommand(0x2B01);  LCD_WriteData(0x00);
LCD_WriteCommand(0x2B02);  LCD_WriteData(0x03);
LCD_WriteCommand(0x2B03);  LCD_WriteData(0x20);
	
	LCD_SetConfig();
	HAL_Delay(10);
	LCD_Fill(0xffff);
}
//LCD configuration set
void LCD_SetConfig(void)
{
	if(!LCD_DIR)
	{
		lcdcfg.direction = 1;
		lcdcfg.height = LCD_WIDTH;
		lcdcfg.width = LCD_HEIGHT;
	}
	else
	{
		lcdcfg.direction = 0;
		lcdcfg.height = LCD_HEIGHT;
		lcdcfg.width = LCD_WIDTH;
	}
}
//LCD fill pure color, in the format of RGB565 (RRRRRGGGGGGBBBBB)
void LCD_Fill(uint16_t color)
{
	uint32_t i;
	LCD_SetWindowSize(0, 0, lcdcfg.width, lcdcfg.height);
	//HAL_DMA2D_Start(&hdma2d, color, LCD_FMC_DAT_ADDR, lcdcfg.width, lcdcfg.height);	
	for(i = 0; i < lcdcfg.width * lcdcfg.height ;i++)
	{
		LCD_WriteData(color);
	}
}

//Set display window size
void LCD_SetWindowSize(uint16_t start_x, uint16_t start_y, uint16_t end_x, uint16_t end_y)
{
	LCD_WriteCommand(0x2a00);
	LCD_WriteData(start_x>>8);
	LCD_WriteCommand(0x2a01);
	LCD_WriteData(start_x);
	
	LCD_WriteCommand(0x2a02);
	LCD_WriteData(end_x>>8);
	LCD_WriteCommand(0x2a03);
	LCD_WriteData(end_x);
	
	LCD_WriteCommand(0x2b00);
	LCD_WriteData(start_y>>8);
	LCD_WriteCommand(0x2b01);
	LCD_WriteData(start_y);
	
	LCD_WriteCommand(0x2b02);
	LCD_WriteData(end_y>>8);
	LCD_WriteCommand(0x2b03);
	LCD_WriteData(end_y);
	
	LCD_PrepareWriteDisplayData();
}
//Prepare to write display data
void LCD_PrepareWriteDisplayData(void)
{
	LCD_WriteCommand(0x2c00);
}
//Set cursor position
void LCD_SetCursorPos(uint16_t pos_x, uint16_t pos_y)
{
	LCD_SetWindowSize(pos_x, pos_x, pos_y, pos_y);
}
//On/off backlight
void LCD_SetBacklight(uint8_t stat)
{
	if(stat) HAL_GPIO_WritePin(LCD_BL_PORT, LCD_BL, GPIO_PIN_SET);
	else HAL_GPIO_WritePin(LCD_BL_PORT, LCD_BL, GPIO_PIN_RESET);
}

