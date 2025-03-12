#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
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
    if (x > 10 && x < 10 + 240 && y > 10*2 + CELL_SIZE*BOARD_SIZE && y < 10*2 + CELL_SIZE*BOARD_SIZE + 80) {
        game.giveHint();
    }
    else {
    // chuyển tọa độ màn hình x, y thành tọa độ hàng cột của game
    int clickedCol = (x - BOARD_X) / CELL_SIZE;
    int clickedRow = (y - BOARD_Y) / CELL_SIZE;
    game.move(clickedRow, clickedCol);
    }
}


int main(int argc, char *argv[])
{

//    int input;
//    cout << "Select your board size: 3   4   5";
//    cin >> input;
//
//    int BOARD_SIZE = input;

    Graphics graphics;
    graphics.init();

    Lightsout game;
    game.init();
    game.gameInit();

    graphics.render(game);

    int x, y;
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
                 graphics.render(game);
                 break;
        }
        SDL_Delay(50);
    }

    graphics.quit();
    return 0;

}
