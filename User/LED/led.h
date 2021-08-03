//-----------------------------------------------------------------
// ��������:
// 		 LED����ͷ�ļ�
// ��    ��: ���ǵ���
// ��ʼ����: 2020-11-11
// �������: 2020-11-11
// �޸�����: 
// ��ǰ�汾: V1.0
// ��ʷ�汾:
//  - V1.0: (2020-11-11)LED IO ����
// ���Թ���: ����STM32H750���İ塢LZE_ST_LINK2
// ˵    ��: 
//    
//-----------------------------------------------------------------
#ifndef _LED_H
#define _LED_H
#include "system.h"
//-----------------------------------------------------------------
// LED���Ŷ���
//-----------------------------------------------------------------
typedef enum 
{
  LEDB = 0,
  LEDG = 1,
	LEDR = 2
}Led_TypeDef;

#define LEDn                                    3

// ����
#define LEDB_PIN                                GPIO_PIN_4
#define LEDB_GPIO_PORT                          GPIOE
#define LEDB_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOE_CLK_ENABLE()  
#define LEDB_GPIO_CLK_DISABLE()                 __HAL_RCC_GPIOE_CLK_DISABLE()  
#define LED_B_ON 																HAL_GPIO_WritePin(LEDB_GPIO_PORT,LEDB_PIN,GPIO_PIN_RESET);
#define LED_B_OFF 															HAL_GPIO_WritePin(LEDB_GPIO_PORT,LEDB_PIN,GPIO_PIN_SET);
#define LED_B_Toggle 														HAL_GPIO_TogglePin(LEDB_GPIO_PORT, LEDB_PIN)

// �̵�
#define LEDG_PIN                                GPIO_PIN_5
#define LEDG_GPIO_PORT                          GPIOE
#define LEDG_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOE_CLK_ENABLE()  
#define LEDG_GPIO_CLK_DISABLE()                 __HAL_RCC_GPIOE_CLK_DISABLE()
#define LED_G_ON 																HAL_GPIO_WritePin(LEDG_GPIO_PORT,LEDG_PIN,GPIO_PIN_RESET);
#define LED_G_OFF 															HAL_GPIO_WritePin(LEDG_GPIO_PORT,LEDG_PIN,GPIO_PIN_SET);
#define LED_G_Toggle 														HAL_GPIO_TogglePin(LEDG_GPIO_PORT, LEDG_PIN)

// ���
#define LEDR_PIN                                GPIO_PIN_6
#define LEDR_GPIO_PORT                          GPIOE
#define LEDR_GPIO_CLK_ENABLE()                  __HAL_RCC_GPIOE_CLK_ENABLE()  
#define LEDR_GPIO_CLK_DISABLE()                 __HAL_RCC_GPIOE_CLK_DISABLE() 
#define LED_R_ON 																HAL_GPIO_WritePin(LEDR_GPIO_PORT,LEDR_PIN,GPIO_PIN_RESET);
#define LED_R_OFF 															HAL_GPIO_WritePin(LEDR_GPIO_PORT,LEDR_PIN,GPIO_PIN_SET);
#define LED_R_Toggle 														HAL_GPIO_TogglePin(LEDR_GPIO_PORT, LEDR_PIN)

#define LEDx_GPIO_CLK_ENABLE(__INDEX__)  do{if((__INDEX__) == 0) LEDB_GPIO_CLK_ENABLE(); else \
                                            if((__INDEX__) == 1) LEDG_GPIO_CLK_ENABLE(); else \
																						if((__INDEX__) == 2) LEDR_GPIO_CLK_ENABLE(); \
                                            }while(0)
#define LEDx_GPIO_CLK_DISABLE(__INDEX__) do{if((__INDEX__) == 0) LEDB_GPIO_CLK_DISABLE(); else \
                                            if((__INDEX__) == 1) LEDG_GPIO_CLK_DISABLE(); else \
																						if((__INDEX__) == 2) LEDR_GPIO_CLK_DISABLE(); \
                                            }while(0)

//-----------------------------------------------------------------

//-----------------------------------------------------------------
// �ⲿ��������
//-----------------------------------------------------------------
extern void LED_Init(void);
extern void BSP_LED_Init(Led_TypeDef Led);
#endif
//-----------------------------------------------------------------
// End Of File
//-----------------------------------------------------------------
