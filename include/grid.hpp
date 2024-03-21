#pragma once
#include <SDL_image.h>
#include <SDL.h>
#include <vector>
#include "constants.hpp"
#include "score.hpp"

class Grid {
    private:
        std::vector<std::vector<int>> g_matrix;
        int g_score;
        int g_level;
    public:
        Grid(int h, int w);
        void affiche();

        void deleteRow(int row);
        std::vector<int> completedRows();
        bool IsCellOutside(int row, int column);
        bool isGameOver();
        bool isCellEmpty(int x, int y);
        void setCellTo(int x, int y, int val);
        int get(int x, int y);
        int get_score();
        int get_level();
        void level_change();
        void updateScore(std::vector<int> rows);

        //Tetromino* spawn(int color, int shape);
        //void delete_line(int line, Score score, int point_multiplier);
};

