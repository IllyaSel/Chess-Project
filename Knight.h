#pragma once
#include "Tool.h"

#define ILLEGAL_KNIGHT !((abs(this->_place.getX() - toMove.getX()) == 1 && abs(this->_place.getY() - toMove.getY()) == 2) || (abs(this->_place.getX() - toMove.getX()) == 2 && abs(this->_place.getY() - toMove.getY()) == 1))


class Knight :
    public Tool
{
public:
    // Constructor & Destructor
    Knight(bool color, Point place);
    ~Knight();

    // Functions
    int canMove(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE]);
    const char getType();
    int checkIfChess(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE]);

};

