#pragma once
#include <iostream>
#include <string.h>

#include "Point.h"
#include "Tool.h"

#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "Knight.h"
#include "Queen.h"
#include "King.h"

#define START_BOARD "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR1"
#define WHITE 1
#define BLACK 0


class Board
{
private:
	Tool* _board[BOARD_SIZE][BOARD_SIZE];
	Point _myPlace;
	bool _colorTurn;
public:
	// Constructor & Destructor
	Board();
	void CreateBoard(const char board_arr[]);
	~Board();

	//Getters & Setters
	void SetMove(Point toMove);
	void SetMyPlace(Point myPlace);

	const std::string getPossibleMoves(Point myPlace);

	//Functions
	int canMove(Point point);
	const std::string toString();
};

