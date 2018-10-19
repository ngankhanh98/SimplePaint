#pragma once
#include "stdafx.h"
#include "SimplePaint.h"
#include <windowsx.h>
#include <vector>

using namespace std;

#define ID_Line 3
#define ID_cRectangle 2
#define	ID_cEllipse 1

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
	virtual void onDraw(PAINTSTRUCT ps, HDC hdc) = 0;
};

class Line : public Figure
{
private:

	Point startingPoint;
	Point endingPoint;
	DWORD  rgbCurrent;
public:
	static int ID;
	Line() { rgbCurrent = RGB(255, 0, 0); startingPoint = Point();  endingPoint = Point(); }
	~Line() {};
	Line(const Point &A, const Point &B, DWORD  color) { startingPoint = A; endingPoint = B; rgbCurrent = color; };
	void onDraw(PAINTSTRUCT ps, HDC hdc);
};

class cRectangle: public Figure
{
private:
	Point startingPoint;
	Point endingPoint;
	DWORD  rgbCurrent;
public:
	static int ID;
	cRectangle();
	cRectangle(const Point & start, const Point & end, DWORD  color);
	~cRectangle();
	void onDraw(PAINTSTRUCT ps,	HDC hdc);
};

class cEllipse: public Figure
{
private:
	Point startingPoint;
	Point endingPoint;
	DWORD  rgbCurrent;
public:
	static int ID;
	cEllipse();
	cEllipse(const Point & start, const Point & end, DWORD  color);
	~cEllipse() {};
	void onDraw(PAINTSTRUCT ps, HDC hdc);
};

class ArrayFigs
{
	static vector<Figure*> arrayFigs;
public:
	void addFigs(Figure* figs);
	void onDraw(PAINTSTRUCT ps, HDC hdc);
};