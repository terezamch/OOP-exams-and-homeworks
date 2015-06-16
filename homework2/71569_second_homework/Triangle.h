#ifndef TRIAGNLE_H
#define TRIANGLE_H
#include "Figure.h"


class Triangle: public Figure{

public:
	Triangle();
	Triangle(Point, Point, Point);
	Triangle(const Triangle&);
	Triangle& operator=(const Triangle&);
	~Triangle();
	
	bool operator==(const Triangle&) const;

	Point getFstEdge() const;
	Point getSndEdge() const;
	Point getThrdEdge() const;

	bool isValidTriangle(Point, Point, Point) const;
	bool isPointInsideFigure(Point) const;
	void setEdges(Point, Point, Point);

	
	float getArea() const;
	float getPerimeter() const;
	Point getFigureCenter() const;
	const char* getType() const;
	
protected:
	
	float* sides;
	void calculateSides();

private:
	Point fstEdge;
	Point sndEdge;
	Point thrdEdge;

};



#endif
