#include <iostream>
#include <vector>
#include 'position.h'

class Tetromino
{
    protected:
    int id; // 0 = I, 1 = J, 2 = L, 3 = O, 4 = S, 5 = T, 6 = Z
    int orientation;
    int RowOffset;
    int ColumnOffset;
    std::vector<std::vector<Position>> cells;

    public:

    Tetromino(int anId, int anOrientation) :
    id(anId), orientation(anOrientation), RowOffset(0), ColumnOffset(0)
    {}

    void rotate() {

    }

    void moveRight(int nb_rows, int nb_columns) {
        RowOffset += nb_rows;
        ColumnOffset += nb_columns;
    }

    void moveLeft() (int nb_rows, int nb_columns) {
        RowOffset -= nb_rows;
        ColumnOffset -= nb_columns;
    }

    void isValid() {

    }

    ~Tetromino()
};


class TBlock : public Tetromino
{
    private: 

    public :
    TBlock(int anId, int anOrientation) : Tetromino(anId, anOrientation) {
        cells[0] = {Position(1,1), Position(2,0), Position(2,1), Position(2,2)};
        cells[1] = {Position(0,0), Position(1,0), Position(1,1), Position(2,0)};
        cells[2] = {Position(0,0), Position(0,1), Position(0,2), Position(1,1)};
        cells[3] = {Position(0,2), Position(1,1), Position(1,2), Position(2,2)};
    }
};

class LBlock : public Tetromino
{
    public:
    LBlock(int anId, int anOrientation) : Tetromino(anId, anOrientation) {
        cells[0] = {Position(0,0), Position(1,0), Position(2,0), Position(2,0)};
        cells[1] = {Position(0,0), Position(0,1), Position(0,2), Position(1,0)};
        cells[2] = {Position(0,1), Position(0,2), Position(1,2), Position(2,2)};
        cells[3] = {Position(1,2), Position(2,0), Position(2,1), Position(2,2)};
    }
};

class JBlock : public Tetromino
{
    public:
    JBlock(int anId, int anOrientation) : Tetromino(anId, anOrientation) {
        cells[0] = {Position(0,2), Position(1,2), Position(2,1), Position(2,2)};
        cells[1] = {Position(1,0), Position(2,0), Position(2,1), Position(2,2)};
        cells[2] = {Position(0,0), Position(0,1), Position(1,0), Position(2,0)};
        cells[3] = {Position(0,0), Position(0,1), Position(0,2), Position(1,2)};
    }
};

class OBlock : public Tetromino
{
    public:
    OBlock(int anId, int anOrientation) : Tetromino(anId, anOrientation) {
        cells[0] = {Position(0,0), Position(1,0), Position(2,0), Position(2,0)};
        cells[1] = {Position(0,0), Position(0,1), Position(0,2), Position(1,0)};
        cells[2] = {Position(0,1), Position(0,2), Position(1,2), Position(2,2)};
        cells[3] = {Position(1,2), Position(2,0), Position(2,1), Position(2,2)};
    }
};

class SBlock : public Tetromino
{

};

class ZBlock : public Tetromino 
{

};

class IBlock : public Tetromino 
{

};

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