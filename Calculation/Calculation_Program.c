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

	// Function to get the precedence of operators
	u8 precedence(u8 op) {
		if (op == 'x' || op == '/') {
			return 2; // Higher precedence
		} else if (op == '+' || op == '-') {
			return 1; // Lower precedence
		}
		return 0;
	}

	// Function to apply an arithmetic operation
	u16 applyOperation(u16 a, u16 b, u8 op) {
		if (op == 'x') return a * b;
		if (op == '/') return a / b;
		if (op == '+') return a + b;
		if (op == '-') return a - b;
		return 0;
	}

	// Function to evaluate the current stack
	void evaluate() {
		u16 b = numStack[--topNum];
		u16 a = numStack[--topNum];
		u8 op = operatorStack[--topOp];
		numStack[topNum++] = applyOperation(a, b, op);
	}

	while (1) {
		Key = u8KeyPressed();
		if (Key != NoKey) {
			LcdWriteData(Key);

			// Form the number if the key is a digit
			if (Key >= '0' && Key <= '9') {
				num = (num * 10) + (Key - '0');
			}

			// If the key is an operator (+, -, x, /)
			if (Key == '+' || Key == '-' || Key == 'x' || Key == '/') {
				// Push the current number to the stack
				numStack[topNum++] = num;
				num = 0;

				// Evaluate previous operators with higher or equal precedence
				while (topOp > 0 && precedence(operatorStack[topOp - 1]) >= precedence(Key)) {
					evaluate();
				}

				// Push the current operator to the stack
				operatorStack[topOp++] = Key;
			}

			// If the key is '=', evaluate the remaining operations
			if (Key == '=') {
				numStack[topNum++] = num;

				// Evaluate all remaining operators
				while (topOp > 0) {
					evaluate();
				}

				// Display the final result
				vSetCursor(2, 1);
				vConvertNumbersToString(numStack[0]);

				// Reset for the next calculation
				num = 0;
				topNum = 0;
				topOp = 0;
			}

			// Clear the display if 'c' is pressed
			if (Key == 'c') {
				vClearDisplay();
				num = 0;
				topNum = 0;
				topOp = 0;
			}
		}
	}


}


