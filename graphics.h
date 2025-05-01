#ifndef _GRAPHICS__H
#define _GRAPHICS__H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "defs.h"
#include "logic.h"
#include <sstream>
#include "timer.h"

struct Graphics {
    SDL_Renderer *renderer;
    SDL_Window *window;
    SDL_Texture *cellEmpty, *helpBox, *lightOn, *outOfHint;
    SDL_Texture *zero, *one, *two, *three, *four, *five, *six, *seven, *eight, *nine;
    SDL_Texture *blackBackground, *backgroundTestTwo, *TitleScreen;
    SDL_Texture *spongebob;
    SDL_Texture *CongratulationText, *ReplayTheGame, *ReplayTheGameYellow, *BackToTitle, *BackToTitleYellow;
    SDL_Texture *LightsOutTitle, *StartTheGame, *StartTheGameYellow, *orButton, *PickTheHardMode, *PickTheHardModeYellow;
    SDL_Texture *HardModeIntro5, *HardModeIntro4,*HardModeIntro3, *HardModeIntro2, *HardModeIntro1;
    TTF_Font* font, *fontTwo;
    SDL_Color color;
//    SDL_Texture* congratText, *closeWindow, *closeWindowTwo;

    int initX = 0, initY = 0;
    int movingX = 10; int movingY = 10;
    int currentX = 0; int currentY = 0;

