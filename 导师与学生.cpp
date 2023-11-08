/*
一名老师带五个学生，共三名老师
创建结构体，老师的结构体中有老师姓名和其五个学生
学生的结构体有学生姓名成绩
*/

#include<iostream>
#include<string>
#include<ctime>

#include"copyright.h"

using namespace std;

struct student{
    string name;
    int score;
};

struct teacher{
    string t_name;
    struct student stuArray[5] ;
};

void input_data (struct teacher teaArray[], int len){
    
    string name_base [3] =
    {"Leven", "Tomas", "Daniel"};

    string stuname_base1 [5] = 
    {"Ryo", "Bocchi", "Kita", "Nijlka", "Starry"};

    string stuname_base2 [5] = 
    {"Vodafone", "Outlook", "Unilink", "Tiktok", "Weibo"};

    string stuname_base3 [5] = 
    {"Bilbil", "Zhifubao", "Discord", "Wechat", "Amazon"};
    
    for (int i = 0; i < len; i++){

        teaArray[i]. t_name = "Tutor_";
        teaArray[i]. t_name += name_base[i];

        for (int j = 0; j < 5; j++){

            teaArray[i]. stuArray[j]. name = "Tutee_";

            if (i == 0){
                teaArray[i]. stuArray[j]. name += stuname_base1 [j];
            }
            else if (i == 1){
                teaArray[i]. stuArray[j]. name += stuname_base2 [j];
            }
            else if (i == 2){
                teaArray[i]. stuArray[j]. name += stuname_base3 [j];
            }

            int A = rand() % 61 + 40;
            teaArray[i]. stuArray[j]. score = A;
        }
    
    }
}

void printInfo (struct teacher teaArray[], int len){

    for (int i = 0; i < len; i++){
        cout << teaArray[i]. t_name << endl;
        for (int j = 0 ; j < 5; j++){
            cout << "Tutee: " << teaArray[i]. stuArray[j]. name << endl;
            cout << " score: " << teaArray[i]. stuArray[j]. score << endl;
        }
    }
}

int main(){

    srand((unsigned int)time(NULL));

    struct teacher teaArray[3];

    int len = sizeof(teaArray) / sizeof(teaArray[0]);
    input_data(teaArray, len);
   
    printInfo(teaArray, len);

    copyright();

    system("pause");

    return 0;
}