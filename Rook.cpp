#include "Rook.h"

Rook::Rook(bool color, Point place) : Tool(color, place)
{
}

Rook::~Rook()
{
}

int Rook::canMove(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE])
{
	if (ILLEGAL_ROOK) return BAD_MOV;

	for (int i = this->_place.getX(); i != toMove.getX() - 1 && i != toMove.getX() + 1 && toMove.getX() != this->_place.getX();)
	{
		i += 1; // TODO: Check if there is need for: (toMove.getX() - this->_place.getX()) / abs(toMove.getX() - this->_place.getX())

		if (board[toMove.getY()][i] != nullptr)
			return BAD_MOV;
	}
	for (int i = this->_place.getY(); i != toMove.getY() - 1 && i != toMove.getY() + 1 && toMove.getY() != this->_place.getY();)
	{
		i += 1; // TODO: Check if there is need for: (toMove.getX() - this->_place.getX()) / abs(toMove.getX() - this->_place.getX())

		if (board[i][toMove.getX()] != nullptr)
			return BAD_MOV;
	}

	return OK_MOV;
}

const char Rook::getType()
{
	if (this->_color)
		return 'r';
	return 'R';
}

int Rook::checkIfChess(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE])
{
	if (canMove(toMove, board) == 1)
		return 1;
	return 0;
}
