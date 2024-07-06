#ifndef __oled_H
#define __oled_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "u8g2.h"
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */



/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */
#define MAX_LEN    128  //
#define OLED_ADDRESS  0x78 // oled_addr
#define OLED_CMD   0x00  // 寫入
#define OLED_DATA  0x40  // 等資料

/* USER CODE BEGIN Prototypes */
uint8_t u8x8_byte_hw_i2c(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
uint8_t u8x8_gpio_and_delay(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr);
void u8g2Init(u8g2_t *u8g2);
 #ifdef __cplusplus
}
#endif
#endif /*__ i2c_H */
/* USER CODE END Prototypes */
