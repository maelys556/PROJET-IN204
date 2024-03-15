#include <iostream>
#include <vector>
#include <random>
#include "../grid.hpp"
#include "../tetromino.hpp"


class Game 
{
    public: 
    Grid grid;
        // 0 = I, 1 = J, 2 = L, 3 = O, 4 = S, 5 = T, 6 = Z
    int current_id;
    Tetromino currentBlock = Tetromino(0,0); 
    

    Game(int aCurrent_id) : current_id(aCurrent_id)
    {
        grid = Grid(10, 20);
        //current_id = aCurrent_id;
        //currentBlock = Tetromino(0, 0); 
    }


    Tetromino getNewBlock(int next_id) {
        /*
        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0,6);
        int next_id = dis(gen);
        */
        if (next_id == 0) {
                return IBlock(0, 0);
            }
            else if (next_id == 1) {
                return LBlock(1, 0);
            }
            else if (next_id == 2) {
                return JBlock(2, 0);
            }
            else if (next_id == 3) {
                return OBlock(3, 0);
            }
            else if (next_id == 4) {
                return SBlock(4, 0);
            }
            else if (next_id == 5) {
                return TBlock(5, 0);
            }
            else {
                return ZBlock(6, 0);
            }
    }
    

    bool IsBlockOutside() {
        std::vector<Position> cells = currentBlock.getCells(); // rowOffset et columnOffset sont déjà pris en
            // compte dans getCells()
        for (int i=0; i<cells.size(); i++) {
            if (grid.IsCellOutside(cells[i].x, cells[i].y) == true) {
                return true;
            }
        }
        return false;
    }

    void undoRotation() {
        currentBlock.orientation = (currentBlock.orientation-1) % 4;
    }

    void rotate() {
        currentBlock.orientation = (currentBlock.orientation+1) % 4;
        if (IsBlockOutside() == true) {
            undoRotation();
        }
        if (isCollision() == true) {
            lockBlock(); // si le tetromino touche un tetromino bloqué alors il se bloque
        }
    }

    void move(int nb_rows, int nb_columns) {
        currentBlock.RowOffset += nb_rows;
        currentBlock.ColumnOffset += nb_columns;
        if (IsBlockOutside() == true) {
            currentBlock.RowOffset -= nb_rows;
            currentBlock.ColumnOffset -= nb_columns;
        }
        if (isCollision() == true) {
            currentBlock.RowOffset -= nb_rows;
            currentBlock.ColumnOffset -= nb_columns;
            lockBlock(); // si le tetromino touche un tetromino bloqué alors il se bloque
        }
    }

    void moveRight() {
        currentBlock.ColumnOffset += 1;
        if (IsBlockOutside() == true) {
            currentBlock.ColumnOffset -= 1;
        }
        if (isCollision() == true) {
            currentBlock.ColumnOffset -= 1;
            lockBlock(); // si le tetromino touche un tetromino bloqué alors il se bloque
        }
    }

    void moveLeft() {
        currentBlock.ColumnOffset -= 1;
        if (IsBlockOutside() == true) {
            currentBlock.ColumnOffset += 1;
        }
        if (isCollision() == true) {
            currentBlock.ColumnOffset += 1;
            lockBlock(); // si le tetromino touche un tetromino bloqué alors il se bloque
        }
    }

    void moveDown() {
        currentBlock.RowOffset += 1;  
        if (IsBlockOutside() == true) {
            currentBlock.RowOffset -= 1;
        }
        if (isCollision() == true) {
            currentBlock.RowOffset -= 1;
            lockBlock(); // si le tetromino touche un tetromino bloqué alors il se bloque
        }
    } 

    void lockBlock() {
        std::vector<Position> cells = currentBlock.getCells();
        for (int i=0; i<cells.size(); i++) {
            grid.grid[cells[i].x][cells[i].y] = currentBlock.id;
        }
        currentBlock = getNewBlock(2); // //!\\ il faut mettre un entier aléatoire
    }

    bool isCollision() { // Ajouter la gestion des collisions dans les méthodes rotate et move !!!!!
        std::vector<Position> cells = currentBlock.getCells();
        for (int i=0; i<cells.size(); i++) {
            if (grid.grid[cells[i].x][cells[i].y]!= 0) {
                return true;
            }
        }
        return false;
    }

    

    //~Game();
};
