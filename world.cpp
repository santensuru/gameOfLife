#include "world.h"
#include <qapplication.h>
#include <qdatetime.h>

using namespace gameOfLife;

World::World()
{

}

int World::getNeighbourFreq(int x, int y, bool isOdds)
{
    int freq = 0;
    for (int i=x-1; i<=x+1; i++)
    {
        for (int j=y-1; j<=y+1; j++)
        {
            if ((i>=0 && i<WORLD_HEIGHT) && (j>=0 && j<WORLD_WIDTH))
            {
                if (i==x && j==y)
                {
                    continue;
                }

                if (isOdds)
                {
                    freq += getStateOdds(i, j);
                }
                else
                {
                    freq += getStateEvens(i, j);
                }
            }
        }
    }
    return freq;
}

int World::getStateOdds(int x, int y)
{
    //return _odds[x][y].getState();
    return _oddsV.at(x).at(y).getState();
}

int World::getStateEvens(int x, int y)
{
    //return _evens[x][y].getState();
    return _evensV.at(x).at(y).getState();
}

void World::setStateOdds(int x, int y, int state)
{
    //_odds[x][y].setState(state);
    _oddsV.at(x).at(y).setState(state);
}

void World::setStateEvens(int x, int y, int state)
{
    //_evens[x][y].setState(state);
    _evensV.at(x).at(y).setState(state);
}

void World::updateState(int x, int y, int state, bool isOdds)
{
    if (isOdds)
    {
        setStateOdds(x, y, state);
    }
    else
    {
        setStateEvens(x, y, state);
    }
}

void World::generate()
{
    qsrand(QDateTime::currentMSecsSinceEpoch() / 1000);
    for (int i=0; i<WORLD_HEIGHT; i+=1)
    {
        std::vector<Cell> _cells;
        std::vector<Cell> _cells2;
        for (int j=0; j<WORLD_WIDTH; j+=1)
        {
            int curState = qrand() % 2;

            Cell curCell;
            curCell.setState(curState);
            _cells.push_back(curCell);
            _cells2.push_back(curCell);

            //updateState(i, j, curState, false);
        }
        _oddsV.push_back(_cells);
        _evensV.push_back(_cells2);
    }
}

void World::update(bool isOdds)
{
    for (int i=0; i<WORLD_HEIGHT; i++)
    {
        for (int j=0; j<WORLD_WIDTH; j++)
        {
            int curState = 0;
            int curFreq = getNeighbourFreq(i, j, !isOdds);
            if (!isOdds)
            {
                curState = getStateOdds(i, j);
            }
            else
            {
                curState = getStateEvens(i, j);
            }

            if (curState == 1)
            {
                // over population: die
                if (curFreq > 3)
                {
                    updateState(i, j, 0, isOdds);
                }
                // under population: die
                else if (curFreq < 2)
                {
                    updateState(i, j, 0, isOdds);
                }
                else
                {
                    updateState(i, j, 1, isOdds);
                }
            }
            else
            {
                // birth
                if (curFreq == 3)
                {
                    updateState(i, j, 1, isOdds);
                }
                else
                {
                    updateState(i, j, 0, isOdds);
                }
            }
        }
    }
}

void World::printStates(bool isOdds)
{
    char states[2] = { ' ', 'X' };
    for (int i=-1; i<=WORLD_HEIGHT; i++)
    {
        for (int j=-1; j<=WORLD_WIDTH; j++)
        {
            if ((i>=0 && i<WORLD_HEIGHT) && (j>=0 && j<WORLD_WIDTH))
            {
                if (isOdds)
                {
                    //printf("%c", states[_odds[i][j].getState()]);
                    printf("%c", states[_oddsV.at(i).at(j).getState()]);
                }
                else
                {
                    //printf("%c", states[_evens[i][j].getState()]);
                    printf("%c", states[_evensV.at(i).at(j).getState()]);
                }
            }
            else
            {
                if (i==-1 || i==WORLD_HEIGHT)
                {
                    if (j==-1 || j==WORLD_WIDTH)
                    {
                        printf("+");
                    }
                    else
                    {
                        printf("-");
                    }
                }
                else
                {
                    printf("|");
                }
            }
        }
        printf("\n");
    }
}

QString World::printStatesToString(bool isOdds)
{
    QString temp = "";

    char states[2] = { ' ', 'X' };
    for (int i=-1; i<=WORLD_HEIGHT; i++)
    {
        for (int j=-1; j<=WORLD_WIDTH; j++)
        {
            if ((i>=0 && i<WORLD_HEIGHT) && (j>=0 && j<WORLD_WIDTH))
            {
                if (isOdds)
                {
                    temp += QChar(states[_oddsV.at(i).at(j).getState()]);
                }
                else
                {
                    temp += QChar(states[_evensV.at(i).at(j).getState()]);
                }
            }
            else
            {
                if (i==-1 || i==WORLD_HEIGHT)
                {
                    if (j==-1 || j==WORLD_WIDTH)
                    {
                        temp += "+";
                    }
                    else
                    {
                        temp += "-";
                    }
                }
                else
                {
                    temp += "|";
                }
            }
        }
        temp += "\n";
    }

    return temp;
}
