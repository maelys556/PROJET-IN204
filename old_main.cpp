// Using SDL and standard IO
#include <SDL2/SDL_image.h>
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdbool.h>
#include <time.h>
#include "bomb.h"
#include "player.h"
#include "constants.h"





int main( int argc, char* argv[] ){
    srand(time(NULL));
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    int map_type = 0;
    int character_anim = 0;
    int death_stage = 0;
    int *death_stage_p = &death_stage;
    int stage = 0;

// Initialise SDL, the window and the renderer

    if( SDL_Init( SDL_INIT_VIDEO ) < 0 ){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
    } else {
        window = SDL_CreateWindow( "Bomberman", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if( window == NULL ) 
        {
            printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
        } else {
            SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
            if( renderer == NULL )
            {
                printf( "Renderer could not be created! SDL_Error: %s\n", SDL_GetError() );
            } else {

    

        // Load sprite sheet image
    
    // block surface allocation
    SDL_Texture* blocktextures[NUM_SPRITES];
    SDL_Rect blockrect[NUM_SPRITES];
    for (int i = 0; i < NUM_SPRITES; i++) {
        blocktextures[i] = malloc(sizeof(SDL_Texture*));
        if (blocktextures[i] == NULL) {
            printf("Allocation error for blocktextures[%d]\n", i);
            return 1;
        }
    }

    // bomb surface allocation
    SDL_Texture* bomb_textures[NUM_SPRITES_BOMB];    
    SDL_Rect bomb_rect[NUM_SPRITES_BOMB];
    for (int i = 0; i < NUM_SPRITES_BOMB; i++) {
            bomb_textures[i] = malloc(sizeof(SDL_Texture*));
            if (bomb_textures[i] == NULL) {
                printf("Allocation error for bomb_textures[%d]\n", i);
            return 1;
        }
    }

    // character surface allocation
    SDL_Texture* character_textures[NUM_SPRITES_CHARACTER];    
    SDL_Rect character_rect[NUM_SPRITES_CHARACTER];
    for (int i = 0; i < NUM_SPRITES_CHARACTER; i++) {
            character_textures[i] = malloc(sizeof(SDL_Texture*));
            if (character_textures[i] == NULL) {
                printf("Allocation error for character_textures[%d]\n", i);
            return 1;
        }
    }
    
    // explosion surface allocation
    SDL_Texture* explosion_textures[10];    
    SDL_Rect explosion_rect[10];
    for (int i = 0; i < 10; i++) {
            explosion_textures[i] = malloc(sizeof(SDL_Texture*));
            if (explosion_textures[i] == NULL) {
                printf("Allocation error for explosion_textures[%d]\n", i);
            return 1;
        }
    }

    // powerup surface allocation
    SDL_Texture* powerup_textures[NUM_POWERUPS];    
    SDL_Rect powerup_rect[NUM_POWERUPS];
    for (int i = 0; i < NUM_POWERUPS; i++) {
            powerup_textures[i] = malloc(sizeof(SDL_Texture*));
            if (powerup_textures[i] == NULL) {
                printf("Allocation error for powerup_textures[%d]\n", i);
            return 1;
        }
    }

    map_load_sprites(map_type, blockrect, blocktextures, renderer);
    bomb_load_sprites(map_type, bomb_rect, bomb_textures, renderer);
    character_load_sprites(map_type, character_rect, character_textures, renderer);
    explosion_load_sprites(map_type, explosion_rect, explosion_textures, renderer);
    powerup_load_sprites(map_type, powerup_rect, powerup_textures, renderer);
    


    // loading the game's icon
    SDL_Surface* icon_surface = SDL_LoadBMP("images/icone.bmp");
    SDL_SetWindowIcon(window, icon_surface);
    SDL_FreeSurface(icon_surface);  

    // loading the background texture
    SDL_Surface* surface = SDL_LoadBMP("images/background.bmp");
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);   

    // rendering the background texture
    SDL_Rect dest_rect = { 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT };
    SDL_RenderCopy(renderer, texture, NULL, &dest_rect);

    
// init variables
    
    // Map creation
            
        int **tile_map; bomb_t ***bomb_map; int **powerup_map; int **explosion_map;

        // Memory allocation 
        tile_map = malloc(NUM_TILES_X * sizeof(int *));
        explosion_map = malloc(NUM_TILES_X * sizeof(int *));
        bomb_map = malloc(NUM_TILES_X * sizeof(bomb_t **));
        powerup_map = malloc(NUM_TILES_X * sizeof(int *));
        for (int i = 0; i < NUM_TILES_X; i++) {
            tile_map[i] = malloc(NUM_TILES_Y * sizeof(int));
            explosion_map[i] = malloc(NUM_TILES_Y * sizeof(int));
            bomb_map[i] = malloc(NUM_TILES_Y * sizeof(bomb_t*));
            powerup_map[i] = malloc(NUM_TILES_Y * sizeof(int ));
        }

        map_create(tile_map,map_type);
        bomb_map_init(bomb_map);
        powerup_map_init(powerup_map);
        explosion_map_init(explosion_map);

    // Player creation
    
    player_t *player = malloc(sizeof(player_t));
    
        player_init(player,1,TILE_SIZE*2/2,TILE_SIZE*2/2);


    int running = 1;
// Game loop
    while (running) {

        // Handle events
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type==SDL_QUIT){
                running=0;
            }
            if (event.type==SDL_KEYDOWN && player->health >0){
                if (event.key.keysym.sym==SDLK_LEFT){player->move_x = -1;}
                if (event.key.keysym.sym==SDLK_RIGHT){player->move_x = 1;}
                if (event.key.keysym.sym==SDLK_UP){player->move_y = -1;}
                if (event.key.keysym.sym==SDLK_DOWN){player->move_y = 1;}
                if (event.key.keysym.sym==SDLK_SPACE){
                    if (can_drop(player, tile_map, bomb_map)==0){
                        bomb_init(player,bomb_map,((player->x + TILE_SIZE/2)/TILE_SIZE),((player->y + TILE_SIZE/2)/TILE_SIZE)); 
                    }               
                }
            }
            if (event.type==SDL_KEYUP && player->health >0){
                if ((player->move_x == -1)&&(event.key.keysym.sym==SDLK_LEFT)){player->move_x = 0;}
                if ((player->move_x == 1)&&(event.key.keysym.sym==SDLK_RIGHT)){player->move_x = 0;}
                if ((player->move_y == -1)&&(event.key.keysym.sym==SDLK_UP)){player->move_y = 0;}
                if ((player->move_y == 1)&&(event.key.keysym.sym==SDLK_DOWN)){player->move_y = 0;}
            }
        }
        // Move player
        player_move(player, tile_map, bomb_map);

        // Update the bomb and explosions
        bomb_update(tile_map, bomb_map, powerup_map, explosion_map, player);
        powerup_update(powerup_map, explosion_map);
        player_status_update(powerup_map, explosion_map, player);

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 34, 139, 34, 255);
        SDL_RenderClear(renderer);

        // Draw the tiles
        
        render_tiles(tile_map,renderer,blocktextures);
        render_bombs(bomb_map,renderer,bomb_textures);
        render_explosions(explosion_map,renderer,explosion_textures);
        render_character(player, renderer, character_textures, character_anim, death_stage_p);
        render_powerup(powerup_map, renderer, powerup_textures);



        // Update the screen
        SDL_RenderPresent(renderer);

        // explosions update
        explosion_update(explosion_map, character_anim);
        
        character_anim = (character_anim + 1 )% (NUM_SPRITES_ANIM*NUM_SPRITES_ANIM*NUM_SPRITES_ANIM);
        SDL_Delay(DELAY);
        
    }
            // Clean up and exit

        for (int i = 0; i < NUM_TILES_X; i++) {
            free(tile_map[i]);
            free(bomb_map[i]);
            free(powerup_map[i]);
            free(explosion_map[i]);
        }
        free(tile_map);
        free(bomb_map);
        free(powerup_map);
        free(explosion_map);

        for (int i = 0; i < NUM_SPRITES; i++) {
            free(blocktextures[i]);
        }
        for (int i = 0; i < NUM_SPRITES_BOMB; i++) {
            free(bomb_textures[i]);
        }
        for (int i = 0; i < NUM_SPRITES_CHARACTER; i++) {
            free(character_textures[i]);
        }
        for (int i = 0; i < 10; i++) {
            free(explosion_textures[i]);
        }
        for (int i = 0; i < NUM_SPRITES_CHARACTER; i++) {
            free(powerup_textures[i]);
        }
        free(player);
    
            }
            SDL_DestroyRenderer(renderer);

        }
        SDL_DestroyWindow(window);
    }
    
    SDL_Quit();
    return 0;
}