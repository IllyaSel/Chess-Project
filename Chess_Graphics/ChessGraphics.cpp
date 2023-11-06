// arg_ - for func arguments, g - for global var, l - for local var

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#include "Pipe.h"
#include <thread>

#undef main

// GUI consts
#define WINDOW_SIZE 800
#define SQUARE_SIZE int(WINDOW_SIZE / 8)

#define GRAY Color{127, 127, 127}
#define LIGHT_GRAY Color{224, 224, 224}

// GUI logic consts
#define BOARD_SIZE 8
#define START_BOARD "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR"

// Communication with logic consts
#define OK_MOV "0"
#define OK_MOV_CHESS "1"
#define OK_MOV_CHECKMATE "8"

// Structures
typedef struct Color {
    int r, g, b;
} Color;

typedef struct PieceIndex {
    int row;
    int col;
} PieceIndex;

// Global variables
std::vector<SDL_Texture*> gPieceTextures;
bool gMoving = false;
PieceIndex gSrcSquare, gDstSquare;

// Graphics Server Pipe
Pipe gPipe;


void FillCharBoard(char arg_board[][BOARD_SIZE], std::string arg_board_str)
{
    for (int i = 0; i < BOARD_SIZE*BOARD_SIZE; i++){
            arg_board[7 - i / BOARD_SIZE][i % BOARD_SIZE] = arg_board_str[i];
    }
}


SDL_Texture* LoadTexture(const std::string arg_filepath, SDL_Renderer* arg_renderer)
{
    SDL_Surface* lSurface = IMG_Load(arg_filepath.c_str());
    if (lSurface == NULL) { 
        std::cout << "Error: function LoadTexture: surface: " 
        << IMG_GetError() << " " << arg_filepath << std::endl; 
    }

    SDL_Texture* lTexture = SDL_CreateTextureFromSurface(arg_renderer, lSurface);
    if (lTexture == NULL) { std::cout << "Error: function LoadTexture: texture: " << IMG_GetError() << std::endl; }

    SDL_FreeSurface(lSurface);
    gPieceTextures.push_back(lTexture); // saving texture pointer for future release of memory

    return lTexture;
}


// Releasing textures taken memory
void ReleaseTextures() { 
    for (SDL_Texture* lTexture : gPieceTextures)
        SDL_DestroyTexture(lTexture);

    gPieceTextures.clear();
}


void RenderChessboard(SDL_Renderer* arg_renderer) 
{
    SDL_SetRenderDrawColor(arg_renderer, 255, 255, 255, 255); // Set the background color to white
    SDL_RenderClear(arg_renderer);

    bool lIsWhiteSquare = true;
    SDL_Rect lSquareRect;

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (lIsWhiteSquare)
                SDL_SetRenderDrawColor(arg_renderer, LIGHT_GRAY.r, LIGHT_GRAY.g, LIGHT_GRAY.b, 255); // White square
            else
                SDL_SetRenderDrawColor(arg_renderer, GRAY.r, GRAY.g, GRAY.b, 255); // Black square
            
            lSquareRect = { x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE };
            SDL_RenderFillRect(arg_renderer, &lSquareRect);
            
            lIsWhiteSquare = !lIsWhiteSquare;
        }
        lIsWhiteSquare = !lIsWhiteSquare;
    }
}


void RenderPieces(SDL_Renderer* arg_renderer, char arg_board[][BOARD_SIZE])
{
    char lPieceName = ' ';
    std::string lIconPath = "";
    SDL_Rect lSquareRect;
    SDL_Texture* lPieceTexture;

    for (int y = 0; y < BOARD_SIZE; y++)
    {
        for (int x = 0; x < BOARD_SIZE; x++)
        {
            lSquareRect = { x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE };
            lPieceName = arg_board[y][x];

            if (lPieceName != '#') {
                if (lPieceName == '@')
                    lIconPath = "icons\\";
                else if (islower(lPieceName))
                    lIconPath = "icons\\w"; // White piece icons
                else
                    lIconPath = "icons\\d"; // Dark piece icons

                lIconPath.push_back(lPieceName);
                lIconPath += ".png";


                lPieceTexture = LoadTexture(lIconPath, arg_renderer); // Replace with actual file paths
                SDL_RenderCopy(arg_renderer, lPieceTexture, NULL, &lSquareRect);

                lIconPath.clear();
            }
        }
    }
}


