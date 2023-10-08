#include "King.h"

King::King(bool color, Point place) : Tool(color, place) {}

King::~King()
{
}

int King::canMove(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE])
{
    if (ILLEGAL_KING) return BAD_MOV;
    //TODO: if (this->checkIfChess(toMove, board) == BAD_MOV_CHESS) return BAD_MOV_CHESS;

    return OK_MOV;
}

char King::getType() const
{
    if (this->_color)
        return 'k';
    return 'K';
}

int King::checkIfChess(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE])
{
    return 0;
}
