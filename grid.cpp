#include <SDL2/SDL.h>
#include <iostream>
#include <vector>

class Grid 
{
    public:
    int width;
    int height;
    //std::vector<std::vector<int>> grid;
    int** grid;

    Grid() {}

    Grid(int aWidth, int aHeight) : width(aWidth), height(aHeight) {
        grid = new int*[height];
        for (int i=0; i<height; i++) {
            grid[i] = new int[width];
            /*for (int j=0; j<height; j++) {
                grid[i][j] = 0;
            }*/
        }
        for (int i=0; i<height; i++) {
            for (int j=0; j<width; j++) {
                grid[i][j] = 0;
            }
        }
    }

    void Print_Grid() {
        for (int i=0; i<height; i++) {
            for (int j=0; j<width; j++) {
                std::cout << grid[i][j] << " ";
            }
            std::cout << std::endl;
        }
    }

    bool IsCellOutside(int row, int column) {
        if (row < 0 || row >= width || column < 0 || column >= height) {
            return true;
        }
        return false;
    }
    
    std::vector<int> completedRows() {
        """
        Renvoie un vecteur avec les indices des lignes complétées et -1 si aucune ligne n'est complétée.
        """
        std::vector<int> res;
        int compteur = 0;
        for (int i=0; i<height; i++) {
            compteur = 0;
            for (int j=0; j<width; j++) {
                if (grid[i][j] != 0) {
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

    void deleteRow(int row) {
        for (int i=row; i>0; i--) {
            for (int j=0; j<width; j++) {
                grid[i][j] = grid[i-1][j];
            }
        }
        for (int j=0; j<width; j++) {
            grid[0][j] = 0;
        }
    }

    bool isGameOver() {
        for (int i=0; i<width; i++) {
            if (grid[0][i]!= 0) {
                return true;
            }
        }
        return false;
    }

    //~Grid();
};




