#include "mbed.h"
#include "ButtonManager.h"
#include "Controller.h"
//#include "CalcDefineList.h"
#include "DebounceIn.h"

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


//Column 1
DebounceIn btn_r1c1(PE_7, PullDown);
DebounceIn btn_r2c1(PB_2, PullDown);
DebounceIn btn_r3c1(PB_1, PullDown);
DebounceIn btn_r4c1(PB_0, PullDown);
DebounceIn btn_r5c1(PC_5, PullDown);
DebounceIn btn_r6c1(PC_4, PullDown);
DebounceIn btn_r7c1(PA_7, PullDown);
DebounceIn btn_r8c1(PA_6, PullDown);
DebounceIn btn_r9c1(PA_5, PullDown);
DebounceIn btn_r10c1(PA_4, PullDown);

//Column 2
DebounceIn btn_r1c2(PA_3, PullDown);
DebounceIn btn_r2c2(PB_12, PullDown);
DebounceIn btn_r3c2(PB_13, PullDown);
DebounceIn btn_r4c2(PD_8, PullDown);
DebounceIn btn_r5c2(PD_9, PullDown);
DebounceIn btn_r6c2(PD_10, PullDown);
DebounceIn btn_r7c2(PA_2, PullDown);
DebounceIn btn_r8c2(PA_1, PullDown);
DebounceIn btn_r9c2(PA_0, PullDown);
DebounceIn btn_r10c2(PD_12, PullDown);

//Column 3
DebounceIn btn_r1c3(PC_3, PullDown);
DebounceIn btn_r2c3(PC_2, PullDown);
DebounceIn btn_r3c3(PC_1, PullDown);
DebounceIn btn_r4c3(PC_0, PullDown);
DebounceIn btn_r5c3(PD_13, PullDown);
DebounceIn btn_r6c3(PD_14, PullDown);
DebounceIn btn_r7c3(PD_15, PullDown);
DebounceIn btn_r8c3(PC_6, PullDown);
DebounceIn btn_r9c3(PC_7, PullDown);
DebounceIn btn_r10c3(PC_8, PullDown);

//Column 4
DebounceIn btn_r1c4(PE_6, PullDown);
DebounceIn btn_r2c4(PE_5, PullDown);
DebounceIn btn_r3c4(PE_4, PullDown);
DebounceIn btn_r4c4(PE_3, PullDown);
DebounceIn btn_r5c4(PE_2, PullDown);
DebounceIn btn_r6c4(PC_9, PullDown);
DebounceIn btn_r7c4(PA_8, PullDown);
DebounceIn btn_r8c4(PA_9, PullDown);
DebounceIn btn_r9c4(PA_10, PullDown);
DebounceIn btn_r10c4(PA_15, PullDown);

//Column 5
DebounceIn btn_r1c5(PC_10, PullDown);
DebounceIn btn_r2c5(PC_12, PullDown);
DebounceIn btn_r3c5(PD_0, PullDown);
DebounceIn btn_r4c5(PD_1, PullDown);
DebounceIn btn_r5c5(PD_2, PullDown);
DebounceIn btn_r6c5(PD_3, PullDown);
DebounceIn btn_r7c5(PD_4, PullDown);
DebounceIn btn_r8c5(PD_5, PullDown);
DebounceIn btn_r9c5(PD_6, PullDown);
DebounceIn btn_r10c5(PD_7, PullDown);

