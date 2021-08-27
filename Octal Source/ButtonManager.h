#include "mbed.h"
#include "Controller.h"

#pragma once

class ButtonManager {
    public:
        ButtonManager();
        void scanKeys();
        void handleKeys();
        void setPC(Serial *pc);
        void setController(Controller *controller);

    private:
        Controller *controller;
        Serial *pc;

        //Column 1
        bool btn_r1c1_press;
        bool btn_r2c1_press;
        bool btn_r3c1_press;
        bool btn_r4c1_press;
        bool btn_r5c1_press;
        bool btn_r6c1_press;
        bool btn_r7c1_press;
        bool btn_r8c1_press;
        bool btn_r9c1_press;
        bool btn_r10c1_press;

        //Column 2
        bool btn_r1c2_press;
        bool btn_r2c2_press;
        bool btn_r3c2_press;
        bool btn_r4c2_press;
        bool btn_r5c2_press;
        bool btn_r6c2_press;
        bool btn_r7c2_press;
        bool btn_r8c2_press;
        bool btn_r9c2_press;
        bool btn_r10c2_press;

        //Column 3
        bool btn_r1c3_press;
        bool btn_r2c3_press;
        bool btn_r3c3_press;
        bool btn_r4c3_press;
        bool btn_r5c3_press;
        bool btn_r6c3_press;
        bool btn_r7c3_press;
        bool btn_r8c3_press;
        bool btn_r9c3_press;
        bool btn_r10c3_press;

        //Column 4
        bool btn_r1c4_press;
        bool btn_r2c4_press;
        bool btn_r3c4_press;
        bool btn_r4c4_press;
        bool btn_r5c4_press;
        bool btn_r6c4_press;
        bool btn_r7c4_press;
        bool btn_r8c4_press;
        bool btn_r9c4_press;
        bool btn_r10c4_press;

        //Column 5
        bool btn_r1c5_press;
        bool btn_r2c5_press;
        bool btn_r3c5_press;
        bool btn_r4c5_press;
        bool btn_r5c5_press;
        bool btn_r6c5_press;
        bool btn_r7c5_press;
        bool btn_r8c5_press;
        bool btn_r9c5_press;
        bool btn_r10c5_press;

};
