#pragma once

#include <iostream>

class Point
{
private:
	int _x, _y;

public:
	// Constructors
	Point();
	Point(const int x, const int y);
	Point(const Point& other);
	
	// Destructor
	~Point();

	// Getters
	const int getX();
	const int getY();

	// Operators
	const Point operator+(const Point& other);
	Point& operator+=(const Point& other);

	void operator=(const Point& other);
	bool operator==(const Point& other);
};

