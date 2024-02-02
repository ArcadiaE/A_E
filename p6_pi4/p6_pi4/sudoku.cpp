/*

===== sudoku.cpp ========================================================

*/

#include <iostream>
#include <cstring>
//#include <string>
//#include <sstream>
//#include <cmath>
//#include <cstdlib>

#ifdef QT_VERSION
#include "../common/cmdlib.h"
#else
#include "cmdlib.h"  //fix me
#endif

#include "sudoku.h"

using namespace std;



Sudoku current_game;

void Sudoku::setSudoku( sudoku_t new_elements )
{
    for(int i=0,j=0; i<97 && j<81; i++)
    {
        switch (new_elements.str[i].str)
        {
        /*
        case '0':
        elements[j] = ZERO;j++;
        break;
        */
        case '1':
            elements[j] = ONE;
            j++;
            break;
        case '2':
            elements[j] = TWO;
            j++;
            break;
        case '3':
            elements[j] = THREE;
            j++;
            break;
        case '4':
            elements[j] = FOUR;
            j++;
            break;
        case '5':
            elements[j] = FIVE;
            j++;
            break;
        case '6':
            elements[j] = SIX;
            j++;
            break;
        case '7':
            elements[j] = SEVEN;
            j++;
            break;
        case '8':
            elements[j] = EIGHT;
            j++;
            break;
        case '9':
            elements[j] = NINE;
            j++;
            break;
        case 'X':
            elements[j] = X;
            j++;
            break;
        case '\n':
            break;
        case '\r':
            break;
        }
        for(int k=j; k<81; k++)
            elements[k] = X;
    }
}

/*
void Sudoku::display() const{

for(int i=0;i<81;i++)
{
    if(i%9 == 0)
        cout<<"\n";
    cout<<elements[i]<<"\t";
}
}
*/

void Sudoku::display() const
{

    for(int i=0; i<81; i++)
    {
        if(i%9 == 0)
            cout<<"\n";
        if(elements[i]==10)
        {
            cout<<'X';
            continue;
        }
        cout<<elements[i];
    }
}

bool Sudoku::isValid() const
{

    int i, j, k, l;

    for (i = 0; i < 9; i++)
    {
        sudoku_element row[10] = {X};
        for (j = 0; j < 9; j++)
        {
            if (elements[i * 9 + j] != X)
            {
                if (row[elements[i * 9 + j]] == ONE)
                {
                    return false;
                }
                else
                {
                    row[elements[i * 9 + j]] = ONE;
                }
            }
        }
    }

    for (i = 0; i < 9; i++)
    {
        sudoku_element column[10] = {X};
        for (j = 0; j < 9; j++)
        {
            if (elements[j * 9 + i] != X)
            {
                if (column[elements[j * 9 + i]] == ONE)
                {
                    return false;
                }
                else
                {
                    column[elements[j * 9 + i]] = ONE;
                }
            }
        }
    }

    for (i = 0; i < 3; i++)
    {
        for (j = 0; j < 3; j++)
        {
            sudoku_element square[10] = {X};
            for (k = i * 3; k < i * 3 + 3; k++)
            {
                for (l = j * 3; l < j * 3 + 3; l++)
                {
                    if (elements[k * 9 + l] != X)
                    {
                        if (square[elements[k * 9 + l]] == ONE)
                        {
                            return false;
                        }
                        else
                        {
                            square[elements[k * 9 + l]] = ONE;
                        }
                    }
                }
            }
        }
    }

    return true;
}


bool Sudoku::isFilled() const
{
    for(int i=0; i<81; i++)
        if(elements[i] == X)
            return false;
    return true;
}

char * Sudoku::to_string(int i) const
{

    switch (elements[i])
    {
    /*
    case 0:
    return (char *)"0";
    break;
    */
    case 1:
        return (char *)"1";
        break;
    case 2:
        return (char *)"2";
        break;
    case 3:
        return (char *)"3";
        break;
    case 4:
        return (char *)"4";
        break;
    case 5:
        return (char *)"5";
        break;
    case 6:
        return (char *)"6";
        break;
    case 7:
        return (char *)"7";
        break;
    case 8:
        return (char *)"8";
        break;
    case 9:
        return (char *)"9";
        break;
    case 10:
        return (char *)"X";
        break;
    default:
        return (char *)"X";
        break;
    }
}

int Sudoku::to_elements( int i,const char input)
{

    switch (input)
    {
    /*
    case '0':
    elements[i] = ZERO;
    return 0;
    break;
    */
    case '1':
        elements[i] = ONE;
        return 0;
        break;
    case '2':
        elements[i] = TWO;
        return 0;
        break;
    case '3':
        elements[i] = THREE;
        return 0;
        break;
    case '4':
        elements[i] = FOUR;
        return 0;
        break;
    case '5':
        elements[i] = FIVE;
        return 0;
        break;
    case '6':
        elements[i] = SIX;
        return 0;
        break;
    case '7':
        elements[i] = SEVEN;
        return 0;
        break;
    case '8':
        elements[i] = EIGHT;
        return 0;
        break;
    case '9':
        elements[i] = NINE;
        return 0;
        break;
    case 'X':
        elements[i] = X;
        return 0;
        break;
    case '\n':
        break;
    case '\r':
        break;
    default:
        return -1;
    }
    return 0;

    /*
                switch (input){
            case "0":
                elements[i] = ZERO;
                return 0;
                break;
            case "1":
                elements[i] = ONE;
                return 0;
                break;
            case "2":
                elements[i] = TWO;
                return 0;
                break;
            case "3":
                elements[i] = THREE;
                return 0;
                break;
            case "4":
                elements[i] = FOUR;
                return 0;
                break;
            case "5":
                elements[i] = FIVE;
                return 0;
                break;
            case "6":
                elements[i] = SIX;
                return 0;
                break;
            case "7":
                elements[i] = SEVEN;
                return 0;
                break;
            case "8":
                elements[i] = EIGHT;
                return 0;
                break;
            case "9":
                elements[i] = NINE;
                return 0;
                break;
            case "X":
                elements[i] = X;
                return 0;
                break;
            default:
                return -1;
                break;
            }
    */
}

Sudoku::operator sudoku_t() const
{
    sudoku_t new_elements;
    for(int i=0,j=0; i<81;)
    {
        if(j==9||j==20||j==31||j==42||j==53||j==64||j==75||j==86||j==97)
        {
            new_elements.str[j].str = '\r';
            new_elements.str[j+1].str = '\n';
            j+=2;
        }
        else
        {
            switch (elements[i])
            {
            /*
            case 0:
            new_elements.str[j].str = '0';
            break;
            */
            case 1:
                new_elements.str[j].str = '1';
                break;
            case 2:
                new_elements.str[j].str = '2';
                break;
            case 3:
                new_elements.str[j].str = '3';
                break;
            case 4:
                new_elements.str[j].str = '4';
                break;
            case 5:
                new_elements.str[j].str = '5';
                break;
            case 6:
                new_elements.str[j].str = '6';
                break;
            case 7:
                new_elements.str[j].str = '7';
                break;
            case 8:
                new_elements.str[j].str = '8';
                break;
            case 9:
                new_elements.str[j].str = '9';
                break;
            case 10:
                new_elements.str[j].str = 'X';
                break;
            }
            i++;
            j++;
        }

//            cout<<elements[j]<<" ";
    }
    return new_elements;
}
