
#include "ultrasonic_sensor.h"

uint8 g_edgeCount = 0;
uint16 HIGH_TIME=0;
uint16 PERIOD_TIME=0;
uint16 PeriodPlusHIGH_TIME=0;
uint16 DISTANCE=0;


void Ultrasonic_init(void)
{

	ICU_ConfigType ICU_Configurations={F_CPU_8,RAISING};
	ICU_init(&ICU_Configurations);

	ICU_setCallBack(Ultrasonic_edgeProcessing);

	GPIO_setupPinDirection(PORTB_ID,PIN5_ID,PIN_OUTPUT); //set trigger pin as output


}


void Ultrasonic_Trigger(void) //send trigger pulse to the ultrasonic
{
GPIO_writePin(PORTB_ID,PIN5_ID,LOGIC_HIGH);
_delay_ms(10);
GPIO_writePin(PORTB_ID,PIN5_ID,LOGIC_LOW);
}


uint16 Ultrasonic_readDistance(void)
{
Ultrasonic_Trigger();
if(HIGH_TIME!=0)
{

	DISTANCE=HIGH_TIME/60;  //Calibration Factor =60
	DISTANCE+=1;   // add 1 for precise measured value
}

return DISTANCE;
}


void Ultrasonic_edgeProcessing(void)
{
	g_edgeCount ++;
	if(g_edgeCount ==1)
	{
		//Clear the timer counter register to start measurements from the first detected rising edge
		ICU_clearTimerValue();

		// Detect falling edge
		ICU_setEdgeDetectionType(FALLING);
	}
	if(g_edgeCount ==2)
	{
		HIGH_TIME=ICU_getInputCaptureValue();

		// Detect RAISING edge
		ICU_setEdgeDetectionType(RAISING);
		g_edgeCount=0;
	}

}
