//-----------------------------------------------------------------
// 程序描述:
//     AD7606串行驱动程序
// 作    者: 凌智电子
// 开始日期: 2020-11-11
// 完成日期: 2020-11-11
// 修改日期: 
// 当前版本: V1.0
// 历史版本:
//  - V1.0:  AD7606驱动程序
// 调试工具: 凌智STM32H750核心板、LZE_ST_LINK2
// 说    明: 
//    
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// 头文件包含
//-----------------------------------------------------------------
#include "AD7606.h"
#include "delay.h"
//-----------------------------------------------------------------
SPI_HandleTypeDef SPI2_Handler;
//-----------------------------------------------------------------
// void MX_SPI2_Init(void)
//-----------------------------------------------------------------
// 
// 函数功能: SPI2初始化
// 入口参数: 无 
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void MX_SPI2_Init(void)
{
  SPI2_Handler.Instance = SPI2;
  SPI2_Handler.Init.Mode = SPI_MODE_MASTER;
  SPI2_Handler.Init.Direction = SPI_DIRECTION_2LINES_RXONLY;
  SPI2_Handler.Init.DataSize = SPI_DATASIZE_16BIT;
  SPI2_Handler.Init.CLKPolarity = SPI_POLARITY_LOW;
  SPI2_Handler.Init.CLKPhase = SPI_PHASE_1EDGE;
  SPI2_Handler.Init.NSS = SPI_NSS_HARD_OUTPUT;
  SPI2_Handler.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
  SPI2_Handler.Init.FirstBit = SPI_FIRSTBIT_MSB;
  SPI2_Handler.Init.TIMode = SPI_TIMODE_DISABLE;
  SPI2_Handler.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
  SPI2_Handler.Init.CRCPolynomial = 0x0;
  SPI2_Handler.Init.NSSPMode = SPI_NSS_PULSE_ENABLE;
  SPI2_Handler.Init.NSSPolarity = SPI_NSS_POLARITY_LOW;
  SPI2_Handler.Init.FifoThreshold = SPI_FIFO_THRESHOLD_01DATA;
  SPI2_Handler.Init.TxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  SPI2_Handler.Init.RxCRCInitializationPattern = SPI_CRC_INITIALIZATION_ALL_ZERO_PATTERN;
  SPI2_Handler.Init.MasterSSIdleness = SPI_MASTER_SS_IDLENESS_00CYCLE;
  SPI2_Handler.Init.MasterInterDataIdleness = SPI_MASTER_INTERDATA_IDLENESS_00CYCLE;
  SPI2_Handler.Init.MasterReceiverAutoSusp = SPI_MASTER_RX_AUTOSUSP_DISABLE;
  SPI2_Handler.Init.MasterKeepIOState = SPI_MASTER_KEEP_IO_STATE_DISABLE;
  SPI2_Handler.Init.IOSwap = SPI_IO_SWAP_DISABLE;
  if (HAL_SPI_Init(&SPI2_Handler) != HAL_OK)
  {
    while(1);
  }
	__HAL_SPI_ENABLE(&SPI2_Handler);
}

//-----------------------------------------------------------------
// void HAL_SPI_MspInit(SPI_HandleTypeDef *hspi)
//-----------------------------------------------------------------
// 
// 函数功能: SPI底层驱动，时钟使能，引脚配置
// 入口参数: SPI_HandleTypeDef *hspi：SPI句柄
// 返 回 值: 无
// 注意事项: 此函数会被HAL_SPI_Init()调用
//
//-----------------------------------------------------------------
void HAL_SPI_MspInit(SPI_HandleTypeDef* hspi)
{
  GPIO_InitTypeDef GPIO_InitStruct;
  if(hspi->Instance==SPI2)
  {
    __HAL_RCC_SPI2_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitStruct.Pin = GPIO_PIN_12|GPIO_PIN_13|GPIO_PIN_14;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_MEDIUM;
    GPIO_InitStruct.Alternate = GPIO_AF5_SPI2;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
  }
}

//-----------------------------------------------------------------
// void SPI2_Write_16bit(s16 *tx_dat, s16 *rx_dat)
//-----------------------------------------------------------------
// 
// 函数功能: SPI2写一个16位的数据
// 入口参数: u8 dat： 待发送的数据
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void SPI2_Write_16bit(s16 *tx_dat, s16 *rx_dat)
{
	HAL_SPI_TransmitReceive(&SPI2_Handler, (uint8_t *)tx_dat, (uint8_t *)rx_dat, 1, 1000);
}

//-----------------------------------------------------------------
// void SPI2_Write_16bit(s16 *tx_dat, s16 *rx_dat)
//-----------------------------------------------------------------
// 
// 函数功能: AD7606引脚配置函数
// 入口参数: 无
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void GPIO_AD7606_Configuration(void)
{
  GPIO_InitTypeDef GPIO_InitStruct = {0};
	
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_GPIOB_CLK_ENABLE();
  __HAL_RCC_GPIOC_CLK_ENABLE();

  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3|
											  GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_0|GPIO_PIN_1;
  GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_15;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLDOWN;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
	HAL_GPIO_WritePin(GPIOB, GPIO_PIN_15, GPIO_PIN_RESET);
}

//-----------------------------------------------------------------
// void AD7606_Init(void)
//-----------------------------------------------------------------
// 
// 函数功能: AD7606初始化函数
// 入口参数: 无 
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void AD7606_Init(void)
{
	MX_SPI2_Init();	
	GPIO_AD7606_Configuration();
	CO_A_H;
	CO_B_H;
	delay_ms(1);
	SER_H;
	STBY_H;
  OS10_L;
	OS11_L;
	OS12_L;
	AD7606_RESET();  
	delay_ms(1);
	AD7606_StartConvst();	
}

//-----------------------------------------------------------------
// void AD7606_StartConvst(void)
//-----------------------------------------------------------------
// 
// 函数功能: 启动转换
// 入口参数: 无 
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void AD7606_StartConvst(void)
{  
	CO_A_L;	
	CO_B_L;	
	delay_us (1);
	CO_A_H;
	CO_B_H;
	delay_us (1);
}
  
//-----------------------------------------------------------------
// void AD7606_RESET(void) 
//-----------------------------------------------------------------
// 
// 函数功能: 复位
// 入口参数: 无 
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void AD7606_RESET(void) 
{ 
	REST_L;
	delay_us (1);
	REST_H; 
	delay_us(1);
	REST_L; 
}  

//-----------------------------------------------------------------
// void AD7606_ReadData(s16 * DB_data)
//-----------------------------------------------------------------
// 
// 函数功能: 读取数据 
// 入口参数: s16 * DB_data：结构体指针，该指针为指向结构体数组的首地址 
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void AD7606_ReadData(s16 * DB_data) 
{ 
	HAL_SPI_Receive(&SPI2_Handler, (uint8_t *)DB_data, 8, 1000);
} 

//-----------------------------------------------------------------
// void AD7606_Delay(uint16_t t) 
//-----------------------------------------------------------------
// 
// 函数功能: 读取数据 
// 入口参数: uint16_t t：延时数 
// 返 回 值: 无
// 注意事项: 无
//
//-----------------------------------------------------------------
void AD7606_Delay(uint16_t t)
{
	do {
			;
	} while (--t); 
}
