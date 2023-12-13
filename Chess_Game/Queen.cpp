#include "Queen.h"

Queen::Queen(bool color, Point place) : Tool(color, place)
{
}

Queen::~Queen()
{
}

int Queen::canMove(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE])
{
	Rook VirtualRook(this->_color, this->_place);
	Bishop VirtualBishop(this->_color, this->_place);

	if (ILEGALL_QUEEN) return BAD_MOV;
	return OK_MOV;
}

const char Queen::getType()
{
	if (this->_color)
		return 'q';
	return 'Q';
}

int Queen::checkIfChess(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE])
{
	Queen VirtualQueen(this->_color, toMove);
	if (canMove(toMove, board) == OK_MOV &&
		VirtualQueen.canMove(this->_kingsLoc[!bool(this->_color)], board)) // checks if the move will risk hostile king
	{
		return OK_MOV_CHESS;
	}

	return BAD_MOV_CHESS;
}
