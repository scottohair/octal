#include "mbed.h"
#include "Controller.h"

//#include "CalcDefineList.h"
#include "DisplayManager.h"
#include "CalculatorManager.h"

// Operator types
#define OP_NONE 0
#define OP_ADDITION 1
#define OP_SUBTRACTION 2
#define OP_MULTIPLICATION 3
#define OP_DIVISION 4
#define OP_AND 5
#define OP_OR 6
#define OP_XOR 7
#define OP_NAND 8
#define OP_NOR 9
#define OP_XNOR 10
#define OP_MODULUS 11
#define OP_BITSHIFTRIGHT 12
#define OP_BITSHIFTLEFT 13
#define OP_XSHIFTRIGHTY 14
#define OP_XSHIFTLEFTY 15


// Number types
#define NUM_0 0
#define NUM_1 1
#define NUM_2 2
#define NUM_3 3
#define NUM_4 4
#define NUM_5 5
#define NUM_6 6
#define NUM_7 7
#define NUM_8 8
#define NUM_9 9
#define NUM_A 10
#define NUM_B 11
#define NUM_C 12
#define NUM_D 13
#define NUM_E 14
#define NUM_F 15
#define NUM_00 16
#define NUM_FF 17

//Fn types
#define FN_CLEAR 0
#define FN_LEFT 1
#define FN_RIGHT 2
#define FN_ENTER 3
#define FN_2ND 4
#define FN_TWOS 5
#define FN_ONES 6
#define FN_BASE8 7
#define FN_BASE10 8
#define FN_BASE16 9
#define FN_WAKE 10
#define FN_UNICODEASCII 11
#define FN_ROR 12
#define FN_ROL 13
#define FN_BFLIP 14
#define FN_WFLIP 15
#define FN_MODULUS 16
#define FN_PUSHBT 17
#define FN_POPBT 17
#define FN_EQUALS 18

Controller::Controller() {
	lcd.initialize();
	calc.initializeMemory();
	clear_count = 0;

	lcd.displayNumber(calc.getCurrentNumber());
}


void Controller::filterOperatorPress(int op_type) {
	calc.setOperator(op_type);

	char op_str[10];
	switch(op_type) {
		case OP_NONE:
			break;
		case OP_ADDITION:
			strcpy(op_str, "+");
			break;
		case OP_SUBTRACTION:
			strcpy(op_str, "-");
			break;
		case OP_MULTIPLICATION:
			strcpy(op_str, "*");
			break;
		case OP_DIVISION:
			strcpy(op_str, "/");
			break;
		case OP_AND:
			strcpy(op_str, "AND");
			break;
		case OP_OR:
			strcpy(op_str, "OR");
			break;
		case OP_XOR:
			strcpy(op_str, "XOR");
			break;
		case OP_NAND:
			strcpy(op_str, "NAND");
			break;
		case OP_NOR:
			strcpy(op_str, "NOR");
			break;
		case OP_XNOR:
			strcpy(op_str, "XNOR");
			break;
		case OP_MODULUS:
			strcpy(op_str, "%");
			break;
		case OP_BITSHIFTRIGHT:
			strcpy(op_str, ">>");
			break;
		case OP_BITSHIFTLEFT:
			strcpy(op_str, "<<");
			break;
		case OP_XSHIFTRIGHTY:
			strcpy(op_str, "X>>Y");
			break;
		case OP_XSHIFTLEFTY:
			strcpy(op_str, "X<<Y");
			break;
	}

	lcd.displayOperator(op_str);

}


void Controller::filterNumberPress(int num_type) {
	switch (num_type) {
		case NUM_0:
			calc.registerNumber('0');
			break;
		case NUM_1:
			calc.registerNumber('1');
			break;
		case NUM_2:
			calc.registerNumber('2');
			break;
		case NUM_3:
			calc.registerNumber('3');
			break;
		case NUM_4:
			calc.registerNumber('4');
			break;
		case NUM_5:
			calc.registerNumber('5');
			break;
		case NUM_6:
			calc.registerNumber('6');
			break;
		case NUM_7:
			calc.registerNumber('7');
			break;
		case NUM_8:
			calc.registerNumber('8');
			break;
		case NUM_9:
			calc.registerNumber('9');
			break;
		case NUM_A:
			calc.registerNumber('A');
			break;
		case NUM_B:
			calc.registerNumber('B');
			break;
		case NUM_C:
			calc.registerNumber('C');
			break;
		case NUM_D:
			calc.registerNumber('D');
			break;
		case NUM_E:
			calc.registerNumber('E');
			break;
		case NUM_F:
			calc.registerNumber('F');
			break;
	}

	lcd.displayNumber(calc.getCurrentNumber());

}

void Controller::filterFnPress(int fn_type) {
	switch (fn_type) {
		case FN_CLEAR:
			if (clear_count == 0) {
				calc.clear();
				clear_count = 1;
				lcd.clearNumber();
			}
			else {
				calc.allClear();
				lcd.clearNumber();
			}
			break;
		case FN_EQUALS:
			calc.equals();
			lcd.displayNumber(calc.getResult());
			break;
	}

}


