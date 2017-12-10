#ifndef CELL_H
#define CELL_H

namespace gameOfLife
{

class Cell
{
    int _state = 0;
public:
    Cell();

    int getState();

    void setState(int);
};

}

#endif // CELL_H
