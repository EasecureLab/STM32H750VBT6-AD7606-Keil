//-----------------------------------------------------------------
// ��������:
// ��	 2.8��/4.3��TFTҺ����ʾ����������  
// ��������: ���ǵ���
// ��ʼ����: 2020-11-11
// �������: 2020-11-11
// �޸�����:  
// ��ǰ�汾: V1.0
// ��ʷ�汾:
//	- V1.0��4.3��/2.8�� TFTҺ����ʾ  
// ���Թ���: ����STM32H750���İ塢LZE_ST_LINK2��4.3��/2.8�� TFTҺ����
// ˵������: 
//
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// ͷ�ļ�����
//-----------------------------------------------------------------
#include "lcd.h"
#include "stdlib.h"
#include "font.h"  
#include "delay.h"	 
//-----------------------------------------------------------------
SRAM_HandleTypeDef SRAM_Handler;    // SRAM���(���ڿ���LCD)

u32 POINT_COLOR=0xFF000000;		// LCDĬ�ϻ�����ɫ
u32 BACK_COLOR =0xFFFFFFFF;  	// LCDĬ�ϱ���ɫ 
  
_lcd_dev lcddev;	// ����LCD��Ҫ����
//-----------------------------------------------------------------
// void LCD_WR_REG(vu16 regval)
//-----------------------------------------------------------------
//
// ��������: д�Ĵ�������
// ��ڲ���: vu16 regval���Ĵ���ֵ
// ���ز���: ��
// ע������: ��
//					 
//-----------------------------------------------------------------
void LCD_WR_REG(vu16 regval)
{   
	regval=regval;			// ʹ��-O2�Ż���ʱ��,����������ʱ
	LCD->LCD_REG=regval;// д��Ҫд�ļĴ������	 
}

//-----------------------------------------------------------------
// void LCD_WR_DATA(vu16 data)
//-----------------------------------------------------------------
//
// ��������: дLCD���ݺ���
// ��ڲ���: vu16 data��д�������
// ���ز���: ��
// ע������: ��
//					 
//-----------------------------------------------------------------
void LCD_WR_DATA(vu16 data)
{	  
	data=data;			// ʹ��-O2�Ż���ʱ��,����������ʱ
	LCD->LCD_RAM=data;		 
}

//-----------------------------------------------------------------
// u16 LCD_RD_DATA(void)
//-----------------------------------------------------------------
//
// ��������: ��LCD���ݺ���
// ��ڲ���: ��
// ���ز���: vu16 ram����ȡ������
// ע������: ��
//					 
//-----------------------------------------------------------------
u16 LCD_RD_DATA(void)
{
	vu16 ram;			// ��ֹ���Ż�
	ram=LCD->LCD_RAM;	
	return ram;	 
}					   

//-----------------------------------------------------------------
// void LCD_WriteReg(u16 LCD_Reg,u16 LCD_RegValue)
//-----------------------------------------------------------------
//
// ��������: ��Ĵ���д������
// ��ڲ���: u16 LCD_Reg���Ĵ�����ַ
//					 u16 LCD_RegValue��Ҫд�������
// ���ز���: ��
// ע������: ��
//					 
//-----------------------------------------------------------------
void LCD_WriteReg(u16 LCD_Reg,u16 LCD_RegValue)
{	
	LCD->LCD_REG = LCD_Reg;			// д��Ҫд�ļĴ������	 
	LCD->LCD_RAM = LCD_RegValue;// д������	    		 
}	   

//-----------------------------------------------------------------
// u16 LCD_ReadReg(u16 LCD_Reg)
//-----------------------------------------------------------------
//
// ��������: ���Ĵ���
// ��ڲ���: u16 LCD_Reg���Ĵ�����ַ
// ���ز���: ����������
// ע������: ��
//					 
//-----------------------------------------------------------------
u16 LCD_ReadReg(u16 LCD_Reg)
{										   
	LCD_WR_REG(LCD_Reg);		// д��Ҫ���ļĴ������
	delay_us(5);		  
	return LCD_RD_DATA();		// ���ض�����ֵ
}   

//-----------------------------------------------------------------
// void LCD_WriteRAM_Prepare(void)
//-----------------------------------------------------------------
//
// ��������: дGRAM
// ��ڲ���: ��
// ���ز���: ��
// ע������: ��
//					 
//-----------------------------------------------------------------
void LCD_WriteRAM_Prepare(void)
{
 	LCD->LCD_REG=lcddev.wramcmd;	// дGRAM�Ĵ�����ַ  
}	 

//-----------------------------------------------------------------
// void LCD_WriteRAM(u16 RGB_Code)
//-----------------------------------------------------------------
//
// ��������: LCDдGRAM
// ��ڲ���: u16 RGB_Code:��ɫֵ
// ���ز���: ��
// ע������: ��
//					 
//-----------------------------------------------------------------
void LCD_WriteRAM(u16 RGB_Code)
{							    
	LCD->LCD_RAM = RGB_Code;// дʮ��λGRAM
}

//-----------------------------------------------------------------
// u16 LCD_BGR2RGB(u16 c)
//-----------------------------------------------------------------
//
// ��������: RRRRRGGGGGGBBBBB ��Ϊ BBBBBGGGGGGRRRRR ��ʽ
// ��ڲ���: u16 c��GBR��ʽ����ɫֵ
// ���ز���: u16 rgb��RGB��ʽ����ɫֵ
// ע������: ��
//					 
//-----------------------------------------------------------------
u16 LCD_BGR2RGB(u16 c)
{
	u16  r,g,b,rgb;   
	b=(c>>0)&0x1f;
	g=(c>>5)&0x3f;
	r=(c>>11)&0x1f;	 
	rgb=(b<<11)+(g<<5)+(r<<0);		 
	return(rgb);
} 

//-----------------------------------------------------------------
// void opt_delay(u8 i)
//-----------------------------------------------------------------
//
// ��������: ��mdk -O1ʱ���Ż�ʱ��Ҫ����
// ��ڲ���: u8 i����ʱ
// ���ز���: ��
// ע������: ��
//					 
//-----------------------------------------------------------------
void opt_delay(u8 i)
{
	while(i--);
}

//-----------------------------------------------------------------
// u32 LCD_ReadPoint(u16 x,u16 y)
//-----------------------------------------------------------------
//
// ��������: ��ȡ��ĳ�����ɫֵ	
// ��ڲ���: u16 x��x����ֵ
//					 u16 y��y����ֵ
// ���ز���: �˵����ɫ
// ע������: �ú���ֻ������TFTLCD 0x5510
//					 
//-----------------------------------------------------------------
u32 LCD_ReadPoint(u16 x,u16 y)
{
 	u16 r=0,g=0,b=0;
	if(x>=lcddev.width||y>=lcddev.height)
		return 0;								// �����˷�Χ,ֱ�ӷ���
	LCD_SetCursor(x,y);	    
	LCD_WR_REG(0X2E00);				// 0x5510 ���Ͷ�GRAMָ��
 	r=LCD_RD_DATA();					// dummy Read	   
	opt_delay(2);	  
 	r=LCD_RD_DATA();  		  	// ʵ��������ɫ
	opt_delay(2);	  
	b=LCD_RD_DATA(); 
	g=r&0XFF;		
	g<<=8; 
	return (((r>>11)<<11)|((g>>10)<<5)|(b>>11));	
}	

//-----------------------------------------------------------------
// void LCD_DisplayOn(void)
//-----------------------------------------------------------------
//
// ��������: LCD������ʾ
// ��ڲ���: ��
// ���ز���: ��
// ע������: ��
//					 
//-----------------------------------------------------------------
void LCD_DisplayOn(void)
{	
	if(lcddev.id==ST7789V_ID)
		LCD_WR_REG(0x28);
	else if(lcddev.id==SPFD5408_ID)
		LCD_WriteReg(LCD_REG_7, 0x00);
	else if(lcddev.id==NT35510_ID)
		LCD_WR_REG(0X2900);	
}	

//-----------------------------------------------------------------
// void LCD_DisplayOff(void)
//-----------------------------------------------------------------
//
// ��������: LCD�ر���ʾ
// ��ڲ���: ��
// ���ز���: ��
// ע������: ��
//					 
//-----------------------------------------------------------------
void LCD_DisplayOff(void)
{	 
	if(lcddev.id==ST7789V_ID)
		LCD_WR_REG(0x29);
	else if(lcddev.id==SPFD5408_ID)
		LCD_WriteReg(LCD_REG_7, 0x0173);
	else if(lcddev.id==NT35510_ID)
		LCD_WR_REG(0X2800);	//�ر���ʾ
}   

