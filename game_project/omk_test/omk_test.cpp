화
15GB 중 19% 사용됨
약관 · 개인정보처리방침 · 프로그램 정책
마지막 계정 활동: 1시간 전
세부정보
﻿#include <iostream>
#include <locale> // For Unicode output
#include <limits> // For numeric_limits
#include <vector>
using namespace std;

class field {
public:

    int** logic_arr() {
        int** l_omk = new int* [19];
        for (int i = 0; i < 19; i++) {
            l_omk[i] = new int[19];
            for (int j = 0; j < 19; j++) {
                l_omk[i][j] = 0;
            }
        }
        return l_omk;
    }

    field() {
        logic_omk = logic_arr();
    }
    int** logic_omk;

    bool win_omk(int x, int y, int color) {
        int arr[4][9] = { 0 }; // Count stones
        printf("color : %d, position : (%d / %d)\n", color, x + 1, y + 1);

        // Check horizontally
        int cnt = 0;
        int cnt_stone = 0;
        printf("%-20s", "Horizontally:");
        for (int i = y - 4; i < y + 5; i++) {
            if (i >= 0 && i < 19) {
                if (logic_omk[x][i] == color) {
                    cnt_stone++;
                }
                else {
                    cnt_stone = 0;
                }
                arr[0][cnt++] = cnt_stone;
                printf("[%d : %2d / %2d] ", cnt_stone, x, i);
                if (cnt_stone == 6) return false; // 6 stones
            }
        }
        printf("\n");

        // Check vertically
        printf("%-20s", "Vertically:");
        cnt = 0;
        cnt_stone = 0;
        for (int i = x - 4; i < x + 5; i++) {
            if (i >= 0 && i < 19) {
                if (logic_omk[i][y] == color) {
                    cnt_stone++;
                }
                else {
                    cnt_stone = 0;
                }
                arr[1][cnt++] = cnt_stone;
                printf("[%d : %2d / %2d] ", cnt_stone, i, y);
                if (cnt_stone == 6) return false; // 6 stones
            }
        }
        printf("\n");

        // Check diagonally up
        printf("%-20s", "Upward Diagonally: ");
        cnt = 0;
        cnt_stone = 0;
        int j = y + 4;
        for (int i = x - 4; i < x + 5; i++) {
            if (i >= 0 && i < 19 && j >= 0 && j < 19) {
                if (logic_omk[i][j] == color) {
                    cnt_stone++;
                }
                else {
                    cnt_stone = 0;
                }
                arr[2][cnt++] = cnt_stone;
                if (cnt_stone == 6) return false; // 6 stones
                printf("[%d : %2d / %2d] ", cnt_stone, i, j);
            }
            j--;
        }
        printf("\n");

        // Check diagonally down
        printf("%-20s", "Downward Diagonally:");
        j = y - 4;
        cnt = 0;
        cnt_stone = 0;
        for (int i = x - 4; i < x + 5; i++) {
            if (i >= 0 && i < 19 && j >= 0 && j < 19) {
                if (logic_omk[i][j] == color) {
                    cnt_stone++;
                }
                else {
                    cnt_stone = 0;
                }
                arr[3][cnt++] = cnt_stone;
                if (cnt_stone == 6) return false; // 6 stones
                printf("[%d : %2d / %2d] ", cnt_stone, j, i);
            }
            j++;
        }
        printf("\n");

        // Print results (for debugging)
        for (int i = 0; i < 4; i++) {
            printf("%d : ", i);
            for (int j = 0; j < 9; j++) {
                printf("%d ", arr[i][j]);
                if (arr[i][j] == 5) return true;
            }
            printf("\n");
        }

        return false;
    }

    void print_board() {
        printf("-----");
        for (int i = 1; i < 20; i++)printf("%2d", i);
        printf("\n");

        for (int i = 0; i < 19; i++) {
            printf("%02d : ", i + 1);
                for (int j = 0; j < 19; j++) {
                    if (logic_omk[i][j] == 0) {
                        if (i == 0) {
                            if (j == 0) printf("┌");
                            else if (j == 18) printf("┐");
                            else printf("┬");
                        }
                        else if (i == 18) {
                            if (j == 0) printf("└");
                            else if (j == 18) printf("┘");
                            else printf("┴");
                        }
                        else {
                            if (j == 0) printf("├");
                            else if (j == 18) printf("┤");
                            else printf("┼");
                        }
                    }
                    else {
                        if (logic_omk[i][j] == 1) printf("●");
                        else printf("○");
                    }
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
            if (x < 1 || x > 19 || y < 1 || y > 19 || logic_omk[x - 1][y - 1] != 0) {
                cout << "Invalid position. Please try again." << endl;
                continue;
            }
            logic_omk[x - 1][y - 1] = color;

            system("cls"); // Clear console screen (Windows specific)
            print_board();
            if (win_omk(x - 1, y - 1, color)) {
                system("cls");
                print_board();
                (color % 2 == 1) ? cout << "Winner: Black" << endl : cout << "Winner: White" << endl;
                break;
            }
            color = (turn % 2 == 0) ? white : black;
            turn++;
        }
    }

    ~field() {
        for (int i = 0; i < 19; i++) {
            delete[] logic_omk[i];
        }
        delete[] logic_omk;
    }
};

int main() {
    field omk;
    omk.play();
    return 0;
}