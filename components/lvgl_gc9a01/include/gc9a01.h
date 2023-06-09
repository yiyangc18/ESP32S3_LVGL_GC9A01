#ifndef MAIN_GC9A01_H_
#define MAIN_GC9A01_H_


/* INCLUDES ------------------------------------------------------------------*/

#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_timer.h"
#include "esp_lcd_panel_io.h"
#include "esp_lcd_panel_vendor.h"
#include "esp_lcd_panel_ops.h"
#include "driver/gpio.h"
#include "driver/spi_master.h"

#include "esp_err.h"
#include "esp_log.h"
/* MACROS --------------------------------------------------------------------*/
// Using SPI2 in the example
#define LCD_HOST  SPI2_HOST

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////// Please update the following configuration according to your LCD spec //////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
#define EXAMPLE_LCD_PIXEL_CLOCK_HZ     (20 * 1000 * 1000)
#define EXAMPLE_LCD_BK_LIGHT_ON_LEVEL  1
#define EXAMPLE_LCD_BK_LIGHT_OFF_LEVEL !EXAMPLE_LCD_BK_LIGHT_ON_LEVEL
#define EXAMPLE_PIN_NUM_SCLK           12//18
#define EXAMPLE_PIN_NUM_MOSI           11//19
#define EXAMPLE_PIN_NUM_MISO           16//21
#define EXAMPLE_PIN_NUM_LCD_DC         6//5
#define EXAMPLE_PIN_NUM_LCD_RST        15//3
#define EXAMPLE_PIN_NUM_LCD_CS         7//4
#define EXAMPLE_PIN_NUM_BK_LIGHT       13//2
#define EXAMPLE_PIN_NUM_TOUCH_CS       17//15

#define EXAMPLE_LCD_H_RES              240
#define EXAMPLE_LCD_V_RES              240

#define EXAMPLE_LCD_CMD_BITS           8
#define EXAMPLE_LCD_PARAM_BITS         8



/* ENUMORATIONS --------------------------------------------------------------*/

/* STRUCTURES & TYPEDEFS -----------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/
extern esp_lcd_panel_handle_t panel_handle;
/* FUNCTIONS DECLARATION -----------------------------------------------------*/
void gc9a01_displayInit(void);


#endif /* MAIN_GC9A01_H_ */

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
