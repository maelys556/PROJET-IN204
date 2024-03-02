#include <SDL_image.h>
#include <SDL.h>

class Interface {
    private:
        SDL_Window* i_window;
        SDL_Renderer* i_renderer;
    public:
        Interface();
        bool inter_init();
        ~Interface();
};