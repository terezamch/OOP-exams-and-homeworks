#ifndef RECTANGLE_H
#define RECTANGLE_H
#include "Figure.h"


class Rectangle : public Figure{


public:
	Rectangle();
	Rectangle(Point, Point);
	Rectangle(const Rectangle&);
	Rectangle& operator=(const Rectangle&);
	~Rectangle() {};

	bool isValidRect(Point, Point) const;
	bool operator==(const Rectangle&) const;
	bool isPointInsideFigure(Point) const;


	void setCorners(Point, Point);

	Point getUpperCorner() const;
	Point getBottomCorner() const;

	float getHeight() const;
	float getWidth() const;

	float getArea() const;
	float getPerimeter() const;
	const char* getType() const;
	Point getFigureCenter() const;



private:
	
	Point upperLeft;
	Point bottomRight;


};


#endif
