#pragma once
#include "Board.h"

class Game
{
private:
	Board _board;
	bool _whiteTurn;
public:
	// Constructors & Destructor
	Game(bool whiteTurn, Board board);
	Game(Game& other);
	~Game();

	// Functions
	void setTurnWhite();
	void setTurnDark();
	const bool getTurn();
	const Board& getBoard();
	int move(Point src, Point dst);
	const std::string toString();
};

