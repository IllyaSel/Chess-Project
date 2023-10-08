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
	if (canMove(toMove, board) == 1)
		return 1;
	return 0;
}
