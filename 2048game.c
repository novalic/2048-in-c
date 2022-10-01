
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "list.h"

#define bool int
#define true 1
#define false 0

int gameMatrix[4][4];
bool playing, exitGame, chosing, theresMoves, initGame, gameOver, wonGame;
int i, j, score;
char keyMove;
List freePositions;

void printMatrix() {

  for (i = 0; i <= 3; i++) {
    printf("\n|");
    for (j = 0; j <= 3; j++)
      switch (gameMatrix[i][j]) {
        case 2: case 4: case 8: {
          printf("    %i   ", gameMatrix[i][j]);
          printf("|");
          break;
        };
        case 16: case 32: case 64: {
          printf("   %i   ", gameMatrix[i][j]);
          printf("|");
          break;
        };
        case 128: case 256: case 512: {
          printf("  %i   ", gameMatrix[i][j]);
          printf("|");
          break;
        };
        case 1024: {
          printf("  %i  ", gameMatrix[i][j]);
          printf("|");
          break;
        };
        case 2048: {
          printf("  %i  ", gameMatrix[i][j]);
          printf("|");
          playing = false;
          break;
        };
        default: {
          printf("        ");
          printf("|");
          break;
        };
      };
  }
}
void checkGameover() {

    theresMoves = false; // checking if game is lost

    for (i = 0; i <= 3; i++) // matrix is full?
        for (j = 0; j <= 3; j++)
            if (gameMatrix[i][j] == 0)
                theresMoves = true;

    if (theresMoves == false) // if matrix is full, checking if theres two contiguous cells with the same number in the rows
        for (i = 0; i <= 3; i++)
            for (j = 0; j < 3; j++)
                if (gameMatrix[i][j] == gameMatrix[i][j + 1])
                    theresMoves = true;

    if (theresMoves == false) // if not, check the same in columns
        for (i = 0; i < 3; i++)
            for (j = 0; j <= 3; j++)
                if (gameMatrix[i][j] == gameMatrix[i + 1][j])
                    theresMoves = true;

    if (theresMoves == false)
        gameOver = true;

    theresMoves = true;
}

void generateNumber() {
  if (wonGame == false && theresMoves == true) {
      freePositions = createList();
      for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
          if (gameMatrix[i][j] == 0)
            insertFront(freePositions, i, j);
      int* freeCell = returnRandom(freePositions);

      if ((freeCell[0] + freeCell[1]) % 4 == 0)
        gameMatrix[freeCell[0]][freeCell[1]] = 4;
      else
        gameMatrix[freeCell[0]][freeCell[1]] = 2;

      destroyList(freePositions);
  };
}

