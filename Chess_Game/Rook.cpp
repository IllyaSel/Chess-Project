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

	if (board[toMove.getY()][toMove.getX()] != nullptr) { if (this->_color == board[toMove.getY()][toMove.getX()]->getColor()) return BAD_MOV_FULL_DST; }
	
	for (int i = this->_place.getX(); i != toMove.getX() - 1 && i != toMove.getX() + 1 && toMove.getX() != this->_place.getX();)
	{
		i += (toMove.getX() - this->_place.getX()) / abs(toMove.getX() - this->_place.getX()); // substracts if dst is on right side and vice versa

		if (board[toMove.getY()][i] != nullptr)// && board[toMove.getY()][i]->getColor() == this->_color)
			return BAD_MOV;
	}
	for (int i = this->_place.getY(); i != toMove.getY() - 1 && i != toMove.getY() + 1 && toMove.getY() != this->_place.getY();)
	{
		i += (toMove.getY() - this->_place.getY()) / abs(toMove.getY() - this->_place.getY()); // substracts if its white piece or adds if dark

		if (board[i][toMove.getX()] != nullptr)// && board[i][toMove.getX()]->getColor() == this->_color)
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
	Rook VirtualRook(this->_color, toMove);
	if (canMove(toMove, board) == OK_MOV &&
		VirtualRook.canMove(this->_kingsLoc[!bool(this->_color)], board)) // checks if the move will risk hostile king
	{
		return OK_MOV_CHESS;
	}

	return BAD_MOV_CHESS;
}
