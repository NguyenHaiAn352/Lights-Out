#ifndef _LOGIC__H
#define _LOGIC__H

#define BOARD_SIZE 3
#define EMPTY_CELL ' '
#define O_CELL 'o'
#define X_CELL 'x'
#define LIGHTED 'l'


struct Lightsout {
    char board[BOARD_SIZE][BOARD_SIZE];
//    char nextMove = O_CELL;
    char LIGHT_ON = LIGHTED;


    void init() {
        for (int i = 0; i < BOARD_SIZE; i++)
            for (int j = 0; j < BOARD_SIZE; j++) board[i][j] = EMPTY_CELL;
    }
    void move(int row, int column) {

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


};


#endif

