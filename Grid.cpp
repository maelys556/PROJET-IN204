#include <SDL2/SDL.h>
#include <iostream>

class Grid 
{
    public:
    int width;
    int height;
    std::vector<std::vector<int>> grid(width, std::vector<height>(height));

    Grid() {}

    Grid(int aWidth, int aHeight) : width(aWidth), height(aHeight) {
        for (int i=0; i<width; i++) {
            for (int j=0; j<height; j++) {
                grid[i][j] = 0;
            }
        }
    }

    void Print_Grid() {
        for (int i=0; i<width; i++) {
            for (int j=0; j<height; j++) {
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

    ~Grid()
}




