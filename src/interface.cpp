#include <SDL_image.h>
#include <SDL.h>

#include "../include/interface.hpp"


Interface::Interface(){
    i_window = NULL;
    i_renderer = NULL;
};

bool Interface::inter_init(){
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    //i_window = SDL_CreateWindow( "Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    i_window = SDL_CreateWindow( "Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_SHOWN);
    if( i_window == NULL ){
        printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    i_renderer = SDL_CreateRenderer(i_window, -1, 0);
    if( i_renderer == NULL )
    {
        printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    return true;
};

Interface::~Interface(){
    SDL_DestroyRenderer(i_renderer);
    SDL_DestroyWindow(i_window);
    SDL_Quit();
}

