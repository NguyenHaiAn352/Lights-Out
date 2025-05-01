#include <iostream>
#include <cstdlib>
#include <ctime>
#include <set>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include "defs.h"
#include "graphics.h"
#include "logic.h"
#include "timer.h"
#include <sstream>
#include <iomanip>
#include <cmath>

using namespace std;

bool isInReplay(Graphics &graphics, Lightsout &game) {
    int x; int y;
    SDL_GetMouseState(&x, &y);
    return (x >= 73 && y >= 145) && (x <= 188 && y <= 194);
}
bool isInQuit(Graphics &graphics, Lightsout &game) {
    int x; int y;
    SDL_GetMouseState(&x, &y);
    return (x >= 92 && y >= 236) && (x <= 171 && y <= 286);
}
bool isInBackToTitle(Graphics &graphics, Lightsout &game) {
    int x; int y;
    SDL_GetMouseState(&x, &y);
    return (x >= 30 && y >= 284) && (x <= 230 && y <= 326);
}
bool isInPlay (Graphics &graphics, Lightsout &game) {
    int x; int y;
    SDL_GetMouseState(&x, &y);
    return (x >= 50 && y >= 120) && (x <= 205 && y <= 202);
}
bool isInHardMode (Graphics &graphics, Lightsout &game) {
    int x; int y;
    SDL_GetMouseState(&x, &y);
    return (x >= 25 && y >= 290) && (x <= 234 && y <= 320);
}

