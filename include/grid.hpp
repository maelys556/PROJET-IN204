#include <SDL_image.h>
#include <SDL.h>
#include <vector>
#include "constants.hpp"

class Grid {
    private:
        std::vector<std::vector<int>> g_matrix;
    public:
        Grid(int h, int w);
        void affiche();
        //Tetromino* spawn(int color, int shape);
        //void delete_line(int line, Score score, int point_multiplier);
};

