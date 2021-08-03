//-----------------------------------------------------------------
// 程序描述:
//     AD7606串行驱动头文件
// 作    者: 凌智电子
// 开始日期: 2020-11-11
// 完成日期: 2020-11-11
// 修改日期: 
// 当前版本: V1.0
// 历史版本:
//  - V1.0:  AD7606驱动头文件
// 调试工具: 凌智STM32H750核心板、LZE_ST_LINK2
// 说    明: 
//    
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// 头文件包含
//-----------------------------------------------------------------
#ifndef _AD7606_H
#define _AD7606_H
#include "system.h"
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// 引脚声明
//-----------------------------------------------------------------
#define OS10_L 	  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_RESET)
#define OS10_H   	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_0,GPIO_PIN_SET)
#define OS11_L 	  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_RESET)
#define OS11_H   	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_1,GPIO_PIN_SET)
#define OS12_L 	  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_RESET)
#define OS12_H   	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_2,GPIO_PIN_SET)
#define SER_L 	  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_RESET)
#define SER_H   	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_3,GPIO_PIN_SET)
#define STBY_L 	  HAL_GPIO_WritePin(GPIO_C,GPIO_PIN_4,GPIO_PIN_RESET)
#define STBY_H 	  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_4,GPIO_PIN_SET)
#define CO_A_L 	  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_RESET)
#define CO_A_H   	HAL_GPIO_WritePin(GPIOC,GPIO_PIN_5,GPIO_PIN_SET)
#define CO_B_L 	  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_RESET)
#define CO_B_H 	  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_6,GPIO_PIN_SET)
#define REST_L 	  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_RESET)
#define REST_H 	  HAL_GPIO_WritePin(GPIOC,GPIO_PIN_7,GPIO_PIN_SET)

#define BUSY 			HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_0)
#define FR_D 			HAL_GPIO_ReadPin(GPIOA,GPIO_PIN_1)

//-----------------------------------------------------------------
// 外部函数声明
//-----------------------------------------------------------------
extern void GPIO_AD7606_Configuration(void);
extern void AD7606_Init(void);
extern void AD7606_StartConvst(void);
extern void AD7606_RESET(void);
extern void AD7606_ReadData(s16 * DB_data);
extern void AD7606_Delay(uint16_t t);

#endif
//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
