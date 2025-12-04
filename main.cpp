#include <iostream>
#include <fstream>
using namespace std;

char board[3][3];
int scoreX = 0;
int scoreO = 0;
int scoreDraw = 0;

void saveScore() {
    ofstream file("score.txt");
    if (file.is_open()) {
        file << scoreX << endl;
        file << scoreO << endl;
        file << scoreDraw << endl;
        file.close();
    }
}

void loadScore() {
    ifstream file("score.txt");
    if (file.is_open()) {
        file >> scoreX;
        file >> scoreO;
        file >> scoreDraw;
        file.close();
    }
}

void resetBoard() {
    char num = '1';
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            board[i][j] = num++;
        }
    }
}

void displayBoard() {
    cout << "\n";
    cout << " " << board[0][0] << " | " << board[0][1] << " | " << board[0][2] << "\n";
    cout << "---+---+---\n";
    cout << " " << board[1][0] << " | " << board[1][1] << " | " << board[1][2] << "\n";
    cout << "---+---+---\n";
    cout << " " << board[2][0] << " | " << board[2][1] << " | " << board[2][2] << "\n";
    cout << "\n";
}

bool checkWin() {
    for (int i = 0; i < 3; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2]) return true;
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i]) return true;
    }
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2]) return true;
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0]) return true;

    return false;
}

bool isDraw() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}

void makeMove(char player) {
    int choice;
    cout << "Player " << player << ", enter a number (1-9): ";
    cin >> choice;

    int row = (choice - 1) / 3;
    int col = (choice - 1) % 3;

    if (choice < 1 || choice > 9 || board[row][col] == 'X' || board[row][col] == 'O') {
        cout << "Invalid move. Try again.\n";
        makeMove(player);
    } else {
        board[row][col] = player;
    }
}

void displayScore() {
    cout << "\n===== SCOREBOARD =====\n";
    cout << "Player X Wins: " << scoreX << endl;
    cout << "Player O Wins: " << scoreO << endl;
    cout << "Draws: " << scoreDraw << endl;
    cout << "=======================\n\n";
}

void resetScore() {
    scoreX = scoreO = scoreDraw = 0;
    saveScore();
    cout << "\nScoreboard reset!\n\n";
}

void playGame() {
    char currentPlayer = 'X';
    resetBoard();

    while (true) {
        displayBoard();
        makeMove(currentPlayer);

        if (checkWin()) {
            displayBoard();
            cout << "Player " << currentPlayer << " wins!\n";

            if (currentPlayer == 'X') scoreX++;
            else scoreO++;

            saveScore();
            break;
        }

        if (isDraw()) {
            displayBoard();
            cout << "It's a draw!\n";
            scoreDraw++;
            saveScore();
            break;
        }

        currentPlayer = (currentPlayer == 'X') ? 'O' : 'X';
    }
}

void mainMenu() {
    int choice;

    while (true) {
        cout << "====== TIC TAC TOE ======\n";
        cout << "1. Play Game\n";
        cout << "2. View Scoreboard\n";
        cout << "3. Reset Scoreboard\n";
        cout << "4. Exit\n";
        cout << "Choose an option (1-4): ";
        cin >> choice;

        switch (choice) {
            case 1:
                playGame();
                break;
            case 2:
                displayScore();
                break;
            case 3:
                resetScore();
                break;
            case 4:
                cout << "Goodbye!\n";
                return;
            default:
                cout << "Invalid option. Try again.\n";
        }
    }
}

int main() {
    loadScore();
    mainMenu();
    return 0;
}
