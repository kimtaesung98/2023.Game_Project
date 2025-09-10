#include <iostream>
#include <vector>
#include <string>
#include <cmath>

using namespace std;

class ChessPiece {
public:
    string color;  // 말의 색
    string type;   // 말의 종류 (King, Queen, Rook, Bishop, Knight, Pawn)

    ChessPiece(string c, string t) : color(c), type(t) {}

    virtual bool validMove(int startX, int startY, int endX, int endY) = 0;  // 각 말마다 유효한 이동인지 확인하는 함수
    virtual char symbol() const = 0;  // 말의 시각적 표시
};

class King : public ChessPiece {
public:
    King(string color) : ChessPiece(color, "King") {}

    bool validMove(int startX, int startY, int endX, int endY) override {
        return abs(endX - startX) <= 1 && abs(endY - startY) <= 1;
    }

    char symbol() const override {
        return (color == "White") ? 'K' : 'k';
    }
};

class Queen : public ChessPiece {
public:
    Queen(string color) : ChessPiece(color, "Queen") {}

    bool validMove(int startX, int startY, int endX, int endY) override {
        return (startX == endX || startY == endY || abs(endX - startX) == abs(endY - startY));
    }

    char symbol() const override {
        return (color == "White") ? 'Q' : 'q';
    }
};

// 나머지 말들에 대한 클래스들도 비슷하게 정의합니다.
class ChessBoard {
public:
    vector<vector<ChessPiece*>> board;

    ChessBoard() {
        board.resize(8, vector<ChessPiece*>(8, nullptr));

        // 기본 체스판 설정 (흰색과 검은색 말을 각각 배치)
        for (int i = 0; i < 8; ++i) {
            board[1][i] = new ChessPiece("White", "Pawn");
            board[6][i] = new ChessPiece("Black", "Pawn");
        }

        board[0][0] = new King("White");
        board[0][7] = new King("Black");
        board[0][1] = new Queen("White");
        board[0][6] = new Queen("Black");
        // 여기에 추가적인 체스말들을 배치합니다.
    }

    void printBoard() {
        for (int i = 0; i < 8; ++i) {
            for (int j = 0; j < 8; ++j) {
                if (board[i][j] != nullptr)
                    cout << board[i][j]->symbol() << " ";
                else
                    cout << ". ";
            }
            cout << endl;
        }
    }

    bool movePiece(int startX, int startY, int endX, int endY) {
        if (board[startX][startY] == nullptr) {
            cout << "No piece at starting position!" << endl;
            return false;
        }

        ChessPiece* piece = board[startX][startY];
        if (piece->validMove(startX, startY, endX, endY)) {
            board[endX][endY] = piece;
            board[startX][startY] = nullptr;
            return true;
        }
        else {
            cout << "Invalid move!" << endl;
            return false;
        }
    }
};
int main() {
    ChessBoard chessBoard;
    int startX, startY, endX, endY;

    // 게임 루프
    while (true) {
        chessBoard.printBoard();

        // 사용자로부터 이동할 말의 시작 위치와 끝 위치를 입력받음
        cout << "Enter move (startX startY endX endY): ";
        cin >> startX >> startY >> endX >> endY;

        // 이동이 성공하면 체스판을 업데이트
        if (chessBoard.movePiece(startX, startY, endX, endY)) {
            cout << "Move successful!" << endl;
        }
        else {
            cout << "Move failed!" << endl;
        }
    }

    return 0;
}
