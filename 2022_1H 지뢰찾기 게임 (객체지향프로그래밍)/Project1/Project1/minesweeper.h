#include <string>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <cctype>
#include <cassert>

using std::endl;
using std::cout;
using std::ifstream;
using std::ofstream;
using std::setw;
using std::setfill;
using std::string;
using std::ostream;

const int SIZE = 8;

void minesweeper( string input, string output );

void initBoard( char board[SIZE][SIZE], string file );

void displayBoard( ostream& out, char board[SIZE][SIZE] );

void touchBoard( char board[SIZE][SIZE], int x, int y, int& Spacestouched, bool& gameOver );