#include <SDL_image.h>
#include <SDL_ttf.h>
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
    // Charger l'image du fond d'écran
    SDL_Surface* backgroundImage = IMG_Load("../images/title_screen.bmp");
    if (backgroundImage == NULL) {
        printf("Unable to load image! SDL_image Error: %s\n", IMG_GetError());
        return false;
    }

    // Convertir la surface en texture
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(i_renderer, backgroundImage);
    if (backgroundTexture == NULL) {
        printf("Unable to create texture from image! SDL Error: %s\n", SDL_GetError());
        return false;
    }

    // Libérer la surface
    SDL_FreeSurface(backgroundImage);

    // Effacer le rendu actuel avec la couleur de fond
    SDL_RenderClear(i_renderer);

    // Copier la texture de l'image du fond sur le renderer
    SDL_RenderCopy(i_renderer, backgroundTexture, NULL, NULL);

    // Mettre à jour l'écran
    SDL_RenderPresent(i_renderer);
    return true;
};
//../images/title_screen.bmp

void Interface::inter_update(Game& current_game, SDL_Texture* blocktextures[], TTF_Font* Font) {
    SDL_RenderClear(i_renderer);
    
    // Load the background image
    SDL_Surface* backgroundImage = IMG_Load("../images/title_screen.bmp");
    if (backgroundImage == nullptr) {
        // Handle error
        std::cerr << "Failed to load background image: " << IMG_GetError() << std::endl;
        return;
    }

    // Create texture from the background image
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(i_renderer, backgroundImage);
    SDL_FreeSurface(backgroundImage); // Free the surface now that we have the texture
    
    // Render the background texture
    SDL_RenderCopy(i_renderer, backgroundTexture, nullptr, nullptr);
    
    // Render other elements (blocks, score, etc.)
    render_blocks(current_game, blocktextures);

    // Render the score
    SDL_Color White = {63, 191, 255};
    std::string score_text = "Score: " + std::to_string(current_game.grid.get_score());
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Font, score_text.c_str(), White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(i_renderer, surfaceMessage);
    int textWidth, textHeight;
    TTF_SizeText(Font, score_text.c_str(), &textWidth, &textHeight);
    SDL_Rect Message_rect; 
    int w_width, w_height;
    SDL_GetWindowSize(i_window, &w_width, &w_height);
    Message_rect.x = w_width / 6; 
    Message_rect.y = w_height / 2; 
    Message_rect.w = textWidth;
    Message_rect.h = textHeight;
    SDL_RenderCopy(i_renderer, Message, nullptr, &Message_rect);

    // Clean up resources
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);

    // Explicitly destroy the background texture
    SDL_DestroyTexture(backgroundTexture);

    // Present the renderer
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

    int y_margin = (height/5) /2;
    int box_size = (height - 2* y_margin)/(GRID_SIZE_Y-4);
    int x_margin = (width - box_size* GRID_SIZE_X) /2;
    y_margin += height/30;


    for (int i=0; i<GRID_SIZE_X; i++){
        for (int j=4; j<GRID_SIZE_Y; j++){
            
            SDL_Rect tile_rect = (SDL_Rect){x_margin + i*box_size, y_margin + (j-4)*box_size, box_size, box_size };

            int val = current_game.grid.get(i,j);
            if(val==-1){
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
        if (y>=4){
            SDL_Rect tile_rect = (SDL_Rect){x_margin + x*box_size, y_margin + (y-4)*box_size, box_size, box_size };            
            SDL_RenderCopyEx(i_renderer, blocktextures[current_game.currentBlock.get_sprite_nbr(current_game.grid.get_level())], NULL, &tile_rect, 0, NULL, SDL_FLIP_NONE);
        }
    }
}

void Interface::game_over(int score, TTF_Font* Font){
    SDL_RenderClear(i_renderer);
    
    SDL_Surface* backgroundImage = IMG_Load("../images/game_over_screen.bmp");
    if (backgroundImage == nullptr) {
        // Handle error
        std::cerr << "Failed to load background image: " << IMG_GetError() << std::endl;
        return;
    }



    // Create texture from the background image
    SDL_Texture* backgroundTexture = SDL_CreateTextureFromSurface(i_renderer, backgroundImage);
    SDL_FreeSurface(backgroundImage); // Free the surface now that we have the texture
    
    // Render the background texture
    SDL_RenderCopy(i_renderer, backgroundTexture, nullptr, nullptr);    

    SDL_Color White = {255, 255, 255};
    std::string score_text = "Score: " + std::to_string(score);
    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Font, score_text.c_str(), White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(i_renderer, surfaceMessage);
    int textWidth, textHeight;
    TTF_SizeText(Font, score_text.c_str(), &textWidth, &textHeight);
    SDL_Rect Message_rect; 
    int w_width, w_height;
    SDL_GetWindowSize(i_window, &w_width, &w_height);
    Message_rect.x = (w_width / 2)  - textWidth/2;
    Message_rect.y =(w_height/2) - textHeight/2;
    Message_rect.w = textWidth;
    Message_rect.h = textHeight;
    SDL_RenderCopy(i_renderer, Message, nullptr, &Message_rect);
}
