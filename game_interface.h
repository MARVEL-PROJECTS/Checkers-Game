#ifndef GAME_INTERFACE 
#define GAME_INTERFACE 

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <SDL/SDL.h>
    #include <SDL/SDL_image.h>

    #include "constants.h"

    // A function to draw the game board
    void printBoard( SDL_Surface *screen, gridType grid[][8]);

    // A function to initialize the state of the board
    void initBoard(gridType grid[][8]);
    
#endif