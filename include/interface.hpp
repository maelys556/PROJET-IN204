#include <SDL_image.h>
#include <SDL.h>

#include "constants.hpp"

class Interface {
    private:
        SDL_Window* i_window;
        SDL_Renderer* i_renderer;
    public:
        Interface();
        bool inter_init();
        void inter_update(SDL_Texture* blocktextures[]);
        void texture_load_blocks(SDL_Texture* blocktextures[]);
        void render_blocks(SDL_Texture* blocktextures[]);
        ~Interface();
};