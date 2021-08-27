#include "mbed.h"

#pragma once

class DisplayManager {
    public:
		DisplayManager();
		void initialize();

		void displayNumber(char* num);
		void clearNumber();
		void displayOperator(char* op);

        void setPC(Serial *pc);

    private:

        Serial *pc;

};
