#include "Bishop.h"

Bishop::Bishop(bool color, Point place) : Tool(color, place)
{
}

Bishop::~Bishop()
{
}

int Bishop::canMove(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE])
{
	int x, y;

	if (ILEGALL_BISHOP) return BAD_MOV;

	for (x = this->_place.getX(), y = this->_place.getY(); toMove.getY() != y;)
	{
		if (this->_place.getX() - toMove.getX() < 0) x++;
		else x--;

		if (this->_place.getY() - toMove.getY() < 0) y++;
		else y--;

		if (board[y][x] != nullptr && toMove.getY() != y) return BAD_MOV;
	}

	return OK_MOV;
}

const char Bishop::getType()
{
	if (this->_color)
		return 'b';
	return 'B';
}

int Bishop::checkIfChess(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE])
{
	if (canMove(toMove, board) == 1)
		return 1;
	return 0;
}
