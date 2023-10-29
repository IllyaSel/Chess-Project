#pragma once
#include "Point.h"

#define BOARD_SIZE 8

#define OK_MOV 0
#define OK_MOV_CHESS 1
#define BAD_MOV_EMPTY_SRC 2
#define BAD_MOV_FULL_DST 3
#define BAD_MOV_CHESS 4
#define BAD_MOV_BAD_INDEX 5
#define BAD_MOV 6
#define BAD_MOV_SAME 7
#define OK_MOVE_CHECKMATE 8


class Tool
{
protected:
	Point _place;
	bool _color;
	
	
	static Point _kingsLoc[2];

public:
	bool _ifMove;

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
	// TODO: virtual int checkIfChessMat(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE]) = 0;

};

