#ifndef FIGURE_H
#define FIGURE_H
	


struct Point{

	float x;
	float y;
	
	Point()
		:x(0), y(0) {}
		
	Point(float p, float q)
		:x(p), y(q){}
	Point(const Point& other)
		:x(other.x), y(other.y){}
	
	Point& operator=(const Point& other)
	{
		if(this!=&other)
		{
			x = other.x;
			y = other.y;
		}
	
		return *this;
	}


};


class Figure{

public:

	virtual float getArea() const = 0;
	virtual float getPerimeter() const = 0;
	virtual const char* getType() const = 0;
	virtual Point getFigureCenter() const = 0;
	virtual bool isPointInsideFigure(Point) const = 0;


};




#endif
