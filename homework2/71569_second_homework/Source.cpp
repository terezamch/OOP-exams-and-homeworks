#include <iostream>
#include <cstring>
#include "Triangle.cpp"
#include "Circle.cpp"
#include "Rectangle.cpp"

using namespace std;



bool isCircleInCircle(Circle& circ1, Circle& circ2) 
{
	if(!circ2.isPointInsideFigure(circ1.getCenter()))
		return false;
		
	if(!circ1.isPointInsideFigure(circ2.getCenter()))
		return false;
		
		
	Point OA(circ1.getCenter().x, circ1.getCenter().y + circ1.getRadius());
	Point OB (circ1.getCenter().x + circ1.getRadius(), circ1.getCenter().y);
	Point OC(circ1.getCenter().x, circ1.getCenter().y - circ1.getRadius());
	Point OD(circ1.getCenter().x - circ1.getRadius(), circ1.getCenter().y);

	if(circ2.isPointInsideFigure(OA) && circ2.isPointInsideFigure(OB) && circ2.isPointInsideFigure(OC) && circ2.isPointInsideFigure(OD))
		return true;
				
	
	Point OA2(circ2.getCenter().x, circ2.getCenter().y + circ2.getRadius());
	Point OB2(circ2.getCenter().x + circ2.getRadius(), circ2.getCenter().y);
	Point OC2(circ2.getCenter().x, circ2.getCenter().y - circ2.getRadius());
	Point OD2(circ2.getCenter().x - circ2.getRadius(), circ2.getCenter().y);
	
	
	
	if(circ1.isPointInsideFigure(OA2) && circ1.isPointInsideFigure(OB2) && circ1.isPointInsideFigure(OC2) && circ1.isPointInsideFigure(OD2))
		return true;
		
	return false;
		
		
}


bool isTriangleInTriangle(Triangle& trig1, Triangle& trig2) 
{
	if(trig1.isPointInsideFigure(trig2.getFstEdge()) && trig1.isPointInsideFigure(trig2.getSndEdge()) && trig1.isPointInsideFigure(trig2.getThrdEdge()))
		return true;
		
	if(trig2.isPointInsideFigure(trig1.getFstEdge()) && trig2.isPointInsideFigure(trig1.getSndEdge()) && trig2.isPointInsideFigure(trig1.getThrdEdge()))
		return true;
		
	return false;
}

bool isRectangleInRectangle(Rectangle& rect1, Rectangle& rect2)
{
	
	Point Br(rect2.getBottomCorner().x, rect2.getUpperCorner().y);
	Point Dr(rect2.getUpperCorner().x, rect2.getBottomCorner().y);
	
	
	if(rect1.isPointInsideFigure(rect2.getUpperCorner()) && rect1.isPointInsideFigure(rect2.getBottomCorner()) && rect1.isPointInsideFigure(Br) && rect1.isPointInsideFigure(Dr))
		return true;
		
		
	Point B(rect1.getBottomCorner().x, rect1.getUpperCorner().y);
	Point D(rect1.getUpperCorner().x, rect1.getBottomCorner().y);
	
	if(rect2.isPointInsideFigure(rect1.getUpperCorner()) && rect2.isPointInsideFigure(rect1.getBottomCorner()) && rect2.isPointInsideFigure(B) && rect2.isPointInsideFigure(D))
		return true;
		
	return false;
}


bool isCircleInTriangle(Circle& circ, Triangle& trig) 
{
	if(!trig.isPointInsideFigure(circ.getCenter()))
		return false;
		
	Point O(circ.getCenter());
	Point OA(circ.getCenter().x, circ.getCenter().y + circ.getRadius());
	Point OB (circ.getCenter().x + circ.getRadius(), circ.getCenter().y);
	Point OC(circ.getCenter().x, circ.getCenter().y - circ.getRadius());
	Point OD(circ.getCenter().x - circ.getRadius(), circ.getCenter().y);

	if(trig.isPointInsideFigure(OA) && trig.isPointInsideFigure(OB) && trig.isPointInsideFigure(OC) && trig.isPointInsideFigure(OD))
		return true;

	return false;
	
}


bool isRectangleInTriangle(Rectangle& rect, Triangle& trig) 
{
	
	Point Br(rect.getBottomCorner().x, rect.getUpperCorner().y);
	Point Dr(rect.getUpperCorner().x, rect.getBottomCorner().y);


	if(trig.isPointInsideFigure(rect.getUpperCorner()) && trig.isPointInsideFigure(Br) && trig.isPointInsideFigure(rect.getBottomCorner()) && trig.isPointInsideFigure(Dr))
		return true;
		
	return false;
	
}


bool isCircleInRectangle(Circle& circ, Rectangle& rect) 
{
	
	Point O(circ.getCenter());
	Point OA(circ.getCenter().x, circ.getCenter().y + circ.getRadius());
	Point OB (circ.getCenter().x + circ.getRadius(), circ.getCenter().y);
	Point OC(circ.getCenter().x, circ.getCenter().y - circ.getRadius());
	Point OD(circ.getCenter().x - circ.getRadius(), circ.getCenter().y);
	
	
	if(rect.isPointInsideFigure(OA) && rect.isPointInsideFigure(OB) && rect.isPointInsideFigure(OC) && rect.isPointInsideFigure(OD))
		return true;


	return false;
}

