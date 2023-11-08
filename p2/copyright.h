#include<iostream>
#include<fstream>
using namespace std;

void copyright(){

cout <<"------------------------------------------------"<<endl;
cout <<"copyright: @A_E"<< endl;
cout << "Email: yz50u22@soton.ac.uk" << endl;
cout <<"------------------------------------------------"<<endl;
}

void cutline(){
    cout << "------------------------------------------------"<<endl;
}

void Yamada_Ryo(){
    string line;
    ifstream myfile("yamadaryo.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            cout << line << '\n';
        }
        myfile.close();
    }
    else
    {
        cout << "Unable to open file";
    }
}

void Ryo(){
    string line;
    ifstream myfile("ryo.txt");
    if (myfile.is_open())
    {
        while (getline(myfile, line))
        {
            cout << line << '\n';
        }
        myfile.close();
    }
    else
    {
        cout << "Unable to open file";
    }


}
