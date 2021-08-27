#include "mbed.h"
#include "DisplayManager.h"
#include "CalculatorManager.h"


#pragma once

class Controller {

	public:
		Controller();

		void filterOperatorPress(int op_type);
		void filterNumberPress(int num_type);
		void filterFnPress(int fn_type);



	private:
		DisplayManager lcd;
		CalculatorManager calc;

		int clear_count;	// Count how many times clear has been pressed (two for all clear)



};

