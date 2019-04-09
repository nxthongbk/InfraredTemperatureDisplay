#include "legato.h"
#include "interfaces.h"

#define DISPLAY_SAMPLE_INTERVAL_IN_MILLISECONDS (10000)

static void DisplayTimerHandler
(
	le_timer_Ref_t displayTimerRef
)
{
	double pixels_temp[64];
	size_t PIXEL_NUM = 64;

	ma_infraredTemperature_read_pixel_temperature(pixels_temp, &PIXEL_NUM);

	for(int i = 0; i < 64; i++) {
		LE_INFO("Tempearture of pixel:%d is %f", i, pixels_temp[i]);
	}
}

COMPONENT_INIT
{
       	ma_infraredTemperature_Init();

        le_timer_Ref_t displayTimerRef = le_timer_Create("Display Timer");
	LE_ASSERT_OK(le_timer_SetMsInterval(displayTimerRef, DISPLAY_SAMPLE_INTERVAL_IN_MILLISECONDS));
	LE_ASSERT_OK(le_timer_SetRepeat(displayTimerRef, 0));
	LE_ASSERT_OK(le_timer_SetHandler(displayTimerRef, DisplayTimerHandler));
	LE_ASSERT_OK(le_timer_Start(displayTimerRef));
}
