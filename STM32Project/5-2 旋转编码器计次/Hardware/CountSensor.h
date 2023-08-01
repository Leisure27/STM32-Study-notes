#ifndef __COUNTSENSOR_H
#define __COUNTSENSOR_H
	void CountSensorInit(void);
	void  EXTI0_IRQHandler(void);
	void  EXTI1_IRQHandler(void);
	uint16_t CountSensor_Get(void);
#endif