//-----------------------------------------------------------------
// void LCD_Display_Dir(u8 dir)
//-----------------------------------------------------------------
//
// ��������: ����LCD��ʾ����
// ��ڲ���: u8 dir��0,������1,����
// ���ز���: ��
// ע������: ��
//					 
//-----------------------------------------------------------------
void LCD_Display_Dir(u8 dir)
{
	lcddev.dir = dir;
  if ( dir == DISPLAY_DIR_L )
  {
		if ( lcddev.id == ST7789V_ID )
    {
      lcddev.width     = 320;                              // ��ʾ���ڿ��
      lcddev.height    = 240;                              // ��ʾ���ڸ߶�
      lcddev.wramcmd   = 0X2C;                             // ��ʾ�Ĵ�������
      lcddev.setxcmd   = 0x2A;                             // X������Ĵ�������
      lcddev.setycmd   = 0x2B;                             // Y������Ĵ�������
      lcddev.scan      = ((0<<7)|(1<<6)|(1<<5));           // MY, MX, MV
    }
    else if ( lcddev.id == SPFD5408_ID )
    {
      lcddev.width     = 320;                              // ��ʾ���ڿ��
      lcddev.height    = 240;                              // ��ʾ���ڸ߶�
      lcddev.wramcmd   = 0X22;
      lcddev.setxcmd   = 0x20;
      lcddev.setycmd   = 0x21;
      lcddev.scan      = 0x1000 | ((0<<5)|(0<<4)|(1<<3));   // MY, MX, MV
    }
    else if ( lcddev.id == NT35510_ID )
    {
      lcddev.width     = 800;                              // ��ʾ���ڿ��
      lcddev.height    = 480;                              // ��ʾ���ڸ߶�
      lcddev.wramcmd   = 0X2C00;                           // ��ʾ�Ĵ�������
      lcddev.setxcmd   = 0x2A00;                           // X������Ĵ�������
      lcddev.setycmd   = 0x2B00;                           // Y������Ĵ�������
			lcddev.scan      = ((1<<7)|(0<<6)|(1<<5));           // MY, MX, MV
		}
  }
  else if ( dir == DISPLAY_DIR_R )
  {
    if ( lcddev.id == ST7789V_ID )
    {
      lcddev.width     = 320;
      lcddev.height    = 240;
      lcddev.wramcmd   = 0X2C;
      lcddev.setxcmd   = 0x2A;
      lcddev.setycmd   = 0x2B;
      lcddev.scan      = ((1<<7)|(0<<6)|(1<<5));           // MY, MX, MV
    }
    else if ( lcddev.id == SPFD5408_ID )
    {
      lcddev.width     = 320;
      lcddev.height    = 240;
      lcddev.wramcmd   = 0X22;
      lcddev.setxcmd   = 0x20;
      lcddev.setycmd   = 0x21;
      lcddev.scan      = 0x1000 | ((1<<5)|(1<<4)|(1<<3));  // MY, MX, MV
    }
    else if ( lcddev.id == NT35510_ID )
    {
      lcddev.width     = 800;                              // ��ʾ���ڿ��
      lcddev.height    = 480;                              // ��ʾ���ڸ߶�
      lcddev.wramcmd   = 0X2C00;                           // ��ʾ�Ĵ�������
      lcddev.setxcmd   = 0x2A00;                           // X������Ĵ�������
      lcddev.setycmd   = 0x2B00;                           // Y������Ĵ�������
      lcddev.scan      = ((0<<7)|(1<<6)|(1<<5));           // MY, MX, MV
    }
  }
  else if ( dir == DISPLAY_DIR_U )
  {
    if ( lcddev.id == ST7789V_ID )
    {
      lcddev.width     = 240;
      lcddev.height    = 320;
      lcddev.wramcmd   = 0X2C;
      lcddev.setxcmd   = 0x2A;
      lcddev.setycmd   = 0x2B;
      lcddev.scan      = ((1<<7)|(1<<6)|(0<<5));           // MY, MX, MV
    }
    else if ( lcddev.id == SPFD5408_ID )
    {
      lcddev.width     = 240;
      lcddev.height    = 320;
      lcddev.wramcmd   = 0X22;
      lcddev.setxcmd   = 0x20;
      lcddev.setycmd   = 0x21;
      lcddev.scan      = 0x1000 | ((1<<5)|(0<<4)|(0<<3));  // MY, MX, MV
    }
    else if ( lcddev.id == NT35510_ID )
    {
      lcddev.width     = 480;                              // ��ʾ���ڿ��
      lcddev.height    = 800;                              // ��ʾ���ڸ߶�
      lcddev.wramcmd   = 0X2C00;                           // ��ʾ�Ĵ�������
      lcddev.setxcmd   = 0x2A00;                           // X������Ĵ�������
      lcddev.setycmd   = 0x2B00;                           // Y������Ĵ�������
      lcddev.scan      = ((1<<7)|(1<<6)|(0<<5));           // MY, MX, MV
    }
  }
  else                                                              //DISPLAY_DIR_D
  {
    if ( lcddev.id == ST7789V_ID )
    {
      lcddev.width     = 240;
      lcddev.height    = 320;
      lcddev.wramcmd   = 0X2C;
      lcddev.setxcmd   = 0x2A;
      lcddev.setycmd   = 0x2B;
      lcddev.scan      = ((0<<7)|(0<<6)|(0<<5));           // MY, MX, MV
    }
    else if ( lcddev.id == SPFD5408_ID )
    {
      lcddev.width     = 240;
      lcddev.height    = 320;
      lcddev.wramcmd   = 0X22;
      lcddev.setxcmd   = 0x20;
      lcddev.setycmd   = 0x21;
      lcddev.scan      = 0x1000 | ((0<<5)|(1<<4)|(0<<3));  // MY, MX, MV
    }
    else if ( lcddev.id == NT35510_ID )
    {
      lcddev.width     = 480;                              // ��ʾ���ڿ��
      lcddev.height    = 800;                              // ��ʾ���ڸ߶�
      lcddev.wramcmd   = 0X2C00;                           // ��ʾ�Ĵ�������
      lcddev.setxcmd   = 0x2A00;                           // X������Ĵ�������
      lcddev.setycmd   = 0x2B00;                           // Y������Ĵ�������
      lcddev.scan      = ((0<<7)|(0<<6)|(0<<5));           // MY, MX, MV
    }
  }
}

//-----------------------------------------------------------------
// void LCD_SetCursor(u16 Xpos, u16 Ypos)
//-----------------------------------------------------------------
//
// ��������: ���ù��λ��(��RGB����Ч)
// ��ڲ���: u16 Xpos��X������
//					 u16 Ypos��Y������
// ���ز���: ��
// ע������: ��
//					 
//-----------------------------------------------------------------
void LCD_SetCursor(u16 Xpos, u16 Ypos)
{
	if(lcddev.id == ST7789V_ID)                    // �Ĵ���ÿ��д�� 8bit, 16bit �����������д��
  {
    LCD_WR_REG ( lcddev.setxcmd );
    LCD_WR_DATA ( Xpos >> 8 );       LCD_WR_DATA ( Xpos & 0XFF );
    LCD_WR_REG ( lcddev.setycmd );
    LCD_WR_DATA ( Ypos >> 8 );       LCD_WR_DATA ( Ypos & 0XFF );
  }
  else if(lcddev.id == SPFD5408_ID)              // �Ĵ���ÿ��д�� 16bit
  {
    LCD_WriteReg ( lcddev.setxcmd, Xpos );
    LCD_WriteReg ( lcddev.setycmd, Ypos );
  }
  else if(lcddev.id == NT35510_ID)               // �Ĵ���ÿ��д�� 8bit, 16bit �����������д��
  {
    LCD_WR_REG ( lcddev.setxcmd + 0 );    LCD_WR_DATA ( Xpos >> 8 );       
    LCD_WR_REG ( lcddev.setxcmd + 1 );    LCD_WR_DATA ( Xpos & 0XFF );
    LCD_WR_REG ( lcddev.setycmd + 0 );    LCD_WR_DATA ( Ypos >> 8 );
    LCD_WR_REG ( lcddev.setycmd + 1 );    LCD_WR_DATA ( Ypos & 0XFF );
  }
} 

//-----------------------------------------------------------------
// void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height)
//-----------------------------------------------------------------
//
// ��������: ���ô���(��RGB����Ч),���Զ����û������굽�������Ͻ�(sx,sy).
// ��ڲ���: u16 sx��������ʼX����
//					 u16 sy��������ʼY����
//					 u16 width�����ڿ��
//					 u16 height�����ڸ߶�
// ���ز���: ��
// ע������: width,height:���ڿ�Ⱥ͸߶�,�������0!!
//					 
//-----------------------------------------------------------------
void LCD_Set_Window(u16 sx,u16 sy,u16 width,u16 height)
{ 
	uint16_t X_Start = 0, X_End = 0; 
  uint16_t Y_Start = 0, Y_End = 0; 
   
  uint16_t Xpos_Start = 0;
  uint16_t Ypos_Start = 0;
	if ( lcddev.id == ST7789V_ID )
  {
    X_Start     = sx;                // Horizontal GRAM Start Address
    X_End       = sx + width - 1;    // Horizontal GRAM End Address
    Y_Start     = sy;                // Vertical GRAM Start Address
    Y_End       = sy + height - 1;   // Vertical GRAM End Address

    Xpos_Start  = X_Start;
    Ypos_Start  = Y_Start;

    /* Horizontal GRAM Start Address */
    LCD_WR_REG(lcddev.setxcmd);
    LCD_WR_DATA ( X_Start >> 8 );                 LCD_WR_DATA ( X_Start & 0xFF );

    /* Horizontal GRAM End Address */
    LCD_WR_DATA ( X_End >> 8 );  LCD_WR_DATA ( X_End & 0XFF );

    /* Vertical GRAM Start Address */
    LCD_WR_REG(lcddev.setycmd);
    LCD_WR_DATA ( Y_Start >> 8 );                 LCD_WR_DATA ( Y_Start & 0xFF );

    /* Vertical GRAM End Address */
    LCD_WR_DATA ( Y_End >> 8); LCD_WR_DATA ( Y_End & 0XFF );

  }
	else if ( lcddev.id == SPFD5408_ID )
	{
		if ( lcddev.dir == DISPLAY_DIR_L )
		{
			X_Start     = lcddev.height - sy - height;   // Horizontal GRAM Start Address
			X_End       = lcddev.height - sy - 1;        // Horizontal GRAM End Address
			Y_Start     = lcddev.width  - sx - width;    // Vertical GRAM Start Address
			Y_End       = lcddev.width  - sx - 1;        // Vertical GRAM End Address 

			Xpos_Start  = X_End;
			Ypos_Start  = Y_End;
		}
		else if ( lcddev.dir == DISPLAY_DIR_R ) 
		{
			X_Start     = sy;                            // Horizontal GRAM Start Address
			X_End       = sy + height - 1;               // Horizontal GRAM End Address
			Y_Start     = sx;                            // Vertical GRAM Start Address
			Y_End       = sx + width - 1;                // Vertical GRAM End Address 

			Xpos_Start  = X_Start;
			Ypos_Start  = Y_Start;
		}
		else if ( lcddev.dir == DISPLAY_DIR_U )
		{
			X_Start     = lcddev.width - sx - width;     // Horizontal GRAM Start Address
			X_End       = lcddev.width - sx - 1;         // Horizontal GRAM End Address
			Y_Start     = sy;                            // Vertical GRAM Start Address
			Y_End       = sy + height;                   // Vertical GRAM End Address 

			Xpos_Start  = X_End;
			Ypos_Start  = Y_Start;
		}
		else 
		{
			X_Start     = sx;                            // Horizontal GRAM Start Address
			X_End       = sx + width - 1;                // Horizontal GRAM End Address
			Y_Start     = lcddev.height - sy - height;   // Vertical GRAM Start Address
			Y_End       = lcddev.height - sy - 1;        // Vertical GRAM End Address 

			Xpos_Start  = X_Start;
			Ypos_Start  = Y_End;
		}
		LCD_WriteReg ( LCD_REG_80, X_Start ); 
		LCD_WriteReg ( LCD_REG_81, X_End );
		LCD_WriteReg ( LCD_REG_82, Y_Start );
		LCD_WriteReg ( LCD_REG_83, Y_End );
	}
	else if(lcddev.id == NT35510_ID)
  {
    X_Start     = sx;                              // Horizontal GRAM Start Address
    X_End       = sx + width - 1;                  // Horizontal GRAM End Address
    Y_Start     = sy;                              // Vertical GRAM Start Address
    Y_End       = sy + height - 1;                 // Vertical GRAM End Address

    Xpos_Start  = X_Start;
    Ypos_Start  = Y_Start;

    /* Horizontal GRAM Start Address */
    LCD_WR_REG(lcddev.setxcmd + 0);    LCD_WR_DATA ( X_Start >> 8 );
    LCD_WR_REG(lcddev.setxcmd + 1);    LCD_WR_DATA ( X_Start & 0xFF );

    /* Horizontal GRAM End Address */
    LCD_WR_REG(lcddev.setxcmd + 2);    LCD_WR_DATA ( X_End >> 8 );  
    LCD_WR_REG(lcddev.setxcmd + 3);    LCD_WR_DATA ( X_End & 0XFF );

    /* Vertical GRAM Start Address */
    LCD_WR_REG(lcddev.setycmd + 0);    LCD_WR_DATA ( Y_Start >> 8 );
    LCD_WR_REG(lcddev.setycmd + 1);    LCD_WR_DATA ( Y_Start & 0xFF );

    /* Vertical GRAM End Address */
    LCD_WR_REG(lcddev.setycmd + 2);    LCD_WR_DATA ( Y_End >> 8); 
    LCD_WR_REG(lcddev.setycmd + 3);    LCD_WR_DATA ( Y_End & 0XFF );
  }
  LCD_SetCursor(Xpos_Start, Ypos_Start);
}



