#ifndef CIRCLE_H
#define CIRCLE_H
#include "Figure.h"


class Circle : public Figure{
	
public:
	Circle();
	Circle(Point, float);
	Circle(const Circle&);
	Circle& operator=(const Circle&);	
	~Circle() {};

	bool operator==(const Circle&) const;
	
	bool isPointInsideFigure(Point) const;

	void setCenter(Point);
	void setRadius(float);

	Point getCenter() const;
	float getRadius() const;
	
	float getArea() const;
	float getPerimeter() const;
	const char* getType() const;
	Point getFigureCenter() const;

private:
	Point center;
	float radius;

};


#endif
