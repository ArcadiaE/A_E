//适度编程益脑，过度编程伤身
//合理安排时间，享受健康生活
//copyright: @A_E 
//email: yz50u22@soton.ac.uk

#include <iostream>
using namespace std;
void swapAfterConfirm (int& a, int& b){
    char choice;
    cout << "Do you want to swap(Y or N)?" << endl;
    cin >> choice;
    if (choice == 'Y'){
        cout << "Confirmed to swap" << endl;
        int temp = a;
        a = b;
        b = temp;
    }
    else if (choice == 'N'){
        cout << "Confirmed not to swap" << endl;
    }
    else {
        cout << "Can't confirm so do nothing" << endl;
    }
}

int main(){
 
    int valueA, valueB;
    cout << "Please enter two integers: ";
    cin >> valueA >> valueB;
    swapAfterConfirm (valueA, valueB);
    cout << "We now have " << valueA << " and " << valueB <<".";

    system("pause");
    return 0;
}