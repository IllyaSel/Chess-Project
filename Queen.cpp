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

char Queen::getType() const
{
	if (this->_color)
		return 'q';
	return 'Q';
}

int Queen::checkIfChess(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE])
{
	if (canMove(toMove, board) == 1)
		return 1;
	return 0;
}
