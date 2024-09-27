/*
 * Calculation_Program.c
 *
 *  Created on: Sep 27, 2024
 *      Author: Mohamed
 */

#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPE.h"
#include"../../MCAL/DIO/DIO_Interface.h"
#include "../../HAL/KEYBAD/KEYBAD_Interface.h"
#include "../../HAL/LCD/LCD_Interface.h"
#include <util/delay.h>
#include "Calculation_Interface.h"

void KeyPadCalc(){
	u8 Key = NoKey;
	u16 num = 0;
	u16 numStack[10];
	u8 operatorStack[10];
	u8 topNum = 0;
	u8 topOp = 0;

	while(1)
	{
		Key = u8KeyPressed();
		if(Key != NoKey){
			LcdWriteData(Key);

			// If the key is a digit, form the number
			if(Key >= '0' && Key <= '9'){
				num = (num * 10) + (Key - '0');
			}

			// If the key is an operator, push the current number to the stack and process operators
			if(Key == '+' || Key == '-' || Key == 'x' || Key == '/'){
				numStack[topNum++] = num; // Push number to stack
				num = 0; // Reset number

				// If there's an operator with higher or equal precedence, calculate it
				while(topOp > 0 && (operatorStack[topOp-1] == 'x' || operatorStack[topOp-1] == '/')){
					u16 b = numStack[--topNum];
					u16 a = numStack[--topNum];
					u8 op = operatorStack[--topOp];

					if(op == 'x'){
						numStack[topNum++] = a * b;
					} else if(op == '/'){
						numStack[topNum++] = a / b;
					}
				}
				operatorStack[topOp++] = Key; // Push operator to stack
			}

			// If the key is '=', evaluate the remaining operations
			if(Key == '='){
				numStack[topNum++] = num; // Push last number to stack

				// Evaluate the remaining operations
				while(topOp > 0){
					u16 b = numStack[--topNum];
					u16 a = numStack[--topNum];
					u8 op = operatorStack[--topOp];

					if(op == '+'){
						numStack[topNum++] = a + b;
					} else if(op == '-'){
						numStack[topNum++] = a - b;
					} else if(op == 'x'){
						numStack[topNum++] = a * b;
					} else if(op == '/'){
						numStack[topNum++] = a / b;
					}
				}

				vSetCursor(2, 1);
				vConvertNumbersToString(numStack[0]); // Final result
				num = 0; // Reset for the next calculation
				topNum = 0;
				topOp = 0;
			}

			// Clear display if 'c' is pressed
			if(Key == 'c'){
				vClearDisplay();
				num = 0;
				topNum = 0;
				topOp = 0;
			}
		}
	}
}
