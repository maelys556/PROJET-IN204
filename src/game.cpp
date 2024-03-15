#include <iostream>
#include <vector>
#include <random>
#include "../include/grid.hpp"
#include "../include/tetromino.hpp"
#include "../include/game.hpp"

Game::Game(int aCurrent_id) : current_id(aCurrent_id)
{
    grid = Grid(10, 20);
    //current_id = aCurrent_id;
    //currentBlock = Tetromino(0, 0); 
}

Tetromino Game::getNewBlock(int next_id) {
    /*std::random_device rd;
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

bool Game::IsBlockOutside() {
    std::vector<Position> cells = currentBlock.getCells(); // rowOffset et columnOffset sont déjà pris en
        // compte dans getCells()
    for (int i=0; i<cells.size(); i++) {
        if (grid.IsCellOutside(cells[i].x, cells[i].y) == true) {
            return true;
        }
    }
    return false;
}

void Game::undoRotation() {
    currentBlock.orientation = (currentBlock.orientation-1) % 4;
}

void Game::rotate() {
    currentBlock.orientation = (currentBlock.orientation+1) % 4;
    if (IsBlockOutside() == true) {
        undoRotation();
    }
    if (isCollision() == true) {
        lockBlock(); // si le tetromino touche un tetromino bloqué alors il se bloque
    }
}

void Game::move(int nb_rows, int nb_columns) {
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

void Game::moveRight() {
    currentBlock.ColumnOffset += 1;
    if (IsBlockOutside() == true) {
        currentBlock.ColumnOffset -= 1;
    }
    if (isCollision() == true) {
        currentBlock.ColumnOffset -= 1;
        lockBlock(); // si le tetromino touche un tetromino bloqué alors il se bloque
    }
}

void Game::moveLeft() {
    currentBlock.ColumnOffset -= 1;
    if (IsBlockOutside() == true) {
        currentBlock.ColumnOffset += 1;
    }
    if (isCollision() == true) {
        currentBlock.ColumnOffset += 1;
        lockBlock(); // si le tetromino touche un tetromino bloqué alors il se bloque
    }
}

void Game::moveDown() {
    currentBlock.RowOffset += 1;  
    if (IsBlockOutside() == true) {
        currentBlock.RowOffset -= 1;
    }
    if (isCollision() == true) {
        currentBlock.RowOffset -= 1;
        lockBlock(); // si le tetromino touche un tetromino bloqué alors il se bloque
    }
} 

void Game::lockBlock() {
    std::vector<Position> cells = currentBlock.getCells();
    for (int i=0; i<cells.size(); i++) {
        grid.grid[cells[i].x][cells[i].y] = currentBlock.id;
    }
    currentBlock = getNewBlock(2); // //!\\ il faut mettre un entier aléatoire
}

bool Game::isCollision() { // Ajouter la gestion des collisions dans les méthodes rotate et move !!!!!
    std::vector<Position> cells = currentBlock.getCells();
    for (int i=0; i<cells.size(); i++) {
        if (grid.grid[cells[i].x][cells[i].y]!= 0) {
            return true;
        }
    }
    return false;
}