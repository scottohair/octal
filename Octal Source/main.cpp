/* mbed Microcontroller Library
 * Copyright (c) 2018 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "ButtonManager.h"
#include "Controller.h"

Serial pc(PB_6, PB_7, 115200);
Controller controller;
ButtonManager button_manager;

FileHandle* mbed::mbed_override_console(int)
{
    static UARTSerial myConsole(PB_6, PB_7, 115200);
    return &myConsole;
}


// main() runs in its own thread in the OS
int main()
{
	// Setup key scan
    pc.printf("setting pc...\n");
    button_manager.setPC(&pc);

    // Setup controller
	pc.printf("setting controller for button scan...\n");
	button_manager.setController(&controller);

	pc.printf("looping...\n");
    while(1) {
        button_manager.scanKeys();
        button_manager.handleKeys();
    }

}
