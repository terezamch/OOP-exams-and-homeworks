#include <iostream>
#include <cmath>
using namespace std;
const double PI = 3.14159265;


struct Point{
public:
	Point(double x = 0, double y = 0) :x(x), y(y){}
	Point(const Point& other) :x(other.x), y(other.y){}
	Point& operator=(const Point& other){
		if (this != &other){
			x = other.x;
			y = other.y;
		}
		return *this;
	}
	double X()const {
		return x;
	}
	double Y()const {
		return y;
	}
	bool operator==(const Point&other){
		return x == other.x && y == other.y;
	}
	double distanceTo(const Point&other)const {
		return sqrt((x - other.x)*(x - other.x) + (y - other.y)*(y - other.y));
	}
	bool pointInT( Point p0, Point p1, Point p2 ){
		double s = p0.Y() * p2.X() - p0.X() * p2.Y() + (p2.Y() - p0.Y()) * x + (p0.X() - p2.X()) * y;
		double t = p0.X() * p1.Y() - p0.Y() * p1.X() + (p0.Y() - p1.Y()) * x + (p1.X() - p0.X()) * y;

		if ((s < 0) != (t < 0))
			return false;

		double A = -p1.Y() * p2.X() + p0.Y() * (p2.X() - p1.X()) + p0.X() * (p1.Y() - p2.Y()) + p1.X() * p2.Y();
		if (A < 0.0)
		{
			s = -s;
			t = -t;
			A = -A;
		}
		return s > 0 && t > 0 && (s + t) < A;
	}
	bool pointInR(Point upperLeft,Point lowerRight)
	{
		return ((x >= upperLeft.X()) &&
			(x <= lowerRight.X()) &&
			(y >= upperLeft.Y()) &&
			(y <= lowerRight.Y()));

	}
	~Point(){}


private:
	double x;
	double y;
};
class Figure
{
public:
	Figure(Point point=Point(0,0)){
		this->point = point;
	}
	Figure(const Figure& other){
		this->point = other.point;
	}
	Figure& operator=(const Figure& other){
		if (this != &other){
			this->point = other.point;
		}
		return *this;
	}
	Point getPoint()const{
		return point;
	}
	virtual Point p(int n)const = 0;
	virtual void print()const {
		cout << "Center:" << point.X()<<" "<<point.Y() << endl;
	}
	virtual double perimeter() const = 0;
	virtual double surface() const = 0;
	virtual Point getCenter()const= 0;
	virtual char* type()const= 0;
	virtual bool isIn(Figure& figure) = 0;
	virtual double getRadious()const = 0;

protected:
	Point point;//center
};
class Triangle :public Figure {
public:
	virtual bool isIn(Figure& figure){
		if (!strcmp(figure.type(), "rectangle")){
			return inR(figure);
		}
		if (!strcmp(figure.type(), "triangle")){
			return inTr(figure);
		}
		if (!strcmp(figure.type(), "circle")){
			return inC(figure);
		}
	}

	virtual bool operator==(const Figure& other){
		if (strcmp(other.type(), "triangle")){
			return false;
		}

		return points[0] == other.p(0) && points[1] == other.p(1) &&
			points[2] == other.p(2);
	}
	Triangle(Point points[3]) :Figure()
	{
		if (points[0].distanceTo(points[1]) + points[2].distanceTo(points[1]) > points[0].distanceTo(points[2])
			&& points[0].distanceTo(points[1]) + points[0].distanceTo(points[2]) > points[2].distanceTo(points[1])
			&& points[2].distanceTo(points[1]) + points[0].distanceTo(points[2]) > points[0].distanceTo(points[1])){
			for (int i = 0; i < 3; i++){
				this->points[i] = points[i];
			}
			this->point = Triangle::getCenter();
		}
	};
	virtual char* type()const{
		return "triangle";
	}
	virtual Point p(int n)const {
		if (n==0){
			return points[0];
		}
		else if (n == 1){
			return points[1];
		}
		else if (n == 2){
			return points[2];
		}
	}