//-----------------------------------------------------------------
// void HAL_SRAM_MspInit(SRAM_HandleTypeDef *hsram)
//-----------------------------------------------------------------
//
// ��������: SRAM�ײ�������ʱ��ʹ�ܣ����ŷ���
// ��ڲ���: SRAM_HandleTypeDef *hsram��SRAM���
// ���ز���: ��
// ע������: �˺����ᱻHAL_SRAM_Init()����
//
//					 LCD_D0  -> PD14				LCD_RS  -> PD11
//					 LCD_D1  -> PD15				LCD_RST -> PH4
//					 LCD_D2  -> PD0					LCD_LED -> PB8
//					 LCD_D3  -> PD1					LCD_NOE -> PD4
//					 LCD_D4  -> PE7					LCD_NWE -> PD5
//					 LCD_D5  -> PE8					LCD_CS  -> PD7
//					 LCD_D6  -> PE9					
//					 LCD_D7  -> PE10
//					 LCD_D8  -> PE11
//					 LCD_D9  -> PE12
//					 LCD_D10 -> PE13
//					 LCD_D11 -> PE14
//					 LCD_D12 -> PE15
//					 LCD_D13 -> PD8
//					 LCD_D14 -> PD9
//					 LCD_D15 -> PD10
//
//-----------------------------------------------------------------
void HAL_SRAM_MspInit(SRAM_HandleTypeDef *hsram)
{
  GPIO_InitTypeDef GPIO_Initure;
	
	__HAL_RCC_FMC_CLK_ENABLE();				// ʹ��FMCʱ��
	__HAL_RCC_GPIOD_CLK_ENABLE();			// ʹ��GPIODʱ��
	__HAL_RCC_GPIOE_CLK_ENABLE();			// ʹ��GPIOEʱ��
  __HAL_RCC_FMC_CLK_ENABLE();				// ʹ��FMCʱ��
	
	GPIO_Initure.Pin=GPIO_PIN_13;           // PD13,�������
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  // �������
	GPIO_Initure.Pull=GPIO_NOPULL;          // ����������
	GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;  // ����
	HAL_GPIO_Init(GPIOD,&GPIO_Initure);
	
	GPIO_Initure.Pin=GPIO_PIN_12;           // PD12,��λ
	GPIO_Initure.Mode=GPIO_MODE_OUTPUT_PP;  // �������
	GPIO_Initure.Pull=GPIO_NOPULL;          // ����������
	GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH; // ����
	HAL_GPIO_Init(GPIOD,&GPIO_Initure); 
	
	// ��ʼ��PD0,1,4,5,7,8,9,10,11,14,15
	GPIO_Initure.Pin=GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_7|GPIO_PIN_8|
                     GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|GPIO_PIN_14|GPIO_PIN_15;
	GPIO_Initure.Mode=GPIO_MODE_AF_PP; 		// ����
	GPIO_Initure.Pull=GPIO_PULLUP;				// ����
	GPIO_Initure.Speed=GPIO_SPEED_FREQ_VERY_HIGH;// ����
	GPIO_Initure.Alternate=GPIO_AF12_FMC;	// ����ΪFMC
	HAL_GPIO_Init(GPIOD,&GPIO_Initure);
	
	// ��ʼ��PE7,8,9,10,11,12,13,14,15
	GPIO_Initure.Pin=GPIO_PIN_7|GPIO_PIN_8|GPIO_PIN_9|GPIO_PIN_10|GPIO_PIN_11|
                     GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14|GPIO_PIN_15;
	HAL_GPIO_Init(GPIOE,&GPIO_Initure);
}

