#pragma once
#include <SDL_image.h>
#include <SDL.h>

// Constants

#define TILE_SIZE 32
#define SCREEN_WIDTH 672
#define SCREEN_HEIGHT 480

#define NUM_TILES_X (SCREEN_WIDTH / TILE_SIZE)
#define NUM_TILES_Y (SCREEN_HEIGHT / TILE_SIZE)

#define MAX_NUMBER_SCORE 10
#define SCORE_FILE_PATH "../score/score.txt"

// SPITES constants
#define NUM_BLOCK_SPRITES 3
#define NUM_LEVELS 10
#define NUM_POWERS 3

// GRID constants
#define GRID_SIZE_X 10
#define GRID_SIZE_Y 24



#define DELAY 10
