#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "graphics.h"
#include "logic.h"

using namespace std;

void waitUntilKeyPressed() //pause coding until key being pressed
{
    SDL_Event e;
    while (true) {
        if ( SDL_PollEvent(&e) != 0 &&
             (e.type == SDL_KEYDOWN || e.type == SDL_QUIT) )
            return;
        SDL_Delay(100);
    }
}

void processClick(int x, int y, Tictactoe& game) {
    // chuyển tọa độ màn hình x, y thành tọa độ hàng cột của game
    int clickedCol = (x - BOARD_X) / CELL_SIZE;
    int clickedRow = (y - BOARD_Y) / CELL_SIZE;
    game.move(clickedRow, clickedCol);
}


int main(int argc, char *argv[])
{
//    Graphics graphics;
//    graphics.init();
//
//    SDL_Texture* background = graphics.loadTexture("images\\whiteStage.png");
//    graphics.prepareScene(background);
//
//    graphics.presentScene();
//    waitUntilKeyPressed();
//
//    SDL_Texture* spongeBob = graphics.loadTexture("Spongebob.png");
//    graphics.renderTexture(spongeBob, 200, 200);
//
//    graphics.presentScene();
//    waitUntilKeyPressed();
//
//    SDL_DestroyTexture( spongeBob );
//    spongeBob = NULL;
//    SDL_DestroyTexture( background );
//    background = NULL;
//
//    graphics.quit();
//    return 0;
    Graphics graphics;
    graphics.init();

    Tictactoe game;
    game.init();
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
        SDL_Delay(100);
    }

    graphics.quit();
    return 0;

}
