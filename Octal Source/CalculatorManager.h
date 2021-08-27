#include "CalcDefineList.h"
#include "mbed.h"
#pragma once

#define MAX_CHAR_CNT 16
#define A_SELECT 0
#define B_SELECT 1



class CalculatorManager {
    public:
		CalculatorManager();
		void initializeMemory();
		void clear();								// Clears current number string entry from memory
		void allClear();							// Resets calculator operations memory to fresh state
		void computeResult();						// Computes the result of a + b, stores into persistent_res and back into a
		void setOperator(int op);					// Sets the operator to be used in the current equation, will also compute result if 2nd entry or greater
		bool registerNumber(char num);				// Adds char digit to current input array
		void toggleAndConvert();					// Converts input array into number and toggles input array
		long long convertStrToNum(char *str);		// Converts char array to long long
		char* getCurrentNumber();
		char* getResult();
		// Controller End Points
		void equals();								// Inputs current numeric entry then computes a + b

        void setPC(Serial *pc);						// Sets serial output for debugging

    private:
        char a_str[MAX_CHAR_CNT];					// Stores first string entry for numbers
        char b_str[MAX_CHAR_CNT];					// Stores second string entry for numbers
        char persistent_res_str[MAX_CHAR_CNT];
        int a_str_pos;								// Track char location for entry
        int b_str_pos;								// Track char location for entry
        int op;										// Current operand will be stored here while next number is input
        bool first_op;								// Only true when first number is being entered

		long long a;								// Numeric representation of first string entry
		long long b;								// Numeric representation of second string entry
		long long persistent_res;					// Current result will always be stored here
		int num_select; 							// A_SELECT == 0 == a, B _SELECT == 1 == b, decides where to store current input


        Serial *pc;

};
