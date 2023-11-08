#include <iostream>
#include <vector>

using namespace std;

const double RAIN_IDEAL = 1.62;
//ideal daily rainfall in mm

void rainfall_check(vector<double> v){
    for(unsigned int i=0; i<v.size(); i++){
        if((v[i]<0)||(v[i]>1000)){
            cout << "Something is wrong!";
            exit (1);
        }
    }
}
//checks the legitimacy of inputs

void rainfall_input(vector<double>& v, int n){

    v.resize(n);
 
    for(unsigned int i=0; i<v.size(); i++)
    {
        double next;
        cin >> next;
        v[i]=next;
    }
 
    rainfall_check(v);
} 
//records rainfall for n days

double rainfall_ave(vector<double> v){ 
    
    double total=0;
 
    for(unsigned int i=0; i<v.size(); i++)
    
    total=total+v[i];
 
    return total/v.size();
}
//calculates the average rainfall

string rainfall_msg(vector<double> v){ 
    
    string message;
 
    if(rainfall_ave(v) < RAIN_IDEAL)
        message="This summer has been dry.";

    else if(rainfall_ave(v) > RAIN_IDEAL)
        message="This summer has been humid.";
    
    else
        message="We have been lucky!";
 
    return message;
}
//displays a comment

int main()
{
 vector<double> rain;
 cout << "Please specify the number of days to record: ";
 int rain_day;
 cin >> rain_day;
 cout << "Please record the daily rainfall of these "
 << rain_day << " days in unit mm:\n";
 rainfall_input(rain, rain_day);
 
 cout << "The average rainfall is calculated to be " 
 << rainfall_ave(rain) << " mm.\n"
 << rainfall_msg(rain);
 return 0;
}
