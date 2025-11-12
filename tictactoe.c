#include <stdio.h>
#include <stdlib.h> // For system("cls") or system("clear")

// Global variables
char board[3][3];       // The 3x3 game board
const char PLAYER_X = 'X';
const char PLAYER_O = 'O';

// Function prototypes
void resetBoard();
void printBoard();
int checkFreeSpaces();
void playerMove(char player);
char checkWinner();
void printWinner(char winner);

int main() {
    char winner = ' ';
    char currentPlayer = PLAYER_X;

    resetBoard();

    while (winner == ' ' && checkFreeSpaces() != 0) {
        // Clear the screen for a cleaner look
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif

        printBoard();
        printf("Player %c's turn.\n", currentPlayer);
        playerMove(currentPlayer);
        
        winner = checkWinner();
        
        // Switch players
        if (currentPlayer == PLAYER_X) {
            currentPlayer = PLAYER_O;
        } else {
            currentPlayer = PLAYER_X;
        }
    }

    // Clear screen and show final board
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
    
    printBoard();
    printWinner(winner);

    return 0;
}

// Fills the board with numbers 1-9
void resetBoard() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = (i * 3) + j + '1';
        }
    }
}

// Prints the current state of the board
void printBoard() {
    printf("\n");
    printf(" Tic-Tac-Toe\n");
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[2][0], board[2][1], board[2][2]);
    printf("---|---|---\n");
    printf("\n");
}

// Counts the number of available squares
int checkFreeSpaces() {
    int freeSpaces = 9;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i][j] == 'X' || board[i][j] == 'O') {
                freeSpaces--;
            }
        }
    }
    return freeSpaces;
}

// Handles the player's move
void playerMove(char player) {
    int choice;
    int row, col;

    do {
        printf("Enter a number (1-9): ");
        scanf("%d", &choice);

        // Convert choice (1-9) to board coordinates (0-2)
        row = (choice - 1) / 3;
        col = (choice - 1) % 3;

        if (choice < 1 || choice > 9) {
            printf("Invalid input! Please choose a number between 1 and 9.\n");
        } else if (board[row][col] == 'X' || board[row][col] == 'O') {
            printf("That spot is already taken! Try again.\n");
        } else {
            board[row][col] = player;
            break;
        }
    } while (1); // Infinite loop until a valid move is made
}

// Checks for a winner
char checkWinner() {
    // Check rows
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][0] == board[i][2]) {
            return board[i][0];
        }
    }
    // Check columns
    for (int i = 0; i < 3; i++) {
        if (board[0][i] == board[1][i] && board[0][i] == board[2][i]) {
            return board[0][i];
        }
    }
    // Check diagonals
    if (board[0][0] == board[1][1] && board[0][0] == board[2][2]) {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[0][2] == board[2][0]) {
        return board[0][2];
    }

    return ' '; // No winner
}

// Prints the final game result
void printWinner(char winner) {
    if (winner == PLAYER_X || winner == PLAYER_O) {
        printf("Player %c wins!\n", winner);
    } else {
        printf("It's a draw!\n");
    }
}