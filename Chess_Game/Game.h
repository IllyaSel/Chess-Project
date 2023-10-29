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

	// Getters & Setters
	void setTurnWhite();
	void setTurnDark();
	const bool getTurn();
	const Board& getBoard();

	// Functions
	int move(Point src, Point dst);
	const std::string toString();
};

