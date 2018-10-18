#include "stdafx.h"
#include "Figures.h"

using namespace std;

#define ID_Line 1
#define ID_cRectangle 2
#define	ID_cEllipse 3


//int Figure::ID = 0;
int Line::ID = ID_Line;
int cRectangle::ID = ID_cRectangle;
int cEllipse::ID = ID_cEllipse;
cRectangle::cRectangle()
{
	startingPoint = Point(0, 0);
	endingPoint = Point(0, 0);
}

cRectangle::cRectangle(const Point & start, const Point & end, DWORD  color)
{
	rgbCurrent = color;
	startingPoint = start;
	endingPoint = end;
}

cRectangle::~cRectangle()
{
}

void cRectangle::onDraw(PAINTSTRUCT ps, HDC hdc)
{
	if (this->startingPoint.getX() == -1)
		return;
	
	SetDCPenColor(hdc, rgbCurrent);
	SelectObject(hdc, GetStockObject(DC_PEN));
	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Rectangle(hdc, startingPoint.getX(), startingPoint.getY(), endingPoint.getX(), endingPoint.getY());
}

cEllipse::cEllipse()
{
	startingPoint = Point(0, 0);
	endingPoint = Point(0, 0);
}

cEllipse::cEllipse(const Point & start, const Point & end, DWORD  color)
{
	rgbCurrent = color;
	startingPoint = start;
	endingPoint = end;

}

void cEllipse::onDraw(PAINTSTRUCT ps, HDC hdc)
{
	if (this->startingPoint.getX() == -1)
		return;
	SetDCPenColor(hdc, rgbCurrent);
	SelectObject(hdc, GetStockObject(DC_PEN));
	SelectObject(hdc, GetStockObject(NULL_BRUSH));
	Ellipse(hdc, startingPoint.getX(), startingPoint.getY(), endingPoint.getX(), endingPoint.getY());
}

void Line::onDraw(PAINTSTRUCT ps, HDC hdc)
{

	if (this->startingPoint.getX() == -1)
		return;
	HPEN hPen = CreatePen(PS_DASHDOT, 3, rgbCurrent);
	SelectObject(hdc, hPen);
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