ButtonManager::ButtonManager() {
    //Column 1
    btn_r1c1.mode(PullDown);
    btn_r2c1.mode(PullDown);
    btn_r3c1.mode(PullDown);
    btn_r4c1.mode(PullDown);
    btn_r5c1.mode(PullDown);
    btn_r6c1.mode(PullDown);
    btn_r7c1.mode(PullDown);
    btn_r8c1.mode(PullDown);
    btn_r9c1.mode(PullDown);
    btn_r10c1.mode(PullDown);

    //Column 2
    btn_r1c2.mode(PullDown);
    btn_r2c2.mode(PullDown);
    btn_r3c2.mode(PullDown);
    btn_r4c2.mode(PullDown);
    btn_r5c2.mode(PullDown);
    btn_r6c2.mode(PullDown);
    btn_r7c2.mode(PullDown);
    btn_r8c2.mode(PullDown);
    btn_r9c2.mode(PullDown);
    btn_r10c2.mode(PullDown);

    //Column 3
    btn_r1c3.mode(PullDown);
    btn_r2c3.mode(PullDown);
    btn_r3c3.mode(PullDown);
    btn_r4c3.mode(PullDown);
    btn_r5c3.mode(PullDown);
    btn_r6c3.mode(PullDown);
    btn_r7c3.mode(PullDown);
    btn_r8c3.mode(PullDown);
    btn_r9c3.mode(PullDown);
    btn_r10c3.mode(PullDown);

    //Column 4
    btn_r1c4.mode(PullDown);
    btn_r2c4.mode(PullDown);
    btn_r3c4.mode(PullDown);
    btn_r4c4.mode(PullDown);
    btn_r5c4.mode(PullDown);
    btn_r6c4.mode(PullDown);
    btn_r7c4.mode(PullDown);
    btn_r8c4.mode(PullDown);
    btn_r9c4.mode(PullDown);
    btn_r10c4.mode(PullDown);

    //Column 5
    btn_r1c5.mode(PullDown);
    btn_r2c5.mode(PullDown);
    btn_r3c5.mode(PullDown);
    btn_r4c5.mode(PullDown);
    btn_r5c5.mode(PullDown);
    btn_r6c5.mode(PullDown);
    btn_r7c5.mode(PullDown);
    btn_r8c5.mode(PullDown);
    btn_r9c5.mode(PullDown);
    btn_r10c5.mode(PullDown);


    //Column 1
    bool btn_r1c1_press = false;
    bool btn_r2c1_press = false;
    bool btn_r3c1_press = false;
    bool btn_r4c1_press = false;
    bool btn_r5c1_press = false;
    bool btn_r6c1_press = false;
    bool btn_r7c1_press = false;
    bool btn_r8c1_press = false;
    bool btn_r9c1_press = false;
    bool btn_r10c1_press = false;

    //Column 2
    bool btn_r1c2_press = false;
    bool btn_r2c2_press = false;
    bool btn_r3c2_press = false;
    bool btn_r4c2_press = false;
    bool btn_r5c2_press = false;
    bool btn_r6c2_press = false;
    bool btn_r7c2_press = false;
    bool btn_r8c2_press = false;
    bool btn_r9c2_press = false;
    bool btn_r10c2_press = false;

    //Column 3
    bool btn_r1c3_press = false;
    bool btn_r2c3_press = false;
    bool btn_r3c3_press = false;
    bool btn_r4c3_press = false;
    bool btn_r5c3_press = false;
    bool btn_r6c3_press = false;
    bool btn_r7c3_press = false;
    bool btn_r8c3_press = false;
    bool btn_r9c3_press = false;
    bool btn_r10c3_press = false;

    //Column 4
    bool btn_r1c4_press = false;
    bool btn_r2c4_press = false;
    bool btn_r3c4_press = false;
    bool btn_r4c4_press = false;
    bool btn_r5c4_press = false;
    bool btn_r6c4_press = false;
    bool btn_r7c4_press = false;
    bool btn_r8c4_press = false;
    bool btn_r9c4_press = false;
    bool btn_r10c4_press = false;

    //Column 5
    bool btn_r1c5_press = false;
    bool btn_r2c5_press = false;
    bool btn_r3c5_press = false;
    bool btn_r4c5_press = false;
    bool btn_r5c5_press = false;
    bool btn_r6c5_press = false;
    bool btn_r7c5_press = false;
    bool btn_r8c5_press = false;
    bool btn_r9c5_press = false;
    bool btn_r10c5_press = false;


}

