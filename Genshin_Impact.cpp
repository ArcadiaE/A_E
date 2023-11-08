/*
结构体加排序
*/

#include<iostream>
#include<string>
#include<ctime>

#include"copyright.h"

using namespace std;

struct c {
    string name;
    int atk;
    int level;
};

void arrange (struct c arr[], int len){
   
    for ( int i =0; i < len - 1; i++){
        for (int j = 0; j < len - i -1; j++){
            if(arr[j]. atk > arr[j+1]. atk){
                int temp = arr[j]. atk;
                arr[j]. atk = arr[j + 1]. atk;
                arr[j + 1]. atk = temp;
            }
        }
    } 

}



int main(){

    struct c arr [5] = {
        {"Ganyu", 2100, 90},
        {"Keqing", 2200, 90},
        {"Zhongli", 1900, 90},
        {"Hutao", 2300, 90},
        {"Shenzi", 2000, 50}
    };

    
    int len = sizeof(arr) / sizeof(arr[0]);
    for (int i = 0; i < 5; i++){
        cout<< arr[i]. name << arr[i]. atk << arr[i]. level << endl;
    }

    arrange(arr, len);

    cout << "----------------------------------------------------" << endl;
    
    for (int i = 0; i < 5; i++){
        cout << "Name: " << arr[i]. name << endl << "ATK: " 
             << arr[i]. atk << endl << "LEVEL: " << arr[i]. level << endl;
    }

    copyright();

    system("pause");

    return 0;
}