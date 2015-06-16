#include <iostream>
#include <cmath>
#include <cstring>
#include "Circle.h"


using namespace std;

Circle::Circle()
  :center(0,0)
{}

Circle::Circle(Point cen, float rad)
  :center(0,0)
{
	this->setCenter(cen);
	this->setRadius(rad);
}

Circle::Circle(const Circle& other)
  :center(0,0)
{
	this->setCenter(other.center);
	this->setRadius(other.radius);
}

Circle& Circle::operator=(const Circle& other)
{
	if (this != &other)
	{
		this->setCenter(other.center);
		this->setRadius(other.radius);
	}

	return *this;

}

bool Circle::operator ==(const Circle& other) const 
{
	return this->radius == other.radius;
}


bool Circle::isPointInsideFigure(Point p) const
{
	return (p.x - center.x)*(p.x - center.x) + (p.y - center.y)* (p.y - center.y)  < radius * radius;
}

void Circle::setCenter(Point cen)
{
	this->center.x = cen.x;
	this->center.y = cen.y;
}

void Circle::setRadius(float rad)
{
	this->radius = rad;
}

Point Circle::getCenter() const
{
	return this->center;
}

float Circle::getRadius() const
{
	return this->radius;
}

float Circle::getArea() const
{
	return this->radius * this->radius * M_PI;
}

float Circle::getPerimeter() const
{
	return 2 * this->radius * M_PI;
}

const char* Circle::getType() const
{
	return "circle";
}

Point Circle::getFigureCenter() const
{
	return this->center;
}




