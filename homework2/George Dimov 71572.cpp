
#include <iostream>
using namespace std;

class Point
{
private:
	double x, y;
public:
	Point(double x =0, double y=0)
	{
		setY(y);
		setX(x);
	}
	void setX(double x)
	{
		this->x = x;
	}
	void setY(double y)
	{
		this->y = y;
	}
	double getX()
	{
		return x;
	}
	double getY()
	{
		return y;
	}
	double Side(Point other)
	{
		return sqrt(pow(this->x - other.x, 2.0) + pow(this->x - other.x,2.0));
	}
	Point operator==(Point&other)
	{
		if (this != &other)
		{
			this->x = other.x;
			this->y = other.y;
		}
		return*this;
	}
};
class Figure
{ // napulno abstracten class 
public:
	virtual double area() = 0;
	virtual double getPerimeter()= 0;
	virtual Point getCenter()= 0;
	virtual bool PointInside(Point&) = 0;
	virtual bool Inside(Figure&) = 0;

};

class Triangle : public Figure
{
private:
	Point a;
	Point b; 
	Point c; 
public:
	Triangle(double x1 = 0, double y1 = 0, double x2 = 0, double y2 = 0, double x3 = 0, double y3 = 0) :a(x1, y1), b(x2, y2), c(x3, y3)
	{}
	void Cpy(const Triangle& other)
	{
		this->a = other.a;
		this->b = other.b;
		this->c = other.c;
	}
	Triangle(const Triangle& other)
	{
		Cpy(other);
	}

	Triangle& operator=(const Triangle& other)
	{
		if (this != &other)
		{
			Cpy(other);
		}
		return *this;
	}
	virtual double area()
	{
		
		return sqrt((getPerimeter() / 2)*(getPerimeter() / 2 - a.Side(b))*(getPerimeter() / 2 - b.Side(c))*(getPerimeter() / 2 - a.Side(c)));
	}
	virtual double getPerimeter() 
	{
		return a.Side(b) + b.Side(c) + c.Side(a);
	}
	virtual Point getCenter() 
	{
		double x=( ( (b.Side(c))*a.getX() + (a.Side(c))*b.getX() + ( b.Side(a))*c.getX()) / getPerimeter() );
		double y = (((b.Side(c))*a.getY() + (a.Side(c))*b.getY() + (b.Side(a))*c.getY()) / getPerimeter());
		Point Center(x,y);
		return Center;
	}

	virtual double getRadius() 
	{
		double s = this->area();
		return 2 * s / (a.Side(b));
	}
	virtual bool PointInside(Point&)
	{

	}
	virtual bool Inside(Figure&)
	{

	}
};



class Rectangle : public Figure
{
	double width;
	double height;
	Point a;
	Point b; 
	Point c;
public:
	Rectangle(double x1 = 0, double y1 = 0, double x2 = 0, double y2 = 0,double x3=0,double y3 = 0 ) :a(x1, y1), b(x2, y2), c(x3,y3)
	{
		width = a.Side(b);
		height = b.Side(c);
	}

	virtual double area()
	{
		return width*height;
	}
	virtual double getPerimeter()
	{
		return width * 2 + height * 2;
	}
	virtual Point getCenter()
	{
		if (height == width)
		{
			return Point(height / 2 , height/2);
		}
		else
		{
			return Point(0,0); 
		}

	}
	virtual bool PointInside(Point& o)
	{

	}
	virtual bool Inside(Figure& o)
	{

	}
};

class Circle : public Figure
{
	double r;
public:
	Circle(double r= 0)
	{
		this->r = r; 
	}
	virtual double area()
	{
		return  3.14*(this->r)*(this->r);

	}
	virtual double getPerimeter()
	{
		return 2 * 3.14*r;

	}
	virtual Point getCenter()
	{
		return Point(0,0); 
	}
	virtual bool PointInside(Point& o)
	{
		return o.Side(Point(0,0)) < this->r;
	}
	virtual bool Inside(Figure&)
	{

	}
};








int main(){
	Figure* arr[15];
	for (int i = 0; i < 5; i++)
	{
		arr[i] = new Circle;
	}
	for (int i = 5; i < 10; i++)
	{
		arr[i] = new Rectangle;
	}
	for (int i = 10; i < 15; i++)
	{
		arr[i] = new Triangle;
	}


	system("pause");
	return 0;
}