int main() {

  exitGame = false;
  while (exitGame == false) {
    score = 0;
    wonGame = false;
    gameOver = false;

    for (i = 0; i <= 3; i++)
      for (j = 0; j <= 3; j++)
        gameMatrix[i][j] = 0;

    int a1, a2, b1, b2;

    initGame = false;
    srand(time(NULL));

    while (initGame == false) {
      b1 = rand() % 4;
      b2 = rand() % 4;
       a1 = rand() % 4;
      a2 = rand() % 4;

      if (!(a1 == b1) && !(a2 == b2))
        initGame = true;
    }; // end while initGame

    gameMatrix[a1][a2] = 2;
    gameMatrix[b1][b2] = 2;

    playing = true;
    while (playing == true) {
      printMatrix();

      printf("\n\nScore: %i", score);
      printf("\n\nKeys: (w,a,s,d,q) for (up,left,down,right,quit)");
      printf("\nType a move: ");
      keyMove = getchar();
      while('\n'!=getchar());
      printf("\n");

      int matrixRow;
      int matrixColumn;

      switch (keyMove) {

        case 'a': {

          theresMoves = false;
          for (i = 0; i <= 3; i++) // theres zero to the lefty
              for (j = 0; j < 3; j++)
                  if ((gameMatrix[i][j] == 0) && (gameMatrix[i][j + 1] != 0))
                      theresMoves = true;

          if (theresMoves == false) { // two contiguous numbers of the same value?
            for (i = 0; i <= 3; i++)
              for (j = 0; j < 3; j++)
                if ((gameMatrix[i][j] != 0) && (gameMatrix[i][j] == gameMatrix[i][j + 1]))
                  theresMoves = true;
          }

          if (theresMoves == true) {

              for (i = 0; i <= 3; i++) // move everything to the lefty
                  for (j = 0; j < 3; j++) {
                      matrixColumn = j + 1;
                      while ((matrixColumn <= 3) && (gameMatrix[i][j] == 0)) {
                          gameMatrix[i][j] = gameMatrix[i][matrixColumn];
                          gameMatrix[i][matrixColumn] = 0;
                          matrixColumn++;
                      };
                  };

              for (i = 0; i <= 3; i++) { // add
                  for (j = 0; j < 3; j++)

                      if (gameMatrix[i][j] == gameMatrix[i][j + 1]) {
                          gameMatrix[i][j] = gameMatrix[i][j] * 2;
                          gameMatrix[i][j + 1] = 0;

                          if (gameMatrix[i][j] == 2048)
                              wonGame = true;

                          score = score + gameMatrix[i][j];
                      };
              };

              for (i = 0; i <= 3; i++) { // moveeverything to the lefty again
                  for (j = 0; j < 3; j++) {
                      matrixColumn = j + 1;
                      while ((matrixColumn <= 3) && (gameMatrix[i][j] == 0)) {
                          gameMatrix[i][j] = gameMatrix[i][matrixColumn];
                          gameMatrix[i][matrixColumn] = 0;
                          matrixColumn++;
                      };
                  };

              };
              generateNumber();
              printf("---------------------------------------");
              printf("\n---------------------------------------");
              printf("\nLast move: Left.\n");
              checkGameover();
          }; // end processing the move
          break;
        };
        case 's': {
          theresMoves = false;
          for (i = 3; i > 0; i--)
              for (j = 0; j <= 3; j++)
                  if ((gameMatrix[i][j] == 0) && (gameMatrix[i - 1][j] != 0))
                      theresMoves = true;

          if (theresMoves == false)
              for (i = 3; i > 0; i--)
                  for (j = 0; j <= 3; j++)
                      if ((gameMatrix[i][j] != 0) && (gameMatrix[i][j] == gameMatrix[i - 1][j]))
                          theresMoves = true;

          if (theresMoves == true) {
              for (i = 3; i > 0; i--)
                  for (j = 0; j <= 3; j++) {
                      matrixRow = i - 1;
                      while ((matrixRow >= 0) && (gameMatrix[i][j] == 0)) {
                          gameMatrix[i][j] = gameMatrix[matrixRow][j];
                          gameMatrix[matrixRow][j] = 0;
                          matrixRow--;
                      };
                  };
              for (i = 3; i > 0; i--)
                  for (j = 0; j <= 3; j++)
                      if (gameMatrix[i][j] == gameMatrix[i - 1][j]) {
                          gameMatrix[i][j] = gameMatrix[i][j] * 2;
                          gameMatrix[i - 1][j] = 0;

                          if (gameMatrix[i][j] == 2048)
                              wonGame = true;

                          score = score + gameMatrix[i][j];
                      };
              for (i = 3; i > 0; i--)
                  for (j = 0; j <= 3; j++) {
                      matrixRow = i - 1;
                      while ((matrixRow >= 0) && (gameMatrix[i][j] == 0)) {
                          gameMatrix[i][j] = gameMatrix[matrixRow][j];
                          gameMatrix[matrixRow][j] = 0;
                          matrixRow--;
                      };
                  };
              generateNumber();
              printf("---------------------------------------");
              printf("\n---------------------------------------");
              printf("\nLast move: Down.\n");
              checkGameover();

          };

          break;
        };
        case 'w': {
          theresMoves = false;
          for (i = 0; i < 3; i++)
              for (j = 0; j <= 3; j++)
                  if ((gameMatrix[i][j] == 0) && (gameMatrix[i + 1][j] != 0))
                      theresMoves = true;

          if (theresMoves == false)
              for (i = 0; i < 3; i++)
                  for (j = 0; j <= 3; j++)
                      if ((gameMatrix[i][j] != 0) && (gameMatrix[i][j] == gameMatrix[i + 1][j]))
                          theresMoves = true;

          if (theresMoves == true) {
              for (i = 0; i < 3; i++)
                  for (j = 0; j <= 3; j++) {
                      matrixRow = i + 1;
                      while ((matrixRow <= 3) && (gameMatrix[i][j] == 0)) {
                          gameMatrix[i][j] = gameMatrix[matrixRow][j];
                          gameMatrix[matrixRow][j] = 0;
                          matrixRow++;
                      };
                  };
              for (i = 0; i < 3; i++)
                  for (j = 0; j <= 3; j++)
                      if (gameMatrix[i][j] == gameMatrix[i + 1][j]) {
                          gameMatrix[i][j] = gameMatrix[i][j] * 2;
                          gameMatrix[i + 1][j] = 0;

                          if (gameMatrix[i][j] == 2048)
                              wonGame = true;

                          score = score + gameMatrix[i][j];
                      };
              for (i = 0; i < 3; i++)
                  for (j = 0; j <= 3; j++) {
                      matrixRow = i + 1;
                      while ((matrixRow <= 3) && (gameMatrix[i][j] == 0)) {
                          gameMatrix[i][j] = gameMatrix[matrixRow][j];
                          gameMatrix[matrixRow][j] = 0;
                          matrixRow++;
                      };

                  };
              generateNumber();
              printf("---------------------------------------");
              printf("\n---------------------------------------");
              printf("\nLast move: Up.\n");
              checkGameover();
          };
          break;
        };
        case 'd': {
          theresMoves = false;

          for (i = 0; i <= 3; i++)
              for (j = 3; j > 0; j--)
                  if ((gameMatrix[i][j] == 0) && (gameMatrix[i][j - 1] != 0))
                      theresMoves = true;

          if (theresMoves == false)
              for (i = 0; i <= 3; i++)
                  for (j = 3; j > 0; j--)
                      if ((gameMatrix[i][j] != 0) && (gameMatrix[i][j] == gameMatrix[i][j - 1]))
                          theresMoves = true;

          if (theresMoves == true) {
              for (i = 0; i <= 3; i++)
                  for (j = 3; j > 0; j--) {
                      matrixColumn = j - 1;
                      while ((matrixColumn >= 0) && (gameMatrix[i][j] == 0)) {
                          gameMatrix[i][j] = gameMatrix[i][matrixColumn];
                          gameMatrix[i][matrixColumn] = 0;
                          matrixColumn--;
                      };

                  };
              for (i = 0; i <= 3; i++)
                  for (j = 3; j > 0; j--)
                      if (gameMatrix[i][j] == gameMatrix[i][j - 1]) {
                          gameMatrix[i][j] = gameMatrix[i][j] * 2;
                          gameMatrix[i][j - 1] = 0;

                          if (gameMatrix[i][j] == 2048)
                              wonGame = true;

                          score = score + gameMatrix[i][j];

                      };
              for (i = 0; i <= 3; i++)
                  for (j = 3; j > 0; j--) {
                      matrixColumn = j - 1;
                      while ((matrixColumn >= 0) && (gameMatrix[i][j] == 0)) {
                          gameMatrix[i][j] = gameMatrix[i][matrixColumn];
                          gameMatrix[i][matrixColumn] = 0;
                          matrixColumn--;
                      };
                  };
              generateNumber();
              printf("---------------------------------------");
              printf("\n---------------------------------------");
              printf("\nLast move: Right.\n");
              checkGameover();

          };
          break;
        };
        case 'q': {
          playing = false;
          break;
        };
        default: {
          printf("---------------------------------------");
          printf("\n---------------------------------------");
          printf("\nYou have entered an invalid key.\n");

        };
      };
        // cheking if the game ended
      if ((wonGame == true) || (gameOver == true)) {
        printMatrix();
        if (wonGame == true) {
          playing = false;
          printf ("\n\nYou won!. Your score was: %i.\n", score);
        };
        if (gameOver == true) {
          playing = false;
          printf ("\n\nGame Over.\n");
        };
      };

      keyMove = 'p'; // randome just to avoid possible bugs
      if (playing == false) {
          while ((keyMove != 'y') && (keyMove != 'n')) {
            printf("Do you wish to play again? (y/n): ");
            keyMove = getchar();
            while('\n'!=getchar());
            printf("\n");
          };
          if (keyMove == 'n')
            exitGame = true;
      };

    }; // juego actual
  };
  return 0;
};
