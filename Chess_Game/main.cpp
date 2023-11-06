// arg_ - for func arguments, g - for global var, l - for local var

#include <iostream>
#include <string>

#include "Game.h"
#include "Pipe.h"


int main()
{
    Pipe lPipe;

    try
    {
        system("start ChessGraphics.exe");

        bool lConnected = lPipe.connect();

        while (!lConnected) {
            std::cout << "Reconecting.." << std::endl;
            Sleep(3000);
            lConnected = lPipe.connect();
        }

        Board lBoard = Board();
        Game lGame(true, lBoard);

        std::string lGraphicsMsg, lResponseMsg;
        int lCode;

        Point lSrc, lDst;

        lGraphicsMsg = lPipe.getMessageFromGraphics();

        while (lGraphicsMsg != "quit") {
            
            lSrc = Point(7 - (lGraphicsMsg[0] - 'a'), 7 - (lGraphicsMsg[1] - '1'));

            if (!isalpha(lGraphicsMsg[2]))  // check if msg is pre-move
            {
                lBoard = lGame.getBoard();
                lResponseMsg = lBoard.getPossibleMoves(lSrc);
            }
            else // msg is move
            { 
                lDst = Point(7 - (lGraphicsMsg[2] - 'a'), 7 - (lGraphicsMsg[3] - '1'));

                lCode = lGame.move(lSrc, lDst);
                lResponseMsg = std::to_string(lCode);
            }

            lPipe.sendMessageToGraphics(&lResponseMsg[0]);
            lGraphicsMsg = lPipe.getMessageFromGraphics(); // format: for pre-move: a1
                                                         //         for move:     a1a2

        }
    }
    catch (std::exception& e) { std::cout << "Error occured: " << e.what() << std::endl; }
    system("PAUSE");
    lPipe.close();

    return 0;

} 
