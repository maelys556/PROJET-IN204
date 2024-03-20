#include <SDL_image.h>
#include <SDL.h>

#include "../include/interface.hpp"
#include "../include/game.hpp"
#include "../include/constants.hpp"
#include "../include/tetromino.hpp"
#include "../include/position.hpp"


Interface::Interface(){
    i_window = NULL;
    i_renderer = NULL;
};

bool Interface::inter_init(){
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
        return false;
    }
    i_window = SDL_CreateWindow( "Tetris", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

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
    SDL_SetRenderDrawColor(i_renderer, 0, 0, 0, 255);
    return true;
};

void Interface::inter_update(Game& current_game, SDL_Texture* blocktextures[]){
    SDL_RenderClear(i_renderer);
    // Here we will had anything we have to render, the background, grid shape, score and most importantly the blocks
    render_blocks(current_game, blocktextures);
    
    SDL_RenderPresent(i_renderer);
}

Interface::~Interface(){
    SDL_DestroyRenderer(i_renderer);
    SDL_DestroyWindow(i_window);
    SDL_Quit();
}




void Interface::texture_load_blocks(SDL_Texture* blocktextures[]){

    // variable creation
    SDL_Surface* sheet = IMG_Load("../images/textures_blocks_1_bmp.bmp");
    SDL_Rect blockrect = (SDL_Rect){ 0, 0, 8, 8 };

    // loop to extract texture from the sheet and the corresponding rectangles
    for (int i = 0; i<NUM_LEVELS; ++i){
        for (int j = 0; j<NUM_BLOCK_SPRITES; ++j){
            for (int k = 0; k<NUM_POWERS; ++k){
                blockrect.x = blockrect.w*k;
                blockrect.y = blockrect.h*i*NUM_BLOCK_SPRITES + blockrect.h*j;
                SDL_Surface* spriteSurface = SDL_CreateRGBSurface(0, blockrect.w, blockrect.h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
                SDL_BlitSurface(sheet, &blockrect, spriteSurface, NULL);
                blocktextures[k + j*NUM_POWERS + i*NUM_BLOCK_SPRITES*NUM_POWERS] = SDL_CreateTextureFromSurface(i_renderer, spriteSurface);
                SDL_FreeSurface(spriteSurface);
            }
        }
    }

    blockrect = (SDL_Rect){0, 8*NUM_LEVELS*NUM_BLOCK_SPRITES, 8, 8};
    SDL_Surface* spriteSurface = SDL_CreateRGBSurface(0, blockrect.w, blockrect.h, 32, 0xFF000000, 0x00FF0000, 0x0000FF00, 0x000000FF);
    SDL_BlitSurface(sheet, &blockrect, spriteSurface, NULL);
    blocktextures[NUM_BLOCK_SPRITES*NUM_LEVELS*NUM_POWERS] = SDL_CreateTextureFromSurface(i_renderer, spriteSurface);
    SDL_FreeSurface(spriteSurface);

    // cleaning
    SDL_FreeSurface(sheet);
}

void Interface::render_blocks(Game& current_game, SDL_Texture* blocktextures[]){
    int width, height;
    SDL_GetWindowSize(i_window, &width, &height);

    int x_border = (width /2) /2;
    int y_border = (height /2) /5;
    int x_size = (width - 2*x_border)/GRID_SIZE_X;
    int y_size = (height - 2*y_border)/GRID_SIZE_Y;



    for (int i=0; i<GRID_SIZE_X; i++){
        for (int j=4; j<GRID_SIZE_Y; j++){
            
            SDL_Rect tile_rect = (SDL_Rect){x_border + i*x_size, y_border + j*y_size, x_size, y_size };

            int val = current_game.grid.get(i,j);
            if(val==0){
                val = NUM_BLOCK_SPRITES*NUM_LEVELS*NUM_POWERS;
            }

            SDL_RenderCopyEx(i_renderer, blocktextures[val], NULL, &tile_rect, 0, NULL, SDL_FLIP_NONE);
        }
    }

    std::vector<Position> cells = current_game.currentBlock.getCells();
    //std::cout << cells.size() << "|||";
    for (int i=0; i<cells.size(); i++){
        int x = cells[i].x;
        int y = cells[i].y;
        SDL_Rect tile_rect = (SDL_Rect){x_border + x*x_size, y_border + y*y_size, x_size, y_size };            
        SDL_RenderCopyEx(i_renderer, blocktextures[i], NULL, &tile_rect, 0, NULL, SDL_FLIP_NONE);
    }
}