#include <MQ4.h>

void MQ4_Init(MQ4*mq4,ADC_HandleTypeDef*adc){

	mq4->ADC = adc;
	mq4->R0 = getR0(mq4);

}


float getVoltage(ADC_HandleTypeDef* hadc) {

	HAL_ADC_Start(hadc);
	HAL_ADC_PollForConversion(hadc, 100);
	uint16_t adcRead = HAL_ADC_GetValue(hadc);
	HAL_ADC_Stop(hadc);

	return  (float)adcRead * Vstep; // PRODUCT With v step

}


float getResistance(MQ4*mq4) {
    float voltage = getVoltage(mq4->ADC);
    float rs = ((5 * RL) / voltage) - (float)RL;
    if (rs < 0) {
        rs = 0;
    }
    return rs;
}

float getR0(MQ4*mq4) {
    float r0 = getResistance(mq4) / 4.4;
    return r0;
}



float getPPM(MQ4*mq4,float m,float b) {
    float ratio = getResistance(mq4) / mq4->R0;
    float ppm_log = (log10(ratio) - b) / m;
    float ppm = pow(10, ppm_log);
    if (ppm < 0) {
        ppm = 0;
    }
    return ppm;
}


float getCH4(MQ4*mq4) {
    return getPPM(mq4,-0.3963,1.1889);
}

