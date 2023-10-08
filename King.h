#pragma once
#include "Tool.h"

#define ILLEGAL_KING !((this->_place.getX() == toMove.getX() + 1 || this->_place.getX() == toMove.getX() - 1 || this->_place.getY() == toMove.getY() + 1 || this->_place.getY() == toMove.getY() - 1) && abs(this->_place.getX() - toMove.getX()) <=1   && abs(this->_place.getY() - toMove.getY()) <= 1)


class King :
    public Tool
{
public:
    // Constructor & Destructor
    King(bool color, Point place);
    ~King();

    //Functions
    int canMove(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE]);
    const char getType();
    int checkIfChess(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE]);
};

