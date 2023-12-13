#include "Tool.h"

Point Tool::_kingsLoc[2] = { Point(4, 0), Point(4, 7) };


Tool::Tool()
{
    this->_color = true;
    this->_place = Point();
    this->_ifMove = 0;
}

Tool::Tool(const bool color, const Point& place)
{
    this->_color = color;
    this->_place = place;
    this->_ifMove = 0;
}

Tool::~Tool()
{
}

void Tool::setPlace(const Point place)
{
    this->_place = place;
}

void Tool::setKingLoc()
{
    this->_kingsLoc[this->_color] = this->_place;
}

const Point Tool::getPlace()
{
    return this->_place;
}

const bool Tool::getColor()
{
    return this->_color;
}

const Point* Tool::getKingLoc()
{
    return this->_kingsLoc;
}
