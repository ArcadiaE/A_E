//适度编程益脑，过度编程伤身
//合理安排时间，享受健康生活
//copyright: @A_E 
//email: yz50u22@soton.ac.uk

#include <iostream>
#include <vector>

using namespace std;

class StudentECS
{
public:
 
    StudentECS() : studentName("No name yet"), studentID(0) {}

    StudentECS(const string& theName, const int& theID) : studentName(theName), studentID(theID){}

    string getName() const {
        return studentName;
    }
    int getID() const {
        return studentID;
    }

    void setName(const string& newName){
        studentName = newName;
    }
    void setID(const int& newID){
        studentID = newID;
    }

    void printStatus() const{
        cout << "Error! Unidentified student!"; 
        exit(1);
    }

private:
    string studentName;
    int studentID;
};

class StudentEEE: public StudentECS{
public:
    StudentEEE() : microcontroller(0){}

    StudentEEE(const string& theName, const int& theID, const bool& 
                theMicrocontroller) : StudentECS(theName, theID), microcontroller(theMicrocontroller){}

    bool getMicrocontroller() const {
        return microcontroller;
    }

    void setMicrocontroller(const bool& newMicrocontroller) {
        microcontroller = newMicrocontroller;
    }

    void printStatus() const {
        if (microcontroller == true)
            cout << "Student" << getName() << "with ID" << getID() << "has received a microcontroller." << endl;
        else
            cout << "Student" << getName() << "with ID" << getID() << "needs a microcontroller." << endl;
    }
private:
    bool microcontroller; 
};

class StudentCS: public StudentECS
{
public:
    StudentCS() : gpuIridis(0){}

    StudentCS(const string& theName, const int& theID, const bool& theIridis)
                : StudentECS(theName, theID), gpuIridis(theIridis){}

    bool getIridis() const {
        return gpuIridis;
    }
    
    void setIridis(const bool& newIridis) {
        gpuIridis = newIridis;
    }

    void printStatus() const {
        if (gpuIridis == true)
            cout << "Student" << getName() << "with ID" << getID() << "has received a gpuIridis." << endl;
        else
            cout << "Student" << getName() << "with ID" << getID() << "needs a gpuIridis." << endl;
    }

private:
    bool gpuIridis; 
};

int operator < (const StudentECS& StudentECS1, const StudentECS& StudentECS2){
    return(StudentECS1.getID() < StudentECS2.getID());
}

int main()
{
    StudentEEE ella("Ella", 202101, true);
    StudentEEE emma("Emma", 202102, false);
    
    StudentCS charlie("Charlie", 202103, true);
    StudentCS charles("Charles", 202104, false);
    
    ella.printStatus();
    emma.printStatus();
    
    charlie.printStatus();
    charles.printStatus();
 
    if(ella<charlie)
        cout << "Ella was enrolled before Charlie as her ID is smaller.\n";
    else
        cout << "Ella was enrolled after Charlie as her ID is larger.\n";
 
    if(charles<emma)
        cout << "Charles was enrolled before Emma as his ID is smaller.\n";
    else
        cout << "Charles was enrolled after Emma as his ID is larger.\n";
 
    StudentECS cranberry;
    
    cranberry.printStatus();
    
    return 0;
}
