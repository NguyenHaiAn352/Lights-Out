#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
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
        SDL_Delay(50);
    }
}

void processClick(int x, int y, Lightsout& game) {
    bool beatenTheGame = true;
    for (int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++){
        if (game.CLICK_STATE[i] != 0) beatenTheGame = false;
    }
    if (beatenTheGame) {
            game.congratulation();

    } else {
        if (x > 10 && x < 10 + 240 && y > 10*2 + CELL_SIZE*BOARD_SIZE && y < 10*2 + CELL_SIZE*BOARD_SIZE + 80) {
            game.giveHint();
        }
        else {
            int clickedCol = (x - BOARD_X) / CELL_SIZE;
            int clickedRow = (y - BOARD_Y) / CELL_SIZE;
            game.move(clickedRow, clickedCol);
        }
    }
}

bool askReplay() {
    cout << "Play again? (y/n): ";
    char choice;
    cin >> choice;
    return choice == 'y';
}

int main(int argc, char *argv[]){
	// Initialization
	Graphics graphics;
   	graphics.init();
    	Lightsout game;
    	game.init();
    	game.gameInit();
    	graphics.render(game);

	bool quit = false;
	int x, y;
	SDL_Event event;
	while (!quit) {
		SDL_PollEvent(&event);
        	switch (event.type) {
            		case SDL_QUIT:
                 		quit == true;
                 		break;
            		case SDL_MOUSEBUTTONDOWN:
                 		SDL_GetMouseState(&x, &y);
                 		processClick(x, y, game);
                 		if (game.haveWon){
                            graphics.render(game);
                            if (askReplay()){
                                game.haveWon = false;
                                game.reset();
                                game.init();
                                game.gameInit();
                            } else {quit == true;}
                		}
                		graphics.render(game);
                break;
		}
        	SDL_Delay(50);
    	}
   	graphics.quit();
	return 0;
}
