#include "cell.h"

using namespace gameOfLife;

Cell::Cell()
{

}

int Cell::getState()
{
    return _state;
}

void Cell::setState(int state)
{
    _state = state;
}
