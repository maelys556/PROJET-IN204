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
}



bool Grid::isGameOver(){
    for (int i=0; i<width; i++) {
        if (g_matrix[3][i]!= 0) {
            return true;
        }
    }
    return false;
}



bool Grid::IsCellOutside(int row, int column) {
    width = g_matrix[0].size()
    height = g_matrix.size()
    if (row < 0 || row >= width || column < 0 || column >= height) {
        return true;
    }
    return false;
}



std::vector<int> Grid::completedRows() {
        """
        Renvoie un vecteur avec les indices des lignes complétées et -1 si aucune ligne n'est complétée.
        """
        std::vector<int> res;
        int compteur = 0;
        for (int i=0; i<height; i++) {
            compteur = 0;
            for (int j=0; j<width; j++) {
                if (g_matrix[i][j] != 0) {
                    compteur += 1;
                }
            }
            if (compteur == width) {
                res.push_back(i);
            }
        }
        if (res.size() == 0) {
            res.push_back(-1);
        }
        return res;
    }



void Grid::deleteRow(int row) {
    for (int i=row; i>0; i--) {
        for (int j=0; j<g_matrix[0].size(); j++) {
            g_matrix[i][j] = g_matrix[i-1][j];
        }
    }
    for (int j=0; j<width; j++) {
        grid[0][j] = 0;
    }
}