bool HandleInput(char arg_board[][BOARD_SIZE])
{
    SDL_Event lEvent;
    std::string lMsg;

    while (SDL_PollEvent(&lEvent))
    {
        switch (lEvent.type)
        {
        case SDL_QUIT:
            gPipe.setMessage("quit");
            return true;
        case SDL_MOUSEBUTTONDOWN:
            if (lEvent.button.button == SDL_BUTTON_LEFT)
            {
                int mouseX = lEvent.button.x;
                int mouseY = lEvent.button.y;


                if (!gMoving) {
                    gSrcSquare = { int(mouseX / SQUARE_SIZE), int(mouseY / SQUARE_SIZE) };
                    std::cout << "Source: " << arg_board[gSrcSquare.col][gSrcSquare.row] << std::endl; // Debug needs
                    gMoving = true;

                    //TODO: send pre-move msg
                }
                else {
                    gDstSquare = { int(mouseX / SQUARE_SIZE), int(mouseY / SQUARE_SIZE) };
                    std::cout << "Destination: " << arg_board[gDstSquare.col][gDstSquare.row] << std::endl; // Debug needs

                    //TODO: send move msg
                    lMsg = std::string(1, char(7 - gSrcSquare.row + 'a')) +
                                      std::string(1, char(7 - gSrcSquare.col + '1')) +
                                      std::string(1, char(7 - gDstSquare.row + 'a')) +
                                      std::string(1, char(7 - gDstSquare.col + '1'));

                    gPipe.setMessage(lMsg);

                    do { // waiting for logics message
                        lMsg = gPipe.getMessage();
                    } while (lMsg == "");

                    if (lMsg == OK_MOV || lMsg == OK_MOV_CHESS || lMsg == OK_MOV_CHECKMATE)
                    {
                        arg_board[gDstSquare.col][gDstSquare.row] = arg_board[gSrcSquare.col][gSrcSquare.row];
                        arg_board[gSrcSquare.col][gSrcSquare.row] = '#';
                    }

                    gSrcSquare = {};
                    gDstSquare = {};
                    
                    gMoving = false;
                }
            }
            break;
        case SDL_MOUSEBUTTONUP:
            break;
        }
    }

    return false;
}


int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) { // Handle SDL2 initialization error
        return -1;
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) { // Handle SDL2_image initialization error
        return -1;
    }

    std::thread lPipeThread(&Pipe::serve, &gPipe);

    SDL_Window* lWindow = SDL_CreateWindow("Chess Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SIZE, WINDOW_SIZE, SDL_WINDOW_SHOWN);
    if (lWindow == NULL) // Handle window creation error
        return -1;

    SDL_Surface* lWindowIcon = IMG_Load("icons\\dQ.png");
    SDL_SetWindowIcon(lWindow, lWindowIcon);

    SDL_Renderer* lRenderer = SDL_CreateRenderer(lWindow, -1, SDL_RENDERER_ACCELERATED);
    if (lRenderer == NULL) // Handle renderer creation error
        return -1;

    // Main game loop 
    bool lQuit = false;
    char lBoard[BOARD_SIZE][BOARD_SIZE] = {};
    FillCharBoard(lBoard, START_BOARD);

    while (!lQuit) {
        // Handle user input
        lQuit = HandleInput(lBoard);
                
        // Render the chessboard and pieces
        RenderChessboard(lRenderer);
        RenderPieces(lRenderer, lBoard);

        // Update the screen
        SDL_RenderPresent(lRenderer);
        ReleaseTextures();
    }

    // Clean up and quit SDL
    SDL_FreeSurface(lWindowIcon);
    SDL_DestroyRenderer(lRenderer);
    SDL_DestroyWindow(lWindow);
    SDL_Quit();

    lPipeThread.join();

    return 0;
}
