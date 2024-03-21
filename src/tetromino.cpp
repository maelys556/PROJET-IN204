#include <iostream>
#include <vector>
#include "../include/position.hpp"
#include "../include/tetromino.hpp"
#include "../include/constants.hpp"



Tetromino::Tetromino(int anId, int anOrientation, int aPower) :
id(anId), orientation(anOrientation), RowOffset((GRID_SIZE_X-1)/2), ColumnOffset(0), t_power(aPower) {
    for (int i = 0 ; i < 4 ; i++) {
        cells[i].resize(4, Position(0,0));
    }
}

int Tetromino::get_sprite_nbr(int level){
    return ((id+1)%NUM_BLOCK_SPRITES)*NUM_POWERS + t_power + NUM_POWERS*NUM_BLOCK_SPRITES*level;
}

std::vector<Position> Tetromino::getCells() {
    std::vector<Position> c = cells[orientation];
    std::vector<Position> occupied_cells;
    for (int i=0; i<c.size(); i++) {
        Position new_pos = Position(c[i].x + RowOffset, c[i].y + ColumnOffset);
        occupied_cells.push_back(new_pos);
    }
    return occupied_cells;
}

void Tetromino::printTetromino() {
    std::vector<Position> c = cells[orientation];
    std::cout << "Tetromino - orientation :" << orientation << std::endl;
    for (int i=0; i<c.size(); i++) {
        std::cout << "(" << c[i].x << "," << c[i].y << ")" << std::endl;
    }
}


TBlock::TBlock(int anId, int anOrientation, int aPower) : Tetromino(anId, anOrientation, aPower) {
    cells[0] = {Position(1,1), Position(2,0), Position(2,1), Position(2,2)};
    cells[1] = {Position(0,0), Position(1,0), Position(1,1), Position(2,0)};
    cells[2] = {Position(0,0), Position(0,1), Position(0,2), Position(1,1)};
    cells[3] = {Position(0,2), Position(1,1), Position(1,2), Position(2,2)};
}

LBlock::LBlock(int anId, int anOrientation, int aPower) : Tetromino(anId, anOrientation, aPower) {
    cells[0] = {Position(0,0), Position(1,0), Position(2,0), Position(2,1)};
    cells[1] = {Position(0,0), Position(0,1), Position(0,2), Position(1,0)};
    cells[2] = {Position(0,1), Position(0,2), Position(1,2), Position(2,2)};
    cells[3] = {Position(1,2), Position(2,0), Position(2,1), Position(2,2)};
}

JBlock::JBlock(int anId, int anOrientation, int aPower) : Tetromino(anId, anOrientation, aPower) {
    cells[0] = {Position(0,2), Position(1,2), Position(2,1), Position(2,2)};
    cells[1] = {Position(1,0), Position(2,0), Position(2,1), Position(2,2)};
    cells[2] = {Position(0,0), Position(0,1), Position(1,0), Position(2,0)};
    cells[3] = {Position(0,0), Position(0,1), Position(0,2), Position(1,2)};
}

OBlock::OBlock(int anId, int anOrientation, int aPower) : Tetromino(anId, anOrientation, aPower) {
    cells[0] = {Position(0,0), Position(0,1), Position(1,0), Position(1,1)};
    cells[1] = {Position(0,0), Position(0,1), Position(1,0), Position(1,1)};
    cells[2] = {Position(0,0), Position(0,1), Position(1,0), Position(1,1)};
    cells[3] = {Position(0,0), Position(0,1), Position(1,0), Position(1,1)};
}

SBlock::SBlock(int anId, int anOrientation, int aPower) : Tetromino(anId, anOrientation, aPower) {
    cells[0] = {Position(0,1), Position(0,2), Position(1,0), Position(1,1)};
    cells[1] = {Position(0,0), Position(1,0), Position(1,1), Position(2,1)};
    cells[2] = {Position(1,1), Position(1,2), Position(2,0), Position(2,1)};
    cells[3] = {Position(0,1), Position(1,1), Position(1,2), Position(2,2)};
}

ZBlock::ZBlock(int anId, int anOrientation, int aPower) : Tetromino(anId, anOrientation, aPower) {
    cells[0] = {Position(0,0), Position(0,1), Position(1,1), Position(1,2)};
    cells[1] = {Position(0,1), Position(1,0), Position(1,1), Position(2,0)};
    cells[2] = {Position(1,0), Position(1,1), Position(2,1), Position(2,2)};
    cells[3] = {Position(0,2), Position(1,1), Position(1,2), Position(2,1)};
}

