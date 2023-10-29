// ChessGraphics.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>

#undef main

#define WINDOW_SIZE 800
#define SQUARE_SIZE int(WINDOW_SIZE / 8)

#define BOARD_SIZE 8
#define START_BOARD "rnbkqbnrpppppppp################################PPPPPPPPRNBKQBNR"

#define GRAY color{127, 127, 127}
#define LIGHT_GRAY color{224, 224, 224}

typedef struct color {
    int r, g, b;
} color;

typedef struct piece_index {
    int row;
    int col;
} piece_index;

std::vector<SDL_Texture*> piece_textures;
bool moving = false;
piece_index src_square, dst_square;


void fill_char_board(char board[][BOARD_SIZE], std::string board_str)
{
    for (int i = 0; i < BOARD_SIZE; i++)
    {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = board_str[i * BOARD_SIZE + j];
        }
    }
}


SDL_Texture* LoadTexture(const std::string filepath, SDL_Renderer* renderer)
{
    SDL_Surface* surface = IMG_Load(filepath.c_str());
    if (surface == NULL) { std::cout << "Error: function LoadTexture: surface: " << IMG_GetError() << " " << filepath << std::endl; }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (texture == NULL) { std::cout << "Error: function LoadTexture: texture: " << IMG_GetError() << std::endl; }

    SDL_FreeSurface(surface);
    piece_textures.push_back(texture); // saving texture pointer for future release of memory

    return texture;
}


// Releasing textures taken memory
void releaseTextures() { 
    for (SDL_Texture* texture : piece_textures)
        SDL_DestroyTexture(texture);

    piece_textures.clear();
}


void renderChessboard(SDL_Renderer* renderer, char board[][BOARD_SIZE]) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Set the background color to white
    SDL_RenderClear(renderer);

    bool isWhiteSquare = true;
    char piece_name = ' ';
    std::string icon_path = "";

    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (isWhiteSquare) {
                SDL_SetRenderDrawColor(renderer, LIGHT_GRAY.r, LIGHT_GRAY.g, LIGHT_GRAY.b, 255); // White square
            }
            else {
                SDL_SetRenderDrawColor(renderer, GRAY.r, GRAY.g, GRAY.b, 255); // Black square
            }
            
            SDL_Rect squareRect = { x * SQUARE_SIZE, y * SQUARE_SIZE, SQUARE_SIZE, SQUARE_SIZE };
            SDL_RenderFillRect(renderer, &squareRect);

            piece_name = board[y][x];

            if (piece_name != '#') {
                if (islower(piece_name))
                    icon_path = "icons\\w"; // White piece icons
                else
                    icon_path = "icons\\d"; // Dark piece icons

                icon_path.push_back(piece_name);
                icon_path += ".png";

                SDL_Texture* pieceTexture = LoadTexture(icon_path, renderer); // Replace with actual file paths
                SDL_RenderCopy(renderer, pieceTexture, NULL, &squareRect);
            }
            
            isWhiteSquare = !isWhiteSquare;
            icon_path.clear();
        }
        isWhiteSquare = !isWhiteSquare;
    }
}


bool handleInput(char board[][BOARD_SIZE])
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
        case SDL_QUIT:
            return true;
        case SDL_MOUSEBUTTONDOWN:
            if (event.button.button == SDL_BUTTON_LEFT)
            {
                int mouseX = event.button.x;
                int mouseY = event.button.y;


                if (!moving) {
                    src_square = { int(mouseX / SQUARE_SIZE), int(mouseY / SQUARE_SIZE) };
                    std::cout << "Source: " << board[src_square.col][src_square.row] << std::endl; // Debug needs
                    moving = true;
                }
                else {
                    dst_square = { int(mouseX / SQUARE_SIZE), int(mouseY / SQUARE_SIZE) };
                    std::cout << "Destination: " << board[dst_square.col][dst_square.row] << std::endl; // Debug needs
                    board[dst_square.col][dst_square.row] = board[src_square.col][src_square.row];
                    board[src_square.col][src_square.row] = '#';

                    src_square = {};
                    dst_square = {};
                    
                    moving = false;
                }
            }
            break;
        case SDL_MOUSEBUTTONUP:
            break;
        }
    }
}


int main()
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        // Handle SDL2 initialization error
        return -1;
    }

    if (IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG) {
        // Handle SDL2_image initialization error
        return -1;
    }

    SDL_Window* window = SDL_CreateWindow("Chess Game", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_SIZE, WINDOW_SIZE, SDL_WINDOW_SHOWN);
    if (window == NULL) // Handle window creation error
        return -1;

    SDL_Surface* window_icon = IMG_Load("icons\\dQ.png");
    SDL_SetWindowIcon(window, window_icon);

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) // Handle renderer creation error
        return -1;

    // Main game loop 
    bool quit = false;
    char board[BOARD_SIZE][BOARD_SIZE] = {};
    fill_char_board(board, START_BOARD);

    while (!quit) {
        // Handle user input
        quit = handleInput(board);
                
        // Render the chessboard and pieces
        renderChessboard(renderer, board);

        // Update the screen
        SDL_RenderPresent(renderer);
        releaseTextures();
    }

    // Clean up and quit SDL
    SDL_FreeSurface(window_icon);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
