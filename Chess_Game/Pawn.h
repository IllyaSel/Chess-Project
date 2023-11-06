#pragma once
#include "Tool.h"

class Pawn :
    public Tool
{
public:
    // Constructor & Destructor
    Pawn(bool color, Point place);
    ~Pawn();

    // Functions
    int canMove(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE]);
    const char getType();
    int checkIfChess(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE]);

};

