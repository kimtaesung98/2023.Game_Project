#include <iostream>
using namespace std;
//글꼴 양식 : 8*16, 래스터 글꼴
int d_x[8] = {1,1,0,0,-1,-1,1,-1};
int d_y[8] = {1,-1,-1,1,1,-1,0,0};

class field {
public:
    int** logic_arr() {
        int** odelo = new int* [8];
        for (int i = 0; i < 8; i++) {
            odelo[i] = new int[8];
            for (int j = 0; j < 8; j++) {
                odelo[i][j] = 0;
            }
        }
        odelo[3][3] = 1;
        odelo[4][4] = 1;
        odelo[3][4] = 2;
        odelo[4][3] = 2;
        return odelo;
    }

    field() {
        arr = logic_arr();
    }
    int** arr;

    bool confine(int x, int y,int color) {
        int cnt[8] = { 0 };
        int position = color;
        
        for (int i = 0; i < 8; i++) {
            cnt[i] = check(x, y, position,i);
        }
        return false;
    }
    int check(int x, int y, int position,int num) {
        int cnt = 0;
        int position = arr[x][y];
        for (int i = d_x[num], j = d_y[num]; i < 8 && j < 8 && i > 0 && j > 0; i += d_x[num], j += d_y[num]) {
            if (position == arr[x + i][y + j]) {
                if (cnt)break;
                else turning( x, y, position, cnt + 1,num);
            }
            else {
                if (arr[x + i][y + j] == 0)break;
                else cnt++;
            }
        }
        return;
    }
    void turning(int x, int y, int position, int cnt,int num) {
        int position = arr[x][y];
        for (int i = d_x[num], j = d_y[num]; cnt--; i += d_x[num], j += d_y[num]) {
            arr[i][j] = position;
        }
    }

    /*
    void print_board() {
        printf("-----");
        for (int i = 1; i < 9; i++)printf("%2d", i);
        printf("\n");

        for (int i = 0; i < 8; i++) {
            printf("%02d : ", i + 1);
            for (int j = 0; j < 8; j++) {
                if (arr[i][j] == 0) {
                    if (i == 0) {
                        if (j == 0) printf("┌");
                        else if (j == 7) printf("┐");
                        else printf("┬");
                    }
                    else if (i == 7) {
                        if (j == 0) printf("└");
                        else if (j == 7) printf("┘");
                        else printf("┴");
                    }
                    else {
                        if (j == 0) printf("├");
                        else if (j == 7) printf("┤");
                        else printf("┼");
                    }
                }
                else {
                    if (arr[i][j] == 1) printf("●");
                    else printf("○");
                }
            }
            printf("\n");
        }
    }
    */
    void print_board() {
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (arr[i][j] == 0)printf(".");
                else if(arr[i][j] == 1)printf("●");
                else printf("○");
            }
            printf("\n");
        }
    }
    void play() {
        print_board();
        int black = 1, white = 2, color = 1;
        int turn = 0;
        int x, y;
        while (true) {
            cout << "Enter the position to place your stone (x,y): ";
            cin >> x >> y;
            if (x < 1 || x > 8 || y < 1 || y > 8 || arr[x - 1][y - 1] != 0) {
                cout << "Invalid position. Please try again." << endl;
                continue;
            }
            if (confine(x, y, color))arr[x - 1][y - 1] = color;
            else continue;
            //논리값 판단하기
            system("cls"); // Clear console screen (Windows specific)
            print_board();
            /*
            if (win_omk(x - 1, y - 1, color)) {
                system("cls");
                print_board();
                (color % 2 == 1) ? cout << "Winner: Black" << endl : cout << "Winner: White" << endl;
                break;
            }
            */
            color = (turn % 2 == 0) ? white : black;
            turn++;
        }
    }

    ~field() {
        for (int i = 0; i < 8; i++) {
            delete[] arr[i];
        }
        delete[] arr;
    }
};

int main() {
    field ocelo;//
    ocelo.play();
    return 0;
}