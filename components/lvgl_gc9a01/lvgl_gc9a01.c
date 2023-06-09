#include "display.h"
#include "gc9a01.h"
#include "sntp.h"
#include "lvgl_demo_ui.h"
#include "ui_helpers.h"
#include "time.h"
#include "esp_sntp.h"
#include "lwip/ip_addr.h"

#include "lvgl_gc9a01.h"
/* PRIVATE STRUCTRES ---------------------------------------------------------*/

/* VARIABLES -----------------------------------------------------------------*/
static const char *main = "main";
char targetString[10] = {0};
/* DEFINITIONS ---------------------------------------------------------------*/

/* MACROS --------------------------------------------------------------------*/

/* PRIVATE FUNCTIONS DECLARATION ---------------------------------------------*/
static void time_config(void);
static void main_encoder_cb(uint8_t knobPosition, uint8_t knobButtonStatus);
static void main_tempretureStringPrepare(char* tempString, char* targetString);
static void lvgl_time_task(void*param);
static void wirless_init_task(void* param);
static void mqtt_msg_pars_task(void* param);
static void time_handle_task(void* param);

/* FUNCTION PROTOTYPES -------------------------------------------------------*/
/**
 * @brief 	Initialize system peripherals and create FreeRTOS tasks
 *
 */
void lv_gca_app_main(void)
{
	gc9a01_displayInit();

	displayConfig();

//	encoder_init(main_encoder_cb);

	 xTaskCreatePinnedToCore(wirless_init_task, "WiFi init", 10000, NULL, 4, NULL, 0);

//	xTaskCreatePinnedToCore(encoder_handler_task, "encoder_handler", 10000, NULL, 4, NULL, 1);

     xTaskCreatePinnedToCore(lvgl_time_task, "lvgl_time_task", 10000, NULL, 4, NULL, 1);

     //Wait for WiFi and MQTT broker connection to be established.
     vTaskDelay(pdMS_TO_TICKS(15000));

     sntp_config();

     xTaskCreatePinnedToCore(mqtt_msg_pars_task, "MQTT parser", 10000, NULL, 4, NULL, 1);

     xTaskCreatePinnedToCore(time_handle_task, "Real time Handler", 10000, NULL, 4, NULL, 1);
}
/**
 * @brief 	LVGL library timer task. Necessary to run once every 10ms
 *
 */
void lvgl_time_task(void* param)
{
	TickType_t xLastWakeTime = xTaskGetTickCount();
	while(1)
	{

        // The task running lv_timer_handler should have lower priority than that running `lv_tick_inc`
        lv_timer_handler();

        _ui_arc_increment();
        // raise the task priority of LVGL and/or reduce the handler period can improve the performance
//        vTaskDelay(pdMS_TO_TICKS(10));

        vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(10) );

	}
}
/**
 * @brief 	Encoder position read callback.
 *
 * @param 	knobPosition	: Read encoder position value.
 */
static void main_encoder_cb(uint8_t knobPosition, uint8_t knobButtonStatus)
{
	set_value((int32_t) knobPosition, knobButtonStatus);
}
/**
 * @brief Initialize WiFi and connect to The configured WiFi network. and then connect to the MQTT broker
 *
 */
static void wirless_init_task(void* param)
{
	wifi_connect();

	mqtt_app_start();

	vTaskDelete(NULL);
}

static void mqtt_msg_pars_task(void* param)
{
	mqtt_buffer_t mqttBuffer = {0};

	const char publishRequest = 1;

	while(1)
	{
		if(xQueueReceive(mqttSubscribe_queue, (void *)&mqttBuffer, portMAX_DELAY))
		{
			switch (mqttBuffer.eventType)
			{
				case MQTT_BROKER_CONNECT:
					_ui_text_wifiIndicate(true);

					mqtt_publish(MQTT_REQUEST_TOPIC, &publishRequest, 1);
					break;
				case MQTT_BROKER_DISCONNECT:
					_ui_text_wifiIndicate(false);
					break;
				case MQTT_TOPIC_DATA_RX:


					main_tempretureStringPrepare(mqttBuffer.data, targetString);

					_ui_temp_set(targetString);

					break;
				default:
					break;
			}
		}
	}
}

static void time_handle_task(void* param)
{
	struct tm  Time = {0};

	char tempString[3] = {0};

	TickType_t xLastWakeTime = xTaskGetTickCount();

	const uint32_t tempUpdatePeriod = 60 * 60; //1 hour

	static uint32_t tempUpdateCounter = 0;

	const char publishRequest = 1;
	while(1)
	{
		vTaskDelayUntil(&xLastWakeTime, pdMS_TO_TICKS(1000) );

		sntp_time_get(&Time);

		sprintf(tempString,"%02d",Time.tm_hour);

		realTime.sel.hour = (tempString[1] << 8);
		realTime.sel.hour |= (tempString[0]);

		sprintf(tempString,"%02d",Time.tm_min);

		realTime.sel.minute = (tempString[1] << 8);
		realTime.sel.minute |= (tempString[0]);

		++tempUpdateCounter;

		if(tempUpdatePeriod <= tempUpdateCounter)
		{
			mqtt_publish(MQTT_REQUEST_TOPIC, &publishRequest, 1);

			tempUpdateCounter = 0;
		}

	}
}
/**
 * @brief 	Create a proper temperature value showing string
 *
 * @param 	tempString	:	string received over MQTT
 *
 * @param 	targetString:	string to copy the formed string to
 */
static void main_tempretureStringPrepare(char* tempString, char* targetString)
{
	const char tempUnit[4] 		= " °C";
	const char tempStingLength 	= 3;
	for(uint8_t i = 0; i < tempStingLength; ++i)
	{
		if(!isalnum((int)tempString[i]))
		{
			strcpy(&tempString[i], tempUnit);
			break;
		}
	}

	strcpy(targetString,tempString);

	targetString[6] = 0;

}

/*************************************** USEFUL ELECTRONICS*****END OF FILE****/
