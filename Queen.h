#pragma once
#include "Tool.h"

#include "Bishop.h"
#include "Rook.h"

#define ILEGALL_QUEEN (VirtualRook.canMove(toMove, board) && VirtualBishop.canMove(toMove, board))


class Queen :
    public Tool
{
public:
    // Constructor & Destructor
    Queen(bool color, Point place);
    ~Queen();

    // Functions
    int canMove(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE]);
    char getType() const;
    int checkIfChess(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE]);
};

