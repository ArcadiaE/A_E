//适度编程益脑，过度编程伤身
//合理安排时间，享受健康生活
//copyright: @A_E 
//email: yz50u22@soton.ac.uk

#include <iostream>
#include <vector>

using namespace std;

void initialScore(vector<int>& v){

    for(int i = 0; i < 5; i++){
        int score;
        cin >> score;
        v[i] = score;
    }
}
//records initial five scores

void addScore(vector<int>& v, int n){  

    for(int i = 0; i < n; i++){
        int score;
        cin >> score;
        v.push_back(score);
    }
}
//add n scores to the list

void showScore(vector<int> v){
    
    cout << "The registered scores are: ";
    for(int i = 0; i < v.size(); i++){
        cout << v[i] << " ";
    }
    cout << endl;
}


//show all scores

int main(){
    vector<int> scoreList(5);
    cout << "We always have five players at first." << endl;
    cout << "Enter their scores:" << endl;;
    initialScore(scoreList);
    cout << "We may have a few more players." << endl;;
    cout << "How many more players this time?" << endl; ;
    int morePlayer;
    cin >> morePlayer;
    if(morePlayer>0)
    {
    cout << "We have " << morePlayer << " more players." << endl;
    cout << "Enter their scores: ";
    addScore(scoreList, morePlayer);
    }
    showScore(scoreList);

    system("pause");
    return 0;
}
