#pragma once
#include "Tool.h"

#define ILEGALL_BISHOP abs(this->_place.getX() - toMove.getX()) != abs(this->_place.getY() - toMove.getY())

class Bishop :
    public Tool
{
public:
	// Constructor & Destructor
	Bishop(bool color, Point place);
	~Bishop();

	// Functions
	int canMove(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE]);
	const char getType();
	int checkIfChess(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE]);

};

