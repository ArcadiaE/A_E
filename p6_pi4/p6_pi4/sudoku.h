//=============================================================================
//
// Purpose:
//
// $NoKeywords: $
//=============================================================================


#ifndef __SUDOKU_H__
#define __SUDOKU_H__


//
// sudoku.h
//

//#include <sstream>
//#include <cmath>
//#include <cstdlib>

//using namespace std;



typedef enum {
//ZERO = 0,
ONE = 1,
TWO,
THREE,
FOUR,
FIVE,
SIX,
SEVEN,
EIGHT,
NINE,
X
}sudoku_element;

typedef struct
{
	char str;
} _sudoku_t;

typedef struct
{
	_sudoku_t str[97];
} sudoku_t;

class Sudoku
{
public:

    void setSudoku( sudoku_t new_elements );
    void display() const ;
    sudoku_element element(int i,int j) const { return elements[i*9+j]; }
    sudoku_element &element(int i,int j) { return elements[i*9+j]; }
    bool isValid() const;
    bool isFilled() const;
    char * to_string(int i = 0) const;
    int to_elements( int i,const char input);

    operator sudoku_t() const;

private:
    sudoku_element elements[81];

};


extern Sudoku current_game;


#endif  //__SUDOKU_H__
