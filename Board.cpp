#include "Board.h"

Board::Board() { CreateBoard(START_BOARD); }

void Board::CreateBoard(const char board_arr[])
{
	for (int i = 0; i < BOARD_SIZE * BOARD_SIZE; i++)
	{
		switch (board_arr[i])
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
	if (this->_board[this->_myPlace.getY()][this->_myPlace.getX()] == nullptr) { return BAD_MOV_EMPTY_SRC; }
	else if (this->_board[this->_myPlace.getY()][this->_myPlace.getX()] != nullptr &&
		this->_board[this->_myPlace.getY()][this->_myPlace.getX()]->getColor() == this->_board[point.getY()][point.getX()]->getColor()) {
		return BAD_MOV_FULL_DST;
	}

	int chess = this->_board[this->_myPlace.getY()][this->_myPlace.getX()]->checkIfChess(point, this->_board);
	int canmove = this->_board[this->_myPlace.getY()][this->_myPlace.getX()]->canMove(point, this->_board);

	if (chess == OK_MOV_CHESS) { return OK_MOV_CHESS; }
	else if (canmove == BAD_MOV) { return BAD_MOV; }

	return OK_MOV;
}

void Board::SetMove(Point toMove)
{
	if (this->_board[toMove.getY()][toMove.getX()] != nullptr) delete this->_board[toMove.getY()][toMove.getX()];

	this->_board[toMove.getY()][toMove.getX()] = this->_board[this->_myPlace.getY()][this->_myPlace.getX()];

	Point kingLoc = this->_board[toMove.getY()][toMove.getX()]->getKingLoc()[this->_board[toMove.getY()][toMove.getX()]->getColor()]; // Hostile King location
	if (kingLoc == Point(toMove)) { this->_board[toMove.getY()][toMove.getX()]->setKingLoc(); }

	this->_board[this->_myPlace.getY()][this->_myPlace.getX()] = nullptr;
	this->_board[toMove.getY()][toMove.getX()]->setPlace(toMove);
	this->_colorTurn = !this->_colorTurn;
}

void Board::SetMyPlace(Point myPlace) { this->_myPlace = myPlace; }

const std::string Board::toString()
{
	std::string board = "";

	if (!this->_board) { return board; }
	else {
		for (int i = 0; i < BOARD_SIZE; i++)
		{
			for (int j = 0; j < BOARD_SIZE; j++)
			{
				if (this->_board[i][j] != nullptr) board += this->_board[i][j]->getType();
				else board += '#';
			}
		}
	}
	return board;
}
