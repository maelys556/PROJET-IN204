#pragma once
#include <iostream>
#include <vector>
#include <random>
#include "grid.hpp"
#include "tetromino.hpp"

class Game {
    public:
    Grid grid;
    int current_id;     // 0 = I, 1 = J, 2 = L, 3 = O, 4 = S, 5 = T, 6 = Z
    Tetromino currentBlock = Tetromino(0,0); 

    Game(int size_X, int size_Y);

    void getNewBlock();
    bool IsBlockOutside();
    void undoRotation();
    void rotate();
    void move(int nb_rows, int nb_columns);
    void moveRight();
    void moveLeft();
    void moveDown();
    void lockBlock();
    bool isCollision();
};