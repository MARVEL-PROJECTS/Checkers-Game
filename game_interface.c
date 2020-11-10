#include "game_interface.h"

void printBoard(SDL_Surface *screen, gridType grid[][8]) {

    SDL_Surface *square[8] = {NULL}, *whiteElipse = NULL, *redElipse = NULL;
    SDL_Rect position; 
    int squareColor = 1;   /* This variable is used to specify the 
                                color of the square. See constants.h */
    

    for (int i = 0 ; i < 8; i++)
        square[i] = SDL_CreateRGBSurface(SDL_HWSURFACE,100, 100, 32, 0, 0, 0, 0);

    position.x = 0; 
    position.y = 0; 

    for (int i = 0; i < SQUARE_NUMBERS; i++) {
        for (int j = 0; j < SQUARE_NUMBERS; j++) {

            position.x = j * 100;

            if (squareColor == RED) {
                SDL_FillRect(square[i], NULL, SDL_MapRGB(square[i]->format,255, 0, 0)); // Red square
            }

            else {
                SDL_FillRect(square[i], NULL, SDL_MapRGB(square[i]->format,0, 0, 0)); // Black square
            }

            SDL_BlitSurface(square[i], NULL, screen, &position);
            squareColor = -squareColor;
        }
        squareColor = -squareColor;
        position.y = position.y + 100;


    }

    whiteElipse = IMG_Load("Sprites/white_elipse.png");
    redElipse = IMG_Load("Sprites/red_elipse.png");

    /* When there is 2 in the grid we fill the square with the white elipse 
        but when it's 1 then we fill it with red elipse */ 
    
    for(int i = 0; i < SQUARE_NUMBERS; i++){
        for(int j = 0; j < SQUARE_NUMBERS; j++){

            position.x = j * 100; 
            position.y = i * 100;

            if (grid[i][j].state == FULL && grid[i][j].color == WHITE) {

                SDL_BlitSurface(whiteElipse, NULL, screen, &position);

            }

            else if (grid[i][j].state == FULL && grid[i][j].color == RED){

                SDL_BlitSurface(redElipse, NULL, screen, &position);
            }
        }
    }

    

    SDL_Flip(screen);
}

void initBoard(gridType grid[][8]) {

    int blit = -1; 

    // Initialize the the grid first with zeros 
    for (int i = 0; i < SQUARE_NUMBERS; i++){
        for(int j = 0; j < SQUARE_NUMBERS; j++){
            grid[i][j].state = EMPTY;
            grid[i][j].color = UNDEFINED;
        }
    }
    
    // the first two rows of the grid will be full of -1s (white pieces)
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < SQUARE_NUMBERS; j++){

            if (blit == 1) {
                grid[i][j].color = WHITE;
                grid[i][j].state = FULL;
            }

            blit = -blit;
            
        }
        blit = -blit;
    }

    // the last two lines of the board will be full of 1s (red pieces)

    blit = 1;
    for (int i = 5; i < SQUARE_NUMBERS; i++){
        for (int j = 0; j < SQUARE_NUMBERS; j++){

            if (blit == 1){
                grid[i][j].color = RED;
                grid[i][j].state = FULL;
            }

            blit = -blit;

        }
        blit = -blit;
    }

}
