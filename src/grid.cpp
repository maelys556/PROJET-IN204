#include <SDL_image.h>
#include <SDL.h>
#include <vector>
#include <iostream>
#include "../include/grid.hpp"

#include "../include/constants.hpp"

#include "../include/score.hpp"

Grid::Grid(int h, int w) {
    g_matrix.resize(h);
    for (int i = 0; i < h; ++i) {
        g_matrix[i].resize(w, -1);
    }
    g_score = 0;
}



void Grid::affiche(){
    for (int i=0; i<g_matrix.size(); ++i){
        for (int j=0; j<g_matrix[0].size(); ++j){
            std::cout << g_matrix[i][j];
        }
        std::cout << std::endl;
    }
}


//works somehow
bool Grid::isGameOver(){
    int width = g_matrix.size();
    for (int i=0; i<width; i++) {
        if (g_matrix[i][3]!= -1) {
            return true;
        }
    }
    return false;
}



bool Grid::IsCellOutside(int row, int column) {
    int width = g_matrix.size();
    int height = g_matrix[0].size();
    if (row < 0 || row >= width || column < 0 || column >= height) {
        return true;
    }
    return false;
}



std::vector<int> Grid::completedRows() {
        
    //Renvoie un vecteur avec les indices des lignes complétées et -1 si aucune ligne n'est complétée.
    int width = g_matrix.size();
    int height = g_matrix[0].size();
    std::vector<int> res;
    int compteur = 0;
    for (int i=0; i<height; i++) {
        compteur = 0;
        for (int j=0; j<width; j++) {
            if (g_matrix[j][i] != -1) {
                compteur += 1;
            }
        }
        if (compteur == width) {
            res.push_back(i);
        }
    }
    return res;
}

void Grid::updateScore(std::vector<int> rows, Score score) {
    int points(0);
    if (rows.size() == 1) {
        points = 100;
    } else if (rows.size() == 2) {
        points = 300;
    } else if (rows.size() == 3) {
        points = 1200;
    }
    
    int width = g_matrix.size();
    for (int k =0; k<rows.size(); ++k){
        for (int j=0; j<width; j++) {
            points += 40 * (((g_matrix[j][rows[k]])%3) + 1);
        }
    }
    score.add_current(points);
}



void Grid::deleteRow(int row) {
    int width = g_matrix.size();
    for (int i=row; i>0; i--) {
        for (int j=0; j<width; j++) {
            g_matrix[j][i] = g_matrix[j][i-1];
        }
    }
}



bool Grid::isCellEmpty(int x, int y){
    return g_matrix[x][y]==-1;
}



void Grid::setCellTo(int x, int y, int val){
    g_matrix[x][y]=val;
}


int Grid::get(int x, int y){
    return(g_matrix[x][y]);
};