void ButtonManager::scanKeys() {
    //Column 1
    if (btn_r1c1.read() && !(btn_r1c1_press)) { btn_r1c1_press = true; return; }
    if (btn_r2c1.read() && !(btn_r2c1_press)) { btn_r2c1_press = true; return; }
    if (btn_r3c1.read() && !(btn_r3c1_press)) { btn_r3c1_press = true; return; }
    if (btn_r4c1.read() && !(btn_r4c1_press)) { btn_r4c1_press = true; return; }
    if (btn_r5c1.read() && !(btn_r5c1_press)) { btn_r5c1_press = true; return; }
    if (btn_r6c1.read() && !(btn_r6c1_press)) { btn_r6c1_press = true; return; }
    if (btn_r7c1.read() && !(btn_r7c1_press)) { btn_r7c1_press = true; return; }
    if (btn_r8c1.read() && !(btn_r8c1_press)) { btn_r8c1_press = true; return; }
    if (btn_r9c1.read() && !(btn_r9c1_press)) { btn_r9c1_press = true; return; }
    if (btn_r10c1.read() && !(btn_r10c1_press)) { btn_r10c1_press = true; return; }

    //Column 2
    if (btn_r1c2.read() && !(btn_r1c2_press)) { btn_r1c2_press = true; return; }
    if (btn_r2c2.read() && !(btn_r2c2_press)) { btn_r2c2_press = true; return; }
    if (btn_r3c2.read() && !(btn_r3c2_press)) { btn_r3c2_press = true; return; }
    if (btn_r4c2.read() && !(btn_r4c2_press)) { btn_r4c2_press = true; return; }
    if (btn_r5c2.read() && !(btn_r5c2_press)) { btn_r5c2_press = true; return; }
    if (btn_r6c2.read() && !(btn_r6c2_press)) { btn_r6c2_press = true; return; }
    if (btn_r7c2.read() && !(btn_r7c2_press)) { btn_r7c2_press = true; return; }
    if (btn_r8c2.read() && !(btn_r8c2_press)) { btn_r8c2_press = true; return; }
    if (btn_r9c2.read() && !(btn_r9c2_press)) { btn_r9c2_press = true; return; }
    if (btn_r10c2.read() && !(btn_r10c2_press)) { btn_r10c2_press = true; return; }

    //Column 3
    if (btn_r1c3.read() && !(btn_r1c3_press)) { btn_r1c3_press = true; return; }
    if (btn_r2c3.read() && !(btn_r2c3_press)) { btn_r2c3_press = true; return; }
    if (btn_r3c3.read() && !(btn_r3c3_press)) { btn_r3c3_press = true; return; }
    if (btn_r4c3.read() && !(btn_r4c3_press)) { btn_r4c3_press = true; return; }
    if (btn_r5c3.read() && !(btn_r5c3_press)) { btn_r5c3_press = true; return; }
    if (btn_r6c3.read() && !(btn_r6c3_press)) { btn_r6c3_press = true; return; }
    if (btn_r7c3.read() && !(btn_r7c3_press)) { btn_r7c3_press = true; return; }
    if (btn_r8c3.read() && !(btn_r8c3_press)) { btn_r8c3_press = true; return; }
    if (btn_r9c3.read() && !(btn_r9c3_press)) { btn_r9c3_press = true; return; }
    if (btn_r10c3.read() && !(btn_r10c3_press)) { btn_r10c3_press = true; return; }

    //Column 4
    if (btn_r1c4.read() && !(btn_r1c4_press)) { btn_r1c4_press = true; return; }
    if (btn_r2c4.read() && !(btn_r2c4_press)) { btn_r2c4_press = true; return; }
    if (btn_r3c4.read() && !(btn_r3c4_press)) { btn_r3c4_press = true; return; }
    if (btn_r4c4.read() && !(btn_r4c4_press)) { btn_r4c4_press = true; return; }
    if (btn_r5c4.read() && !(btn_r5c4_press)) { btn_r5c4_press = true; return; }
    if (btn_r6c4.read() && !(btn_r6c4_press)) { btn_r6c4_press = true; return; }
    if (btn_r7c4.read() && !(btn_r7c4_press)) { btn_r7c4_press = true; return; }
    if (btn_r8c4.read() && !(btn_r8c4_press)) { btn_r8c4_press = true; return; }
    if (btn_r9c4.read() && !(btn_r9c4_press)) { btn_r9c4_press = true; return; }
    if (btn_r10c4.read() && !(btn_r10c4_press)) { btn_r10c4_press = true; return; }

    //Column 5
    if (btn_r1c5.read() && !(btn_r1c5_press)) { btn_r1c5_press = true; return; }
    if (btn_r2c5.read() && !(btn_r2c5_press)) { btn_r2c5_press = true; return; }
    if (btn_r3c5.read() && !(btn_r3c5_press)) { btn_r3c5_press = true; return; }
    if (btn_r4c5.read() && !(btn_r4c5_press)) { btn_r4c5_press = true; return; }
    if (btn_r5c5.read() && !(btn_r5c5_press)) { btn_r5c5_press = true; return; }
    if (btn_r6c5.read() && !(btn_r6c5_press)) { btn_r6c5_press = true; return; }
    if (btn_r7c5.read() && !(btn_r7c5_press)) { btn_r7c5_press = true; return; }
    if (btn_r8c5.read() && !(btn_r8c5_press)) { btn_r8c5_press = true; return; }
    if (btn_r9c5.read() && !(btn_r9c5_press)) { btn_r9c5_press = true; return; }
    if (btn_r10c5.read() && !(btn_r10c5_press)) { btn_r10c5_press = true; return; }
}



