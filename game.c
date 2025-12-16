#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct{
  int isBomb; // is it a bomb? [0 - no] [1 - yes]
  int isOpen; // is it open? [0 - no] [1 - yes]
  int bombsAround; // 0 to 4
}Cell;

/* GLOBAL VARIABLES */
int row, column;
int boardSize = 10; // Board 10x10
Cell game[10][10];

// Initialize the game matrix
void initializeGame(){
    for(row = 0; row < boardSize; row++){
      for(column = 0; column < boardSize; column++){
        game[row][column].isBomb = 0;
        game[row][column].isOpen = 0;
        game[row][column].bombsAround = 0;
      }
    }
}

// Draw N bombs randomly
void drawBombs(int numberOfBombs){
  int index;
  srand(time(NULL));
  for(index = 0; index <= numberOfBombs; index++){
    row = rand() % boardSize; // always stays between 0 and 9
    column = rand() % boardSize; // always stays between 0 and 9

    if(game[row][column].isBomb == 0){
      game[row][column].isBomb = 1; // places a bomb
    } else {
      // If we get here it means the cell already has a bomb
      index--; // ensures the loop runs at least one more time
    }
  }
}

int main(){
    initializeGame();
    drawBombs(10);
    return 0;
}