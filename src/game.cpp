#include <iostream>
#include <vector>
#include <random>
#include "../include/grid.hpp"
#include "../include/tetromino.hpp"
#include "../include/game.hpp"

Game::Game(int size_X, int size_Y) :grid(size_X, size_Y)
{
    //current_id = aCurrent_id;
    currentBlock = Tetromino(0, 0); 
}

void Game::getNewBlock() {

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0,6);
    int next_id = dist(gen);         // apparemment pas besoin de time() ou truc du genre

    if (next_id == 0) {
        currentBlock = IBlock(0, 0);
    }
    else if (next_id == 1) {
        currentBlock = LBlock(1, 0);
    }
    else if (next_id == 2) {
        currentBlock = JBlock(2, 0);
    }
    else if (next_id == 3) {
        currentBlock = OBlock(3, 0);
    }
    else if (next_id == 4) {
        currentBlock = SBlock(4, 0);
    }
    else if (next_id == 5) {
        currentBlock = TBlock(5, 0);
    }
    else {
        currentBlock = ZBlock(6, 0);
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
        undoRotation(); 
    }
}

void Game::move(int nb_rows, int nb_columns) {
    
    //Cette fonction ne gère pas correctement les collisions et bloquage de tetrominos, il vaut mieux utiliser moveLeft,
    //moveDown et moveRight.
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

void Game::moveRight() {/*
    currentBlock.ColumnOffset += 1;
    if (IsBlockOutside() == true) {
        currentBlock.ColumnOffset -= 1;
    }
    if (isCollision() == true) {
        currentBlock.ColumnOffset -= 1;
        //lockBlock(); // si le tetromino touche un tetromino bloqué à sa droite il peut tjrs move down
    }*/
    currentBlock.RowOffset += 1;  
    if (IsBlockOutside() == true) {
        currentBlock.RowOffset -= 1;
    }
    if (isCollision() == true) {
        currentBlock.RowOffset -= 1;
    }
}

void Game::moveLeft() {
    /*currentBlock.ColumnOffset -= 1;
    if (IsBlockOutside() == true) {
        currentBlock.ColumnOffset += 1;
    }
    if (isCollision() == true) {
        currentBlock.ColumnOffset += 1;
        //lockBlock(); // si le tetromino touche un tetromino bloqué à sa gauche il peut tjrs move down
    }*/
    currentBlock.RowOffset += -1;  
    if (IsBlockOutside() == true) {
        currentBlock.RowOffset -= +1;
    }
    if (isCollision() == true) {
        currentBlock.RowOffset -= +1;
    }
}

void Game::moveDown() {
    /*
    currentBlock.RowOffset += 1;  
    if (IsBlockOutside() == true) {
        currentBlock.RowOffset -= 1;
        lockBlock(); // si le tetromino sort de la grille en bas, il se bloque
    }
    if (isCollision() == true) {
        currentBlock.RowOffset -= 1;
        lockBlock(); // si le tetromino touche un tetromino bloqué en-dessous de lui alors il se bloque
    }
    */
    currentBlock.ColumnOffset += 1;
    if (IsBlockOutside() == true) {
        currentBlock.ColumnOffset -= 1;
        lockBlock();
    }
    if (isCollision() == true) {
        currentBlock.ColumnOffset -= 1;
        lockBlock();
    }

} 

void Game::lockBlock() {
    std::vector<Position> cells = currentBlock.getCells();
    for (int i=0; i<cells.size(); i++) {
        grid.setCellTo(cells[i].x,cells[i].y,currentBlock.id);
    }
}

bool Game::isCollision() { // Ajouter la gestion des collisions dans les méthodes rotate et move !!!!!
    std::vector<Position> cells = currentBlock.getCells();
    for (int i=0; i<cells.size(); i++) {
        const Position& cell = cells[i];
        if (not grid.isCellEmpty(cell.x, cell.y)){
            return true;
        }
    }
    return false;
}