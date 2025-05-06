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
        if (x > 10 && x < 250 && y > 10 && y < 250 && game.HardModeMoves != 0) {
            int clickedCol = (x - BOARD_X) / CELL_SIZE;
            int clickedRow = (y - BOARD_Y) / CELL_SIZE;
            game.HardModeMoves--;
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
void gameLoop (Graphics &graphics, Lightsout &game);

void NormalGame (Graphics &graphics, Lightsout &game, bool &isInSession){
    cout << "normal game was triggered.";
    Mix_HaltMusic();
    int x, y; bool quit = false;
     int yPos = 0;
    Mix_Music *bgMusic = graphics.loadMusic("audio\\sundowner.mp3");
    SDL_Event event;
    gameProgressReset(game);
    graphics.render(game);
    LTimer countdown;
    countdown.start();
    while (!quit) { // Normal Game.
        graphics.play(bgMusic);
		SDL_PollEvent(&event);
		graphics.renderAnimatedBackgroundGray(countdown, yPos);
		graphics.render(game);
//		stringstream hintInfo;
//		hintInfo.str("");
//		hintInfo << game.hintNumbers -1;
//		string hintInfoString = hintInfo.str();
//		TTF_Font *font = graphics.loadFont("assets/DKCoolCrayon.ttf", 27);
//        SDL_Color color = {255, 255, 255, 0};
//        SDL_Texture *hintNumbersLeft = graphics.renderText(hintInfoString.c_str(), font, color);
//        graphics.renderTexture(hintNumbersLeft, 55, 250);

        switch (event.type) {
            case SDL_QUIT:
                quit = true;
                break;
            case SDL_MOUSEBUTTONDOWN:
                SDL_GetMouseState(&x, &y);
                processClick(x, y, game);
                graphics.render(game);
                if (game.haveWon){
//                    SDL_DestroyTexture(hintNumbersLeft); hintNumbersLeft = nullptr;
                    Mix_HaltMusic();
                    EndScreen(graphics, game, isInSession);
                    quit = true;
                }
                break;
		}
//        SDL_Delay(30);
    }
    if (quit) {
        SDL_Quit();  // Cleanly shut down SDL before exiting
        return;  // Exit function immediately
//        SDL_DestroyTexture(hintNumbersLeft); hintNumbersLeft = nullptr;
    }
    Mix_FreeMusic(bgMusic);
}
void HardMode(Graphics &graphics, Lightsout &game, bool &isInSession) {
    cout << "Hard Mode was triggered.";
    Mix_HaltMusic();
    int x, y;
    bool winningTheGame = false;
    bool quit = false;

    Mix_Music *bgMusic = graphics.loadMusic("audio\\eternal_hope_eternal_fight.mp3");
    Mix_Chunk *clockTick = graphics.loadSoundEffect("audio\\clocktick.wav");

    SDL_Event event;
    gameProgressResetHard(game);
    graphics.renderHardModeIntro();
    graphics.renderHardMode(game);

    stringstream timeText, moveText;
    TTF_Font *font = graphics.loadFont("assets/DKCoolCrayon.ttf", 27);
    SDL_Color color = {255, 255, 255, 0};
    SDL_Color redColor = {255, 0, 0, 0};
    SDL_Texture *countdownText, *moveLeftTexture;

    LTimer countdown;
    countdown.start();
    int yPos = 0;
    Uint32 startTime = SDL_GetTicks();

    while (!quit && countdown.getTicks() <= 73000 && !winningTheGame) {
        graphics.renderAnimatedBackgroundBlack(countdown, yPos);
//        graphics.renderStarburst(countdown, startTime);

        timeText.str("");
        moveText.str("");

        timeText << fixed << setprecision(2) << ((73000 - countdown.getTicks()) / 1000.f);
        moveText << game.HardModeMoves;

        string timeTextInString = timeText.str();
        string moveTextInString = moveText.str();

        SDL_Texture *countdownText0 = graphics.renderText("Time Left: ", font, color);
        SDL_Texture *moveLeft = graphics.renderText("Moves Left: ", font, color);

        countdownText = graphics.renderText(timeTextInString.c_str(), font, color);
        if (game.HardModeMoves == 0) moveLeftTexture = graphics.renderText(moveTextInString.c_str(), font, redColor);
        else moveLeftTexture = graphics.renderText(moveTextInString.c_str(), font, color);

        graphics.play(bgMusic);

        while (SDL_PollEvent(&event)) {  // Ensure all events are processed
            if (event.type == SDL_QUIT) {
                quit = true; // Stop the loop
                SDL_DestroyTexture(countdownText0); countdownText0 = nullptr;
                SDL_DestroyTexture(moveLeft); moveLeft = nullptr;
                break;
            }
            if (event.type == SDL_MOUSEBUTTONDOWN) {
                SDL_GetMouseState(&x, &y);
                processClickHardMode(x, y, game);

                if (game.haveWon) {
                    countdown.stop();
                    winningTheGame = true;
                    Mix_HaltMusic();
                    SDL_RenderClear(graphics.renderer);
                    EndScreenHardMode(graphics, game, isInSession);
                    break;
                }
            }
        }

        graphics.renderHardMode(game);
        graphics.renderTexture(moveLeft, 27, 302);
        graphics.renderTexture(moveLeftTexture, 199, 302);
        graphics.renderTexture(countdownText0, 27, 270);
        graphics.renderTexture(countdownText, 172, 270);
        graphics.presentScene();

        if ((countdown.getTicks() >= 43000 && countdown.getTicks() < 55000 && (countdown.getTicks() - 43000) % 850 < 12.3)
            || (countdown.getTicks() >= 55000 && (countdown.getTicks() - 43000) % 852 < 12.3)) {
            cout << "Clock ticked. ";
            Mix_PlayChannel(-1, clockTick, 0);
        }

        SDL_DestroyTexture(countdownText0); countdownText0 = nullptr;
        SDL_DestroyTexture(moveLeft); moveLeft = nullptr;
    }

    Mix_FreeMusic(bgMusic);
    Mix_FreeChunk(clockTick);
    SDL_DestroyTexture(countdownText); countdownText = nullptr;
    SDL_DestroyTexture(moveLeftTexture); moveLeftTexture = nullptr;
    TTF_CloseFont(font);

    if (quit) {
        SDL_Quit();  // Cleanly shut down SDL before exiting
        return;  // Exit function immediately
    }

    if (countdown.getTicks() > 73000) {
        game.HardModeLost = true;
        LoseScreen(graphics, game, isInSession);
    }
}
void EndScreen (Graphics &graphics, Lightsout &game, bool &isInSession){
    Mix_Chunk *yippie = graphics.loadSoundEffect("audio\\yippie.wav");
    Mix_Music *TitleMusic = graphics.loadMusic("audio\\safe_space.mp3");
    Mix_PlayChannel(-1, yippie, 0);
    graphics.render(game);
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
                graphics.renderTitle(game);
                gameLoop(graphics, game);
                cout << "No Longer In End Screen!" << endl;
                break;
            }
        }

    }
    Mix_FreeChunk(yippie);
    Mix_FreeMusic(TitleMusic);
}
void EndScreenHardMode (Graphics &graphics, Lightsout &game, bool &isInSession){
    Mix_Chunk *yippie = graphics.loadSoundEffect("audio\\yippie.wav");
    Mix_PlayChannel(-1, yippie, 0);
    graphics.render(game);
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
                graphics.renderTitle(game);
                gameLoop(graphics, game);
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
                graphics.renderTitle(game);
                gameLoop(graphics, game);
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
            } else if (event.type == SDL_QUIT){
                quit = true;
            }
    }
    Mix_FreeMusic(TitleMusic);
}

int main(int argc, char *argv[]){
	// Initialization
	Graphics graphics;
   	graphics.init();
    Lightsout game;
	graphics.renderTitle(game);
	gameLoop(graphics, game);
   	graphics.quit();
	return 0;
}

// convert to while askReplay, making the replay button directly interactive on the game surface.
