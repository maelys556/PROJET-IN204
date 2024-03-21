#include <SDL_image.h>
#include <SDL.h>
#include <vector>
#include <iostream>
#include "../include/grid.hpp"

#include "../include/constants.hpp"

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
    int width = g_matrix[0].size();
    int height = g_matrix.size();
    std::vector<int> res;
    int compteur = 0;
    for (int i=0; i<height; i++) {
        compteur = 0;
        for (int j=0; j<width; j++) {
            if (g_matrix[i][j] != -1) {
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

void Grid::updateScore() {
    std::vector<int> completed_rows = completedRows();
    int multiplicity = 0;
    for (int i=0; i<completed_rows.size(); i++) {
        if (completed_rows[i] == completed_rows[i+1]) {
            multiplicity += 1;
        }
    }
    if (multiplicity == 0) {
        g_score += 40*completed_rows.size();
    }
    if (multiplicity == 1) { // si 2 lignes sont supprimées d'un coup le score augmente de 100 pour ces 2 lignes + 40
                                // pour les autres lignes si il y en a
        g_score += 100 + 40*(completed_rows.size()-2);
    }
    if (multiplicity == 2) { // si 2 lignes successives sont supprimées d'un coup le score augmente de 100
        g_score += 300 + 40*(completed_rows.size()-3);
    }
    if (multiplicity == 3) { // le max est de 4 lignes successives
        g_score += 1200 + 40*(completed_rows.size()-4);
    }
}



void Grid::deleteRow(int row) {
    int width = g_matrix.size();
    for (int i=row; i>0; i--) {
        for (int j=0; j<width; j++) {
            g_matrix[i][j] = g_matrix[i-1][j];
        }
    }
    for (int j=0; j<g_matrix.size(); j++) {
        g_matrix[0][j] = -1;
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