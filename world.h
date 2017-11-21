#ifndef WORLD_H
#define WORLD_H

// max 10*10; 6*13
// best 6*100;
#define WORLD_HEIGHT 15
#define WORLD_WIDTH 105

#include "cell.h"
#include <vector>
#include <qstring.h>

class World
{
    //Cell _odds [WORLD_HEIGHT][WORLD_WIDTH];
    //Cell _evens[WORLD_HEIGHT][WORLD_WIDTH];

    std::vector<std::vector<Cell>> _oddsV;
    std::vector<std::vector<Cell>> _evensV;

    int getNeighbourFreq(int, int, bool);

    int getStateOdds(int, int);
    int getStateEvens(int, int);

    void setStateOdds(int, int, int);
    void setStateEvens(int, int, int);

    void updateState(int, int, int, bool);

public:
    World();

    void generate();
    void update(bool);

    void printStates(bool);
    QString printStatesToString(bool);
};

#endif // WORLD_H