	virtual Point getCenter()const {
		Point center((points[0].X() + points[2].X()+points[1].X()) / 3,
			(points[0].Y() + points[2].Y()+points[1].Y()) / 3);
		return center;
	}
	Triangle(const Triangle&other):Figure(other){
		for (int i = 0; i < 3; i++){
			this->points[i] = other.points[i];
		}
	}
	Triangle& operator=(const Triangle& other){
		if (this != &other){
			Figure::operator=(other);
			for (int i = 0; i < 3; i++){
				this->points[i] = other.points[i];
			}

		}
		return *this;
	}

	virtual void print() const
	{
		Figure::print();
		cout << "Point A: " << points[0].X() << "," << points[0].Y() << endl
			<< "Point B: " << points[1].X() << "," << points[1].Y() << endl
			<< "Point C: " << points[2].X() << "," << points[2].Y() << endl;
	}

	double perimeter() const
	{
		return points[1].distanceTo(points[0]) + points[2].distanceTo(points[1])
			+ points[3].distanceTo(points[2]);
	}

	double surface() const
	{
		return sqrt((perimeter() / 2)*(perimeter() / 2 - points[1].distanceTo(points[0]))
			*(perimeter() / 2 - points[2].distanceTo(points[1]))
			*(perimeter() / 2 - points[3].distanceTo(points[2])));
	}
	virtual double getRadious()const{
		return 0;
	}

private:
	Point points[3];

	bool inTr(Figure& figure){//triangle in other triangle
		bool result = true;
		for (int i = 0; i < 3; i++){
			if (!points[i].pointInT(figure.p(0), figure.p(1), figure.p(2))){
				result = false;
				break;
			}
		}
		return result;
	}
	bool inC(Figure& figure){//triangle in circle
		bool result = true;
		for (int i = 0; i < 3; i++){
			if (!((points[i].X() - figure.getCenter().X())*(points[i].X() - figure.getCenter().X()) + 
				(points[i].Y() - figure.getCenter().Y())*(points[i].Y() - figure.getCenter().Y()) 
				< figure.getRadious()*figure.getRadious())){
				result = false;
				break;
			}
		}
		return result;
	}
	bool inR(Figure& figure){//triangle in rectangle
		bool result = true;
		for (int i = 0; i < 3; i++){
			if (!(points[i].pointInR(figure.p(3), figure.p(2)))){
				result = false;
				break;
			}
		}
		return result;
	}
	
};

class Circle : public Figure
{
public:
	virtual Point p(int n)const {
		return NULL;
	}

	virtual bool isIn(Figure& figure){
		if (!strcmp(figure.type(), "rectangle")){
			return inR(figure);
		}
		if (!strcmp(figure.type(), "triangle")){
			return inTr(figure);
		}
		if (!strcmp(figure.type(), "circle")){
			return inC(figure);
		}
	}
	
	Circle(Point point, double r) :radius(r), Figure(point)
	{}
	Circle(const Circle&other) :Figure(other), radius(other.radius){}
	Circle& operator=(const Circle& other){
		if (this != &other){
			Figure::operator=(other);
			this->radius = other.radius;
			
		}
		return *this;
	}
	virtual double getRadious()const{
		return radius;
	}
	virtual char* type()const {
		return "circle";
	}
	virtual Point getCenter()const {
		return point;
	}

	virtual void print() const
	{
		Figure::print();
		cout << "Radius: " << radius << endl;
	}

	double perimeter() const
	{
		return 2 * PI*radius;
	}

	double surface() const
	{
		return PI*radius*radius;
	}
	virtual bool operator==(const Figure& other){
		if (strcmp(other.type(), "circle")){
			return false;
		}
		return radius == other.getRadious();
		//tova e samo za radius ,ako trqbva da sa napulno ednakvi da se dobavi i && point==other.getCenter()
	}

private:
	double radius;

