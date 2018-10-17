#pragma once
#include "stdafx.h"
#include "SimplePaint.h"
#include <windowsx.h>
#include <vector>

using namespace std;

class Point
{
private:
	int x;
	int y;

public:
	Point() { x = 0; y = 0; }
	~Point() { };
	Point(int iX, int iY) { x = iX, y = iY; }
	Point& operator=(const Point &iX) { x = iX.x; y = iX.y; return *this; }
	int getX() { return x; }
	int getY() { return y; }
};

class Figure
{
public:
	Figure() {};
	virtual void onDraw(PAINTSTRUCT ps, HDC hdc) = 0;
};

class Line : public Figure
{
private:

	Point startingPoint;
	Point endingPoint;

public:
	static int ID;
	Line() { startingPoint = Point();  endingPoint = Point(); }
	~Line() {};
	Line(const Point &A, const Point &B) { startingPoint = A; endingPoint = B; };
	void onDraw(PAINTSTRUCT ps, HDC hdc);
};

class cRectangle: public Figure
{
private:
	Point upper_leftPoint;
	Point lower_rightPoint;

public:
	static int ID;
	cRectangle();
	cRectangle(const Point & start, const Point & end);
	~cRectangle();
	void onDraw(PAINTSTRUCT ps,	HDC hdc);
};

class cEllipse: public Figure
{
private:
	Point upper_leftPoint;
	Point lower_rightPoint;

public:
	static int ID;
	cEllipse();
	cEllipse(const Point & start, const Point & end);
	~cEllipse() {};
	void onDraw(PAINTSTRUCT ps, HDC hdc);
};

class ArrayFigs
{
	static vector<Figure*> arrayFigs;
public:
	int getSize() { return arrayFigs.size(); };
	void addFigs(Figure* figs);
	void onDraw(PAINTSTRUCT ps, HDC hdc);
};