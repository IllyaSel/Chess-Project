#include "Game.h"

Game::Game(bool arg_whiteTurn, Board arg_board)
{
	this->_board = Board();
	this->_whiteTurn = arg_whiteTurn;
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

int Game::move(Point arg_src, Point arg_dst)
{
	this->_board.SetMyPlace(arg_src);
	
	switch (this->_board.canMove(arg_dst))
	{
	case OK_MOV:
		this->_board.SetMove(arg_dst);
		return OK_MOV;
	case OK_MOV_CHESS:
		this->_board.SetMove(arg_dst);
		std::cout << "CHESS\n";
		return OK_MOV_CHESS;
	default:
		return this->_board.canMove(arg_dst);
	}
}

const std::string Game::toString()
{
	return this->_board.toString();
}
