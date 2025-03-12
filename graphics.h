#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include "defs.h"
#include "logic.h"

struct Graphics {
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Texture *cellEmpty, *helpBox, *lightOn;
    SDL_Texture *one, *two, *three, *four, *five, *six, *seven, *eight, *nine;
    void logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR,
                       "%s: %s", msg, error);
        SDL_Quit();
    }

    void initSDL() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED,
                   SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT,
                   SDL_WINDOW_SHOWN);
        if (window == nullptr)
                   logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1,
                     SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

        //renderer =
                  SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

        if (renderer == nullptr)
             logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    }

    void init(){
        initSDL();
        cellEmpty = loadTexture("images//cell_empty.png");
        lightOn = loadTexture("images//light_on.png");
        helpBox = loadTexture("images//hint.png");
        one = loadTexture("images//one.png");
        two = loadTexture("images//two.png");
        three = loadTexture("images//three.png");
        four = loadTexture("images//four.png");
        five = loadTexture("images//five.png");
        six = loadTexture("images//six.png");
        seven = loadTexture("images//seven.png");
        eight = loadTexture("images//eight.png");
        nine = loadTexture("images//nine.png");
    }

    void prepareScene(SDL_Texture * background)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy( renderer, background, NULL, NULL);
    }

    void presentScene()
    {
        SDL_RenderPresent(renderer);
    }

    SDL_Texture *loadTexture(const char *filename)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO,
                       "Loading %s", filename);
        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                  SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

        return texture;
    }

    void renderTexture(SDL_Texture *texture, int x, int y)
    {
        SDL_Rect dest;
        dest.x = x;
        dest.y = y;
        SDL_QueryTexture(texture, NULL, NULL, &dest.w, &dest.h);
        SDL_RenderCopy(renderer, texture, NULL, &dest);
    }

    void quit()
    {
        SDL_DestroyTexture(cellEmpty);
        cellEmpty = nullptr;
        SDL_DestroyTexture(lightOn);
        lightOn = nullptr;
        SDL_DestroyTexture(one);
        one = nullptr;
        SDL_DestroyTexture(two);
        two = nullptr;
        SDL_DestroyTexture(three);
        three = nullptr;
        SDL_DestroyTexture(four);
        four = nullptr;
        SDL_DestroyTexture(five);
        five = nullptr;
        SDL_DestroyTexture(six);
        six = nullptr;
        SDL_DestroyTexture(seven);
        seven = nullptr;
        SDL_DestroyTexture(eight);
        eight = nullptr;
        SDL_DestroyTexture(nine);
        nine = nullptr;

        IMG_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

     void render(const Lightsout& game) {
        //prepareScene();
         for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++) {
                int x = BOARD_X + j * CELL_SIZE;
                int y = BOARD_Y + i * CELL_SIZE;
                switch (game.board[i][j]) {
                    case EMPTY_CELL: renderTexture(cellEmpty, x, y); break;
                    case LIGHTED: renderTexture(lightOn, x, y); break;
                };
            };
        renderTexture(helpBox, 10, 10*2 + CELL_SIZE*BOARD_SIZE);
        switch(game.hintPosition){
            case 1: renderTexture(one, 10 + 160, 10 + 240 + 10); break;
            case 2: renderTexture(two, 10 + 160, 10 + 240 + 10); break;
            case 3: renderTexture(three, 10 + 160, 10 + 240 + 10); break;
            case 4: renderTexture(four, 10 + 160, 10 + 240 + 10); break;
            case 5: renderTexture(five, 10 + 160, 10 + 240 + 10); break;
            case 6: renderTexture(six, 10 + 160, 10 + 240 + 10); break;
            case 7: renderTexture(seven, 10 + 160, 10 + 240 + 10); break;
            case 8: renderTexture(eight, 10 + 160, 10 + 240 + 10); break;
            case 9: renderTexture(nine, 10 + 160, 10 + 240 + 10); break;
        }
        presentScene();
     }
};


#endif // _GRAPHICS__H

