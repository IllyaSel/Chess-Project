#include "Pawn.h"

Pawn::Pawn(bool color, Point place) : Tool(color, place)
{
}

Pawn::~Pawn()
{
}

int Pawn::canMove(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE])
{
    if (board[toMove.getY()][toMove.getX()] == nullptr) {
        // Destination square is unoccupied
        if (this->_place.getX() == toMove.getX()) {
            if (this->_color) {
                if (toMove.getY() == this->_place.getY() - 1) {
                    this->_ifMove = true;
                    return OK_MOV;
                }
                else if (toMove.getY() == this->_place.getY() - 2 && !this->_ifMove) { this->_ifMove = true; return OK_MOV; } // move two squares forward as the first move
            }
            else {
                if (toMove.getY() == this->_place.getY() + 1) {
                    this->_ifMove = true;
                    return OK_MOV;
                }
                else if (toMove.getY() == this->_place.getY() + 2 && !this->_ifMove) { this->_ifMove = true; return OK_MOV; } // move two squares forward as the first move
            }
        }
    }
    else {
        // Destination holds piece of opposite color
        if (((this->_place.getX() == toMove.getX() + 1) || (this->_place.getX() == toMove.getX() - 1))) {
            if (this->_color) {
                if (toMove.getY() == this->_place.getY() - 1) {
                    this->_ifMove = true;
                    return OK_MOV;
                }
            }
            else {
                if (toMove.getY() == this->_place.getY() + 1) {
                    this->_ifMove = true;
                    return OK_MOV;
                }
            }
        }
    }

    return BAD_MOV;
}

const char Pawn::getType()
{
    if (this->_color) // is white
        return 'p';
    return 'P';
}

int Pawn::checkIfChess(Point toMove, Tool* board[BOARD_SIZE][BOARD_SIZE])
{
    Pawn VirtualPawn(this->_color, toMove);
    if (canMove(toMove, board) == OK_MOV &&
        VirtualPawn.canMove(this->_kingsLoc[!bool(this->_color)], board)) // checks if the move will risk hostile king
    {
        return OK_MOV_CHESS;
    }

    return BAD_MOV_CHESS;
}