//-----------------------------------------------------------------
// void LCD_Init(void)
//-----------------------------------------------------------------
//
// ��������: ��ʼ��LCD
// ��ڲ���: ��
// ���ز���: ��
// ע������: ��
//					 
//-----------------------------------------------------------------
void LCD_Init(void)
{
	FMC_NORSRAM_TimingTypeDef FSMC_ReadWriteTim;
	FMC_NORSRAM_TimingTypeDef FSMC_WriteTim;
	
	SRAM_Handler.Instance=FMC_NORSRAM_DEVICE;        									// BANK1
	SRAM_Handler.Extended=FMC_NORSRAM_EXTENDED_DEVICE;       
	
	SRAM_Handler.Init.NSBank=FMC_NORSRAM_BANK1;     									// ʹ��NE1
	SRAM_Handler.Init.DataAddressMux=FMC_DATA_ADDRESS_MUX_DISABLE;  	// ������������
	SRAM_Handler.Init.MemoryType=FMC_MEMORY_TYPE_SRAM;              	// SRAM
	SRAM_Handler.Init.MemoryDataWidth=FMC_NORSRAM_MEM_BUS_WIDTH_16; 	// 16λ���ݿ��
	SRAM_Handler.Init.BurstAccessMode=FMC_BURST_ACCESS_MODE_DISABLE; 	// �Ƿ�ʹ��ͻ������,����ͬ��ͻ���洢����Ч,�˴�δ�õ�
	SRAM_Handler.Init.WaitSignalPolarity=FMC_WAIT_SIGNAL_POLARITY_LOW;// �ȴ��źŵļ���,����ͻ��ģʽ����������
	SRAM_Handler.Init.WaitSignalActive=FMC_WAIT_TIMING_BEFORE_WS;   	// �洢�����ڵȴ�����֮ǰ��һ��ʱ�����ڻ��ǵȴ������ڼ�ʹ��NWAIT
	SRAM_Handler.Init.WriteOperation=FMC_WRITE_OPERATION_ENABLE;    	// �洢��дʹ��
	SRAM_Handler.Init.WaitSignal=FMC_WAIT_SIGNAL_DISABLE;           	// �ȴ�ʹ��λ,�˴�δ�õ�
	SRAM_Handler.Init.ExtendedMode=FMC_EXTENDED_MODE_ENABLE;        	// ��дʹ�ò�ͬ��ʱ��
	SRAM_Handler.Init.AsynchronousWait=FMC_ASYNCHRONOUS_WAIT_DISABLE;	// �Ƿ�ʹ��ͬ������ģʽ�µĵȴ��ź�,�˴�δ�õ�
	SRAM_Handler.Init.WriteBurst=FMC_WRITE_BURST_DISABLE;           	// ��ֹͻ��д
	SRAM_Handler.Init.ContinuousClock=FMC_CONTINUOUS_CLOCK_SYNC_ASYNC;
	
	// FSMC��ʱ����ƼĴ���
	FSMC_ReadWriteTim.AddressSetupTime=0x10;        // ��ַ����ʱ��(ADDSET)Ϊ16��HCLK 1/200M*16=5ns*16=80ns
	FSMC_ReadWriteTim.AddressHoldTime=0x01;
	FSMC_ReadWriteTim.DataSetupTime=0x4D;           // ���ݱ���ʱ��(DATAST)Ϊ77��HCLK	=5ns*77=385ns
	FSMC_ReadWriteTim.AccessMode=FMC_ACCESS_MODE_A; // ģʽA
	//FSMCдʱ����ƼĴ���
	FSMC_WriteTim.AddressSetupTime=0x05;            // ��ַ����ʱ��(ADDSET)
	FSMC_WriteTim.AddressHoldTime=0x01;
	FSMC_WriteTim.DataSetupTime=0x05;               // ���ݱ���ʱ��(DATAST)
	FSMC_WriteTim.AccessMode=FMC_ACCESS_MODE_A;     // ģʽA
	HAL_SRAM_Init(&SRAM_Handler,&FSMC_ReadWriteTim,&FSMC_WriteTim);	
	delay_ms(10); 
	LCD_RS_Clr;
	delay_ms(10); // delay 50 ms 
	LCD_RST_Set;								 	 
	delay_ms(10); 
	
	/* Read the LCD ID */
  // ���� ST7789V  ID�Ķ�ȡ
  LCD_ReadReg ( 0x04 );
  lcddev.id =   LCD_RD_DATA();                    // ��Ч����
  lcddev.id =   LCD_RD_DATA();                    // ����0x85
  lcddev.id <<= 8;
  lcddev.id |=  LCD_RD_DATA();                    // ��ȡ0x52
	
	if( lcddev.id != ST7789V_ID )                   // �����ͺŷ� ST7789V
  {
    lcddev.id = LCD_ReadReg ( 0x00 );             // ���Ի�ȡ 5408 �� ID
    
    if ( lcddev.id != SPFD5408_ID )
    {
      LCD_WR_REG ( 0xF000 );	LCD_WR_DATA ( 0x55 );
      LCD_WR_REG ( 0xF001 );	LCD_WR_DATA ( 0xAA );
      LCD_WR_REG ( 0xF002 );	LCD_WR_DATA ( 0x52 );
      LCD_WR_REG ( 0xF003 );	LCD_WR_DATA ( 0x08 );
      LCD_WR_REG ( 0xF004 );	LCD_WR_DATA ( 0x01 );
 
      LCD_ReadReg ( 0xC500 ); lcddev.id  = LCD_RD_DATA();      // ����0x55
      lcddev.id <<= 8;
      LCD_ReadReg ( 0xC501 ); lcddev.id |= LCD_RD_DATA();      // ��ȡ0x10
    }
  }
	if ( lcddev.id == ST7789V_ID )                               // ST7789V
  {
    //-------------------------------------------------------------------------------------//
    LCD_WR_REG ( 0x11 );
    delay_ms  ( 120  );                                        // Delay 120 ms
    //------------------------------display and color format setting-----------------------//
    LCD_WR_REG ( 0x36 );  LCD_WR_DATA ( 0x00 );
    LCD_WR_REG ( 0x3a );  LCD_WR_DATA ( 0x05 );
    //--------------------------------ST7789V Frame rate setting---------------------------//
    LCD_WR_REG ( 0xb2 );  LCD_WR_DATA ( 0x0c );  LCD_WR_DATA ( 0x0c );
                          LCD_WR_DATA ( 0x00 );  LCD_WR_DATA ( 0x33 );
                          LCD_WR_DATA ( 0x33 );
    LCD_WR_REG ( 0xb7 );  LCD_WR_DATA ( 0x35 );
    //---------------------------------ST7789V Power setting-------------------------------//
    LCD_WR_REG ( 0xbb );  LCD_WR_DATA ( 0x28 );
    LCD_WR_REG ( 0xc0 );  LCD_WR_DATA ( 0x2c );
    LCD_WR_REG ( 0xc2 );  LCD_WR_DATA ( 0x01 );
    LCD_WR_REG ( 0xc3 );  LCD_WR_DATA ( 0x0b );
    LCD_WR_REG ( 0xc4 );  LCD_WR_DATA ( 0x20 );
    LCD_WR_REG ( 0xc6 );  LCD_WR_DATA ( 0x0f );                // Frame Rate Control in Normal Mode
    LCD_WR_REG ( 0xd0 );  LCD_WR_DATA ( 0xa4 );  LCD_WR_DATA ( 0xa1 );
    //--------------------------------ST7789V gamma setting--------------------------------//
    LCD_WR_REG ( 0xe0 );  LCD_WR_DATA ( 0xd0 );  LCD_WR_DATA ( 0x01 );
                          LCD_WR_DATA ( 0x08 );  LCD_WR_DATA ( 0x0f );
                          LCD_WR_DATA ( 0x11 );  LCD_WR_DATA ( 0x2a );
                          LCD_WR_DATA ( 0x36 );  LCD_WR_DATA ( 0x55 );
                          LCD_WR_DATA ( 0x44 );  LCD_WR_DATA ( 0x3a );
                          LCD_WR_DATA ( 0x0b );  LCD_WR_DATA ( 0x06 );
                          LCD_WR_DATA ( 0x11 );  LCD_WR_DATA ( 0x20 );

    LCD_WR_REG ( 0xe1 );  LCD_WR_DATA ( 0xd0 );  LCD_WR_DATA ( 0x02 );
                          LCD_WR_DATA ( 0x07 );  LCD_WR_DATA ( 0x0a );
                          LCD_WR_DATA ( 0x0b );  LCD_WR_DATA ( 0x18 );
                          LCD_WR_DATA ( 0x34 );  LCD_WR_DATA ( 0x43 );
                          LCD_WR_DATA ( 0x4a );  LCD_WR_DATA ( 0x2b );
                          LCD_WR_DATA ( 0x1b );  LCD_WR_DATA ( 0x1c );
                          LCD_WR_DATA ( 0x22 );  LCD_WR_DATA ( 0x1f );

    LCD_WR_REG ( 0x29 );
    LCD_WR_REG ( 0x2c );

    LCD_Display_Dir ( LCD_DIR );                            // ������ʾ����

    LCD_WR_REG ( 0X36 );  LCD_WR_DATA ( lcddev.scan );      // ����ɨ�跽��

    LCD_Set_Window ( 0, 0, lcddev.width , lcddev.height);   // ������ʾ����
  }
	else if ( lcddev.id == SPFD5408_ID )                      // SPFD5408
	{
		 /* Start Initial Sequence ------------------------------------------------*/
		LCD_WriteReg ( LCD_REG_1,   0x0100 );  /* Set SS bit */
		LCD_WriteReg ( LCD_REG_2,   0x0700 );  /* Set 1 line inversion */
		LCD_WriteReg ( LCD_REG_3,   0x1030 );  /* Set GRAM write direction and BGR=1. */
		LCD_WriteReg ( LCD_REG_4,   0x0000 );  /* Resize register */

		LCD_WriteReg ( LCD_REG_8,   0x0202 );  /* Set the back porch and front porch */
		LCD_WriteReg ( LCD_REG_9,   0x0000 );  /* Set non-display area refresh cycle ISC[3:0] */
		LCD_WriteReg ( LCD_REG_10,  0x0000 );  /* FMARK function */
		LCD_WriteReg ( LCD_REG_12,  0x0000 );  /* RGB 18-bit System interface setting */
		LCD_WriteReg ( LCD_REG_13,  0x0000 );  /* Frame marker Position */
		LCD_WriteReg ( LCD_REG_15,  0x0000 );  /* RGB interface polarity, no impact */

		/* Power On sequence -----------------------------------------------------*/
		LCD_WriteReg ( LCD_REG_16,  0x0000 );  /* SAP, BT[3:0], AP, DSTB, SLP, STB */
		LCD_WriteReg ( LCD_REG_17,  0x0000 );  /* DC1[2:0], DC0[2:0], VC[2:0] */
		LCD_WriteReg ( LCD_REG_18,  0x0000 );  /* VREG1OUT voltage */
		LCD_WriteReg ( LCD_REG_19,  0x0000 );  /* VDV[4:0] for VCOM amplitude */
		delay_ms ( 200 );                     /* Dis-charge capacitor power voltage (200ms) */

		LCD_WriteReg ( LCD_REG_17,  0x0007 );  /* DC1[2:0], DC0[2:0], VC[2:0] */
		delay_ms ( 50 );                      /* Delay 50 ms */
		LCD_WriteReg ( LCD_REG_16,  0x12B0 );  /* SAP, BT[3:0], AP, DSTB, SLP, STB */
		delay_ms ( 50 );                      /* Delay 50 ms */
		LCD_WriteReg ( LCD_REG_18,  0x01BD );  /* External reference voltage= Vci */
		delay_ms ( 50 );
		LCD_WriteReg ( LCD_REG_19,  0x1400 );  /* VDV[4:0] for VCOM amplitude */
		LCD_WriteReg ( LCD_REG_41,  0x000E );  /* VCM[4:0] for VCOMH */
		delay_ms ( 50 );                      /* Delay 50 ms */
		LCD_WriteReg ( LCD_REG_32,  0x0000 );  /* GRAM horizontal Address */
		LCD_WriteReg ( LCD_REG_33,  0x013F );  /* GRAM Vertical Address */

		/* Adjust the Gamma Curve (SPFD5408B)-------------------------------------*/
		LCD_WriteReg ( LCD_REG_48,  0x0b0d );    LCD_WriteReg ( LCD_REG_49,  0x1923 );
		LCD_WriteReg ( LCD_REG_50,  0x1c26 );    LCD_WriteReg ( LCD_REG_51,  0x261c );
		LCD_WriteReg ( LCD_REG_52,  0x2419 );    LCD_WriteReg ( LCD_REG_53,  0x0d0b );
		LCD_WriteReg ( LCD_REG_54,  0x1006 );    LCD_WriteReg ( LCD_REG_55,  0x0610 );
		LCD_WriteReg ( LCD_REG_56,  0x0706 );    LCD_WriteReg ( LCD_REG_57,  0x0304 );
		LCD_WriteReg ( LCD_REG_58,  0x0e05 );    LCD_WriteReg ( LCD_REG_59,  0x0e01 );
		LCD_WriteReg ( LCD_REG_60,  0x010e );    LCD_WriteReg ( LCD_REG_61,  0x050e );
		LCD_WriteReg ( LCD_REG_62,  0x0403 );    LCD_WriteReg ( LCD_REG_63,  0x0607 );

		/* Set GRAM area ---------------------------------------------------------*/
		LCD_WriteReg ( LCD_REG_80,  0x0000 );  /* Horizontal GRAM Start Address */
		LCD_WriteReg ( LCD_REG_81,  0x00EF );  /* Horizontal GRAM End Address */
		LCD_WriteReg ( LCD_REG_82,  0x0000 );  /* Vertical GRAM Start Address */
		LCD_WriteReg ( LCD_REG_83,  0x013F );  /* Vertical GRAM End Address */

		LCD_WriteReg ( LCD_REG_96,  0xA700 );  /* Gate Scan Line */
		LCD_WriteReg ( LCD_REG_97,  0x0001 );  /* NDL, VLE, REV */
		LCD_WriteReg ( LCD_REG_106, 0x0000 );  /* set scrolling line */

		/* Partial Display Control -----------------------------------------------*/
		LCD_WriteReg ( LCD_REG_128, 0x0000 );    LCD_WriteReg ( LCD_REG_129, 0x0000 );
		LCD_WriteReg ( LCD_REG_130, 0x0000 );    LCD_WriteReg ( LCD_REG_131, 0x0000 );
		LCD_WriteReg ( LCD_REG_132, 0x0000 );    LCD_WriteReg ( LCD_REG_133, 0x0000 );

		/* Panel Control ---------------------------------------------------------*/
		LCD_WriteReg ( LCD_REG_144, 0x0010 );    LCD_WriteReg ( LCD_REG_146, 0x0000 );
		LCD_WriteReg ( LCD_REG_147, 0x0003 );    LCD_WriteReg ( LCD_REG_149, 0x0110 );
		LCD_WriteReg ( LCD_REG_151, 0x0000 );    LCD_WriteReg ( LCD_REG_152, 0x0000 );

		LCD_Display_Dir ( LCD_DIR );   // ������ʾ����

		/* Set GRAM write direction and BGR=1
			 I/D=01 (Horizontal : increment, Vertical : decrement)
			 AM=1 (address is updated in vertical writing direction) */
		LCD_WriteReg ( LCD_REG_3, lcddev.scan );

		LCD_WriteReg ( LCD_REG_7,  0x0112 );  /* 262K color and display ON */

		LCD_Set_Window ( 0, 0, lcddev.width , lcddev.height);   // ������ʾ����
	}
	else if ( lcddev.id == NT35510_ID ) // NT35510
	{
		// �������ʱ����Ȼreset����Ļ�ײ�����ֺ�����
    delay_ms ( 50 );
    //************* NT35510��ʼ��**********//	
    LCD_WriteReg ( 0xf000, 0x0055 );	    LCD_WriteReg ( 0xf001, 0x00aa );	
    LCD_WriteReg ( 0xf002, 0x0052 );	    LCD_WriteReg ( 0xf003, 0x0008 );	
    LCD_WriteReg ( 0xf004, 0x0001 );	                                  
                                                                        
    LCD_WriteReg ( 0xbc01, 0x0086 );	    LCD_WriteReg ( 0xbc02, 0x006a );	
    LCD_WriteReg ( 0xbd01, 0x0086 );	    LCD_WriteReg ( 0xbd02, 0x006a );	
    LCD_WriteReg ( 0xbe01, 0x0067 );	                                  
                                                                        
    LCD_WriteReg ( 0xd100, 0x0000 );	    LCD_WriteReg ( 0xd101, 0x005d );	
    LCD_WriteReg ( 0xd102, 0x0000 );	    LCD_WriteReg ( 0xd103, 0x006b );	
    LCD_WriteReg ( 0xd104, 0x0000 );	    LCD_WriteReg ( 0xd105, 0x0084 );	
    LCD_WriteReg ( 0xd106, 0x0000 );	    LCD_WriteReg ( 0xd107, 0x009c );	
    LCD_WriteReg ( 0xd108, 0x0000 );	    LCD_WriteReg ( 0xd109, 0x00b1 );	
    LCD_WriteReg ( 0xd10a, 0x0000 );	    LCD_WriteReg ( 0xd10b, 0x00d9 );	
    LCD_WriteReg ( 0xd10c, 0x0000 );	    LCD_WriteReg ( 0xd10d, 0x00fd );	
    LCD_WriteReg ( 0xd10e, 0x0001 );	    LCD_WriteReg ( 0xd10f, 0x0038 );	
    LCD_WriteReg ( 0xd110, 0x0001 );	    LCD_WriteReg ( 0xd111, 0x0068 );	
    LCD_WriteReg ( 0xd112, 0x0001 );	    LCD_WriteReg ( 0xd113, 0x00b9 );	
    LCD_WriteReg ( 0xd114, 0x0001 );	    LCD_WriteReg ( 0xd115, 0x00fb );	
    LCD_WriteReg ( 0xd116, 0x0002 );	    LCD_WriteReg ( 0xd117, 0x0063 );	
    LCD_WriteReg ( 0xd118, 0x0002 );	    LCD_WriteReg ( 0xd119, 0x00b9 );	
    LCD_WriteReg ( 0xd11a, 0x0002 );	    LCD_WriteReg ( 0xd11b, 0x00bb );	
    LCD_WriteReg ( 0xd11c, 0x0003 );	    LCD_WriteReg ( 0xd11d, 0x0003 );	
    LCD_WriteReg ( 0xd11e, 0x0003 );	    LCD_WriteReg ( 0xd11f, 0x0046 );	
    LCD_WriteReg ( 0xd120, 0x0003 );	    LCD_WriteReg ( 0xd121, 0x0069 );	
    LCD_WriteReg ( 0xd122, 0x0003 );	    LCD_WriteReg ( 0xd123, 0x008f );	
    LCD_WriteReg ( 0xd124, 0x0003 );	    LCD_WriteReg ( 0xd125, 0x00a4 );	
    LCD_WriteReg ( 0xd126, 0x0003 );	    LCD_WriteReg ( 0xd127, 0x00b9 );	
    LCD_WriteReg ( 0xd128, 0x0003 );	    LCD_WriteReg ( 0xd129, 0x00c7 );	
    LCD_WriteReg ( 0xd12a, 0x0003 );	    LCD_WriteReg ( 0xd12b, 0x00c9 );	
    LCD_WriteReg ( 0xd12c, 0x0003 );	    LCD_WriteReg ( 0xd12d, 0x00cb );	
    LCD_WriteReg ( 0xd12e, 0x0003 );	    LCD_WriteReg ( 0xd12f, 0x00cb );	
    LCD_WriteReg ( 0xd130, 0x0003 );	    LCD_WriteReg ( 0xd131, 0x00cb );	
    LCD_WriteReg ( 0xd132, 0x0003 );	    LCD_WriteReg ( 0xd133, 0x00cc );	
                                                                        
    LCD_WriteReg ( 0xd200, 0x0000 );	    LCD_WriteReg ( 0xd201, 0x005d );	
    LCD_WriteReg ( 0xd202, 0x0000 );	    LCD_WriteReg ( 0xd203, 0x006b );	
    LCD_WriteReg ( 0xd204, 0x0000 );	    LCD_WriteReg ( 0xd205, 0x0084 );	
    LCD_WriteReg ( 0xd206, 0x0000 );	    LCD_WriteReg ( 0xd207, 0x009c );	
    LCD_WriteReg ( 0xd208, 0x0000 );	    LCD_WriteReg ( 0xd209, 0x00b1 );	
    LCD_WriteReg ( 0xd20a, 0x0000 );	    LCD_WriteReg ( 0xd20b, 0x00d9 );	
    LCD_WriteReg ( 0xd20c, 0x0000 );	    LCD_WriteReg ( 0xd20d, 0x00fd );	
    LCD_WriteReg ( 0xd20e, 0x0001 );	    LCD_WriteReg ( 0xd20f, 0x0038 );	
    LCD_WriteReg ( 0xd210, 0x0001 );	    LCD_WriteReg ( 0xd211, 0x0068 );	
    LCD_WriteReg ( 0xd212, 0x0001 );	    LCD_WriteReg ( 0xd213, 0x00b9 );	
    LCD_WriteReg ( 0xd214, 0x0001 );	    LCD_WriteReg ( 0xd215, 0x00fb );	
    LCD_WriteReg ( 0xd216, 0x0002 );	    LCD_WriteReg ( 0xd217, 0x0063 );	
    LCD_WriteReg ( 0xd218, 0x0002 );	    LCD_WriteReg ( 0xd219, 0x00b9 );	
    LCD_WriteReg ( 0xd21a, 0x0002 );	    LCD_WriteReg ( 0xd21b, 0x00bb );	
    LCD_WriteReg ( 0xd21c, 0x0003 );	    LCD_WriteReg ( 0xd21d, 0x0003 );	
    LCD_WriteReg ( 0xd21e, 0x0003 );	    LCD_WriteReg ( 0xd21f, 0x0046 );	
    LCD_WriteReg ( 0xd220, 0x0003 );	    LCD_WriteReg ( 0xd221, 0x0069 );	
    LCD_WriteReg ( 0xd222, 0x0003 );	    LCD_WriteReg ( 0xd223, 0x008f );	
    LCD_WriteReg ( 0xd224, 0x0003 );	    LCD_WriteReg ( 0xd225, 0x00a4 );	
    LCD_WriteReg ( 0xd226, 0x0003 );	    LCD_WriteReg ( 0xd227, 0x00b9 );	
    LCD_WriteReg ( 0xd228, 0x0003 );	    LCD_WriteReg ( 0xd229, 0x00c7 );	
    LCD_WriteReg ( 0xd22a, 0x0003 );	    LCD_WriteReg ( 0xd22b, 0x00c9 );	
    LCD_WriteReg ( 0xd22c, 0x0003 );	    LCD_WriteReg ( 0xd22d, 0x00cb );	
    LCD_WriteReg ( 0xd22e, 0x0003 );	    LCD_WriteReg ( 0xd22f, 0x00cb );	
    LCD_WriteReg ( 0xd230, 0x0003 );	    LCD_WriteReg ( 0xd231, 0x00cb );	
    LCD_WriteReg ( 0xd232, 0x0003 );	    LCD_WriteReg ( 0xd233, 0x00cc );	
                                                                        
    LCD_WriteReg ( 0xd300, 0x0000 );	    LCD_WriteReg ( 0xd301, 0x005d );	
    LCD_WriteReg ( 0xd302, 0x0000 );	    LCD_WriteReg ( 0xd303, 0x006b );	
    LCD_WriteReg ( 0xd304, 0x0000 );	    LCD_WriteReg ( 0xd305, 0x0084 );	
    LCD_WriteReg ( 0xd306, 0x0000 );	    LCD_WriteReg ( 0xd307, 0x009c );	
    LCD_WriteReg ( 0xd308, 0x0000 );	    LCD_WriteReg ( 0xd309, 0x00b1 );	
    LCD_WriteReg ( 0xd30a, 0x0000 );	    LCD_WriteReg ( 0xd30b, 0x00d9 );	
    LCD_WriteReg ( 0xd30c, 0x0000 );	    LCD_WriteReg ( 0xd30d, 0x00fd );	
    LCD_WriteReg ( 0xd30e, 0x0001 );	    LCD_WriteReg ( 0xd30f, 0x0038 );	
    LCD_WriteReg ( 0xd310, 0x0001 );	    LCD_WriteReg ( 0xd311, 0x0068 );	
    LCD_WriteReg ( 0xd312, 0x0001 );	    LCD_WriteReg ( 0xd313, 0x00b9 );	
    LCD_WriteReg ( 0xd314, 0x0001 );	    LCD_WriteReg ( 0xd315, 0x00fb );	
    LCD_WriteReg ( 0xd316, 0x0002 );	    LCD_WriteReg ( 0xd317, 0x0063 );	
    LCD_WriteReg ( 0xd318, 0x0002 );	    LCD_WriteReg ( 0xd319, 0x00b9 );	
    LCD_WriteReg ( 0xd31a, 0x0002 );	    LCD_WriteReg ( 0xd31b, 0x00bb );	
    LCD_WriteReg ( 0xd31c, 0x0003 );	    LCD_WriteReg ( 0xd31d, 0x0003 );	
    LCD_WriteReg ( 0xd31e, 0x0003 );	    LCD_WriteReg ( 0xd31f, 0x0046 );	
    LCD_WriteReg ( 0xd320, 0x0003 );	    LCD_WriteReg ( 0xd321, 0x0069 );	
    LCD_WriteReg ( 0xd322, 0x0003 );	    LCD_WriteReg ( 0xd323, 0x008f );	
    LCD_WriteReg ( 0xd324, 0x0003 );	    LCD_WriteReg ( 0xd325, 0x00a4 );	
    LCD_WriteReg ( 0xd326, 0x0003 );	    LCD_WriteReg ( 0xd327, 0x00b9 );	
    LCD_WriteReg ( 0xd328, 0x0003 );	    LCD_WriteReg ( 0xd329, 0x00c7 );	
    LCD_WriteReg ( 0xd32a, 0x0003 );	    LCD_WriteReg ( 0xd32b, 0x00c9 );	
    LCD_WriteReg ( 0xd32c, 0x0003 );	    LCD_WriteReg ( 0xd32d, 0x00cb );	
    LCD_WriteReg ( 0xd32e, 0x0003 );	    LCD_WriteReg ( 0xd32f, 0x00cb );	
    LCD_WriteReg ( 0xd330, 0x0003 );	    LCD_WriteReg ( 0xd331, 0x00cb );	
    LCD_WriteReg ( 0xd332, 0x0003 );	    LCD_WriteReg ( 0xd333, 0x00cc );	
                                                                        
    LCD_WriteReg ( 0xd400, 0x0000 );	    LCD_WriteReg ( 0xd401, 0x005d );	
    LCD_WriteReg ( 0xd402, 0x0000 );	    LCD_WriteReg ( 0xd403, 0x006b );	
    LCD_WriteReg ( 0xd404, 0x0000 );	    LCD_WriteReg ( 0xd405, 0x0084 );	
    LCD_WriteReg ( 0xd406, 0x0000 );	    LCD_WriteReg ( 0xd407, 0x009c );	
    LCD_WriteReg ( 0xd408, 0x0000 );	    LCD_WriteReg ( 0xd409, 0x00b1 );	
    LCD_WriteReg ( 0xd40a, 0x0000 );	    LCD_WriteReg ( 0xd40b, 0x00d9 );	
    LCD_WriteReg ( 0xd40c, 0x0000 );	    LCD_WriteReg ( 0xd40d, 0x00fd );	
    LCD_WriteReg ( 0xd40e, 0x0001 );	    LCD_WriteReg ( 0xd40f, 0x0038 );	
    LCD_WriteReg ( 0xd410, 0x0001 );	    LCD_WriteReg ( 0xd411, 0x0068 );	
    LCD_WriteReg ( 0xd412, 0x0001 );	    LCD_WriteReg ( 0xd413, 0x00b9 );	
    LCD_WriteReg ( 0xd414, 0x0001 );	    LCD_WriteReg ( 0xd415, 0x00fb );	
    LCD_WriteReg ( 0xd416, 0x0002 );	    LCD_WriteReg ( 0xd417, 0x0063 );	
    LCD_WriteReg ( 0xd418, 0x0002 );	    LCD_WriteReg ( 0xd419, 0x00b9 );	
    LCD_WriteReg ( 0xd41a, 0x0002 );	    LCD_WriteReg ( 0xd41b, 0x00bb );	
    LCD_WriteReg ( 0xd41c, 0x0003 );	    LCD_WriteReg ( 0xd41d, 0x0003 );	
    LCD_WriteReg ( 0xd41e, 0x0003 );	    LCD_WriteReg ( 0xd41f, 0x0046 );	
    LCD_WriteReg ( 0xd420, 0x0003 );	    LCD_WriteReg ( 0xd421, 0x0069 );	
    LCD_WriteReg ( 0xd422, 0x0003 );	    LCD_WriteReg ( 0xd423, 0x008f );	
    LCD_WriteReg ( 0xd424, 0x0003 );	    LCD_WriteReg ( 0xd425, 0x00a4 );	
    LCD_WriteReg ( 0xd426, 0x0003 );	    LCD_WriteReg ( 0xd427, 0x00b9 );	
    LCD_WriteReg ( 0xd428, 0x0003 );	    LCD_WriteReg ( 0xd429, 0x00c7 );	
    LCD_WriteReg ( 0xd42a, 0x0003 );	    LCD_WriteReg ( 0xd42b, 0x00c9 );	
    LCD_WriteReg ( 0xd42c, 0x0003 );	    LCD_WriteReg ( 0xd42d, 0x00cb );	
    LCD_WriteReg ( 0xd42e, 0x0003 );	    LCD_WriteReg ( 0xd42f, 0x00cb );	
    LCD_WriteReg ( 0xd430, 0x0003 );	    LCD_WriteReg ( 0xd431, 0x00cb );	
    LCD_WriteReg ( 0xd432, 0x0003 );	    LCD_WriteReg ( 0xd433, 0x00cc );	
                                                                        
    LCD_WriteReg ( 0xd500, 0x0000 );	    LCD_WriteReg ( 0xd501, 0x005d );	
    LCD_WriteReg ( 0xd502, 0x0000 );	    LCD_WriteReg ( 0xd503, 0x006b );	
    LCD_WriteReg ( 0xd504, 0x0000 );	    LCD_WriteReg ( 0xd505, 0x0084 );	
    LCD_WriteReg ( 0xd506, 0x0000 );	    LCD_WriteReg ( 0xd507, 0x009c );	
    LCD_WriteReg ( 0xd508, 0x0000 );	    LCD_WriteReg ( 0xd509, 0x00b1 );	
    LCD_WriteReg ( 0xd50a, 0x0000 );	    LCD_WriteReg ( 0xd50b, 0x00D9 );	
    LCD_WriteReg ( 0xd50c, 0x0000 );	    LCD_WriteReg ( 0xd50d, 0x00fd );	
    LCD_WriteReg ( 0xd50e, 0x0001 );	    LCD_WriteReg ( 0xd50f, 0x0038 );	
    LCD_WriteReg ( 0xd510, 0x0001 );	    LCD_WriteReg ( 0xd511, 0x0068 );	
    LCD_WriteReg ( 0xd512, 0x0001 );	    LCD_WriteReg ( 0xd513, 0x00b9 );	
    LCD_WriteReg ( 0xd514, 0x0001 );	    LCD_WriteReg ( 0xd515, 0x00fb );	
    LCD_WriteReg ( 0xd516, 0x0002 );	    LCD_WriteReg ( 0xd517, 0x0063 );	
    LCD_WriteReg ( 0xd518, 0x0002 );	    LCD_WriteReg ( 0xd519, 0x00b9 );	
    LCD_WriteReg ( 0xd51a, 0x0002 );	    LCD_WriteReg ( 0xd51b, 0x00bb );	
    LCD_WriteReg ( 0xd51c, 0x0003 );	    LCD_WriteReg ( 0xd51d, 0x0003 );	
    LCD_WriteReg ( 0xd51e, 0x0003 );	    LCD_WriteReg ( 0xd51f, 0x0046 );	
    LCD_WriteReg ( 0xd520, 0x0003 );	    LCD_WriteReg ( 0xd521, 0x0069 );	
    LCD_WriteReg ( 0xd522, 0x0003 );	    LCD_WriteReg ( 0xd523, 0x008f );	
    LCD_WriteReg ( 0xd524, 0x0003 );	    LCD_WriteReg ( 0xd525, 0x00a4 );	
    LCD_WriteReg ( 0xd526, 0x0003 );	    LCD_WriteReg ( 0xd527, 0x00b9 );	
    LCD_WriteReg ( 0xd528, 0x0003 );	    LCD_WriteReg ( 0xd529, 0x00c7 );	
    LCD_WriteReg ( 0xd52a, 0x0003 );	    LCD_WriteReg ( 0xd52b, 0x00c9 );	
    LCD_WriteReg ( 0xd52c, 0x0003 );	    LCD_WriteReg ( 0xd52d, 0x00cb );	
    LCD_WriteReg ( 0xd52e, 0x0003 );	    LCD_WriteReg ( 0xd52f, 0x00cb );	
    LCD_WriteReg ( 0xd530, 0x0003 );	    LCD_WriteReg ( 0xd531, 0x00cb );	
    LCD_WriteReg ( 0xd532, 0x0003 );	    LCD_WriteReg ( 0xd533, 0x00cc );	
                                                                        
    LCD_WriteReg ( 0xd600, 0x0000 );	    LCD_WriteReg ( 0xd601, 0x005d );	
    LCD_WriteReg ( 0xd602, 0x0000 );	    LCD_WriteReg ( 0xd603, 0x006b );	
    LCD_WriteReg ( 0xd604, 0x0000 );	    LCD_WriteReg ( 0xd605, 0x0084 );	
    LCD_WriteReg ( 0xd606, 0x0000 );	    LCD_WriteReg ( 0xd607, 0x009c );	
    LCD_WriteReg ( 0xd608, 0x0000 );	    LCD_WriteReg ( 0xd609, 0x00b1 );	
    LCD_WriteReg ( 0xd60a, 0x0000 );	    LCD_WriteReg ( 0xd60b, 0x00d9 );	
    LCD_WriteReg ( 0xd60c, 0x0000 );	    LCD_WriteReg ( 0xd60d, 0x00fd );	
    LCD_WriteReg ( 0xd60e, 0x0001 );	    LCD_WriteReg ( 0xd60f, 0x0038 );	
    LCD_WriteReg ( 0xd610, 0x0001 );	    LCD_WriteReg ( 0xd611, 0x0068 );	
    LCD_WriteReg ( 0xd612, 0x0001 );	    LCD_WriteReg ( 0xd613, 0x00b9 );	
    LCD_WriteReg ( 0xd614, 0x0001 );	    LCD_WriteReg ( 0xd615, 0x00fb );	
    LCD_WriteReg ( 0xd616, 0x0002 );	    LCD_WriteReg ( 0xd617, 0x0063 );	
    LCD_WriteReg ( 0xd618, 0x0002 );	    LCD_WriteReg ( 0xd619, 0x00b9 );	
    LCD_WriteReg ( 0xd61a, 0x0002 );	    LCD_WriteReg ( 0xd61b, 0x00bb );	
    LCD_WriteReg ( 0xd61c, 0x0003 );	    LCD_WriteReg ( 0xd61d, 0x0003 );	
    LCD_WriteReg ( 0xd61e, 0x0003 );	    LCD_WriteReg ( 0xd61f, 0x0046 );	
    LCD_WriteReg ( 0xd620, 0x0003 );	    LCD_WriteReg ( 0xd621, 0x0069 );	
    LCD_WriteReg ( 0xd622, 0x0003 );	    LCD_WriteReg ( 0xd623, 0x008f );	
    LCD_WriteReg ( 0xd624, 0x0003 );	    LCD_WriteReg ( 0xd625, 0x00a4 );	
    LCD_WriteReg ( 0xd626, 0x0003 );	    LCD_WriteReg ( 0xd627, 0x00b9 );	
    LCD_WriteReg ( 0xd628, 0x0003 );	    LCD_WriteReg ( 0xd629, 0x00c7 );	
    LCD_WriteReg ( 0xd62a, 0x0003 );	    LCD_WriteReg ( 0xd62b, 0x00c9 );	
    LCD_WriteReg ( 0xd62c, 0x0003 );	    LCD_WriteReg ( 0xd62d, 0x00cb );	
    LCD_WriteReg ( 0xd62e, 0x0003 );	    LCD_WriteReg ( 0xd62f, 0x00cb );	
    LCD_WriteReg ( 0xd630, 0x0003 );	    LCD_WriteReg ( 0xd631, 0x00cb );	
    LCD_WriteReg ( 0xd632, 0x0003 );	    LCD_WriteReg ( 0xd633, 0x00cc );	
                                                                        
    LCD_WriteReg ( 0xba00, 0x0024 );	    LCD_WriteReg ( 0xba01, 0x0024 );	
    LCD_WriteReg ( 0xba02, 0x0024 );	    LCD_WriteReg ( 0xb900, 0x0024 );	
    LCD_WriteReg ( 0xb901, 0x0024 );	    LCD_WriteReg ( 0xb902, 0x0024 );	
                                                                        
    LCD_WriteReg ( 0xf000, 0x0055 );      LCD_WriteReg ( 0xf001, 0x00aa );	
    LCD_WriteReg ( 0xf002, 0x0052 );	    LCD_WriteReg ( 0xf003, 0x0008 );	
    LCD_WriteReg ( 0xf004, 0x0000 );	                                  
                                                                        
    LCD_WriteReg ( 0xb100, 0x00cc );	                                  
                                                                        
    LCD_WriteReg ( 0xbc00, 0x0005 );	    LCD_WriteReg ( 0xbc01, 0x0005 );	
    LCD_WriteReg ( 0xbc02, 0x0005 );	                                  
                                                                        
    LCD_WriteReg ( 0xb800, 0x0001 );	    LCD_WriteReg ( 0xb801, 0x0003 );	
    LCD_WriteReg ( 0xb802, 0x0003 );	    LCD_WriteReg ( 0xb803, 0x0003 );	
                                                                        
    LCD_WriteReg ( 0xbd02, 0x0007 );	    LCD_WriteReg ( 0xbd03, 0x0031 );	
    LCD_WriteReg ( 0xbe02, 0x0007 );	    LCD_WriteReg ( 0xbe03, 0x0031 );	
    LCD_WriteReg ( 0xbf02, 0x0007 );	    LCD_WriteReg ( 0xbf03, 0x0031 );	
                                                                        
    LCD_WriteReg ( 0xff00, 0x00aa );	    LCD_WriteReg ( 0xff01, 0x0055 );	
    LCD_WriteReg ( 0xff02, 0x0025 );	    LCD_WriteReg ( 0xff03, 0x0001 );	
                                                                        
    LCD_WriteReg ( 0xf304, 0x0011 );	    LCD_WriteReg ( 0xf306, 0x0010 );	
    LCD_WriteReg ( 0xf308, 0x0000 );	    LCD_WriteReg ( 0x3500, 0x0000 );	
                                                                        
    LCD_WriteReg ( 0x3A00, 0x0055 );                                    
                                                                        
    LCD_WriteReg ( 0x2a00, 0x0000 );      LCD_WriteReg ( 0x2a01, 0x0000 );	
    LCD_WriteReg ( 0x2a02, 0x0001 );      LCD_WriteReg ( 0x2a03, 0x00df );	
                                                                        
    LCD_WriteReg ( 0x2b00, 0x0000 );      LCD_WriteReg ( 0x2b01, 0x0000 );
    LCD_WriteReg ( 0x2b02, 0x0003 );      LCD_WriteReg ( 0x2b03, 0x001f );	

    LCD_WR_REG(0x1100);
    delay_ms(10);

    LCD_WR_REG(0x2900);
    delay_ms(5);

    LCD_WriteReg(0x3A00, 0x55);
    LCD_WriteReg(0x3600, 0x60);			// bit3  Color selector switch control��0��= RGB,��1�� = BGR 

    LCD_Display_Dir ( LCD_DIR );                            // ������ʾ����

    LCD_WriteReg ( 0X3600, lcddev.scan );                   // ����ɨ�跽��

    LCD_Set_Window ( 0, 0, lcddev.width , lcddev.height);   // ������ʾ����
	}
	if ( lcddev.id == NT35510_ID )                            // NT35510
  {
		LCD_LED_ON;  // ��������
  }
  else 
  {
    LCD_LED_OFF; // ��������
  }
	LCD_Clear(WHITE);
}



