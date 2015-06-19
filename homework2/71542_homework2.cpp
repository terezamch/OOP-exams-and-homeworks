#include <iostream>
#include <cstring>
#include <cassert>
#include <cmath>
using namespace std;

class Point
{
    double x;
    double y;
public:

    Point(double x = 0, double y = 0)
    {
        this->x = x;
        this->y = y;
    }

    Point(const Point& other)
    {
        this->x = other.x;
        this->y = other.y;
    }

    ~Point()
    {

    }

    Point& operator=(const Point& other)
    {
        if(this != &other)
        {
            this->x = other.x;
            this->y = other.y;
        }
        return *this;
    }

    double getX() const
    {
        return x;
    }

    double getY() const
    {
        return y;
    }

    bool operator==(const Point& p)
    {
        if(this->getX() == p.getX() && this->getY() == p.getY())
            return true;
        return false;
    }

    void printP()
    {
        cout<<"("<<x<<","<<y<<")"<<endl;
    }

    class Figure : public Point
{
public:
    virtual double getPerimeter() const = 0;
    virtual double getArea() const = 0;
    virtual Point getCenter() const = 0;
    virtual char* getType() const = 0;
    virtual Point getA() const = 0;
    virtual Point getB() const = 0;
    virtual Point getC() const = 0;
    virtual Point getD() const = 0;
    virtual double getR() const = 0;
    virtual double getHeight() const = 0 ;
    virtual double getWidth() const = 0;
    virtual void print() = 0;
};

class Circle : public Figure
{
    Point c;
    double r;
public:
    Circle(double x1 = 0, double y1 = 0, double r = 1)
    {
        this->c = Point(x1, y1);
        this->r = r;
    }
    Circle(const Circle& other)
    {
        this->c = other.c;
        this->r = other.r;
    }
    ~Circle()
    {

    }
    Circle& operator=(const Circle& other)
    {
        if(this != &other)
        {
            this->c = other.c;
            this->r = other.r;
        }
        return *this;
    }
    double getR() const
    {
        return r;
    }
    Point getCenter() const
    {
        return c;
    }

    bool operator==(const Circle& other)
    {
        if(this->getCenter() == other.getCenter() && this->getR() == other.getR())
            return true;
        return false;
    }
    double getPerimeter() const
    {
        return 2*r*M_PI;
    }
    double getArea() const
    {
        return r*r*M_PI;
    }
    char* getType() const
    {
        return "circle";
    }
    void print()
    {
        cout<<"Circle: "<<endl;
        cout<<"R: "<<r<<" ";
        c.printP();
    }

    Point getA() const
    {

    }
    Point getB() const
    {

    }
    Point getC() const
    {

    }
    Point getD() const
    {

    }
};


class Triangle : public Figure
{
    Point a,b,c;
public:

    Triangle(double x1 = 0, double y1 = 0, double x2 = 1, double y2 = 1, double x3 = 2, double y3 = 2)
    {
        this->a = Point(x1, y1);
        this->b = Point(x2, y2);
        this->c = Point(x3, y3);
    }

    Triangle(const Triangle& other)
    {
        this->a = other.a;
        this->b = other.b;
        this->c = other.c;
    }

    ~Triangle()
    {

    }

    Triangle& operator=(const Triangle& other)
    {
        if(this != &other)
        {
            this->a = other.a;
            this->b = other.b;
            this->c = other.c;
        }
        return *this;
    }

    bool operator==(const Triangle& t)
    {
        if(this->a == t.a && this->b == t.b && this->c == t.c)
            return true;
        return false;
    }

    Point getA() const
    {
        return a;
    }

    Point getB() const
    {
        return b;
    }

    Point getC() const
    {
        return c;
    }

    Point getCenter() const
    {
        double x = (a.getX()*this->trdSide() + b.getX()*this->sndSide() + c.getX()*this->fstSide())/this->getPerimeter();
        double y = (a.getY()*this->trdSide() + b.getY()*this->sndSide() + c.getY()*this->fstSide())/this->getPerimeter();
        Point c(x,y);
        return c;
    }

    double fstSide() const
    {
        return sqrt(pow((a.getX() - b.getX()),2) + pow((a.getY() - b.getY()),2));
    }

    double sndSide() const
    {
        return sqrt(pow((a.getX() - c.getX()),2) + pow((a.getY() - c.getY()),2));
    }

    double trdSide() const
    {
        return sqrt(pow((c.getX() - b.getX()),2) + pow((c.getY() - b.getY()),2));
    }

    double getPerimeter() const
    {
        return (this->fstSide() + this->sndSide() + this->trdSide());
    }

    double getArea() const
    {
        double p = this->getPerimeter()/2;
        return sqrt(p*(p - this->fstSide())*(p - this->sndSide())*(p - this->trdSide()));
    }

    char* getType() const
    {
        return "triangle";
    }

    double getR() const
    {

    }

    void print()
    {
        cout<<"Triangle: "<<endl;
        a.printP();
        b.printP();
        c.printP();
    }
};


class Rectangle : public Figure
{
    Point bottomLeft, // A
          bottomRight; // B
          topRight, // C
          topLeft, // D


public:
    Rectangle(double x1 = 0, double y1 = 0, double x2 = 1, double y2 = 1, double x3 = 2, double y3 = 2, double x4 = 3, double y4 = 3)
    {
        this->bottomLeft = Point(x1, y1);
        this->bottomRight = Point(x2, y2);
        this->topLeft = Point(x3, y3);
        this->topRight = Point(x4, y4);
    }
    Rectangle(const Rectangle& other)
    {
        this->bottomLeft = other.bottomLeft;
        this->bottomRight = other.bottomRight;
        this->topLeft = other.topLeft;
        this->topRight = other.topRight;
    }
    ~Rectangle()
    {

    }
    Rectangle& operator=(const Rectangle& other)
    {
        if(this != &other)
        {
            this->bottomLeft = other.bottomLeft;
            this->bottomRight = other.bottomRight;
            this->topLeft = other.topLeft;
            this->topRight = other.topRight;
        }
        return *this;
    }
    bool operator==(const Rectangle& r)
    {
        if(this->bottomLeft == r.bottomLeft && this->bottomRight == r.bottomRight && this->topLeft == r.topLeft && this->topRight == r.topRight)
            return true;
        return false;
    }


     Point getA() const
    {
        return bottomLeft;
    }
    Point getB() const
    {
        return bottomRight;
    }

    Point getD() const
    {
        return topLeft;
    }
    Point getC() const
    {
        return topRight;
    }

    double getHeight() const
    {
        return sqrt(pow((topLeft.getX() - bottomLeft.getX()),2) + pow((topLeft.getY() - bottomLeft.getY()),2));
    }
    double getWidth() const
    {
        return sqrt(pow((bottomRight.getX() - bottomLeft.getX()),2) + pow((bottomRight.getY() - bottomLeft.getY()),2));
    }
    Point getCenter() const
    {
        cout << "presechnata tochka na diagonalite" ;
    }


    double getPerimeter() const
    {
        return (2*this->getHeight() + 2*this->getWidth());
    }
    double getArea() const
    {
        return this->getWidth()*this->getHeight();
    }
    char* getType() const
    {
        return "rectangle";
    }
    void print()
    {
        cout<<"Rectangle: "<<endl;
        bottomLeft.printP();
        bottomRight.printP();
        topRight.printP();
        topLeft.printP();
    }
};


int main()
{


    return 0 ;
}
