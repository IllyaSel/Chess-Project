#include "Bishop.h"

Bishop::Bishop(bool arg_color, Point arg_place) : Tool(arg_color, arg_place)
{
}

Bishop::~Bishop()
{
}

int Bishop::canMove(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE])
{
	int lx, ly;

	if (ILEGALL_BISHOP) return BAD_MOV;

	for (lx = this->_place.getX(), ly = this->_place.getY(); toMove.getY() != ly;)
	{
		if (this->_place.getX() - toMove.getX() < 0) lx++;
		else lx--;

		if (this->_place.getY() - toMove.getY() < 0) ly++;
		else ly--;

		if ((board[ly][lx] != nullptr && toMove.getY() != ly) || (board[ly][lx] != nullptr && board[ly][lx]->getColor() == this->_color)) return BAD_MOV;
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