//-----------------------------------------------------------------
// void LCD_DrawPoint(u16 x,u16 y)
//-----------------------------------------------------------------
//
// ��������: ����
// ��ڲ���: u16 x��X����
//					 u16 y��Y����
// ���ز���: ��
// ע������: ��
//					 
//-----------------------------------------------------------------
void LCD_DrawPoint(u16 x,u16 y)
{
	if(lcddev.id == SPFD5408_ID)
	{
		LCD_Set_Window ( x, y, 1, 1);   // ������ʾ����
	}
	else
	{
		LCD_SetCursor(x,y);		// ���ù��λ�� 
	}
	LCD_WriteRAM_Prepare();	// ��ʼд��GRAM
	LCD->LCD_RAM=POINT_COLOR; 
}

//-----------------------------------------------------------------
// void LCD_Fast_DrawPoint(u16 x,u16 y,u32 color)
//-----------------------------------------------------------------
//
// ��������: ���ٻ���
// ��ڲ���: u16 x��X����
//					 u16 y��Y����
//					 u32 color����ɫ
// ���ز���: ��
// ע������: ��
//					 
//-----------------------------------------------------------------
void LCD_Fast_DrawPoint(u16 x,u16 y,u32 color)
{	
	if(lcddev.id == ST7789V_ID)                    // �Ĵ���ÿ��д�� 8bit, 16bit �����������д��
  {
    LCD_WR_REG ( lcddev.setxcmd );
    LCD_WR_DATA ( x >> 8 );       LCD_WR_DATA ( x & 0XFF );
    LCD_WR_REG ( lcddev.setycmd );
    LCD_WR_DATA ( y >> 8 );       LCD_WR_DATA ( y & 0XFF );
  }
  else if(lcddev.id == SPFD5408_ID)              // �Ĵ���ÿ��д�� 16bit
  {
		LCD_Set_Window ( x, y, 1, 1);   						 // ������ʾ����
  }
  else if(lcddev.id == NT35510_ID)               // �Ĵ���ÿ��д�� 8bit, 16bit �����������д��
  {
    LCD_WR_REG ( lcddev.setxcmd + 0 );    LCD_WR_DATA ( x >> 8 );       
    LCD_WR_REG ( lcddev.setxcmd + 1 );    LCD_WR_DATA ( x & 0XFF );
    LCD_WR_REG ( lcddev.setycmd + 0 );    LCD_WR_DATA ( y >> 8 );
    LCD_WR_REG ( lcddev.setycmd + 1 );    LCD_WR_DATA ( y & 0XFF );
  }
	
	LCD->LCD_REG=lcddev.wramcmd; 
	LCD->LCD_RAM=color; 
}	 