IBlock::IBlock(int anId, int anOrientation, int aPower) : Tetromino(anId, anOrientation, aPower) {
    cells[0] = {Position(0,1), Position(1,1), Position(2,1), Position(3,1)};
    cells[1] = {Position(1,0), Position(1,1), Position(1,2), Position(1,3)};
    cells[2] = {Position(0,2), Position(1,2), Position(2,2), Position(3,2)};
    cells[3] = {Position(2,0), Position(2,1), Position(2,2), Position(2,3)};
}



    /*
    T(int anOrientation) {
        id = 5;
        if (anOrientation==0) {
            cells[0][0] = 0;
            cells[0][1] = 0;
            cells[0][2] = 0;
            cells[0][3] = 0;
            cells[1][0] = 0;
            cells[1][1] = 1;
            cells[1][2] = 0;
            cells[1][3] = 0;
            cells[2][0] = 1;
            cells[2][1] = 1;
            cells[2][2] = 1;
            cells[2][3] = 0;
            cells[3][0] = 0;
            cells[3][1] = 0;
            cells[3][2] = 0;
            cells[3][3] = 0;
        }
        if (anOrientation==1) {
            cells[0][0] = 1;
            cells[0][1] = 0;
            cells[0][2] = 0;
            cells[0][3] = 0;
            cells[1][0] = 1;
            cells[1][1] = 1;
            cells[1][2] = 0;
            cells[1][3] = 0;
            cells[2][0] = 1;
            cells[2][1] = 0;
            cells[2][2] = 0;
            cells[2][3] = 0;
            cells[3][0] = 0;
            cells[3][1] = 0;
            cells[3][2] = 0;
            cells[3][3] = 0;
        }
        if (anOrientation==2) {
            cells[0][0] = 1;
            cells[0][1] = 1;
            cells[0][2] = 1;
            cells[0][3] = 0;
            cells[1][0] = 0;
            cells[1][1] = 1;
            cells[1][2] = 0;
            cells[1][3] = 0;
            cells[2][0] = 0;
            cells[2][1] = 0;
            cells[2][2] = 0;
            cells[2][3] = 0;
            cells[3][0] = 0;
            cells[3][1] = 0;
            cells[3][2] = 0;
            cells[3][3] = 0;
        }
        if (anOrientation==3) {
            cells[0][0] = 0;
            cells[0][1] = 0;
            cells[0][2] = 1;
            cells[0][3] = 0;
            cells[1][0] = 0;
            cells[1][1] = 1;
            cells[1][2] = 1;
            cells[1][3] = 0;
            cells[2][0] = 0;
            cells[2][1] = 0;
            cells[2][2] = 1;
            cells[2][3] = 0;
            cells[3][0] = 0;
            cells[3][1] = 0;
            cells[3][2] = 0;
            cells[3][3] = 0;
        }

    };
};
    

    void rotateRight() {
        self.orientation = (self.orientation+1) % 4;
        if (self.orientation==0) {
            bloc2_x = bloc1_x + 1;
            bloc2_y = bloc1_y;
            bloc3_x = bloc1_x + 2;
            bloc3_y = bloc1_y;
            bloc4_x = bloc1_x + 3;
            bloc4_y = bloc1_y;
        } 
        if (self.orientation==1) {
            bloc2_x = bloc1_x;
            bloc2_y = bloc1_y - 1;
            bloc3_x = bloc1_x;
            bloc3_y = bloc1_y - 2;
            bloc4_x = bloc1_x;
            bloc4_y = bloc1_y - 3;
        }
        if (self.orientation==2) {
            bloc2_x = bloc1_x - 1;
            bloc2_y = bloc1_y;
            bloc3_x = bloc1_x - 2;
            bloc3_y = bloc1_y;
            bloc4_x = bloc1_x - 3;
            bloc4_y = bloc1_y;
        }
        if (self.orientation==3) {
            bloc2_x = bloc1_x;
            bloc2_y = bloc1_y + 1;
            bloc3_x = bloc1_x;
            bloc3_y = bloc1_y + 2;
            bloc4_x = bloc1_x;
            bloc4_y = bloc1_y + 3;
        }
    }
}

int main() {
    TBlock primo = TBlock();
    return 0;
}*/