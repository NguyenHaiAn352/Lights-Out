#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "logic.h"
#include "additional.h"

using namespace std;

void waitUntilKeyPressed() //pause coding until key being pressed
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(50);
    }
}

void processClick(int x, int y, Lightsout& game) {
    // chuyển tọa độ màn hình x, y thành tọa độ hàng cột của game
    int clickedCol = (x - BOARD_X) / CELL_SIZE;
    int clickedRow = (y - BOARD_Y) / CELL_SIZE;
    game.move(clickedRow, clickedCol);
}


int main(int argc, char *argv[])
{
    Graphics graphics;
    graphics.init();

    Lightsout game;
    game.init();
    graphics.render(game);

    int x, y;

//    bool CLICK_STATE[BOARD_SIZE][BOARD_SIZE];
//    for (int i = 0; i < BOARD_SIZE; i++){
//        for (int j = 0; j < BOARD_SIZE; j++){
//            CLICK_STATE[i][j] = 0;
//        }
//    }

    Additional dlc;
    dlc.init();

    SDL_Event event;
    bool quit = false;
    while (! quit) {
        SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                 quit = true;
                 break;
            case SDL_MOUSEBUTTONDOWN:
                 SDL_GetMouseState(&x, &y);
                 processClick(x, y, game);
//                 internalClickTracker(x, y, game, CLICK_STATE);
                 dlc.internalLightState(x, y);
                 graphics.render(game);
                 break;
        }
        SDL_Delay(50);
    }

    graphics.quit();
    return 0;

}
