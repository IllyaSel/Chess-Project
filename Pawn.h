#pragma once
#include "Tool.h"

#define ILLEGAL_PAWN !((this->_place.getY() - toMove.getY() == 1 && !this->getColor() || this->_place.getY() - toMove.getY() == -1 && this->getColor() || (!this->_ifMove) && (this->_place.getY() - toMove.getY() == 2 && !this->getColor() || this->_place.getY() - toMove.getY() == -2 && this->getColor())) && (this->_place.getX() - toMove.getX() == 0 || abs(this->_place.getX() - toMove.getX()) == 1 && board[toMove.getY()][toMove.getX()] != nullptr && board[toMove.getY()][toMove.getX()]->getColor() != !this->getColor()) || (this->_place.getY() - toMove.getY() == 1 && board[toMove.getY()][toMove.getX()] != nullptr || this->_place.getY() - toMove.getY() == -1 && board[toMove.getY()][toMove.getX()] != nullptr) || (board[toMove.getY()][toMove.getX()] != nullptr && this->_place.getX() - toMove.getX() != -1 || board[toMove.getY()][toMove.getX()] != nullptr && this->_place.getX() - toMove.getX() != 1))


class Pawn :
    public Tool
{
public:
    // Constructor & Destructor
    Pawn(bool color, Point place);
    ~Pawn();

    // Functions
    int canMove(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE]);
    const char getType();
    int checkIfChess(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE]);

};