//-----------------------------------------------------------------
// void LCD_Clear(uint16_t Color)
//-----------------------------------------------------------------
//
//  ��������: LCD ����
//  ��ڲ���: Color ������ɫ
//  ���ز���: ��
//  ע������: ��
//
//-----------------------------------------------------------------
void LCD_Clear(uint16_t Color)
{
	LCD_Fill( 0, 0, lcddev.width , lcddev.height, Color);
}

//-----------------------------------------------------------------
// void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u32 color)
//-----------------------------------------------------------------
//
// ��������: LCD��ָ����������䵥����ɫ
// ��ڲ���: u16 sx��������ʼX����
//					 u16 sy��������ʼY����
//					 u16 ex��������ֹX����
//					 u16 ey��������ֹY����
//					 u32 color��Ҫ������ɫ
// ���ز���: ��
// ע������: ��
//					 
//-----------------------------------------------------------------
void LCD_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u32 color)
{          
	u16 i,j;
	u16 xlen=0;
	u32 index = 0;
	if(lcddev.id == SPFD5408_ID)
	{
		LCD_Set_Window (sx, sy, ex-sx, ey-sy );
		LCD_WriteRAM_Prepare();                     /* Prepare to write GRAM */

		for(index = 0; index < ((ey-sy)* (ex-sx)); index++)
		{
			LCD_WriteRAM ( color );
		}
		LCD_Set_Window ( 0, 0, lcddev.width , lcddev.height);        // ������ʾ����
	}
	else
	{
		xlen=ex-sx+1;	 
		for(i=sy;i<=ey;i++)
		{
			LCD_SetCursor(sx,i);      // ���ù��λ�� 
			LCD_WriteRAM_Prepare();   // ��ʼд��GRAM	  
			for(j=0;j<xlen;j++)
				LCD->LCD_RAM=color;			// ��ʾ��ɫ 	    
		} 
	}
} 

