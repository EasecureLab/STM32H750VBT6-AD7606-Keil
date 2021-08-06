
// 硬件连接：
//							AD7606模块							STM32H750核心板
//								+5V				 ------->				+5V
//								GND				 ------->				GND
// 								SER 			 -------> 			PC3
// 								STBY 			 -------> 			PC4
// 								C0-A 			 -------> 			PC5
// 								C0-B 			 -------> 			PC6
// 								REST 			 -------> 			PC7
// 								BUSY 			 -------> 			PA0
// 								CS_N 			 -------> 			PB12
// 								RD/SC 	 	     -------> 			PB13
// 						  	    DB7    		     -------> 			PB14


#include "system.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"
#include "led.h"
#include "AD7606.h"

int main(void)
{
	uint8_t i;
	uint8_t dis_buf[40];
	s16 DB_data[8] = {0};
	
	HAL_Init();          		// 初始化HAL库
	SystemClock_Config(); 	// 设置系统时钟,400Mhz  
	SysTick_clkconfig(400);	// SysTick参数配置
	uart_init(115200);			// 初始化串口
	AD7606_Init();					// 初始化AD7606
	
	printf("hello wang 00\r\n");
	
	while(1)
	{
		AD7606_StartConvst();
		
		while((BUSY == GPIO_PIN_SET))	// 读取BUSY的状态，为低电平表示电平转换结束，可以读取数据
			delay_ms(10);
		
		AD7606_ReadData(DB_data); 		//读取数据放至数组DB_data[]

		printf("ch4 =%8.1f mv \n",(float)(DB_data[3]*10000.0/32768));
		
		for(i=0;i<8;i++)
		{
			sprintf((char*)dis_buf,"CH%1d:%8.1f mv  0x%04x %6d\r\n", i+1, (float)(DB_data[i]*10000.0/32768), (uint16_t)(DB_data[i]^0x8000), (uint16_t)(DB_data[i]^0x8000));
			printf("%s",dis_buf);                  //???????
			delay_ms(10);
		}	
		
		delay_ms(500);
	}									
}
