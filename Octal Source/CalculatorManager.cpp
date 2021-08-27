#include "mbed.h"
#include "CalculatorManager.h"



CalculatorManager::CalculatorManager() {
}

void CalculatorManager::initializeMemory() {
	memset(a_str, 0, sizeof(a_str));
	memset(b_str, 0, sizeof(b_str));
	memset(persistent_res_str, 0, sizeof(persistent_res_str));
	a_str_pos = 0;
	b_str_pos = 0;
	a = 0;
	b = 0;
	persistent_res = 0;
	num_select = 0; 	// Select 'a' for first number capture
	first_op = true;

}

void CalculatorManager::clear() {
	switch (num_select) {
		case A_SELECT:
			memset(a_str, 0, sizeof(a_str));
			a_str_pos = 0;
			break;
		case B_SELECT:
			memset(b_str, 0, sizeof(a_str));
			b_str_pos = 0;
			break;
	}
}

void CalculatorManager::allClear() {
	initializeMemory();
}

void CalculatorManager::equals() {
	toggleAndConvert();
	computeResult();
}

void CalculatorManager::computeResult() {
	long long res = 0;

	switch (op) {
		case OP_NONE:
			break;
		case OP_ADDITION:
			res = a + b;
			break;
		case OP_SUBTRACTION:
			res = a - b;
			break;
		case OP_MULTIPLICATION:
			res = a * b;
			break;
		case OP_DIVISION:
			res = a / b;
			break;
		case OP_AND:
			res = a & b;
			break;
		case OP_OR:
			res = a | b;
			break;
		case OP_XOR:
			res = a ^ b;
			break;
		case OP_NAND:
			res = ~(a & b);
			break;
		case OP_NOR:
			res = ~(a | b);
			break;
		case OP_XNOR:
			res = ~(a ^ b);
			break;

	}

	persistent_res = res;   // Result is stored in persistent_res for use in view
	sprintf(persistent_res_str, "%lld", res);
	a = res;                // Result is stored in a for use in continuing operations
	num_select = B_SELECT;  // num_select set to B to capture next input number

}

void CalculatorManager::setOperator(int op) {
	this->op = op;
	toggleAndConvert();

	if (first_op) {
		first_op = false;
	}
	else {
		computeResult();
	}

}

bool CalculatorManager::registerNumber(char num) {
	switch (num_select) {
		case A_SELECT:
			if (a_str_pos < MAX_CHAR_CNT - 1) {
				a_str[a_str_pos] = num;
				a_str_pos++;
			}
			else {
				return false;	// Max char limit hit
			}
			break;
		case B_SELECT:
			if (b_str_pos < MAX_CHAR_CNT - 1) {
				b_str[b_str_pos] = num;
				b_str_pos++;
			}
			else {
				return false; 	// Max char limit hit
			}
			break;
	}

	return true;
}

void CalculatorManager::toggleAndConvert() {
	// Toggle between numbers
	if (num_select == A_SELECT) {
		a = convertStrToNum(a_str);
		memset(a_str, 0, sizeof(a_str));
		a_str_pos = 0;
		num_select = B_SELECT;
	}
	else if (num_select == B_SELECT) {
		b = convertStrToNum(b_str);
		memset(b_str, 0, sizeof(b_str));
		b_str_pos = 0;
		num_select = A_SELECT;
	}
}

long long CalculatorManager::convertStrToNum(char *str) {
	return strtoll(str, NULL, 16);
}


void CalculatorManager::setPC(Serial *pc) {
    this->pc = pc;
    pc->printf("PC Set!\n");
}


char* CalculatorManager::getCurrentNumber() {
	if (num_select == A_SELECT) {
		return a_str;
	}
	else if (num_select == B_SELECT) {
		return b_str;
	}
}

char* CalculatorManager::getResult() {
	return persistent_res_str;
}