//-----------------------------------------------------------------
// void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
//-----------------------------------------------------------------
//
// ��������: LTCD��ָ����������䵥����ɫ
// ��ڲ���: u16 sx��������ʼX����
//					 u16 sy��������ʼY����
//					 u16 ex��������ֹX����
//					 u16 ey��������ֹY����
//					 u32 color��Ҫ������ɫ
// ���ز���: ��
// ע������: ��
//					 
//-----------------------------------------------------------------
void LCD_Color_Fill(u16 sx,u16 sy,u16 ex,u16 ey,u16 *color)
{  
	u16 height,width;
	u16 i,j;
	u32 index = 0;
	
	if(lcddev.id == SPFD5408_ID)
	{
		LCD_Set_Window (sx, sy, ex-sx, ey-sy );
		LCD_WriteRAM_Prepare();                     /* Prepare to write GRAM */

		for(index = 0; index < ((ey-sy)* (ex-sx)); index++)
		{
			LCD_WriteRAM ( color[index] );
		}
		LCD_Set_Window ( 0, 0, lcddev.width , lcddev.height);        // ������ʾ����
	}
	else
	{
		width=ex-sx+1; 			// �õ����Ŀ��
		height=ey-sy+1;			// �߶�
		for(i=0;i<height;i++)
		{
			LCD_SetCursor(sx,sy+i);   	// ���ù��λ�� 
			LCD_WriteRAM_Prepare();     // ��ʼд��GRAM
			for(j=0;j<width;j++)
				LCD->LCD_RAM=color[i*width+j];// д������ 
		}
	}
	
} 