void waitUntilKeyPressed(){ //pause coding until key being pressed
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
void processClickHardMode(int x, int y, Lightsout& game) {
    bool beatenTheGame = true;
    for (int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++){
        if (game.CLICK_STATE[i] != 0) beatenTheGame = false;
    }
    if (beatenTheGame) {
            game.congratulation();

    } else {
        if (x > 10 && x < 250 && y > 10 && y < 250) {
            int clickedCol = (x - BOARD_X) / CELL_SIZE;
            int clickedRow = (y - BOARD_Y) / CELL_SIZE;
            game.move(clickedRow, clickedCol);
        }
    }
}

void gameProgressReset (Lightsout &game) {
    game.haveWon = false;
    game.reset();
    game.init();
    game.gameInit();
}
void gameProgressResetHard (Lightsout &game) {
    game.haveWon = false;
    game.reset();
    game.init();
    game.hardModeInit();
}

void waitForReplayResponse(Graphics &graphics, Lightsout &game){
    // If mouse is on the surface of text, make it yellow
    // Else return it back to black
    // If clicked, proceed; Else stay in a loop
    int x; int y;
    SDL_GetMouseState(&x, &y);
    if ((x >= 73 && y >= 145) && (x <= 188 && y <= 194)){
        graphics.renderReplay(game);
    } else if ((x >= 30 && y >= 284) && (x <= 230 && y <= 326)) {
        graphics.renderBackToTitle(game);
    } else {
        graphics.render(game);
    }
    SDL_Delay(30);
}
void waitForPlayResponse (Graphics &graphics, Lightsout &game){
    int x; int y;
    SDL_GetMouseState(&x, &y);
    if ((x >= 50 && y >= 120) && (x <= 205 && y <= 202)){
        graphics.renderTitleYellow(game);
    } else if ((x >= 25 && y >= 290) && (x <= 234 && y <= 320)) {
        graphics.renderTitleHardModeYellow(game);
    } else graphics.renderTitle(game);
    SDL_Delay(30);
}

void EndScreen(Graphics &graphics, Lightsout &game, bool &isInSession);
void EndScreenHardMode (Graphics &graphics, Lightsout &game, bool &isInSession);
void LoseScreen (Graphics &graphics, Lightsout &game, bool &isInSession);

void NormalGame (Graphics &graphics, Lightsout &game, bool &isInSession){
    cout << "normal game was triggered.";
    Mix_HaltMusic();
    int x, y; bool quit = false;
    Mix_Music *bgMusic = graphics.loadMusic("audio\\resting_place.mp3");
    Mix_Music *yippie = graphics.loadMusic("audio\\yippie.mp3");
    SDL_Event event;
    gameProgressReset(game);
    graphics.render(game);
    while (!quit) { // Normal Game.
        graphics.play(bgMusic);
		SDL_PollEvent(&event);
        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&x, &y);
                processClick(x, y, game);
                graphics.render(game);
                if (game.haveWon){
                    EndScreen(graphics, game, isInSession);
                    quit = true;
                }
                break;
		}
        SDL_Delay(30);
    }
    Mix_FreeMusic(bgMusic);
    Mix_FreeMusic(yippie);
}
void HardMode (Graphics &graphics, Lightsout &game, bool &isInSession) {
    cout << "Hard Mode was triggered.";
    Mix_HaltMusic();
    int x, y; bool winningTheGame = false; bool quit = false;
    Mix_Music *bgMusic = graphics.loadMusic("audio\\eternal_hope_eternal_fight.mp3");
    Mix_Music *yippie = graphics.loadMusic("audio\\yippie.mp3");
    SDL_Event event;
    gameProgressResetHard(game);
    graphics.renderHardModeIntro();
    graphics.renderHardMode(game);

    stringstream timeText;
    timeText.str("");
    TTF_Font *font = graphics.loadFont("assets/DKCoolCrayon.ttf", 27);
    SDL_Color color = {255, 216, 0, 0};
    SDL_Texture* countdownText;
    LTimer countdown;
    countdown.start();

    Uint32 startTime = SDL_GetTicks();
    float pulseDuration = 1250.0f; // 1.25s cycle

    while (countdown.getTicks() <= 73000 && winningTheGame == false){
////        graphics.prepareScene(graphics.backgroundTestTwo);
//       Uint32 currentTime = SDL_GetTicks();
//        float elapsed = fmod(currentTime - startTime, pulseDuration) / pulseDuration;
//        Uint8 colorValue;
//        if (elapsed < 0.25f) {
//            // **Rapid Pulse to White (0-312.5ms)**
//            colorValue = 255;
//        } else {
//            // **Gradual Fade to Black (312.5ms - 1250ms)**
//            float fadeFactor = (1.0f - ((elapsed - 0.25f) / 0.75f)); // Slow fade formula
//            colorValue = static_cast<Uint8>(255 * fadeFactor);
//        }
//        // Apply the new brightness modulation
//        SDL_SetTextureColorMod(graphics.blackBackground, colorValue, colorValue, colorValue);
        // Render the pulsing background
        graphics.prepareScene(graphics.backgroundTestTwo);
//        cout << "Current color: " << (int)colorValue << endl;
        timeText.str("");
        timeText << fixed << setprecision(2) << ((73000 - countdown.getTicks()) / 1000.f);
        string timeTextInString = timeText.str();
        SDL_Texture *countdownText0 = graphics.renderText("Round Ends In:", font, color);
        countdownText = graphics.renderText(timeTextInString.c_str(), font, color);
        graphics.play(bgMusic);
        SDL_PollEvent(&event);
        switch (event.type) {
        case SDL_QUIT:
            quit = true;
            break;
        case SDL_MOUSEBUTTONDOWN:
            SDL_GetMouseState(&x, &y);
            processClickHardMode(x, y, game);
            if (game.haveWon){
                winningTheGame = true;
                EndScreenHardMode(graphics, game, isInSession);
                break;
            }
        }
        graphics.renderHardMode(game);
        graphics.renderTexture(countdownText0, 35, 265);
        graphics.renderTexture(countdownText, 96, 293);
        graphics.presentScene();
    }
    LoseScreen(graphics, game, isInSession);
    Mix_FreeMusic(bgMusic);
    Mix_FreeMusic(yippie);
}
void EndScreen (Graphics &graphics, Lightsout &game, bool &isInSession){
    Mix_Music *yippie = graphics.loadMusic("audio\\yippie.mp3");
    Mix_HaltMusic();
    graphics.play(yippie);
    graphics.render(game);
    SDL_Delay(3500);
    Mix_HaltMusic();
    bool isInEndScreen = true; SDL_Event event;
    while (isInEndScreen){
        if(!(SDL_PollEvent(&event))) {continue;}
        if (event.type == SDL_MOUSEMOTION) {
            waitForReplayResponse(graphics, game);
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (isInReplay(graphics, game)) {
                isInEndScreen = false;
                NormalGame(graphics, game, isInSession);
                break;
            } else if (isInBackToTitle(graphics, game)) {
                isInEndScreen = false;
                isInSession = false;
                cout << "No Longer In End Screen!" << endl;
                break;
            }
        }
    }
}
void EndScreenHardMode (Graphics &graphics, Lightsout &game, bool &isInSession){
    Mix_Music *yippie = graphics.loadMusic("audio\\yippie.mp3");
    Mix_HaltMusic();
    graphics.play(yippie);
    graphics.render(game);
    SDL_Delay(3500);
    Mix_HaltMusic();
    bool isInEndScreen = true; SDL_Event event;
    while (isInEndScreen){
        if(!(SDL_PollEvent(&event))) {continue;}
        if (event.type == SDL_MOUSEMOTION) {
            waitForReplayResponse(graphics, game);
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (isInReplay(graphics, game)) {
                isInEndScreen = false;
                HardMode(graphics, game, isInSession);
                break;
            } else if (isInBackToTitle(graphics, game)) {
                isInEndScreen = false;
                isInSession = false;
                cout << "No Longer In End Screen!" << endl;
                break;
            }
        }
    }
}
void LoseScreen(Graphics &graphics, Lightsout &game, bool &isInSession){

    Mix_HaltMusic();
    bool isInEndScreen = true; SDL_Event event;
    game.haveWon = true;
    graphics.render(game);
    while (isInEndScreen){
        if(!(SDL_PollEvent(&event))) {continue;}
        if (event.type == SDL_MOUSEMOTION) {
            waitForReplayResponse(graphics, game);
        } else if (event.type == SDL_MOUSEBUTTONDOWN) {
            if (isInReplay(graphics, game)) {
                isInEndScreen = false;
                HardMode(graphics, game, isInSession);
                break;
            } else if (isInBackToTitle(graphics, game)) {
                isInEndScreen = false;
                isInSession = false;
                cout << "No Longer In End Screen!" << endl;
                break;
            }
        }
    }
}
void TitleScreenClickProcess(Graphics &graphics, Lightsout &game, bool &isInSession){
    if (isInPlay(graphics, game)) {NormalGame(graphics, game, isInSession); isInSession = true;}
    else if (isInHardMode(graphics, game)) {HardMode(graphics, game, isInSession); isInSession = true;}
}
void DetectTitleScreenState(Graphics &graphics, Lightsout &game) {
    int x; int y;
    SDL_GetMouseState(&x, &y);
    if ((x >= 50 && y >= 120) && (x <= 205 && y <= 202)){
        graphics.renderTitleYellow(game);
    } else if ((x >= 25 && y >= 290) && (x <= 234 && y <= 320)) {
        graphics.renderTitleHardModeYellow(game);
    } else graphics.renderTitle(game);
    SDL_Delay(30);
}
void gameLoop (Graphics &graphics, Lightsout &game){
    // renderTitleScreen
    // if HardMode: void HardMode, if NormalMode: void NormalMode, if quit: quit
    bool quit = false; bool isInSession = false;
    int x, y;
    SDL_Event event;
    Mix_Music *TitleMusic = graphics.loadMusic("audio\\safe_space.mp3");
    graphics.play(TitleMusic);
    while (!quit){
            if(!(SDL_PollEvent(&event))) {continue;}
            if (event.type == SDL_QUIT) {quit = true;}
            else if (event.type == SDL_MOUSEMOTION){
                DetectTitleScreenState(graphics, game);
            } else if (event.type == SDL_MOUSEBUTTONDOWN){
                TitleScreenClickProcess(graphics, game, isInSession);
            }
    }
    Mix_FreeMusic(TitleMusic);
}

int main(int argc, char *argv[]){
	// Initialization
	Graphics graphics;
   	graphics.init();
    Lightsout game;
    Mix_Music *bgMusic = graphics.loadMusic("audio\\resting_place.mp3");
    Mix_Music *yippie = graphics.loadMusic("audio\\yippie.mp3");
	bool quit = false;
	bool replay = true;
	bool chooseToPlay = false;
	bool chooseHardMode = false;
	int x, y;
	SDL_Event event;
	SDL_Event event2;
	graphics.renderTitle(game);
	gameLoop(graphics, game);
   	graphics.quit();
	return 0;
}

// convert to while askReplay, making the replay button directly interactive on the game surface.
