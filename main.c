

#include "ultrasonic_sensor.h"
#include "lcd.h"
#include "avr/io.h"

int main(void)
{

uint16 Distance=0;

SREG |=(1<<7);
Ultrasonic_init();
LCD_init();

LCD_displayString("Distance= ");
	while(1)
	{
		Distance=Ultrasonic_readDistance();
		LCD_moveCursor(0,9);
		LCD_intgerToString(Distance);
		LCD_displayString(" cm");

	}

	return 0;
}