//-----------------------------------------------------------------
// void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
//-----------------------------------------------------------------
//
// ��������: ����
// ��ڲ���: u16 sx��������ʼX����
//					 u16 sy��������ʼY����
//					 u16 ex��������ֹX����
//					 u16 ey��������ֹY����
// ���ز���: ��
// ע������: ��
//					 
//-----------------------------------------------------------------
void LCD_DrawLine(u16 x1, u16 y1, u16 x2, u16 y2)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance; 
	int incx,incy,uRow,uCol; 
	delta_x=x2-x1; // ������������ 
	delta_y=y2-y1; 
	uRow=x1; 
	uCol=y1; 
	if(delta_x>0)incx=1; // ���õ������� 
	else if(delta_x==0)incx=0;// ��ֱ�� 
	else {incx=-1;delta_x=-delta_x;} 
	if(delta_y>0)incy=1; 
	else if(delta_y==0)incy=0;// ˮƽ�� 
	else{incy=-1;delta_y=-delta_y;} 
	if( delta_x>delta_y)distance=delta_x; // ѡȡ�������������� 
	else distance=delta_y; 
	for(t=0;t<=distance+1;t++ )// ������� 
	{  
		LCD_DrawPoint(uRow,uCol);// ���� 
		xerr+=delta_x ; 
		yerr+=delta_y ; 
		if(xerr>distance) 
		{ 
			xerr-=distance; 
			uRow+=incx; 
		} 
		if(yerr>distance) 
		{ 
			yerr-=distance; 
			uCol+=incy; 
		} 
	}  
}   

//-----------------------------------------------------------------
// void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
//-----------------------------------------------------------------
//
// ��������: ������	
// ��ڲ���: u16 x1��������ʼX����
//					 u16 y1��������ʼY����
//					 u16 x2��������ֹX����
//					 u16 y2��������ֹY����
// ���ز���: ��
// ע������: ��
//					 
//-----------------------------------------------------------------
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2)
{
	LCD_DrawLine(x1,y1,x2,y1);
	LCD_DrawLine(x1,y1,x1,y2);
	LCD_DrawLine(x1,y2,x2,y2);
	LCD_DrawLine(x2,y1,x2,y2);
}

//-----------------------------------------------------------------
// void LCD_Draw_Circle(u16 x0,u16 y0,u8 r)
//-----------------------------------------------------------------
//
// ��������: ��ָ��λ�û�һ��ָ����С��Բ
// ��ڲ���: u16 x1�����ĵ�X����
//					 u16 y1�����ĵ�Y����
//					 u8 r���뾶
// ���ز���: ��
// ע������: ��
//					 
//-----------------------------------------------------------------
void LCD_Draw_Circle(u16 x0,u16 y0,u8 r)
{
	int a,b;
	int di;
	a=0;b=r;	  
	di=3-(r<<1);             // �ж��¸���λ�õı�־
	while(a<=b)
	{
		LCD_DrawPoint(x0+a,y0-b);            
 		LCD_DrawPoint(x0+b,y0-a);                      
		LCD_DrawPoint(x0+b,y0+a);                           
		LCD_DrawPoint(x0+a,y0+b);            
		LCD_DrawPoint(x0-a,y0+b);                  
 		LCD_DrawPoint(x0-b,y0+a);             
		LCD_DrawPoint(x0-a,y0-b);                     
  		LCD_DrawPoint(x0-b,y0-a);             	         
		a++;
		// ʹ��Bresenham�㷨��Բ     
		if(di<0)di +=4*a+6;	  
		else
		{
			di+=10+4*(a-b);   
			b--;
		} 						    
	}
} 

//-----------------------------------------------------------------
// void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
//-----------------------------------------------------------------
//
// ��������: ��ָ��λ����ʾһ���ַ�
// ��ڲ���: u16 x��X����
//					 u16 y��Y����
//					 u8 num��Ҫ��ʾ���ַ�:" "--->"~"
//					 u8 size�������С 12/16/24/32
//					 u8 mode���ӷ�ʽ(1)���Ƿǵ��ӷ�ʽ(0)
// ���ز���: ��
// ע������: ��
//					 
//-----------------------------------------------------------------
void LCD_ShowChar(u16 x,u16 y,u8 num,u8 size,u8 mode)
{  							  
    u8 temp,t1,t;
	u16 y0=y;
	u8 csize=(size/8+((size%8)?1:0))*(size/2);	// �õ�����һ���ַ���Ӧ������ռ���ֽ���	
 	num=num-' ';// �õ�ƫ�ƺ��ֵ��ASCII�ֿ��Ǵӿո�ʼȡģ������-' '���Ƕ�Ӧ�ַ����ֿ⣩
	for(t=0;t<csize;t++)
	{   
		if(size==12)temp=asc2_1206[num][t]; 	 		// ����1206����
		else if(size==16)temp=asc2_1608[num][t];	// ����1608����
		else if(size==24)temp=asc2_2412[num][t];	// ����2412����
		else if(size==32)temp=asc2_3216[num][t];	// ����3216����
		else return;															// û�е��ֿ�
		for(t1=0;t1<8;t1++)
		{			    
			if(temp&0x80)LCD_Fast_DrawPoint(x,y,POINT_COLOR);
			else if(mode==0)LCD_Fast_DrawPoint(x,y,BACK_COLOR);
			temp<<=1;
			y++;
			if(y>=lcddev.height)
				return;		// ��������
			if((y-y0)==size)
			{
				y=y0;
				x++;
				if(x>=lcddev.width)
					return;	// ��������
				break;
			}
		}  	 
	}  	    	   	 	  
}

//-----------------------------------------------------------------
// u32 LCD_Pow(u8 m,u8 n)
//-----------------------------------------------------------------
//
// ��������: m^n����
// ��ڲ���: u8 m����ֵ
//					 u8 n����ֵ
// ���ز���: u32 result��m^n�η�.
// ע������: ��
//					 
//-----------------------------------------------------------------
u32 LCD_Pow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}			 

//-----------------------------------------------------------------
// void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
//-----------------------------------------------------------------
//
// ��������: ��ʾ����,��λΪ0,����ʾ
// ��ڲ���: u16 x��X����
//					 u16 y��Y����
//					 u32 num����ֵ(0~4294967295);	 
//					 u8 len�����ֵ�λ��
//					 u8 size�������С 12/16/24/32
// ���ز���: ��
// ע������: ��
//					 
//-----------------------------------------------------------------
void LCD_ShowNum(u16 x,u16 y,u32 num,u8 len,u8 size)
{         	
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				LCD_ShowChar(x+(size/2)*t,y,' ',size,0);
				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,0); 
	}
} 

//-----------------------------------------------------------------
// void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
//-----------------------------------------------------------------
//
// ��������: ��ʾ����,��λΪ0,������ʾ
// ��ڲ���: u16 x��X����
//					 u16 y��Y����
//					 u32 num����ֵ(0~999999999);	 
//					 u8 len�����ֵ�λ��
//					 u8 size�������С 12/16/24/32
//					 8 mode��0,�ǵ�����ʾ;1,������ʾ.
// ���ز���: ��
// ע������: ��
//					 
//-----------------------------------------------------------------
void LCD_ShowxNum(u16 x,u16 y,u32 num,u8 len,u8 size,u8 mode)
{  
	u8 t,temp;
	u8 enshow=0;						   
	for(t=0;t<len;t++)
	{
		temp=(num/LCD_Pow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				if(mode&0X80)LCD_ShowChar(x+(size/2)*t,y,'0',size,mode&0X01);  
				else LCD_ShowChar(x+(size/2)*t,y,' ',size,mode&0X01);  
 				continue;
			}else enshow=1; 
		 	 
		}
	 	LCD_ShowChar(x+(size/2)*t,y,temp+'0',size,mode&0X01); 
	}
} 

//-----------------------------------------------------------------
// void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,u8 *p)
//-----------------------------------------------------------------
//
// ��������: ��ʾ�ַ���
// ��ڲ���: u16 x��X����
//					 u16 y��Y����
//					 u16 width�����򳤶�	 
//					 u16 height������߶�
//           u8 size�������С
//					 u8 *p���ַ�����ʼ��ַ		
// ���ز���: ��
// ע������: ��
//					 
//-----------------------------------------------------------------
void LCD_ShowString(u16 x,u16 y,u16 width,u16 height,u8 size,char *p)
{         
	u8 x0=x;
	width+=x;
	height+=y;
    while((*p<='~')&&(*p>=' '))	// �ж��ǲ��ǷǷ��ַ�!
    {       
			if(x>=width){x=x0;y+=size;}
			if(y>=height)break;				// �˳�
			if((x+size/2)>lcddev.width)
			{
				x=0;
				y+=size;
			}
			LCD_ShowChar(x,y,*p,size,0);
			x+=size/2;
			p++;
    }  
}

//-----------------------------------------------------------------
// End Of File
//----------------------------------------------------------------- 
