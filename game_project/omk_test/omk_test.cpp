#include <iostream>
#include <locale> // For Unicode output
#include <limits> // For numeric_limits
#include <vector>

using namespace std;

// 전역 변수 (필요시 클래스 내부로 옮길 수 있습니다)
const int SIZE = 19; // 바둑판 크기

// 돌을 표현하는 클래스
class stone {
public:
    int x, y;
    int color; // 0: 빈 칸, 1: 흑돌, 2: 백돌
    stone(int x = -1, int y = -1, int color = 0) : x(x), y(y), color(color) {}
};

// 바둑판과 게임 로직을 관리하는 클래스
class field {
public:
    stone** logic_baduk;

    // 초기자: 19x19 stone 객체 배열을 동적으로 생성하고 초기화합니다.
    stone** logic_arr() {
        stone** arr = new stone*[SIZE];
        for (int i = 0; i < SIZE; i++) {
            arr[i] = new stone[SIZE];
            for (int j = 0; j < SIZE; j++) {
                arr[i][j].x = i;
                arr[i][j].y = j;
                arr[i][j].color = 0; // 초기 색상은 0 (빈 칸)
            }
        }
        return arr;
    }

    // field 클래스 생성자
    field() {
        logic_baduk = logic_arr();
    }

    // 바둑판을 출력하는 함수
    void print_board() {
        // 유니코드 출력을 위해 locale 설정 (Windows 환경에서 한글 깨짐 방지)
        // setlocale(LC_ALL, "ko_KR.UTF-8"); // Linux/macOS
        setlocale(LC_ALL, ""); // Windows

        printf("   "); // 여백
        for (int i = 1; i <= SIZE; i++) printf("%2d", i);
        printf("\n");

        for (int i = 0; i < SIZE; i++) {
            printf("%2d ", i + 1);
            for (int j = 0; j < SIZE; j++) {
                if (logic_baduk[i][j].color == 0) {
                    if (i == 0) {
                        if (j == 0) printf("┌ ");
                        else if (j == SIZE - 1) printf("┐ ");
                        else printf("┬ ");
                    } else if (i == SIZE - 1) {
                        if (j == 0) printf("└ ");
                        else if (j == SIZE - 1) printf("┘ ");
                        else printf("┴ ");
                    } else {
                        if (j == 0) printf("├ ");
                        else if (j == SIZE - 1) printf("┤ ");
                        else printf("┼ ");
                    }
                } else {
                    if (logic_baduk[i][j].color == 1) printf("● "); // 흑돌
                    else printf("○ "); // 백돌
                }
            }
            printf("\n");
        }
    }

    // 게임 플레이 로직
    void play() {
        print_board();
        int black = 1, white = 2;
        int currentPlayer = black; // 첫 턴은 흑돌
        int turn = 0;
        int x, y;

        cout << "Welcome to the Go game!" << endl;
        cout << "Enter '0 0' at any time to quit." << endl;

        while (true) {
            cout << (currentPlayer == black ? "Black" : "White") << " turn. Enter the position to place your stone (row, col): ";
            cin >> x >> y;

            // 게임 종료 조건
            if (x == 0 && y == 0) {
                cout << "Game ended by player request." << endl;
                break;
            }

            // 유효성 검사
            if (cin.fail() || x < 1 || x > SIZE || y < 1 || y > SIZE || logic_baduk[x - 1][y - 1].color != 0) {
                cin.clear(); // 입력 버퍼 초기화
                cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 잘못된 입력 제거
                cout << "Invalid position. Please try again." << endl;
                continue;
            }

            // 돌 놓기
            logic_baduk[x - 1][y - 1].color = currentPlayer;

            // 콘솔 화면 지우기 (Windows에서만 작동, Linux/macOS는 `clear` 명령 사용)
            // system("cls");
            // system("clear"); // cross-platform: system("cls || clear");

            print_board();

            // 턴 전환
            currentPlayer = (currentPlayer == black) ? white : black;
            turn++;
        }
    }
                                
    // 소멸자: 동적으로 할당된 메모리 해제
    ~field() {
        for (int i = 0; i < SIZE; i++) {
            delete[] logic_baduk[i];
        }
        delete[] logic_baduk;
    }
};

int main() {
    field baduk;
    baduk.play();
    return 0;
}