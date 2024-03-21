#pragma once
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL.h>

#include "constants.hpp"
#include "game.hpp"
#include "tetromino.hpp"

class Interface {
    private:
        SDL_Window* i_window;
        SDL_Renderer* i_renderer;
    public:
        Interface();
        bool inter_init();
        void load_score(SDL_Texture* scoretextures, SDL_Rect& scoreRenderRect, Score score);
        void inter_update(Game& current_game, Score score, SDL_Texture* blocktextures[], SDL_Texture* scoretextures, SDL_Rect& scoreRenderRect);
        void texture_load_blocks(SDL_Texture* blocktextures[]);
        void render_blocks(Game& current_game, SDL_Texture* blocktextures[]);
        ~Interface();
};