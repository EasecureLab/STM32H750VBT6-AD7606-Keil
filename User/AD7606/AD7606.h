//-----------------------------------------------------------------
// ��������:
//     AD7606��������ͷ�ļ�
// ��    ��: ���ǵ���
// ��ʼ����: 2020-11-11
// �������: 2020-11-11
// �޸�����: 
// ��ǰ�汾: V1.0
// ��ʷ�汾:
//  - V1.0:  AD7606����ͷ�ļ�
// ���Թ���: ����STM32H750���İ塢LZE_ST_LINK2
// ˵    ��: 
//    
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// ͷ�ļ�����
//-----------------------------------------------------------------
#ifndef _AD7606_H
#define _AD7606_H
#include "system.h"
//-----------------------------------------------------------------

//-----------------------------------------------------------------
// ��������
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
// �ⲿ��������
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
