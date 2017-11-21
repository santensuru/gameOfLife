#include "cell.h"

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
