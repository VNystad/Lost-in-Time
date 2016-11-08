#ifndef LOST_IN_TIME_TILE_H
#define LOST_IN_TIME_TILE_H


class Tile
{
public:
    Tile(int xCoord, int yCoord) : xCoord(xCoord), yCoord(yCoord) {}

    int GetXCoord () const { return xCoord; }
    int GetYCoord () const { return yCoord; }

protected:
    int xCoord;
    int yCoord;
};


#endif //LOST_IN_TIME_TILE_H
