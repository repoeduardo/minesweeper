#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// ANSI Color Codes
#define RESET   "\033[0m"
#define RED     "\033[31m"
#define YELLOW  "\033[33m"
#define CYAN    "\033[36m"

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

// Function that verifies if coordinates are valid or not: [0 - not valid] and [1 - valid]
int coordinateIsValid(int r, int c){
  if(r >= 0 && r < boardSize && c >= 0 && c < boardSize){
    return 1;
  } else {
    return 0;
  }
}

// Function that calculates and returns the number of bombs around `row` and `column`
int calculateBombsAround(int r, int c){
  /* Task: check the position immediately above, below, left and right
    above = r - 1 and c
    below = r + 1 and c
    right = r and c + 1
    left = r and c - 1
    verify if the coordinate is valid
  */

  int quantity = 0;

  // above
  if(coordinateIsValid(r - 1, c) && game[r-1][c].isBomb){
    quantity++;
  }
  // below
  if(coordinateIsValid(r + 1, c) && game[r+1][c].isBomb){
    quantity++;
  }
  // right
  if(coordinateIsValid(r, c + 1) && game[r][c+1].isBomb){
    quantity++;
  }
  // left
  if(coordinateIsValid(r, c - 1) && game[r][c-1].isBomb){
    quantity++;
  }

  return quantity;
}

// Procedure that populates the `bombsAround` field
void populateBombsAround(){
  for(row = 0; row < boardSize; row++){
      for(column = 0; column < boardSize; column++){
        game[row][column].bombsAround = calculateBombsAround(row, column);
      }
    }
}

void printBoard(){
  printf("\n\n\t  ");
  for(row = 0; row < boardSize; row++){
    printf(YELLOW "  %d " RESET, row); // column indices
  }
  printf("\n\t  -----------------------------------------\n");
  for(row = 0; row < boardSize; row++){
    printf("\t" YELLOW "%d" RESET " |", row); // row indices 
      for(column = 0; column < boardSize; column++){
        if(game[row][column].isOpen){

          if(game[row][column].isBomb == 1){
            printf(RED " * " RESET); // bomb in red
          } else {
            printf(CYAN " %d " RESET, game[row][column].bombsAround);
          }
          
        } else {
          printf("   ");
        }
        printf("|");
      }
      printf("\n\t  -----------------------------------------\n");
      printf("\n");
    }
}

int main(){
    initializeGame();
    drawBombs(10);
    populateBombsAround();
    printBoard();
    return 0;
}