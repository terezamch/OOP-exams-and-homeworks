#include <iostream>
#include <cstring>
#include "Rectangle.h"


using namespace std;

Rectangle::Rectangle()
	:upperLeft(0,0), bottomRight(0,0)
{}

Rectangle::Rectangle(Point upC, Point bottomC)
	:upperLeft(0,0), bottomRight(0,0)
{

	this->setCorners(upC, bottomC);

}

bool Rectangle::isValidRect(Point upC, Point bottomC) const
{
	return !((upC.x == bottomC.x)||(upC.y == bottomC.y)); // не могат да лежат на една права или да съвпадат
}

void Rectangle::setCorners(Point upC, Point bottomC)
{
	if(this->isValidRect(upC, bottomC))	
	{
		this->upperLeft.x = upC.x;
		this->upperLeft.y = upC.y;
		this->bottomRight.x = bottomC.x;
		this->bottomRight.y = bottomC.y;
		
	}
}

Rectangle::Rectangle(const Rectangle& other)
	:upperLeft(0,0), bottomRight(0,0)
{
	this->setCorners(other.upperLeft, other.bottomRight);
}

Rectangle& Rectangle::operator=(const Rectangle& other)
{
	if (this != &other)
	{
		this->setCorners(other.upperLeft, other.bottomRight);
	}

	return *this;
}


bool Rectangle::operator==(const Rectangle& other) const // проверка дали фигурите са еднакви, не едни и същи
{
	return this->getHeight() == other.getHeight() && this->getWidth() == other.getWidth();
}

bool Rectangle::isPointInsideFigure(Point p) const
{
	return (p.x > upperLeft.x) && (p.x < bottomRight.x) && (p.y < upperLeft.y) && (p.y > bottomRight.y);
}


Point Rectangle::getUpperCorner() const
{
	return this->upperLeft;
}

Point Rectangle::getBottomCorner() const
{
	return this->bottomRight;
}

float Rectangle::getHeight() const
{
	return this->upperLeft.y - this->bottomRight.y;
}

float Rectangle::getWidth() const
{
	return this->bottomRight.x - this->upperLeft.x;

}

float Rectangle::getArea() const
{
	return this->getHeight() * this->getWidth();
}

float Rectangle::getPerimeter() const
{
	return 2 * (this->getHeight() + this->getWidth());
}

const char* Rectangle::getType() const
{
	return "rectangle";
}

Point Rectangle::getFigureCenter() const
{
	Point center(this->upperLeft.x + this->getWidth()/2, this->bottomRight.y+this->getHeight()/2);
	
	return center;
}