bool isTriangleInRectangle(Triangle& trig, Rectangle& rect) 
{
	
	if(rect.isPointInsideFigure(trig.getFstEdge()) && rect.isPointInsideFigure(trig.getSndEdge()) && rect.isPointInsideFigure(trig.getThrdEdge()))
		return true;

	return false;
}

bool isRectangleInCircle(Rectangle& rect, Circle& circ) 
{
	
	Point Br(rect.getBottomCorner().x, rect.getUpperCorner().y);
	Point Dr(rect.getUpperCorner().x, rect.getBottomCorner().y);


	if(circ.isPointInsideFigure(rect.getUpperCorner()) && circ.isPointInsideFigure(Br) && circ.isPointInsideFigure(rect.getBottomCorner()) && circ.isPointInsideFigure(Dr))
		return true;
		
	return false;
	
}


bool isTriangleInCircle(Triangle& trig, Circle& circ) 
{
	if(circ.isPointInsideFigure(trig.getFstEdge()) && circ.isPointInsideFigure(trig.getSndEdge()) && circ.isPointInsideFigure(trig.getThrdEdge()))
		return true;

	return false;
}


void compareFigures(Triangle* trig1, Triangle* trig2)
{
	if(isTriangleInTriangle(*trig1, *trig2))
	{
		cout << "Triangle is in triangle!" << endl;
	}
		
	
}

void compareFigures(Rectangle* rect1, Rectangle* rect2)
{
	if(isRectangleInRectangle(*rect1, *rect2))
	{
		cout << "Rectangle is in rectangle!" << endl;
	}
		
	
}


void compareFigures(Circle* circ1, Circle* circ2)
{
	if(isCircleInCircle(*circ1, *circ2))
	{
		cout << "Circle is in circle!" << endl;
	}
		
	
}



void compareFigures(Triangle* trig, Rectangle* rect) 
{

		
			if(isTriangleInRectangle(*trig, *rect))
			{
				cout <<"Triangle is in rectangle!" <<endl;
				return;
			}
		
	
			if(isRectangleInTriangle(*rect, *trig))
			{
				cout <<"Rectangle is in triangle!" <<endl;
				return;
			}
			
	
}


void compareFigures(Triangle* trig, Circle* circ) 
{

			if(isTriangleInCircle(*trig, *circ))
			{
				cout <<"Triangle is in circle!" <<endl;
				return;
			}
		
	
			if(isCircleInTriangle(*circ, *trig))
			{
				cout <<"Circle is in triangle!" <<endl;
				return;
			}
			
	
}

void compareFigures(Rectangle* rect, Circle* circ) 
{

			if(isRectangleInCircle(*rect, *circ))
			{
				cout <<"Rectangle is in circle!" <<endl;
				return;
			}
		
	
			if(isCircleInRectangle(*circ, *rect))
			{
				cout <<"Circle is rectangle!" <<endl;
				return;
			}
}

void compareShit(Figure* fig1, Figure* fig2)
{
	
	if(!strcmp(fig1->getType(),"triangle"))
	{
		if(!strcmp(fig2->getType(),"rectangle"))
		{
			compareFigures((static_cast<Triangle*>(fig1)),(static_cast<Rectangle*>(fig2)));
		}
		else if(!strcmp(fig2->getType(),"triangle"))
		{
			compareFigures(static_cast<Triangle*>(fig1),(static_cast<Triangle*>(fig2)));
		}
		else if(!strcmp(fig2->getType(),"circle"))
		{
			compareFigures((static_cast<Triangle*>(fig1)),(static_cast<Circle*>(fig2)));
		}
		
	}
	
	if(!strcmp(fig1->getType(),"circle"))
	{
		if(!strcmp(fig2->getType(),"rectangle"))
		{
			compareFigures((static_cast<Rectangle*>(fig1)),(static_cast<Circle*>(fig2)));
		}
		else if(!strcmp(fig2->getType(),"triangle"))
		{
			compareFigures((static_cast<Triangle*>(fig1)),(static_cast<Circle*>(fig2)));
		}
		else if(!strcmp(fig2->getType(),"circle"))
		{
			compareFigures((static_cast<Circle*>(fig1)),(static_cast<Circle*>(fig2)));
		}
		
	}
	
	if(!strcmp(fig1->getType(),"rectangle"))
	{
		if(!strcmp(fig2->getType(),"rectangle"))	
		{
			compareFigures((static_cast<Rectangle*>(fig1)),(static_cast<Rectangle*>(fig2)));
		}
		else if(!strcmp(fig2->getType(),"triangle"))	
		{
			compareFigures((static_cast<Triangle*>(fig1)),(static_cast<Rectangle*>(fig2)));
		}
		else if(!strcmp(fig2->getType(),"circle"))
		{
			compareFigures((static_cast<Rectangle*>(fig1)),(static_cast<Circle*>(fig2)));
		}
		
	}
			
}


int main(){

	Point A(3,2);
	Point C(10, 0);
	
	Point At(1,1);
	Point Bt(5,2);
	Point Ct(3,4);
	
	Triangle trig(At, Bt, Ct);
	Rectangle rect(A, C);
	Circle circ(A, 0.1);
	
	Figure* tri = &trig;
	Figure* ci = &circ;
	Figure* re = &rect;
	

	

	
	compareShit(tri, ci);
	
	

	return 0;
}
