#include "stdafx.h"
#include "Figures.h"

using namespace std;

int Line::ID = 0;
int cRectangle::ID = 1;
int cEllipse::ID = 2;
cRectangle::cRectangle()
{
	upper_leftPoint = Point(0, 0);
	lower_rightPoint = Point(0, 0);
}

cRectangle::cRectangle(const Point & start, const Point & end)
{
	upper_leftPoint = start;
	lower_rightPoint = end;
}

cRectangle::~cRectangle()
{
}

void cRectangle::onDraw(PAINTSTRUCT ps, HDC hdc)
{
	Rectangle(hdc, upper_leftPoint.getX(), upper_leftPoint.getY(), lower_rightPoint.getX(), lower_rightPoint.getY());
}

cEllipse::cEllipse()
{
	upper_leftPoint = Point(0, 0);
	lower_rightPoint = Point(0, 0);
}

cEllipse::cEllipse(const Point & start, const Point & end)
{
	upper_leftPoint = start;
	lower_rightPoint = end;

}

void cEllipse::onDraw(PAINTSTRUCT ps, HDC hdc)
{
	Ellipse(hdc, upper_leftPoint.getX(), upper_leftPoint.getY(), lower_rightPoint.getX(), lower_rightPoint.getY());
}

void Line::onDraw(PAINTSTRUCT ps, HDC hdc)
{
	MoveToEx(hdc, startingPoint.getX(), startingPoint.getY(), NULL);
	LineTo(hdc, endingPoint.getX(), endingPoint.getY());
}

vector<Figure*> ArrayFigs::arrayFigs;	// init static attribute of ArrayyFigs

void ArrayFigs::addFigs(Figure * figs)
{
	arrayFigs.push_back(figs);
}

void ArrayFigs::onDraw(PAINTSTRUCT ps, HDC hdc)
{
	for (int i = 0; i < arrayFigs.size(); i++)
	{
		arrayFigs[i]->onDraw(ps, hdc);
	}
}
