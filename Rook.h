#pragma once
#include "Tool.h"

#define ILLEGAL_ROOK !(this->_place.getX() == toMove.getX() && this->_place.getY() != toMove.getY()|| this->_place.getX() != toMove.getX() && this->_place.getY() == toMove.getY())


class Rook :
    public Tool
{
public:
    // Constructor & Destructor
    Rook(bool color, Point place);
    ~Rook();

    // Functions
    int canMove(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE]);
    const char getType();
    int checkIfChess(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE]);
};

