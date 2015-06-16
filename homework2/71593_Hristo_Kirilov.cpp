#include <iostream>
#include <cmath>
using namespace std;

class Point
{
public:
    double x, y;
    Point(double x = 0, double y = 0):x(x),y(y){}
    Point& operator= (const Point& other)
    {
        if(this == &other)
            return *this;
        x = other.x;
        y = other.y;
        return *this;
    }

    bool operator== (const Point& other) const
    {
        if(x != other.x || y != other.y)
            return 0;
        return 1;
    }

    Point operator- (const Point& other) const
    {
        Point tmp = *this;
        tmp.x -= other.x;
        tmp.y -= other.y;
        return tmp;
    }

    double distance (const Point& other) const
    {
        Point result = *this;
        result.x -= other.x;
        result.y -= other.y;
        return sqrt(result.x * result.x + result.y * result.y);
    }
};

class Figure
{
protected:
    virtual int getType() const = 0;
    virtual bool isIn(const Point&) = 0;
    virtual Point getPoint (int) = 0;
    virtual double getRadius () = 0;
public:
    virtual ~Figure() {}
    virtual double area () const = 0;
    virtual double perimeter () const = 0;
    virtual Point center () const = 0;
    bool isIn (Figure* other)
    {
        int l = other -> getType();
        bool flag = 1;
        switch(l)
        {
        case 1:
            {
                for(int i = 0; i < 3 && flag; i++)
                    if(!isIn(other -> getPoint(i)))
                        flag = 0;
                if(flag)
                    return 1;
            }break;
        case 2:
            {
                for(int i = 0; i < 4 && flag; i++)
                    if(!isIn(other -> getPoint(i)))
                        flag = 0;
                if(flag)
                    return 1;
            }break;
        case 3:
            {
                if(!isIn(other -> getPoint(0)))
                    flag = 0;
                if(area() <= other -> area())
                    flag = 0;
                if(flag)
                    return 1;
            }
        }
    }

        l = getType();
        flag = 1;
        switch(l)
        {
        case 1:
            {
                for(int i = 0; i < 3 && flag; i++)
                    if(!other -> isIn(getPoint(i)))
                        flag = 0;
                if(flag)
                    return 1;
            }break;
        case 2:
            {
                for(int i = 0; i < 4 && flag; i++)
                    if(!other -> isIn(getPoint(i)))
                        flag = 0;
                if(flag)
                    return 1;
            }break;
        case 3:
            {
                if(!other -> isIn(getPoint(0)))
                    flag = 0;
                if(area() >= other -> area())
                    flag = 0;
                if(flag)
                    return 1;
            }
        }
    }
    return 0;
};

class Triangle: public Figure
{
private:
    Point A, B, C;
public:
    Triangle ()
    {
        A.x = 0;
        A.y = 0;
        B.x = 0;
        B.y = 0;
        C.x = 0;
        C.y = 0;
    }
    Triangle(const Point& A, const Point& B, const Point& C)
    {
        if(validation(A,B,C))
        {
            this -> A = A;
            this -> B = B;
            this -> C = C;
        }
        else
        {
            cout << "Incorrect data!\n";
        }
    }

    Triangle (const Triangle& other)
    {
        A = other.A;
        B = other.B;
        C = other.C;
    }

    Triangle& operator= (const Triangle& other)
    {
        if(this == &other)
            return *this;
        A = other.A;
        B = other.B;
        C = other.C;
        return *this;
    }

    ~Triangle(){}

    virtual double area () const
    {
        return ((A.x*B.y + A.y*C.x + B.x*C.y) - (C.x*B.y + B.x*A.y + A.x*C.y))*0.5;
    }

    virtual double perimeter () const
    {
        return B.distance(C) + A.distance(C) + B.distance(A);
    }

    virtual Point center () const
    {
        Point O;
        O.x = (A.x + B.x + C.x) / 3;
        O.y = (A.y + B.y + C.y) / 3;
        return O;
    }

    bool operator== (const Triangle& other)
    {
        if(A == other.A && B == other.B && C == other.C)
            return 1;
        else return 0;
    }

    virtual int getType() const
    {
        return 1;
    }

    bool validation (const Point& A, const Point& B, const Point& C) const
    {
        double a = B.distance(C),
               b = A.distance(C),
               c = B.distance(A);
        if(a + b <= c || a + c <= b || b + c <= a)
            return 0;
        return 1;
    }

