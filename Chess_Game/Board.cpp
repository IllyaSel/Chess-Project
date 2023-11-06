#include "Board.h"

Board::Board() { CreateBoard(START_BOARD); }

void Board::CreateBoard(const char arg_board_arr[])
{
	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
	{
		switch (arg_board_arr[i])
		{
		case 'r':
			this->_board[7 - i / BOARD_SIZE][i % BOARD_SIZE] = new Rook(WHITE, Point(i % BOARD_SIZE, 7 - i / BOARD_SIZE));
			break;
		case 'R':
			this->_board[7 - i / BOARD_SIZE][i % BOARD_SIZE] = new Rook(BLACK, Point(i % BOARD_SIZE, 7 - i / BOARD_SIZE));
			break;
		case 'k':
			this->_board[7 - i / BOARD_SIZE][i % BOARD_SIZE] = new King(WHITE, Point(i % BOARD_SIZE, 7 - i / BOARD_SIZE));
			break;
		case 'K':
			this->_board[7 - i / BOARD_SIZE][i % BOARD_SIZE] = new King(BLACK, Point(i % BOARD_SIZE, 7 - i / BOARD_SIZE));
			break;
		case 'b':
			this->_board[7 - i / BOARD_SIZE][i % BOARD_SIZE] = new Bishop(WHITE, Point(i % BOARD_SIZE, 7 - i / BOARD_SIZE));
			break;
		case 'B':
			this->_board[7 - i / BOARD_SIZE][i % BOARD_SIZE] = new Bishop(BLACK, Point(i % BOARD_SIZE, 7 - i / BOARD_SIZE));
			break;
		case 'n':
			this->_board[7 - i / BOARD_SIZE][i % BOARD_SIZE] = new Knight(WHITE, Point(i % BOARD_SIZE, 7 - i / BOARD_SIZE));
			break;
		case 'N':
			this->_board[7 - i / BOARD_SIZE][i % BOARD_SIZE] = new Knight(BLACK, Point(i % BOARD_SIZE, 7 - i / BOARD_SIZE));
			break;
		case 'q':
			this->_board[7 - i / BOARD_SIZE][i % BOARD_SIZE] = new Queen(WHITE, Point(i % BOARD_SIZE, 7 - i / BOARD_SIZE));
			break;
		case 'Q':
			this->_board[7 - i / BOARD_SIZE][i % BOARD_SIZE] = new Queen(BLACK, Point(i % BOARD_SIZE, 7 - i / BOARD_SIZE));
			break;
		case 'p':
			this->_board[7 - i / BOARD_SIZE][i % BOARD_SIZE] = new Pawn(WHITE, Point(i % BOARD_SIZE, 7 - i / BOARD_SIZE));
			break;
		case 'P':
			this->_board[7 - i / BOARD_SIZE][i % BOARD_SIZE] = new Pawn(BLACK, Point(i % BOARD_SIZE, 7 - i / BOARD_SIZE));
			break;
		default:
			this->_board[7 - i / BOARD_SIZE][i % BOARD_SIZE] = nullptr;
			break;
		}

	}

	this->_myPlace = Point(0, 0);
	this->_colorTurn = WHITE;
}

Board::~Board()
{
}

int Board::canMove(Point point)
{
	if (this->_board[this->_myPlace.getY()][this->_myPlace.getX()] == nullptr) {
		return BAD_MOV_EMPTY_SRC; 
	}
	else if (this->_board[this->_myPlace.getY()][this->_myPlace.getX()] != nullptr &&
			 this->_board[point.getY()][point.getX()] != nullptr) 
	{
		if (this->_board[this->_myPlace.getY()][this->_myPlace.getX()]->getColor() ==
			this->_board[point.getY()][point.getX()]->getColor()) 
		{
			return BAD_MOV_FULL_DST;
		}
	}

	int lCanMove = this->_board[this->_myPlace.getY()][this->_myPlace.getX()]->canMove(point, this->_board);
	int lChess = this->_board[this->_myPlace.getY()][this->_myPlace.getX()]->checkIfChess(point, this->_board);

	if (lChess == OK_MOV_CHESS) 
	{
		return OK_MOV_CHESS; 
	}
	else if (lCanMove == BAD_MOV ||
		this->_board[this->_myPlace.getY()][this->_myPlace.getX()]->getColor() != this->_colorTurn) // checks if the turn is of current piece's color
	{
		return BAD_MOV; 
	}

	return OK_MOV;
}

void Board::SetMove(Point toMove)
{
	if (this->_board[toMove.getY()][toMove.getX()] != nullptr) { 
		delete this->_board[toMove.getY()][toMove.getX()]; 
	}

	this->_board[toMove.getY()][toMove.getX()] = this->_board[this->_myPlace.getY()][this->_myPlace.getX()];

	Point kingLoc = this->_board[toMove.getY()][toMove.getX()]->getKingLoc()[this->_board[toMove.getY()][toMove.getX()]->getColor()]; // King location
	if (kingLoc == Point(toMove)) {
		this->_board[toMove.getY()][toMove.getX()]->setKingLoc(); 
	}

	this->_board[this->_myPlace.getY()][this->_myPlace.getX()] = nullptr;
	this->_board[toMove.getY()][toMove.getX()]->setPlace(toMove);
	this->_colorTurn = !this->_colorTurn;
}

void Board::SetMyPlace(Point myPlace) { this->_myPlace = myPlace; }

// Functions that returns all the possible piece's moves
const std::string Board::getPossibleMoves(Point arg_myPlace)
{
	std::string lMoves = "";
	bool lIfMove;
	int lCode;

	for (int i = 0; i < BOARD_SIZE; i++)
	{
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			lIfMove = this->_board[arg_myPlace.getY()][arg_myPlace.getX()]->_ifMove; // save the initial ifMove condition
			lCode = this->_board[arg_myPlace.getY()][arg_myPlace.getX()]->canMove(Point(i, j), this->_board);
			this->_board[arg_myPlace.getY()][arg_myPlace.getX()]->_ifMove = lIfMove; // returns initial ifMove

			if (lCode == OK_MOV || lCode == OK_MOV_CHESS)
				lMoves.append(std::string{ char(7 - i + 'a'), char(7 - j + '1')});
		}
	}

	return lMoves;
}

const std::string Board::toString()
{
	std::string lBoard = "";

	if (!this->_board) { return lBoard; }
	else {
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (this->_board[i][j] != nullptr) lBoard += this->_board[i][j]->getType();
				else lBoard += '#';
			}
		}
	}

	return lBoard;
}
