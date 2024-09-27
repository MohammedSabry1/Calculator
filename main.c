/*
 * main.c
 *
 *  Created on: Aug 9, 2024
 *      Author: Mohamed
 */
#include "../LIB/STD_TYPE.h"
#include "../LIB/BIT_MATH.h"
#include"../MCAL/DIO/DIO_Interface.h"
#include "../HAL/LCD/LCD_Interface.h"
#include "../HAL/KEYBAD/KEYBAD_Interface.h"
#include "../MCAL/EXTI/EXTI_Interface.h"
#include "../MCAL/Global_Interrupt/GIE_Interface.h"
#include "../MCAL/ADC/ADC_Interface.h"
#include "../APP/Calculation/Calculation_Interface.h"
#include <avr/interrupt.h>
#include <util/delay.h>



int main(){
	LcdInit();
	vKeyPadInit();


	while(1){

		KeyPadCalc();
	}
}









//	vSetPinDirection(PORT_C,PIN_2,output);
//	vMod_EXTI(EXTI0,LOGIC_CHANGE);
//	vEnable_EXTI(EXTI0);
//	ENABLE_GIE();

//		vConvertNumbersToString(u16ADCVoltRead(Channel_A1));
//		_delay_ms(1000);
//		vClearDisplay();
//		_delay_ms(1000);





//	vSetPinDirection(PORT_D,PIN_5,output);
//	// SELECR OCR1A NON INVERTING
//	SET_BIT(TCCR1A,COM1A1);
//	CLEAR_BIT(TCCR1A,COM1A0);
//
//	// SELECT TIMEFR1 MODE 14
//	CLEAR_BIT(TCCR1A,WGM10);
//	SET_BIT(TCCR1A , WGM11);
//	SET_BIT(TCCR1B,WGM12);
//	SET_BIT(TCCR1B,WGM13);
//	// SELECT PRESCALLER 256
//	CLEAR_BIT(TCCR1B,CS10);
//	CLEAR_BIT(TCCR1B,CS11);
//	SET_BIT(TCCR1B,CS12);
//
//
//	ICR1 = 1250;
//
//
//	for(int i=0 ; i<5 ;i++)
//	{
//		OCR1A = 61;
//		_delay_ms(1000);
//		OCR1A = 93;
//		_delay_ms(1000);
//		OCR1A = 125;
//		_delay_ms(1000);
//		OCR1A = 93;
//				_delay_ms(1000);
//	}
