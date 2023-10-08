#pragma once
#include "Point.h"

#define BOARD_SIZE 8

class Tool
{
protected:
	Point _place;
	bool _color;
	bool _ifMove;
	
	static Point _kingsLoc[2];

public:
	// Constructors
	Tool();
	Tool(const bool color, const Point& place);
	
	// Destructor
	virtual ~Tool();

	// Functions
	void setPlace(const Point place);
	void setKingLoc();

	const Point getPlace();
	const bool getColor();
	const Point* getKingLoc();

	virtual const char getType() = 0;
	virtual int canMove(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE]) = 0;
	virtual int checkIfChess(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE]) = 0;
	virtual int checkIfChessMat(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE]) = 0;

};

