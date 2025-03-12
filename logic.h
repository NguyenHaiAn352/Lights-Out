#ifndef _LOGIC__H
#define _LOGIC__H

#define BOARD_SIZE 3
#define EMPTY_CELL ' '
#define O_CELL 'o'
#define X_CELL 'x'
#define LIGHTED 'l'

using namespace std;

struct Lightsout {
    char board[BOARD_SIZE][BOARD_SIZE];
    char LIGHT_ON = LIGHTED;
    bool CLICK_STATE [BOARD_SIZE*BOARD_SIZE];
    set <int> uniqueNumbers;
    int blocks = BOARD_SIZE*BOARD_SIZE;
    int hintPosition = 1;

    void init() {
        for (int i = 0; i < BOARD_SIZE; i++){
            for (int j = 0; j < BOARD_SIZE; j++) {board[i][j] = EMPTY_CELL;}
        }
        for (int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++){
            CLICK_STATE[i] = 0;
        }
    }

    void gameInit(){
        srand(time(0));
        while(uniqueNumbers.size() < 5) {
            int randomNumber = rand() % (blocks - 1);
            if (uniqueNumbers.insert(randomNumber).second) {
                cout << randomNumber + 1 << " " << endl;
                int tempRow = randomNumber/3;
                move(tempRow, randomNumber%3);
            }
        }
        auto initPos = uniqueNumbers.begin();
        hintPosition = *initPos;
        cout << endl;
    }

    void move(int row, int column) {
        CLICK_STATE[row*3+column] = (CLICK_STATE[row*3+column] == 1) ? 0 : 1;
        for (int i = 0; i < blocks; i++){
            cout << CLICK_STATE[i] << " ";
        }
        cout << endl;
    if (row >= 0 && row < BOARD_SIZE && column >= 0 && column < BOARD_SIZE){
        if (row == 0 && column == 0) {
            board[row][column] = (board[row][column] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row+1][column] = (board[row+1][column] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row][column+1] = (board[row][column+1] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
        } else if (row == BOARD_SIZE - 1 && column == 0) {
            board[row][column] = (board[row][column] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row-1][column] = (board[row-1][column] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row][column+1] = (board[row][column+1] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
        } else if (row == 0 && column == BOARD_SIZE - 1){
            board[row][column] = (board[row][column] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row+1][column] = (board[row+1][column] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row][column-1] = (board[row][column-1] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
        } else if (row  == BOARD_SIZE - 1 && column == BOARD_SIZE - 1){
            board[row][column] = (board[row][column] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row-1][column] = (board[row-1][column] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row][column-1] = (board[row][column-1] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
        } else if (row == 0){
            board[row][column] = (board[row][column] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row+1][column] = (board[row+1][column] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row][column+1] = (board[row][column+1] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row][column-1] = (board[row][column-1] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
        } else if (column == 0){
            board[row][column] = (board[row][column] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row-1][column] = (board[row-1][column] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row+1][column] = (board[row+1][column] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row][column+1] = (board[row][column+1] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
        } else if (row == BOARD_SIZE - 1){
            board[row][column] = (board[row][column] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row-1][column] = (board[row-1][column] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row][column-1] = (board[row][column-1] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row][column+1] = (board[row][column+1] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
        } else if (column == BOARD_SIZE - 1){
            board[row][column] = (board[row][column] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row-1][column] = (board[row-1][column] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row+1][column] = (board[row+1][column] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row][column-1] = (board[row][column-1] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
        } else {
            board[row][column] = (board[row][column] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row-1][column] = (board[row-1][column] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row+1][column] = (board[row+1][column] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row][column+1] = (board[row][column+1] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
            board[row][column-1] = (board[row][column-1] == EMPTY_CELL) ? LIGHT_ON : EMPTY_CELL;
        }
    }
    }

    void giveHint(){
        srand(time(0));
        int temp = rand() % (blocks - 1);

//
//        if (for (int i = 0; i < blocks; i++){CLICK_STATE = 1})
        //CHECK IF THERE IS 1 ELEMENT IN CLICK_STATE BEFORE EXECUTING; ELSE RETURN NO MORE HINTS, YOU HAVE BEATEN THE GAME;

        do {
            temp = rand() % (blocks - 1);
        } while (CLICK_STATE[temp] != 1);
        cout << temp + 1 << " ";
        hintPosition = temp + 1;
    }
};


#endif