    void logErrorAndExit(const char* msg, const char* error)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "%s: %s", msg, error);
        SDL_Quit();
    }

    void initSDL() {
        if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
            logErrorAndExit("SDL_Init", SDL_GetError());

        window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        //full screen
        //window = SDL_CreateWindow(WINDOW_TITLE, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_FULLSCREEN_DESKTOP);
        if (window == nullptr) logErrorAndExit("CreateWindow", SDL_GetError());

        if (!IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG))
            logErrorAndExit( "SDL_image error:", IMG_GetError());

        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED |
                                              SDL_RENDERER_PRESENTVSYNC);
        //Khi chạy trong máy ảo (ví dụ phòng máy ở trường)
        //renderer = SDL_CreateSoftwareRenderer(SDL_GetWindowSurface(window));

        if (renderer == nullptr) logErrorAndExit("CreateRenderer", SDL_GetError());

        SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");
        SDL_RenderSetLogicalSize(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);

        if (TTF_Init() == -1) {
            logErrorAndExit("SDL_ttf could not initialize! SDL_ttf Error: ", TTF_GetError());
        }
        if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
            logErrorAndExit( "SDL_mixer could not initialize! SDL_mixer Error: %s\n",
            Mix_GetError() );
        }

    }

    void init(){
        initSDL();
        spongebob = loadTexture("images//Spongebob.png");
//        font = loadFont("assets/DKCoolCrayon.ttf", 30);
//        fontTwo = loadFont("assets/DKCoolCrayon.ttf", 15);
        TitleScreen = loadTexture("images//TitleScreen.png");
        CongratulationText = loadTexture("texts//CongratulationText.png");
        ReplayTheGame = loadTexture("texts//ReplayTheGame.png");
        ReplayTheGameYellow = loadTexture("texts//ReplayTheGameYellow.png");
        BackToTitle = loadTexture("texts//BackToTitle.png");
        BackToTitleYellow = loadTexture("texts//BackToTitleYellow.png");
        LightsOutTitle = loadTexture("texts//LightsOutTitle.png");
        StartTheGame = loadTexture("texts//StartTheGame.png");
        StartTheGameYellow = loadTexture("texts//StartTheGameYellow.png");
        orButton = loadTexture("texts//or.png");
        PickTheHardMode = loadTexture("texts//PickTheHardMode.png");
        PickTheHardModeYellow = loadTexture("texts//PickTheHardModeYellow.png");
        color = {219, 219, 219, 0};
        cellEmpty = loadTexture("images//cell_empty.png");
        lightOn = loadTexture("images//light_on.png");
        helpBox = loadTexture("images//hint.png");
        outOfHint = loadTexture("images//OutOfHint.png");
        zero = loadTexture("images//zero.png");
        one = loadTexture("images//one.png");
        two = loadTexture("images//two.png");
        three = loadTexture("images//three.png");
        four = loadTexture("images//four.png");
        five = loadTexture("images//five.png");
        six = loadTexture("images//six.png");
        seven = loadTexture("images//seven.png");
        eight = loadTexture("images//eight.png");
        nine = loadTexture("images//nine.png");
        blackBackground = loadTexture("images//blackBackground.png");
        backgroundTestTwo = loadTexture("images//graybackground.png");
        HardModeIntro5 = loadTexture("images//HardModeIntro5.png");
        HardModeIntro4 = loadTexture("images//HardModeIntro4.png");
        HardModeIntro3 = loadTexture("images//HardModeIntro3.png");
        HardModeIntro2 = loadTexture("images//HardModeIntro2.png");
        HardModeIntro1 = loadTexture("images//HardModeIntro1.png");

        SDL_SetTextureBlendMode(blackBackground, SDL_BLENDMODE_MOD);
        SDL_SetTextureAlphaMod(blackBackground, 255);

    }

    TTF_Font* loadFont(const char* path, int size)
    {
        TTF_Font* gFont = TTF_OpenFont( path, size );
        if (gFont == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                           "Load font %s", TTF_GetError());
        }
    }

    void prepareScene(SDL_Texture * background)
    {
        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, background, NULL, NULL);
    }

    void presentScene()
    {
        SDL_RenderPresent(renderer);
    }

    SDL_Texture *loadTexture(const char *filename)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);

        SDL_Texture *texture = IMG_LoadTexture(renderer, filename);
        if (texture == NULL)
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_ERROR, "Load texture %s", IMG_GetError());

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

    void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y)
    {
        SDL_Rect dest;

        dest.x = x;
        dest.y = y;
        dest.w = src->w;
        dest.h = src->h;

        SDL_RenderCopy(renderer, texture, src, &dest);
    }

    Mix_Music *loadMusic(const char* path)
    {
        Mix_Music *gMusic = Mix_LoadMUS(path);
        if (gMusic == nullptr) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                "Could not load music! SDL_mixer Error: %s", Mix_GetError());
        }
        return gMusic;
    }

    void play(Mix_Music *gMusic)
    {
        if (gMusic == nullptr) return;

        if (Mix_PlayingMusic() == 0) {
            Mix_PlayMusic( gMusic, -1 );
        }
        else if( Mix_PausedMusic() == 1 ) {
            Mix_ResumeMusic();
        }
    }

    void quit() {
        SDL_DestroyTexture(spongebob);
        spongebob = nullptr;
        SDL_DestroyTexture(zero);
        zero = nullptr;
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
        SDL_DestroyTexture(blackBackground);
        blackBackground = nullptr;
        SDL_DestroyTexture(backgroundTestTwo);
        backgroundTestTwo = nullptr;

        TTF_CloseFont(font);
        IMG_Quit();
        TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        Mix_Quit();
    }

    SDL_Texture* renderText(const char* text, TTF_Font* font, SDL_Color textColor)
    {
        SDL_Surface* textSurface =
                TTF_RenderText_Solid( font, text, textColor );
        if( textSurface == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                           "Render text surface %s", TTF_GetError());
            return nullptr;
        }

        SDL_Texture* texture =
                SDL_CreateTextureFromSurface( renderer, textSurface );
        if( texture == nullptr ) {
            SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION,
                           SDL_LOG_PRIORITY_ERROR,
                           "Create texture from text %s", SDL_GetError());
        }
        SDL_FreeSurface( textSurface );
        return texture;
    }

     void render(const Lightsout& game) {
        prepareScene(backgroundTestTwo);
        if (game.haveWon){
            renderTexture(CongratulationText, 9, 8);
            renderTexture(ReplayTheGame, 70, 146);
            renderTexture(BackToTitle, 30, 284);
            cout << " You should be able to see this message after beating the game (and all other supporting graphics)." << endl;
            presentScene();
        } else {
             for (int i = 0; i < BOARD_SIZE; i++)
                for (int j = 0; j < BOARD_SIZE; j++) {
                    int x = BOARD_X + j * CELL_SIZE;
                    int y = BOARD_Y + i * CELL_SIZE;
                    switch (game.board[i][j]) {
                        case EMPTY_CELL: renderTexture(cellEmpty, x, y); break;
                        case LIGHTED: renderTexture(lightOn, x, y); break;
                    };
                };
            if (game.hintNumbers == 0) {
                renderTexture(outOfHint, 10, 10*2 + CELL_SIZE*BOARD_SIZE);
            } else {
                renderTexture(helpBox, 10, 10*2 + CELL_SIZE*BOARD_SIZE);
                switch(game.hintPosition){
                    case 0: renderTexture(zero, 10 + 160, 10 + 240 + 10); break;
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
            }
            presentScene();
        }
     }

     void renderHardMode (const Lightsout &game){
        if (game.haveWon){
            renderTexture(CongratulationText, 9, 8);
            renderTexture(ReplayTheGame, 70, 146);
            renderTexture(BackToTitle, 30, 284);
            cout << " You should be able to see this message after beating the game (and all other supporting graphics)." << endl;
            presentScene();
        } else {
             for (int i = 0; i < BOARD_SIZE; i++)
                for (int j = 0; j < BOARD_SIZE; j++) {
                    int x = BOARD_X + j * CELL_SIZE;
                    int y = BOARD_Y + i * CELL_SIZE;
                    switch (game.board[i][j]) {
                        case EMPTY_CELL: renderTexture(cellEmpty, x, y); break;
                        case LIGHTED: renderTexture(lightOn, x, y); break;
                    };
                };
            }
            presentScene();
        }

     void renderReplay (const Lightsout& game){
        prepareScene(backgroundTestTwo);
        renderTexture(CongratulationText, 9, 8);
        renderTexture(ReplayTheGameYellow, 70, 146);
        renderTexture(BackToTitle, 30, 284);
        presentScene();
     }

     void renderBackToTitle (const Lightsout& game){
        prepareScene(backgroundTestTwo);
        renderTexture(CongratulationText, 9, 8);
        renderTexture(ReplayTheGame, 70, 146);
        renderTexture(BackToTitleYellow, 30, 282);
        presentScene();
     }

     void renderTitle (const Lightsout & game){
        prepareScene(TitleScreen);
        renderTexture(LightsOutTitle, 25, 19);
        renderTexture (StartTheGame, 50, 120);
        renderTexture (orButton, 112, 252);
        renderTexture  (PickTheHardMode, 25, 290);
        presentScene();
    }

    void renderTitleYellow (const Lightsout & game){
        prepareScene(TitleScreen);
        renderTexture(LightsOutTitle, 25, 19);
        renderTexture (StartTheGameYellow, 50, 120);
        renderTexture (orButton, 112, 252);
        renderTexture  (PickTheHardMode, 25, 290);
        presentScene();
     }

     void renderTitleHardModeYellow (const Lightsout & game){
        prepareScene(TitleScreen);
        renderTexture(LightsOutTitle, 25, 19);
        renderTexture (StartTheGame, 50, 120);
        renderTexture (orButton, 112, 252);
        renderTexture  (PickTheHardModeYellow, 25, 290);
        presentScene();
    }

    void renderHardModeIntro (){
        prepareScene(backgroundTestTwo);
        renderTexture(HardModeIntro5, 0, 0);
        presentScene();
        SDL_Delay(1000);
        renderTexture(HardModeIntro4, 0, 0);
        presentScene();
        SDL_Delay(1000);
        renderTexture(HardModeIntro3, 0, 0);
        presentScene();
        SDL_Delay(1000);
        renderTexture(HardModeIntro2, 0, 0);
        presentScene();
        SDL_Delay(1000);
        renderTexture(HardModeIntro1, 0, 0);
        presentScene();
        SDL_Delay(1000);
    }
};


#endif // _GRAPHICS__H

