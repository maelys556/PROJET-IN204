#include <iostream>

class Tetromino
{
    public:
    int couleur;
    int orientation;

    Tetromino() {}

    Tetromino(int aColor, int anOrientation) :
    couleur(aColor), orientation(anOrientation)
    {}

    ~Tetromino()
}


class T : public Tetromino
{
    public: 
    int bloc1_x;
    int bloc1_y;
    int bloc2_x;
    int bloc2_y;
    int bloc3_x;
    int bloc3_y;
    int bloc4_x;
    int bloc4_y;

    T() {}

    T(int x, int y, int anOrientation) :
    bloc1_x(x), bloc1_y(y)
    if (anOrientation == 0) {
        bloc2_x(x+1), bloc2_y(y), bloc3_x(x+2), bloc3_y(y), bloc4_x(x+3), bloc4_y(y)
    }
    if (anOrientation == 1) {
        bloc2_x(x), bloc2_y(y-1), bloc3_x(x), bloc3_y(y-2), bloc4_x(x), bloc4_y(y-3)
    }
    if (anOrientation == 2) {
        bloc2_x(x+1), bloc2_y(y), bloc3_x(x+2), bloc3_y(y), bloc4_x(x+3), bloc4_y(y)
    }
    if (anOrientation == 3) {
        bloc2_x(x), bloc2_y(y-1), bloc3_x(x), bloc3_y(y-2), bloc4_x(x), bloc4_y(y-3)
    }

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