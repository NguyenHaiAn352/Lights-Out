#ifndef _ADDITIONAL__H
#define _ADDITIONAL__H
#include "defs.h"
#include "logic.h"

struct Additional {

    bool LIGHT_STATE [BOARD_SIZE][BOARD_SIZE];
    void init(){
        for (int i = 0; i < BOARD_SIZE; i++){
            for (int j = 0; j < BOARD_SIZE; j++){
            LIGHT_STATE[i][j] = 0;
            }
        }
    }
    void internalLightState(){


    }
};

#endif
