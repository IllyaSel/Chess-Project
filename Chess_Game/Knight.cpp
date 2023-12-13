#include "Knight.h"

Knight::Knight(bool color, Point place) : Tool(color, place)
{
}

Knight::~Knight()
{
}

int Knight::canMove(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE])
{
	if (ILLEGAL_KNIGHT) return BAD_MOV;
	if (board[toMove.getY()][toMove.getX()] != nullptr && board[toMove.getY()][toMove.getX()]->getColor() == this->_color) return BAD_MOV_FULL_DST;
	return OK_MOV;
}

const char Knight::getType()
{
	if (this->_color)
		return 'n';
	return 'N';
}

int Knight::checkIfChess(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE])
{
	Knight VirtualKnight(this->_color, toMove);
	if (canMove(toMove, board) == OK_MOV &&
		VirtualKnight.canMove(this->_kingsLoc[!bool(this->_color)], board)) // checks if the move will risk hostile king
	{
		return OK_MOV_CHESS;
	}

	return BAD_MOV_CHESS;
}
