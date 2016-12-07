#include <SDL2/SDL.h>
#include <stdio.h>
#include <iostream>
#include <vector>
#include <thread>         // std::this_thread::sleep_for
#include <chrono>         // std::chrono::seconds
#include "Piece.h"
#include "GameState.h"

SDL_Renderer* renderer;
// Create a Game State
GameState gameState;

using namespace std;

SDL_Rect makeNewRect(int x, int y, int w, int h){
    SDL_Rect a;
    a.x = x;
    a.y = y;
    a.w = w;
    a.h = h;
    return a;
};

void makePieces()
{
    // Generate the game board UI
    
    int hXw = 50;
  
    // Vector of SDL Rectangles
    vector<SDL_Rect> rekts;
    // Vector of Game Pieces
    vector<Piece> pieces = gameState.getPieces();
    
    // Loops and populates the vectors of Rectangles, and Pieces
    for(int i = 0; i < pieces.size(); i++) {
            SDL_SetRenderDrawColor(renderer,
                                   pieces.at(i).getR(),
                                   pieces.at(i).getG(),
                                   pieces.at(i).getB(),
                                   255);
            SDL_Rect a = makeNewRect(pieces.at(i).getX(), pieces.at(i).getY(), hXw, hXw);
            SDL_RenderFillRect(renderer, &a);
    }
}


int main (int argc, char** argv)
{
    //int SDL_Init(SDL_INIT_EVERYTHING);
    SDL_Window* window = NULL;
    window = SDL_CreateWindow
    (
     "CPP BEEJeWeLeD - Shapez", SDL_WINDOWPOS_UNDEFINED,
     SDL_WINDOWPOS_UNDEFINED,
     800,
     600,
     SDL_WINDOW_SHOWN
     );
    
    // Setup renderer
    renderer = NULL;
    renderer =  SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED);
    
    // Set render color to red ( background will be rendered in this color )
    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
    
    // Clear winow
    SDL_RenderClear( renderer );
    
    makePieces();
    
    // Render the rects to the screen
    SDL_RenderPresent(renderer);
    
    
    // Wait for 5 sec
    SDL_Delay( 1000 );
    
    bool running = true;
    SDL_Event event;
    
    // Mouse Cursor Positions x, y
    int x_mouse;
    int y_mouse;
    int x_old_mouse = 0;
    int y_old_mouse = 0;
    
    while(running)
    {
        while(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }
        
        
        if(event.type == SDL_MOUSEBUTTONUP)
        {
            /* If the left button was pressed. */
            if (event.button.button == SDL_BUTTON_LEFT){
                SDL_GetMouseState(&x_mouse, &y_mouse);
                
                if(x_mouse != x_old_mouse || y_mouse != y_old_mouse){
                    // Send Mouse Coords to Game State
                    gameState.catchXYfromClick(x_mouse, y_mouse);
                    x_old_mouse = x_mouse;
                    y_old_mouse = y_mouse;
                    // Set render color to red ( background will be rendered in this color )
                    SDL_SetRenderDrawColor( renderer, 0, 0, 0, 0 );
                    SDL_RenderClear(renderer);
                    //SDL_RenderCopy(renderer);
                    makePieces();
                    SDL_RenderPresent(renderer);
                }
                
            }
            
        }
    }
    
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    return EXIT_SUCCESS;
}

