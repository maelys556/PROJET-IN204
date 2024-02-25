

class Grid 
{
    public:
    int width;
    int height;
    int* grid;

    Grid() {}

    Grid(int aWidth, int aHeight) :
    width(aWidth), height(aHeight), grid(new int[aWidth*aHeight])

    ~Grid()
}

