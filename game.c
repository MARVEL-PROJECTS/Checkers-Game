#include "game.h" 

// The whole game is inside this procedure 
void initGame(SDL_Surface *screen) {

    gridType grid[8][8]; 
    Positions destPositions;
    Positions fromPositions;
    Positions click; 
    int gameover = 0;
    int turn = RED;
    int valid;

    initBoard(grid); 

    while (!gameover) {

        printBoard(screen, grid);
        int movechoosed = 0;

        while (!movechoosed) {

            click = getClick(screen);

            if ((click.x > 7) || ( click.x < 0) || ( click.y > 7) || (click.y < 0)) 
                exit(0);

            else if (validFromPiece(turn, grid, click)) { 
                fromPositions = click; 
                printBoard(screen, grid); 
            }

            else if (validDestPiece(turn, grid, fromPositions, click)) {
                destPositions = click; 
                movechoosed = 1; 
            }

            else if (takePiece(turn, grid, fromPositions, click) == WHITE_LEFT) {
                destPositions = click;
                grid[fromPositions.x+1][fromPositions.y-1].color = UNDEFINED; 
                grid[fromPositions.x+1][fromPositions.y-1].state = EMPTY;
                movechoosed = 1; 

            }

            else if (takePiece(turn, grid, fromPositions, click) == WHITE_RIGHT) {

                destPositions = click; 
                grid[fromPositions.x +1][fromPositions.y+1].color = UNDEFINED;
                grid[fromPositions.x +1][fromPositions.y+1].state = EMPTY;
                movechoosed = 1;

            }

            else if (takePiece(turn, grid, fromPositions, click) == RED_LEFT) {
                destPositions = click; 
                grid[fromPositions.x-1][fromPositions.y-1].color = UNDEFINED;
                grid[fromPositions.x-1][fromPositions.y-1].state = EMPTY; 
                movechoosed = 1;

            }

            else if (takePiece(turn, grid, fromPositions, click) == RED_RIGHT) {

                destPositions = click; 
                grid[fromPositions.x-1][fromPositions.y+1].color = UNDEFINED; 
                grid[fromPositions.x-1][fromPositions.y+1].state = EMPTY; 
                movechoosed = 1;


            }

        }

        refreshBoard(turn, grid, fromPositions, destPositions);
        turn = -turn;

        if (win(grid) == WHITE) {

            printf("The winner is the WHITE player!"); 
            gameover = 1; 
        }

        else if (win(grid) == RED) {
            
            printf("The winner is the RED player!"); 
            gameover = 1;
        }

    }

    exit(0);


}


void refreshBoard(int turn, gridType grid[][8], Positions from, Positions dest) {

    grid[from.x][from.y].state = EMPTY;
    grid[from.x][from.y].color = UNDEFINED;

    grid[dest.x][dest.y].state = FULL; 
    grid[dest.x][dest.y].color = turn; 

}


Positions getClick(SDL_Surface *screen){

    Positions mousePosition; 
    SDL_Event event;
    int wait = 1;

    while (wait)
    {

        SDL_Flip(screen);
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                wait = 0;
                mousePosition.x = -1; // The user closes the window
                mousePosition.y = -1;
                return mousePosition;


            case SDL_MOUSEBUTTONDOWN:
                mousePosition.x = event.button.y;
                mousePosition.y = event.button.x;

                // I divided by 100 in order to have a number within the range of our 8 x 8 array 
                // So this function makes sure that it returns a number between 0 and 7 (included) 
                if ((mousePosition.x / 100 < 8) && (mousePosition.y / 100 < 8))
                 {
                     mousePosition.x = mousePosition.x / 100;  // The rows 
                     mousePosition.y = mousePosition.y / 100; // The columns
                     return mousePosition;

                 }

                break;
        }
    }
}

int validFromPiece(int turn, gridType grid[][8], Positions fromPositions) {


    if ((grid[fromPositions.x][fromPositions.y].state == FULL) && (grid[fromPositions.x][fromPositions.y].color == turn )){
        return 1; 
    }

    return 0;
 
}

int validDestPiece(int turn, gridType grid[][8], Positions from, Positions dest) {

    // a simple white move to the right 
    if ((turn == WHITE ) && (grid[dest.x][dest.y].state == EMPTY) && (dest.x == from.x + 1) && (dest.y == from.y + 1))
        return 1;
    

    // a simple white move to the left 
    else if ((turn == WHITE) && (grid[dest.x][dest.y].state == EMPTY) && (dest.x == from.x + 1) && (dest.y == from.y-1))
        return 1;

    
    // a simple red move to the right 
    else if ((turn == RED) && (grid[dest.x][dest.y].state == EMPTY) && (dest.x == from.x - 1) && (dest.y == from.y + 1))
        return 1; 

    // a simple red move to the left 
    else if ((turn == RED) && (grid[dest.x][dest.y].state == EMPTY) && (dest.x == from.x - 1)&& (dest.y == from.y - 1))
        return 1; 

    


    return 0; 
}

int takePiece(int turn, gridType grid[][8], Positions from, Positions dest) {

    // White piece taking red piece to the left 
    if ((turn == WHITE)&& (grid[dest.x][dest.y].state == EMPTY) && (grid[from.x+1][from.y-1].color == RED)
        && (dest.x == from.x + 2) && (dest.y == from.y -2))

            return WHITE_LEFT;


    // White piece taking red piece to the right 
    else if ((turn == WHITE) && (grid[dest.x][dest.y].state == EMPTY) && (grid[from.x+1][from.y +1].color == RED)
        && (dest.x == from.x + 2) && (dest.y == from.y + 2))

            return WHITE_RIGHT;


    // red piece taking white piece to the left 
    else if ((turn == RED) &&(grid[dest.x][dest.y].state == EMPTY) && (grid[from.x-1][from.y-1].color == WHITE)
        && (dest.x == from.x -2) && (dest.y == from.y - 2))

            return RED_LEFT;     

        

    // red piece taking white piece to the right 
    else if ((turn == RED) && (grid[dest.x][dest.y].state == EMPTY) && (grid[from.x -1][from.y+1].color == WHITE)
        && (dest.x == from.x - 2) && (dest.y == from.y + 2)) 

            return RED_RIGHT;


    
}

int win(gridType grid[][8]) {

    int redPieces, whitePieces = 0; 

    /* if the number of red pieces is 0 then the winner is white. The same thing if
        the number of white pieces is 0 */ 

    for(int i = 0; i < SQUARE_NUMBERS; i++) {
        for(int j = 0; j < SQUARE_NUMBERS; j++) {

            if (grid[i][j].color == RED)
                redPieces++;

            else if (grid[i][j].color == WHITE) 
                whitePieces++;  

        }
    }


    if (redPieces == 0)
        return WHITE; 
    else if (whitePieces == 0)
        return RED; 

    return 0;
}