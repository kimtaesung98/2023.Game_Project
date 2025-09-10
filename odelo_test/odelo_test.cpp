#include <iostream>
using namespace std;

//글꼴 양식 : 8*16, 래스터 글꼴
int d_x[8] = { 1, 1, 0, 0, -1, -1, 1, -1 };
int d_y[8] = { 1, -1, -1, 1, 1, -1, 0, 0 };

class othello {
private:
    int** arr;
    int size;  // 배열의 크기를 저장할 변수 추가
public:
    othello(int num) : size(num) {  // 생성자 수정
        arr = new int* [size];
        for (int i = 0; i < size; i++) {
            arr[i] = new int[size];
            for (int j = 0; j < size; j++) {
                arr[i][j] = 0;
            }
        }
        arr[size / 2 - 1][size / 2] = 1;
        arr[size / 2][size / 2 - 1] = 1;
        arr[size / 2][size / 2] = 2;
        arr[size / 2 - 1][size / 2 - 1] = 2;
    }
    ~othello() {  // 소멸자 추가하여 동적으로 할당된 메모리 해제
        for (int i = 0; i < size; i++) {
            delete[] arr[i];
        }
        delete[] arr;
    }
    //그리기
    void draw() {
        for (int i = 0; i < size; i++) {  // 배열 크기 계산 수정
            for (int j = 0; j < size; j++) {
                if (arr[i][j] == 0) cout << " " << "." << " ";
                if (arr[i][j] == 1) cout << " " << "●";
                if (arr[i][j] == 2) cout << " " << "○";
            }
            cout << endl;
        }
    }
    // 입력값이 유효한지 확인하는 함수
    
    int check(int x, int y, int position, int  num) {
        int cnt = 0;
        int position = arr[x][y];
        for (int i = d_x[num], j = d_y[num]; i < size && j < 8 && i > 0 && j > 0; i += d_x[num], j += d_y[num]) {
            if (position == arr[x + i][y + j]) {
                if (cnt)break;
            }
            else {
                if (arr[x + i][y + j] == 0)break;
                else cnt++;
            }
        }
        return;
    }
    //8방향을 유효한지 확인하기
    bool confine(int x, int y, int color) {
        int cnt[8] = { 0 };
        int position = color;

        for (int i = 0; i < size; i++) {
            cnt[i] = check(x, y, position, i);
        }
        return false;
    }
};

int main() {
    int n;
    cout << "select board wide: ";
    cin >> n;
    int color;
    othello o(n);
    o.draw();
    while (1) {
        cout << "input : x , y :";
        int x; int y; scanf_s("%d %d", &x, &y);
        if (0 > x && x > n && 0 > y && y > n) {
            //입력 범위 밖의 입력값
            cout << "try again, can't push this" << endl;
            continue;
        }
        //입력값이 유효한지 검사
        if (o.confine(x,y,color)) {
            
        }
        //유효하지 않은 입력값, 상대턴으로
        else
        {
            color = (color == 2) ? 1 : 2;
        }

    }

    return 0;
}
