#include <iostream>
#include <vector>
#include "position.cpp"

class Tetromino {
    public:

    int id; // 0 = I, 1 = J, 2 = L, 3 = O, 4 = S, 5 = T, 6 = Z
    int orientation;
    int RowOffset;
    int ColumnOffset;
    std::vector<std::vector<Position>> cells = std::vector<std::vector<Position>>(4);

    Tetromino(int anId, int anOrientation);
    std::vector<Position> getCells();
    void printTetromino();
};


class TBlock : public Tetromino {
    public :
    TBlock(int anId, int anOrientation);
};

class LBlock : public Tetromino {
    public:
    LBlock(int anId, int anOrientation);
};


class JBlock : public Tetromino {
    public:
    JBlock(int anId, int anOrientation);
};

class OBlock : public Tetromino {
    public:
    OBlock(int anId, int anOrientation);
};


class SBlock : public Tetromino {
    public:
    SBlock(int anId, int anOrientation);
};


class ZBlock : public Tetromino {
    public:
    ZBlock(int anId, int anOrientation);
};


class IBlock : public Tetromino {
    public:
    IBlock(int anId, int anOrientation);
};