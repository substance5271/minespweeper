#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

const int BOARD_SIZE = 9;
const int NUM_MINES = 10;

vector<vector<bool> > mineBoard(BOARD_SIZE, vector<bool>(BOARD_SIZE, false));
vector<vector<bool> > revealed(BOARD_SIZE, vector<bool>(BOARD_SIZE, false));

void placeMines() {
    int count = 0;
    while (count < NUM_MINES) {
        int row = rand() % BOARD_SIZE;
        int col = rand() % BOARD_SIZE;
        if (!mineBoard[row][col]) {
            mineBoard[row][col] = true;
            count++;
        }
    }
}

int countAdjacentMines(int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int newRow = row + i;
            int newCol = col + j;
            if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE) {
                if (mineBoard[newRow][newCol])
                    count++;
            }
        }
    }
    return count;
}

void revealCell(int row, int col) {
    if (revealed[row][col])
        return;

    revealed[row][col] = true;

    if (mineBoard[row][col]) {
        cout << "Game Over! You hit a mine." << endl;
        exit(0);
    }

    int numAdjacentMines = countAdjacentMines(row, col);
    if (numAdjacentMines == 0) {
        for (int i = -1; i <= 1; i++) {
            for (int j = -1; j <= 1; j++) {
                int newRow = row + i;
                int newCol = col + j;
                if (newRow >= 0 && newRow < BOARD_SIZE && newCol >= 0 && newCol < BOARD_SIZE) {
                    revealCell(newRow, newCol);
                }
            }
        }
    }
}

void printBoard() {
    // Print column numbers
    cout << "   ";
    for (int col = 1; col <= BOARD_SIZE; col++) {
        cout << col << " ";
    }
    cout << endl;

    // Print horizontal line
    cout << "  +";
    for (int col = 1; col <= BOARD_SIZE; col++) {
        cout << "- ";
    }
    cout << endl;

    for (int row = 0; row < BOARD_SIZE; row++) {
        // Print row number
        cout << row + 1 << " |";

        for (int col = 0; col < BOARD_SIZE; col++) {
            if (revealed[row][col]) {
                if (mineBoard[row][col])
                    cout << "X ";
                else {
                    int numAdjacentMines = countAdjacentMines(row, col);
                    cout << numAdjacentMines << " ";
                }
            } else {
                cout << "- ";
            }
        }
        cout << "|" << endl;
    }

    // Print horizontal line
    cout << "  +";
    for (int col = 1; col <= BOARD_SIZE; col++) {
        cout << "- ";
    }
    cout << endl;
}

int main() {
    srand(time(0));
    placeMines();

    while (true) {
        printBoard();

        int row, col;
        cout << "Enter the row and column to reveal (0 to quit): ";
        cin >> row >> col;

        if (row == 0 || col == 0)
            break;

        row--;
        col--;

        if (row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE) {
            revealCell(row, col);
        } else {
            cout << "Invalid input. Try again." << endl;
        }
    }

    return 0;
}