    virtual bool isIn(const Point& other)
    {
        Triangle a1 (A, B, other),
                 a2 (A, C, other),
                 a3 (B, C, other);
        if(a1.area() + a2.area() + a3.area() < area())
            return 1;
        return 0;
    }

    virtual Point getPoint (int i)
    {
        if(i == 0)
            return A;
        if(i == 1)
            return B;
        return C;
    }

    virtual double getRadius ()
    {
        return 0;
    }
};

class Rectangle: public Figure
{
private:
    Point A, B, C, D;
public:
    Rectangle()
    {
        A.x = 0;
        A.y = 0;
        B.x = 0;
        B.y = 0;
        C.x = 0;
        C.y = 0;
        D.x = 0;
        D.y = 0;
    }

    Rectangle(const Point& A, const Point& B, const Point& C, const Point& D)
    {
        if(validation(A, B, C, D))
        {
            this -> A = A;
            this -> B = B;
            this -> C = C;
            this -> D = D;
        }
        else
        {
            cout << "Incorrect data!\n";
        }
    }

    Rectangle(const Rectangle& other)
    {
        A = other.A;
        B = other.B;
        C = other.C;
        D = other.D;
    }

    Rectangle& operator= (const Rectangle& other)
    {
        if(this == &other)
            return *this;
        A = other.A;
        B = other.B;
        C = other.C;
        D = other.D;
        return *this;
    }

    ~Rectangle() {}

    bool validation (const Point& A, const Point& B, const Point& C, const Point& D)
    {
        if(A.distance(B) != C.distance(D) || A.distance(D) != B.distance(C))
            return 0;
        Point tmp1 = B - A,
              tmp2 = D - A;
        if(tmp1.x * tmp2.x + tmp1.y * tmp2.y != 0)
            return 0;
        return 1;
    }

    bool operator== (const Rectangle& other) const
    {
        if(A == other.A && B == other.B && C == other.C && D == other.D)
            return 1;
        return 0;
    }

    virtual double area () const
    {
        return A.distance(B) * B.distance(C);
    }

    virtual double perimeter () const
    {
        return 2 * (A.distance(B) + B.distance(C));
    }

    virtual Point center () const
    {
        if(A.distance(B) != B.distance(C))
        {
            cout << "Center does not exist";
        }
        else
        {
            Point O;
            O.x = A.x + (C.x - A.x) / 2;
            O.y = A.y + (C.y - A.y) / 2;
            return O;
        }
    }

    virtual int getType() const
    {
        return 2;
    }

    virtual bool isIn(const Point& other)
    {
        if(other.x < A.x || other.x > D.x || other.y < A.y || other.y > B.y)
            return 0;
        return 1;
    }

    virtual Point getPoint (int i)
    {
        if(i == 0)
            return A;
        if(i == 1)
            return B;
        if(i == 2)
            return C;
        return D;
    }

    virtual double getRadius ()
    {
        return 0;
    }
};

class Circle: public Figure
{
    double r;
    Point o;
public:
    Circle ()
    {
        r = 1;
        o.x = 0;
        o.y = 0;
    }

    Circle(double R, Point O)
    {
        if(R > 0)
        {
            r = R;
            o = O;
        }
        else
            cout << "Incorrect data\n";
    }

    Circle (const Circle& other)
    {
        r = other.r;
        o = other.o;
    }

    Circle& operator= (const Circle& other)
    {
        if(this == &other)
            return *this;
        r = other.r;
        o = other.o;
        return *this;
    }

    ~Circle() {}

    bool operator== (const Circle& other) const
    {
        if(r == other.r && o == other.o)
            return 1;
        return 0;
    }

    virtual double area () const
    {
        return M_PI * r * r;
    }

    virtual double perimeter () const
    {
        return 2 * M_PI * r;
    }

    virtual Point center () const
    {
        return o;
    }

    virtual int getType() const
    {
        return 3;
    }

    virtual bool isIn(const Point& other)
    {
        if(other.distance(o) >= r)
            return 0;
        return 1;
    }

    virtual Point getPoint (int i)
    {
        return o;
    }

    virtual double getRadius ()
    {
        return r;
    }
};


int main ()
{
    Figure* A = new Rectangle(Point (0, 0), Point (0, 10), Point (10, 10), Point (10, 0));

    Figure* B = new Rectangle(Point (2, 2), Point (2, 5), Point (5, 5), Point (5, 2));
    cout << A -> isIn(B);
    Figure* C = new Circle (5, Point (10,10));
    return 0;
}
