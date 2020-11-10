#ifndef GAME
#define GAME 

    #include <stdlib.h>
    #include <string.h>
    #include <stdio.h>
    #include <SDL/SDL.h>
    #include <SDL/SDL_image.h>

    #include "constants.h"
    #include "game_interface.h"

    void initGame(SDL_Surface *screen);
    Positions getClick(SDL_Surface *screen); // A function to get the position of the mouse

    /* A function to return true if the user clicked on a piece so we can get 
    its position with getClick. It returns false if he clicked on an empty square */ 
    int validFromPiece(int turn, gridType grid[][8], Positions fromPositions); 
   

   /* A function to return true if the destination coordinations are valid */
   int validDestPiece(int turn, gridType grid[][8], Positions from, Positions dest);

   /* a procedure to refresh the board after every move */ 
    void refreshBoard(int turn, gridType grid[][8], Positions from, Positions dest);

   /* a procedure to remove the taken piece from the board */ 
    int takePiece(int turn, gridType grid[][8], Positions from, Positions dest);

    /* The win function: returns WHITE if the winner is white player, else returns RED */ 
    int win(gridType grid[][8]);


#endif