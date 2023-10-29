#include "Game.h"

Game::Game(bool whiteTurn, Board board)
{
	this->_board = Board();
	this->_whiteTurn = whiteTurn;
}

Game::Game(Game& other)
{
	this->_board = other.getBoard();
	this->_whiteTurn = other.getTurn();
}

Game::~Game()
{
	this->_board.~Board();
}

void Game::setTurnWhite() { this->_whiteTurn = true; }

void Game::setTurnDark() { this->_whiteTurn = false; }

const bool Game::getTurn() { return this->_whiteTurn; }

const Board& Game::getBoard() { return this->_board; }

int Game::move(Point src, Point dst)
{
	this->_board.SetMyPlace(src);
	
	switch (this->_board.canMove(dst))
	{
	case OK_MOV:
		this->_board.SetMove(dst);
		return OK_MOV;
	case OK_MOV_CHESS:
		this->_board.SetMove(dst);
		return OK_MOV_CHESS;
	default:
		return this->_board.canMove(dst);
	}
}

const std::string Game::toString()
{
	return this->_board.toString();
}
