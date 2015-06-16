#include <iostream>
#include <cmath>
#include <cstring>
#include "Triangle.h"



using namespace std;



float calculateDistance(Point p1, Point p2)
{
		float b = p2.x - p1.x;
		float c = p2.y - p1.y;
        return sqrt(b*b + c*c);
}



Triangle::Triangle()
	:fstEdge(0,0), sndEdge(0,0), thrdEdge(0,0), sides(NULL)
{}


Triangle:: Triangle(Point p1, Point p2, Point p3)
	:fstEdge(0,0), sndEdge(0,0), thrdEdge(0,0), sides(NULL)
{
	this->setEdges(p1, p2, p3);

}

Triangle::Triangle(const Triangle& other)
	:fstEdge(0,0), sndEdge(0,0), thrdEdge(0,0), sides(NULL)
{
	this->setEdges(other.fstEdge, other.sndEdge, other.thrdEdge);
	
}

Triangle& Triangle:: operator=(const Triangle& other)
{
	if(this!=&other)
	{
		this->setEdges(other.fstEdge, other.sndEdge, other.thrdEdge);
		
	}	

	return *this;
}

Triangle::~Triangle()
{
	delete[] this->sides;
}



bool Triangle::operator ==(const Triangle& other) const
{
	return this->sides[0] == other.sides[0] && this->sides[1] == other.sides[1] && this->sides[2] == other.sides[2];
}


Point Triangle::getFstEdge() const
{
	return this->fstEdge;
}

Point Triangle::getSndEdge() const
{
	return this->sndEdge;
}

Point Triangle::getThrdEdge() const
{
	return this->thrdEdge;
}

void Triangle::calculateSides() 
{
	delete[] this->sides;
	
	sides = new float[3];
	sides[0] = calculateDistance(fstEdge, sndEdge);
	sides[1] = calculateDistance(sndEdge, thrdEdge);
	sides[2] = calculateDistance(fstEdge, thrdEdge);
	
	
}

bool Triangle::isValidTriangle(Point p1, Point p2, Point p3) const
{
	float* distance = new float[3];
	distance[0] = calculateDistance(p1, p2);
	distance[1] = calculateDistance(p2, p3);
	distance[2] = calculateDistance(p1, p3);
	
	
	return (distance[0] + distance[1]) > distance[2] && (distance[0] + distance[2]) > distance[1] && (distance[1] + distance[2]) > distance[0];

}


bool Triangle::isPointInsideFigure(Point p) const
{
		float alpha = ((thrdEdge.y - thrdEdge.y)*(p.x - thrdEdge.x) + (thrdEdge.x - sndEdge.x)*(p.y - thrdEdge.y)) / ((sndEdge.y - thrdEdge.y)*(fstEdge.x - thrdEdge.x) + (thrdEdge.x - sndEdge.x)*(fstEdge.y - thrdEdge.y));
		float beta = ((thrdEdge.y - fstEdge.y)*(p.x - thrdEdge.x) + (fstEdge.x - thrdEdge.x)*(p.y - thrdEdge.y)) /((sndEdge.y - thrdEdge.y)*(fstEdge.x - thrdEdge.x) + (thrdEdge.x - sndEdge.x)*(fstEdge.y - thrdEdge.y));
		float gamma = 1.0f - alpha - beta;

		return alpha > 0 && beta > 0 && gamma > 0;

}

void Triangle::setEdges(Point p1, Point p2, Point p3)
{
	if(isValidTriangle(p1, p2, p3))
	{
		this->fstEdge = p1;
		this->sndEdge = p2;
		this->thrdEdge = p3;
		
		this->calculateSides();
	}
}



float Triangle::getArea() const
{
	
	float p = (sides[0]+sides[1]+sides[2])/2;

	return sqrt(p*(p-sides[0])*p*(p-sides[1])*p*(p-sides[2]));
	
}


float Triangle::getPerimeter() const
{
	return sides[0] + sides[1] + sides[2];
}

const char* Triangle::getType() const
{
	return "triangle";
}


Point Triangle::getFigureCenter() const
{
		float p = getPerimeter();
		Point center;
		center.x = (sides[1]*fstEdge.x + sides[2]*sndEdge.x + sides[0]*thrdEdge.x)/p;
		center.y = (sides[1]*fstEdge.y + sides[2]*sndEdge.y + sides[0]*thrdEdge.y)/p;
		
		return center;
}




