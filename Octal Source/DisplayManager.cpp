#include "mbed.h"
#include "DisplayManager.h"
#include "Adafruit_GFX.h"
#include "SharpMem.h"

SharpMem lcd(400, 240);
#define BLACK 0
#define WHITE 1
int minorHalfSize; // 1/2 of lesser of display width or height


DisplayManager::DisplayManager() {

}

void DisplayManager::initialize() {
	// Setup display
	lcd.begin();
	lcd.clearDisplay();
	wait_ms(50);	// Wait for initialization

	// Print to the display
	lcd.setTextSize(3);
	lcd.setTextColor(BLACK);
	lcd.setCursor(0,0);
	lcd.refresh();

	displayNumber((char*)"TESTYWESTY");
}


void DisplayManager::displayNumber(char* num) {
	lcd.setCursor(0,0);
	lcd.printf("%s", num);
	lcd.refresh();
}

void DisplayManager::clearNumber() {
	lcd.setCursor(0,0);
	lcd.printf("                ");
	lcd.refresh();
}

void DisplayManager::displayOperator(char* op) {
	lcd.setCursor(16,5);
	lcd.printf("%s", op);
	lcd.refresh();
}


void DisplayManager::setPC(Serial *pc) {
    this->pc = pc;
    pc->printf("PC Set!\n");
}