void ButtonManager::handleKeys() {
	//Column 1
	if (btn_r1c1_press == true) { btn_r1c1_press = false; }
	if (btn_r2c1_press == true) { btn_r2c1_press = false; }
	if (btn_r3c1_press == true) { btn_r3c1_press = false; }
	if (btn_r4c1_press == true) { btn_r4c1_press = false; }
	if (btn_r5c1_press == true) { btn_r5c1_press = false; }
	if (btn_r6c1_press == true) { btn_r6c1_press = false; }
	if (btn_r7c1_press == true) { btn_r7c1_press = false; }
	if (btn_r8c1_press == true) { btn_r8c1_press = false; }
	if (btn_r9c1_press == true) { btn_r9c1_press = false; }
	if (btn_r10c1_press == true) { btn_r10c1_press = false; }

	//Column 2
	if (btn_r1c2_press == true) { btn_r1c2_press = false; }
	if (btn_r2c2_press == true) { btn_r2c2_press = false; }
	if (btn_r3c2_press == true) { btn_r3c2_press = false; }
	if (btn_r4c2_press == true) { btn_r4c2_press = false; }
	if (btn_r5c2_press == true) { controller->filterNumberPress(NUM_D); btn_r5c2_press = false; }
	if (btn_r6c2_press == true) { controller->filterNumberPress(NUM_A); btn_r6c2_press = false; }
	if (btn_r7c2_press == true) { controller->filterNumberPress(NUM_7); btn_r7c2_press = false; }
	if (btn_r8c2_press == true) { controller->filterNumberPress(NUM_4); btn_r8c2_press = false; }
	if (btn_r9c2_press == true) { controller->filterNumberPress(NUM_1); btn_r9c2_press = false; }
	if (btn_r10c2_press == true) { btn_r10c2_press = false; }

	//Column 3
	if (btn_r1c3_press == true) { btn_r1c3_press = false; }
	if (btn_r2c3_press == true) { btn_r2c3_press = false; }
	if (btn_r3c3_press == true) { btn_r3c3_press = false; }
	if (btn_r4c3_press == true) { btn_r4c3_press = false; }
	if (btn_r5c3_press == true) { controller->filterNumberPress(NUM_E); btn_r5c3_press = false; }
	if (btn_r6c3_press == true) { controller->filterNumberPress(NUM_B); btn_r6c3_press = false; }
	if (btn_r7c3_press == true) { controller->filterNumberPress(NUM_8); btn_r7c3_press = false; }
	if (btn_r8c3_press == true) { controller->filterNumberPress(NUM_5); btn_r8c3_press = false; }
	if (btn_r9c3_press == true) { controller->filterNumberPress(NUM_2); btn_r9c3_press = false; }
	if (btn_r10c3_press == true) { btn_r10c3_press = false; }

	//Column 4
	if (btn_r1c4_press == true) { btn_r1c4_press = false; }
	if (btn_r2c4_press == true) { btn_r2c4_press = false; }
	if (btn_r3c4_press == true) { btn_r3c4_press = false; }
	if (btn_r4c4_press == true) { btn_r4c4_press = false; }
	if (btn_r5c4_press == true) { controller->filterNumberPress(NUM_F); btn_r5c4_press = false; }
	if (btn_r6c4_press == true) { controller->filterNumberPress(NUM_C); btn_r6c4_press = false; }
	if (btn_r7c4_press == true) { controller->filterNumberPress(NUM_9); btn_r7c4_press = false; }
	if (btn_r8c4_press == true) { controller->filterNumberPress(NUM_6); btn_r8c4_press = false; }
	if (btn_r9c4_press == true) { controller->filterNumberPress(NUM_3); btn_r9c4_press = false; }
	if (btn_r10c4_press == true) { btn_r10c4_press = false; }

	//Column 5
	if (btn_r1c5_press == true) { controller->filterFnPress(FN_CLEAR); btn_r1c5_press = false; }
	if (btn_r2c5_press == true) { controller->filterOperatorPress(OP_XOR); btn_r2c5_press = false; }
	if (btn_r3c5_press == true) { controller->filterOperatorPress(OP_NOR); btn_r3c5_press = false; }
	if (btn_r4c5_press == true) { controller->filterOperatorPress(OP_OR); btn_r4c5_press = false; }
	if (btn_r5c5_press == true) { controller->filterOperatorPress(OP_AND); btn_r5c5_press = false; }
	if (btn_r6c5_press == true) { controller->filterOperatorPress(OP_DIVISION); btn_r6c5_press = false; }
	if (btn_r7c5_press == true) { controller->filterOperatorPress(OP_MULTIPLICATION); btn_r7c5_press = false; }
	if (btn_r8c5_press == true) { controller->filterOperatorPress(OP_SUBTRACTION); btn_r8c5_press = false; }
	if (btn_r9c5_press == true) { controller->filterOperatorPress(OP_ADDITION); btn_r9c5_press = false; }
	if (btn_r10c5_press == true) { controller->filterFnPress(FN_EQUALS); btn_r10c5_press = false; }

	wait_ms(250); //manual debounce here for now, should be threaded for later

	/*
	 *  void Controller::filterOperatorPress(int op_type) {
			calc.setOperator(op_type);
		}


		void Controller::filterNumberPress(int num) {
			calc.registerNumber(num);
		}

		void Controller::filterFnPress(int num) {
			calc.registerNumber(num);
		}
	 */

}

void ButtonManager::setPC(Serial *pc) {
    this->pc = pc;
    pc->printf("PC Set!\n");
}

void ButtonManager::setController(Controller *controller) {
    this->controller = controller;
}


