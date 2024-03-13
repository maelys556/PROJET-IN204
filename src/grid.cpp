#include <SDL_image.h>
#include <SDL.h>
#include <vector>
#include <iostream>
#include "../include/grid.hpp"

#include "../include/constants.hpp"

Grid::Grid(int h, int w) {
    g_matrix.resize(h);
    for (int i = 0; i < h; ++i) {
        g_matrix[i].resize(w, 0);
    }
}



void Grid::affiche(){
    for (int i=0; i<g_matrix.size(); ++i){
        for (int j=0; j<g_matrix[0].size(); ++j){
            std::cout << g_matrix[i][j];
        }
        std::cout << std::endl;
    }
};





//Tetromino* spawn(int color, int shape){};
//void delete_line(int line, Score score, int point_multiplier){};
