#include "King.h"

King::King(bool color, Point place) : Tool(color, place) {}

King::~King()
{
}

int King::canMove(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE])
{
    if (ILLEGAL_KING) return BAD_MOV;
    //TODO: if (this->checkIfChess(toMove, board) == BAD_MOV_CHESS) return BAD_MOV_CHESS;
    if (board[toMove.getY()][toMove.getX()] != nullptr && board[toMove.getY()][toMove.getX()]->getColor() == this->_color) return BAD_MOV_FULL_DST;

    return OK_MOV;
}

const char King::getType()
{
    if (this->_color)
        return 'k';
    return 'K';
}

int King::checkIfChess(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE])
{
    return 0;
}
