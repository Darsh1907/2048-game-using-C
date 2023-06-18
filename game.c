#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 4

int board[SIZE][SIZE];

void initialize() {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            board[i][j] = 0;
        }
    }
}

void generateTile() {
    int i, j;
    int count = 0;
    int emptyTiles[SIZE * SIZE][2];

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                emptyTiles[count][0] = i;
                emptyTiles[count][1] = j;
                count++;
            }
        }
    }

    if (count > 0) {
        int index = rand() % count;
        int x = emptyTiles[index][0];
        int y = emptyTiles[index][1];
        board[x][y] = (rand() % 2 + 1) * 2; // generates either 2 or 4
    }
}

void printBoard() {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            printf("%6d", board[i][j]);
        }
        printf("\n");
    }
}

int isGameOver() {
    int i, j;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            if (board[i][j] == 0) {
                return 0; // game is not over
            }
            if ((i < SIZE - 1 && board[i][j] == board[i + 1][j]) ||
                (j < SIZE - 1 && board[i][j] == board[i][j + 1])) {
                return 0; // game is not over
            }
        }
    }
    return 1; // game is over
}

void slideLeft() {
    int i, j, k;
    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE - 1; j++) {
            for (k = j + 1; k < SIZE; k++) {
                if (board[i][k] != 0) {
                    if (board[i][j] == 0) {
                        board[i][j] = board[i][k];
                        board[i][k] = 0;
                        j--;
                    } else if (board[i][j] == board[i][k]) {
                        board[i][j] *= 2;
                        board[i][k] = 0;
                    }
                    break;
                }
            }
        }
    }
}

void rotateBoard() {
    int i, j;
    int temp[SIZE][SIZE];

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            temp[i][j] = board[j][SIZE - 1 - i];
        }
    }

    for (i = 0; i < SIZE; i++) {
        for (j = 0; j < SIZE; j++) {
            board[i][j] = temp[i][j];
        }
    }
}

int main(){
    srand(time(0)); // seed the random number generator
    initialize();
    generateTile();
    generateTile();
    printBoard();

    while (!isGameOver()) {
        char move;
        printf("Enter move (a: left, d: right, w: up, s: down, q: quit): ");
        scanf(" %c", &move);

        switch (move) {
            case 'a': // left
                slideLeft();
                break;
            case 'd': // right
                rotateBoard();
                rotateBoard();
                slideLeft();
                rotateBoard();
                rotateBoard();
                break;
            case 'w': // up
                rotateBoard();
                slideLeft();
                rotateBoard();
                rotateBoard();
                rotateBoard();
                break;
            case 's': // down
                rotateBoard();
                rotateBoard();
                rotateBoard();
                slideLeft();
                rotateBoard();
                break;
            case 'q': // quit
                break;
            default:
                printf("Invalid move!\n");
                continue;
        }
        
        if(move == 'q') break;

        generateTile();
        printBoard();
    }

    printf("Game Over!\n");

    return 0;
}