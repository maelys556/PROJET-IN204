#include <iostream>
#include <vector>
#include <random>
#include "grid.cpp"
#include "tetromino.cpp"


class Game 
{
    public: 
    Grid grid;
        // 0 = I, 1 = J, 2 = L, 3 = O, 4 = S, 5 = T, 6 = Z
    int current_id;
    Tetromino currentBlock; // le premier bloc est arbitrairement un bloc T
    

    Game(int aCurrent_id) : current_id(aCurrent_id) {
        grid = Grid(10, 20);
        //current_id = aCurrent_id;
        currentBlock = Tetromino(0, 0);
    } 

    Tetromino getNewBlock(int next_id) {
        /*std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_int_distribution<> dis(0,6);
        int next_id = dis(gen);*/
        if (next_id == 0) {
                return TBlock(0, 0);
            }
            if (next_id == 1) {
                return LBlock(1, 0);
            }
            if (next_id == 2) {
                return JBlock(2, 0);
            }
            if (next_id == 3) {
                return OBlock(3, 0);
            }
            if (next_id == 4) {
                return SBlock(4, 0);
            }
            if (next_id == 5) {
                return TBlock(5, 0);
            }
            if (next_id == 6) {
                return ZBlock(6, 0);
            }
        }
    

    bool IsBlockOutside() {
        std::vector<Position> cells = currentBlock.getCells();
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
    }

    void move(int nb_rows, int nb_columns) {
        currentBlock.RowOffset += nb_rows;
        currentBlock.ColumnOffset += nb_columns;
        if (IsBlockOutside() == true) {
            currentBlock.RowOffset -= nb_rows;
            currentBlock.ColumnOffset -= nb_columns;
        }
    }

    void moveRight() {
        currentBlock.ColumnOffset += 1;
        if (IsBlockOutside() == true) {
            currentBlock.ColumnOffset -= 1;
        }
        if (isCollision() == true) {
            lockBlock(); // si le tetromino touche un tetromino bloqué alors il se bloque
        }
    }

    void moveLeft() {
        currentBlock.ColumnOffset -= 1;
        if (IsBlockOutside() == true) {
            currentBlock.ColumnOffset += 1;
        }
        if (isCollision() == true) {
            lockBlock(); // si le tetromino touche un tetromino bloqué alors il se bloque
        }
    }

    void moveDown() {
        currentBlock.RowOffset += 1;  // //!\\ ATTENTION ! dans quel sens augmentent les y de la grille ?
        if (IsBlockOutside() == true) {
            currentBlock.RowOffset -= 1;
        }
        if (isCollision() == true) {
            lockBlock(); // si le tetromino touche un tetromino bloqué alors il se bloque
        }
    } 

    void lockBlock() {
        std::vector<Position> cells = currentBlock.getCells();
        for (int i=0; i<cells.size(); i++) {
            grid.grid[cells[i].x][cells[i].y] = currentBlock.id;
        }
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