	bool inC(Figure& figure){//circle in circle
		return getCenter().distanceTo(figure.getCenter()) <= radius;
	}
	bool inTr(Figure& figure){//circle in triangle
		if (abs(((figure.p(1).Y() - figure.p(0).Y())*getCenter().X() +
			(figure.p(0).X() - figure.p(1).X())*getCenter().Y())
			/ sqrt((figure.p(1).Y() - figure.p(0).Y())*(figure.p(1).Y() - figure.p(0).Y())
			+ (figure.p(0).X() - figure.p(1).X())*(figure.p(0).X() - figure.p(1).X()))) > radius){
			return false;
		}
		if (abs(((figure.p(2).Y() - figure.p(1).Y())*getCenter().X() +
			(figure.p(1).X() - figure.p(2).X())*getCenter().Y())
			/ sqrt((figure.p(2).Y() - figure.p(1).Y())*(figure.p(2).Y() - figure.p(1).Y())
			+ (figure.p(1).X() - figure.p(2).X())*(figure.p(1).X() - figure.p(2).X()))) > radius){
			return false;
		}
		if (abs(((figure.p(0).Y() - figure.p(2).Y())*getCenter().X() +
			(figure.p(2).X() - figure.p(0).X())*getCenter().Y())
			/ sqrt((figure.p(0).Y() - figure.p(2).Y())*(figure.p(0).Y() - figure.p(2).Y())
			+ (figure.p(2).X() - figure.p(0).X())*(figure.p(2).X() - figure.p(0).X()))) > radius){
			return false;
		}
		return true;

	}
	bool inR(Figure& figure){//circle in rectangle
		if ((((figure.p(1).Y() - figure.p(0).Y())*getCenter().X() +
			(figure.p(0).X() - figure.p(1).X())*getCenter().Y())
			/ sqrt((figure.p(1).Y() - figure.p(0).Y())*(figure.p(1).Y() - figure.p(0).Y())
			+ (figure.p(0).X() - figure.p(1).X())*(figure.p(0).X() - figure.p(1).X()))) > radius){
			return false;
		}
		if ((((figure.p(2).Y() - figure.p(1).Y())*getCenter().X() +
			(figure.p(1).X() - figure.p(2).X())*getCenter().Y())
			/ sqrt((figure.p(2).Y() - figure.p(1).Y())*(figure.p(2).Y() - figure.p(1).Y())
			+ (figure.p(1).X() - figure.p(2).X())*(figure.p(1).X() - figure.p(2).X()))) > radius){
			return false;
		}
		if ((((figure.p(0).Y() - figure.p(3).Y())*getCenter().X() +
			(figure.p(3).X() - figure.p(0).X())*getCenter().Y())
			/ sqrt((figure.p(0).Y() - figure.p(3).Y())*(figure.p(0).Y() - figure.p(3).Y())
			+ (figure.p(3).X() - figure.p(0).X())*(figure.p(3).X() - figure.p(0).X()))) > radius){
			return false;
		}
		if ((((figure.p(3).Y() - figure.p(2).Y())*getCenter().X() +
			(figure.p(2).X() - figure.p(3).X())*getCenter().Y())
			/ sqrt((figure.p(3).Y() - figure.p(2).Y())*(figure.p(3).Y() - figure.p(2).Y())
			+ (figure.p(2).X() - figure.p(3).X())*(figure.p(2).X() - figure.p(3).X()))) > radius){
			return false;
		}
		return true;

	}
};



class Rectangle : public Figure
{
public:
	virtual Point p(int n)const {
		if (n == 0){
			return points[0];
		}
		else if (n == 1){
			return points[1];
		}
		else if (n == 2){
			return points[2];
		}
		else if (n == 3){
			return points[3];
		}
	}
	virtual bool isIn(Figure& figure){
		if (!strcmp(figure.type(), "rectangle")){
			return inR(figure);
		}
		if (!strcmp(figure.type(), "triangle")){
			return inTr(figure);
		}
		if (!strcmp(figure.type(), "circle")){
			return inC(figure);
		}
	}
	

