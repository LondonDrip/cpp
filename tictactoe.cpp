#include <iostream>
#include <vector>

using namespace std;

// �����, �������������� ���� � ��������-������
class TicTacToe {
private:
    int size;             // ������ �������� ����
    int winLength;        // ����� ���������� ������������������
    vector<vector<char>> board;  // ������� ���� � ���� ���������� ������� ��������

public:
    // ����������� ��� ������������� �������� ���� � ��������� �������� � ������ ���������� ������������������
    TicTacToe(int _size, int _winLength) : size(_size), winLength(_winLength) {
        // ������������� �������� ���� ������� ��������
        board = vector<vector<char>>(size, vector<char>(size, ' '));
    }

    // ����������� �������� ��������� �������� ����
    void displayBoard() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                cout << board[i][j] << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    // ���������� ���� ������
    bool makeMove(int row, int col, char symbol) {
        // ��������� ��������� �� 1 �� size
        --row;
        --col;

        // �������� ������������ ���� � ��������� ������� � ������
        if (row < 0 || row >= size || col < 0 || col >= size || board[row][col] != ' ') {
            return false;
        }

        board[row][col] = symbol;
        return true;
    }

    // ��������, �������� �� ������� ������ �����������
    bool isWinner(char symbol) const {
        // �������� �� ������� � ��������
        for (int i = 0; i < size; ++i) {
            int countRow = 0;
            int countCol = 0;
            for (int j = 0; j < size; ++j) {
                if (board[i][j] == symbol) {
                    ++countRow;
                }
                if (board[j][i] == symbol) {
                    ++countCol;
                }
            }
            if (countRow == winLength || countCol == winLength) {
                return true;
            }
        }

        // �������� �� ����������
        for (int i = 0; i <= size - winLength; ++i) {
            for (int j = 0; j <= size - winLength; ++j) {
                int countDiagonal1 = 0;
                int countDiagonal2 = 0;
                for (int k = 0; k < winLength; ++k) {
                    if (board[i + k][j + k] == symbol) {
                        ++countDiagonal1;
                    }
                    if (board[i + k][j + winLength - 1 - k] == symbol) {
                        ++countDiagonal2;
                    }
                }
                if (countDiagonal1 == winLength || countDiagonal2 == winLength) {
                    return true;
                }
            }
        }

        return false;
    }

    // ��������, ��������� �� ������� ����
    bool isBoardFull() const {
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                if (board[i][j] == ' ') {
                    return false;
                }
            }
        }
        return true;
    }
};

// ����������� �����, �������������� ������
class Player {
protected:
    char symbol;  // ������ ������ (X ��� O)

public:
    // ����������� ��� ��������� ������� ������
    Player(char _symbol) : symbol(_symbol) {}

    // ����������� ������� ��� ���������� ���� ������
    virtual void makeMove(TicTacToe& game) = 0;
};

// �����, �������������� ������������� ������
class HumanPlayer : public Player {
public:
    // ����������� ��� ��������� ������� ������������� ������
    HumanPlayer(char _symbol) : Player(_symbol) {}

    // ���������� ������� ��� ���������� ���� ������������� ������
    void makeMove(TicTacToe& game) override {
        int row, col;
        cout << "������� ��� ��� (������ � �������): ";
        cin >> row >> col;

        // ��������� ����, ���� ��� �����������
        while (!game.makeMove(row, col, symbol)) {
            cout << "������������ ���. ���������� �����: ";
            cin >> row >> col;
        }
    }
};

// �������� ������� ���������
int main() {
    const int boardSize = 3;   // ������ �������� ����
    const int winLength = 3;   // ����� ���������� ������������������

    // �������� ������� ���� � ���� ������������ �������
    TicTacToe game(boardSize, winLength);
    HumanPlayer playerX('X');
    HumanPlayer playerO('O');

    // ������� ���� �� ���������� ���� (������, �����)
    while (!game.isBoardFull() && !game.isWinner('X') && !game.isWinner('O')) {
        // ��� ������ X
        playerX.makeMove(game);
        game.displayBoard();

        // �������� ������ ��� ������ ����� ���� ������ X
        if (game.isWinner('X')) {
            cout << "����� X ���������!" << endl;
            break;
        }
        else if (game.isBoardFull()) {
            cout << "�����!" << endl;
            break;
        }

        // ��� ������ O
        playerO.makeMove(game);
        game.displayBoard();

        // �������� ������ ��� ������ ����� ���� ������ O
        if (game.isWinner('O')) {
            cout << "����� O ���������!" << endl;
            break;
        }
        else if (game.isBoardFull()) {
            cout << "�����!" << endl;
            break;
        }
    }

    return 0;
}

