//适度编程益脑，过度编程伤身
//合理安排时间，享受健康生活
//copyright: @A_E email: yz50u22@soton.ac.uk
//山田凉请和我结婚

#include <iostream>
#include <fstream>
#include"copyright.h"
using namespace std;

const int SIZE = 9;

//打印横的分割线
void draw_line() {
    cout << " -  -  - + -  -  - + -  -  -" << endl;
}

//横着写，并检测数组中的数，发现X就替换成_，不是X就直接打印当前的数
void draw_cell(int value) {
    if(value == 0){
        cout << " _ ";
    }else{
        cout << " " << value << " ";
    }
}

//竖着写，每三列的下一列写一个|
void draw_row(int row[SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        draw_cell(row[i]);
        if ((i+1) % 3 == 0) {
            cout << "|";
        }
    }
    cout << endl;
}

//打印数独
void display_board(int board[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        if (i % 3 == 0) {
            draw_line();
        }
        draw_row(board[i]);
    }
    draw_line();
}

//检查是否符合规定
//i是表示行/列/组中的第i个元素，num是填入的数
bool is_valid(int board[SIZE][SIZE], int row, int col, int num) {
    // 检查行
    for (int i = 0; i < SIZE; i++) {
        if (board[row][i] == num) {
            return false;
        }
    }
    // 检查列
    for (int i = 0; i < SIZE; i++) {
        if (board[i][col] == num) {
            return false;
        }
    }
    // 检查3x3宫格
    int startRow = row - row % 3;
    int startCol = col - col % 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (board[i + startRow][j + startCol] == num) {
                return false;
            }
        }
    }
    return true;
}

//解数独，发现空格就填入1-9的数，并调用检验功能，如果不符合规定就归零重新填入数字，0=X代表空格
bool solve_board(int board[SIZE][SIZE]) {
    for (int row = 0; row < SIZE; row++) {
        for (int col = 0; col < SIZE; col++) {
            if (board[row][col] == 0) {
                for (int num = 1; num <= 9; num++) {
                    if (is_valid(board, row, col, num)) {
                        board[row][col] = num;
                        if (solve_board(board)) {
                            return true;
                        } else {
                            board[row][col] = 0;
                        }
                    }
                }
                return false;
            }
        }
    }
    return true;
}

//主函数
int main() {
    // 打开数据文件
    ifstream file("sudoku.txt");
    if (file.is_open()) {
        int board[9][9];
        // 读取数据并填入数独
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) {
                char c;
                file >> c;
                if (c == 'X') {
                    board[i][j] = 0;
                } else {
                    board[i][j] = c - '0';
                }
            }
        }
        // 关闭文件
        file.close();
        // 继续使用数独代码      
        display_board(board);
        solve_board(board);
        display_board(board);
        copyright();
        Ryo();
    } 
    else {
        cout << "Error: Unable to open file" << endl;
    }

    system("pause");    
    return 0;
}