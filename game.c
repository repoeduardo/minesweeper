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

void openCell(int r, int c){
  if(coordinateIsValid(r, c) == 1 && game[r][c].isOpen == 0){
    game[r][c].isOpen = 1;
    if(game[r][c].bombsAround == 0){

      // Recursive
      openCell(r-1, c); // above
      openCell(r+1, c); // below
      openCell(r, c+1); // right
      openCell(r, c-1); // left
    }
  }
}

// Function that verifies victory. Won: returns N; Not won yet: returns 0;
int hasWon(){
  int numberOfClosedPositions = 0;
  for(row = 0; row < boardSize; row++){
    for(column = 0; column < boardSize; column++){
      if(game[row][column].isOpen == 0 && game[row][column].isBomb == 0){ // Is it closed and is it a bomb?
        numberOfClosedPositions++;
      }
    }
  }
  return numberOfClosedPositions;
}

// Reads the coordinates
void play(){
  int r, c;

  do{
    printBoard();
    do{
      printf("\nEnter the row and column coordinates in this format [y] [x]. Example: 5 7");
      printf("\n> ");
      scanf("%d%d", &r, &c);

      if(coordinateIsValid(r, c) == 0 || game[r][c].isOpen == 1){
        printf("\nInvalid coordinate or already open");
      }
    }while(coordinateIsValid(r, c) == 0 || game[r][c].isOpen == 1);

    openCell(r, c);
  }while(hasWon() != 0 && game[r][c].isBomb == 0);

  if(game[r][c].isBomb == 1){
    printf("\n\t Too bad, you lost\n");
  } else {
    printf("\n\tCONGRATULATIONS, YOU WON \n");
  }
  printBoard();
}


int main(){
    initializeGame();
    drawBombs(10);
    populateBombsAround();
    play();
    return 0;
}