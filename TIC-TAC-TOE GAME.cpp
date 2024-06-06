#include <iostream>
#include <cstdlib>

using namespace std;

const int SIZE = 3;
char board[SIZE][SIZE];
// SIZE OF DISPLAY BOARD
void initializeBoard() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            board[i][j] = ' ';
        }
    }
}
// THIS FUNCTION DISPLAY BOARD IN CONSOLE
void displayBoard() {
    cout << "\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            cout << " " << board[i][j];
            if (j < SIZE - 1) cout << " |";
        }
        cout << "\n";
        if (i < SIZE - 1) cout << "---+---+---\n";
    }
    cout << "\n";
}
// CHECKS THE VALID MOVES
bool isMoveValid(int row, int col) {
    return row >= 0 && row < SIZE && col >= 0 && col < SIZE && board[row][col] == ' ';
}

void playerMove(char player) {
    int row, col;
    while (true) {
        cout << "Player " << player << ", enter your move (row and column): ";
        cin >> row >> col;
        row--; col--; // Convert to 0-indexed
        if (isMoveValid(row, col)) {
            board[row][col] = player;
            break;
        } else {
            cout << "Invalid move. Try again.\n";
        }
    }
}
// CHECK WITCH PLAYER IS WIN THE OR NOT
bool checkWin(char player) {
    // Check rows and columns
    for (int i = 0; i < SIZE; ++i) {
        if ((board[i][0] == player && board[i][1] == player && board[i][2] == player) ||
            (board[0][i] == player && board[1][i] == player && board[2][i] == player)) {
            return true;
        }
    }
    // Check diagonals
    if ((board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        return true;
    }
    return false;
}
// CHECK WITCH PLAYER IS DEAW THE OR NOT
bool checkDraw() {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}
// SWITCH PLAYER AFTER EACH MOVES
void switchPlayer(char &currentPlayer) {
    currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
}

bool playAgain() {
    char choice;
    cout << "Do you want to play again? (y/n): ";
    cin >> choice;
    return choice == 'y' || choice == 'Y';
}

int main() {
    char currentPlayer;
    bool gameWon, gameDraw;
    
    do {
        initializeBoard();
        currentPlayer = 'X';
        gameWon = gameDraw = false;

        while (!gameWon && !gameDraw) {
            displayBoard();
            playerMove(currentPlayer);
            gameWon = checkWin(currentPlayer);
            if (!gameWon) {
                gameDraw = checkDraw();
                if (!gameDraw) {
                    switchPlayer(currentPlayer);
                }
            }
        }

        displayBoard();
        if (gameWon) {
            cout << "Player " << currentPlayer << " wins!\n";
        } else if (gameDraw) {
            cout << "The game is a draw!\n";
        }
    } while (playAgain());

    cout << "Thanks for playing!\n";

    return 0;
}
