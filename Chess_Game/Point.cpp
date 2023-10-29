#include "Point.h"

//Constructors

Point::Point(int x, int y) { this->_x = x; this->_y = y; }

Point::Point(const Point& other) { this->_x = other._x; this->_y = other._y; }

Point::Point() { this->_x = 0; this->_y = 0; }

// Destructor

Point::~Point() {}

// Getters

const int Point::getX() { return this->_x; }

const int Point::getY() { return this->_y; }

// operators

const Point Point::operator+(const Point& other)
{
	return Point(this->_x + other._x, this->_y + other._y);
}

Point& Point::operator+=(const Point& other)
{
	return *(new Point(this->_x + other._x, this->_y + other._y));
}

void Point::operator=(const Point& other)
{
	this->_x = other._x;
	this->_y = other._y;
}

bool Point::operator==(const Point& other)
{
	if (this->_x == other._x && this->_y == other._y)
		return true;
	return false;
}
