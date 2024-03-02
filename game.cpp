#include <iostream>
# include <vector>
#include 'grid.h'
#include 'tetromino.h'


class Game 
{
    public: 
    grid = Grid(20,10);
    blocks = {}   // //!\\ gérer la liste d'attente des blocs
    Tetromino currentBlock;
    Tetromino nextBlock;

    bool IsBlockOutside() {
        std::<vector<Position>> cells = currentBlock.getCells();
        for (int i=0; i<cells.size(); i++) {
            if (IsCellOutsideGrid(cells[i].x, cells[i].y) == True) {
                return True;
            }
        }
        return False;
    }

    void undoRotation() {
        currentBlock.orientation = (currentBlock.orientation-1) % 4;
    }

    void rotate() {
        currentBlock.orientation = (currentBlock.orientation+1) % 4;
        if (IsBlockOutside() == True) {
            undoRotation();
        }
    }

    void move(int nb_rows, int nb_columns) {
        currentBlock.RowOffset += nb_rows;
        currentBlock.ColumnOffset += nb_columns;
        if (IsBlockOutside() == True) {
            currentBlock.RowOffset -= nb_rows;
            currentBlock.ColumnOffset -= nb_columns;
        }
    }

    void moveRight() {
        currentBlock.ColumnOffset += 1;
        if (IsBlockOutside() == True) {
            currentBlock.ColumnOffset -= 1;
        }
        if (isCollision() == True) {
            lockBlock(); // si le tetromino touche un tetromino bloqué alors il se bloque
        }
    }

    void moveLeft() {
        currentBlock.ColumnOffset -= 1;
        if (IsBlockOutside() == True) {
            currentBlock.ColumnOffset += 1;
        }
        if (isCollision() == True) {
            lockBlock(); // si le tetromino touche un tetromino bloqué alors il se bloque
        }
    }

    void moveDown() {
        currentBlock.RowOffset += 1;  // //!\\ ATTENTION ! dans quel sens augmentent les y de la grille ?
        if (IsBlockOutside() == True) {
            currentBlock.RowOffset -= 1;
        }
        if (isCollision() == True) {
            lockBlock(); // si le tetromino touche un tetromino bloqué alors il se bloque
        }
    } 

    void lockBlock() {
        std::<vector<Position>> cells = currentBlock.getCells();
        for (int i=0; i<cells.size(); i++) {
            grid.grid[cells[i].x][cells[i].y] = currentBlock.id;
        }
    }

    void isCollision() { // Ajouter la gestion des collisions dans les méthodes rotate et move !!!!!
        std::vector<Position> cells = currentBlock.getCells();
        for (int i=0; i<cells.size(); i++) {
            if (grid.grid[cells[i].x][cells[i].y]!= 0) {
                return True;
            }
        }
        return False;
    }


};