	virtual bool operator==(const Figure& other){
		if (strcmp(other.type(), "rectangle")){
			return false;
		}
		return points[0] == other.p(0) && points[1] == other.p(1) &&
			points[2] == other.p(2) && points[3] == other.p(2);
	}
	virtual Point getCenter()const {
		Point center((points[0].X() + points[2].X()) / 2, (points[0].Y() + points[2].Y()) / 2);
		return center;
	}

	Rectangle(Point points[4]) :Figure()
	{
		if (points[0].distanceTo(points[1]) == points[2].distanceTo(points[3]) &&
			points[1].distanceTo(points[2]) == points[3].distanceTo(points[0])){
			for (int i = 0; i < 4; i++){
				this->points[i] = points[i];
			}
			this->point = Rectangle::getCenter();
		}
	};
	virtual char* type()const {
		return "rectangle";
	}
	Rectangle(const Rectangle& other) :Figure(other){
		for (int i = 0; i < 4; i++){
			this->points[i] = other.points[i];
		}
	}
	Rectangle& operator=(const Rectangle& other){
		if (this != &other){
			Figure::operator=(other);
			for (int i = 0; i < 4; i++){
				this->points[i] = other.points[i];
			}
		}
		return *this;
	}

	virtual void print() const
	{
		Figure::print();
		cout << "Point A: " << points[0].X() << "," << points[0].Y() << endl
			<< "Point B: " << points[1].X() << "," << points[1].Y() << endl
			<< "Point C: " << points[2].X() << "," << points[2].Y() << endl
			<< "Point D: " << points[3].X() << "," << points[3].Y() << endl;
	}

	double perimeter() const
	{
		return points[1].distanceTo(points[0]) + points[2].distanceTo(points[1])
			+ points[3].distanceTo(points[2]) + points[0].distanceTo(points[3]);
	}

	double surface() const
	{
		return  points[1].distanceTo(points[0]) * points[2].distanceTo(points[1]);
	}
	virtual double getRadious()const{
		return 0;
	}

private:
	Point points[4];

	bool inTr(Figure& figure){//rectangle in triangle
		bool result = true;
		for (int i = 0; i < 4; i++){
			if (!points[i].pointInT(figure.p(0), figure.p(1), figure.p(2))){
				result = false;
				break;
			}
		}
		return result;
	}
	bool inC(Figure& figure){//rectangle in circle
		bool result = true;
		for (int i = 0; i < 4; i++){
			if (!((points[i].X() - figure.getCenter().X())*(points[i].X() - figure.getCenter().X())
				+ (points[i].Y() - figure.getCenter().Y())*(points[i].Y() - figure.getCenter().Y())
				< figure.getRadious()*figure.getRadious())){
				result = false;
				break;
			}
		}
		return result;
	}
	bool inR(Figure& figure){//rectangle in other rectangle
		bool result = true;
		for (int i = 0; i < 4; i++){
			if (!points[i].pointInR(figure.p(3), figure.p(1))){
				result = false;
				break;
			}
		}
		return result;
	}


};

int main()
{
	Point A(1, 1);
	Point B(3, 1);
	Point C(3, 3);
	Point D(1, 3);
	Point O(2, 2);
	Point points[4];
	points[0] = A;
	points[1] = B;
	points[2] = C;
	points[3] = D;


	Rectangle r(points);
	cout << "rectangle:" << endl;
	r.print();


	Circle p(O, 5);
	cout << "circle:" << endl;
	p.print();


	cout << "Is the rectangle in the circle?" << endl;
	if (r.isIn(p)){
		cout << "Yes!!"<< endl;
	}
	else {
		cout << "No!!" << endl;
	}
	

	return 0;
}
