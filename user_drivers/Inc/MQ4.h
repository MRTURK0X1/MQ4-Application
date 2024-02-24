#ifndef USER_DRIVERS_INC_MQ4_H_
#define USER_DRIVERS_INC_MQ4_H_

#include "stm32f1xx_hal.h"
#include <math.h>
/// Resistor on Sensor in kΩ
#define RL 1.0

/// Voltage on Sensor in V
#define VIn 5

/// Board analog Input Resolution
#define Resolution 4096



#define Vstep (float)VIn/(Resolution-1)



typedef struct _MQ4{

	ADC_HandleTypeDef* ADC;
	float R0;

}MQ4;



void MQ4_Init(MQ4*mq4,ADC_HandleTypeDef*adc);

/// Assume CO2 Level is the default Atmospheric Level (~400ppm)
float getR0(MQ4*mq4);

/// Gets the resolved sensor voltage
float getVoltage(ADC_HandleTypeDef* hadc);

/// Calculates the Resistance of the Sensor
float getResistance(MQ4*mq4);


/// Calculates ppm
float getPPM(MQ4*mq4, float m, float b);


/// Gets ppm of ammonia in Air (NH3)
float getCH4(MQ4*mq4);

#endif /* USER_DRIVERS_INC_MQ4_H_ */
