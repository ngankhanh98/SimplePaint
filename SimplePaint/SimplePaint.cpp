// SimplePaint.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "SimplePaint.h"
#include "resource.h"
#include <windowsx.h>
#include "Figures.h"
#include <commctrl.h>
#pragma comment(lib, "Comctl32.lib")
#include <commdlg.h>

#define MAX_LOADSTRING 100
#pragma comment(linker, \
    "\"/manifestdependency:type='Win32' "\
    "name='Microsoft.Windows.Common-Controls' "\
    "version='6.0.0.0' "\
    "processorArchitecture='*' "\
    "publicKeyToken='6595b64144ccf1df' "\
    "language='*'\"")

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name
HDC hdc;

CHOOSECOLOR  cc; // Thông tin màu chọn
COLORREF  acrCustClr[16]; // Mảng custom color
DWORD  rgbCurrent = RGB(0, 0, 0); // Black
HBRUSH  hbrush; // Tạo ra brush từ màu đã chọn
CHOOSEFONT  cf;
LOGFONT  lf;
HFONT  hfont, hfontPrev;
DWORD rgbPrev;

int typeOfFigure = ID_Line;
Point Start(-1, -1), End(-1, -1);
BOOL isPreview = true;


// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
BOOL				OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct);
void				OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify);
void				OnDestroy(HWND hwnd);
void				OnPaint(HWND hwnd);
void				OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags);
void				OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags);
void				OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags);


int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.

	// Initialize global strings
	LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadStringW(hInstance, IDC_SIMPLEPAINT, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance(hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_SIMPLEPAINT));

	MSG msg;

	// Main message loop:
	while (GetMessage(&msg, nullptr, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int)msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEXW wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_SIMPLEPAINT));
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName = MAKEINTRESOURCEW(IDC_SIMPLEPAINT);
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	hInst = hInstance; // Store instance handle in our global variable

	HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE: Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		HANDLE_MSG(hWnd, WM_CREATE, OnCreate);
		HANDLE_MSG(hWnd, WM_COMMAND, OnCommand);
		HANDLE_MSG(hWnd, WM_PAINT, OnPaint);
		HANDLE_MSG(hWnd, WM_DESTROY, OnDestroy);
		HANDLE_MSG(hWnd, WM_LBUTTONDOWN, OnLButtonDown);
		HANDLE_MSG(hWnd, WM_LBUTTONUP, OnLButtonUp);
		HANDLE_MSG(hWnd, WM_MOUSEMOVE, OnMouseMove);
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}

BOOL OnCreate(HWND hwnd, LPCREATESTRUCT lpCreateStruct)
{
	LOGFONT lf;
	GetObject(GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	HFONT hFont = CreateFont(lf.lfHeight, lf.lfWidth,
		lf.lfEscapement, lf.lfOrientation, lf.lfWeight,
		lf.lfItalic, lf.lfUnderline, lf.lfStrikeOut, lf.lfCharSet,
		lf.lfOutPrecision, lf.lfClipPrecision, lf.lfQuality,
		lf.lfPitchAndFamily, lf.lfFaceName);

	InitCommonControls();
	TBBUTTON tbButtons[] =
	{
		{ STD_FILENEW,	ID_FILE_NEW, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ STD_FILEOPEN,	ID_FILE_OPEN, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ STD_FILESAVE,	ID_FILE_SAVE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 }
	};
	HWND hToolBarWnd = CreateToolbarEx(hwnd,
		WS_CHILD | WS_VISIBLE | CCS_ADJUSTABLE | TBSTYLE_TOOLTIPS,
		ID_TOOLBAR, sizeof(tbButtons) / sizeof(TBBUTTON), HINST_COMMCTRL,
		0, tbButtons, sizeof(tbButtons) / sizeof(TBBUTTON),
		BUTTON_WIDTH, BUTTON_HEIGHT, IMAGE_WIDTH, IMAGE_HEIGHT,
		sizeof(TBBUTTON));
	TBBUTTON buttonsToAdd[] =
	{
		{ 0, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 }, // Nút phân cách
		{ STD_CUT,	ID_EDIT_CUT, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ STD_COPY,	ID_EDIT_COPY, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ STD_PASTE, ID_EDIT_PASTE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ STD_DELETE, ID_EDIT_DELETE, TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 }
	};
	SendMessage(hToolBarWnd, TB_ADDBUTTONS, (WPARAM) sizeof(buttonsToAdd) / sizeof(TBBUTTON),
		(LPARAM)(LPTBBUTTON)&buttonsToAdd);

	TBBUTTON userButtons[] =
	{
		{ 0, 0,	TBSTATE_ENABLED, TBSTYLE_SEP, 0, 0 },
		{ 0, ID_DRAW_ELLIPSE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ 1, ID_DRAW_RECTANGLE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ 2, ID_DRAW_LINE,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 },
		{ 3, ID_DRAW_TEXT,	TBSTATE_ENABLED, TBSTYLE_BUTTON, 0, 0 }
	};

	
	TBADDBITMAP tbBitmap[] = { { hInst, IDB_BITMAP1 }, { hInst, IDB_BITMAP2 }, { hInst, IDB_BITMAP3 }, { hInst, IDB_BITMAP4 } };
	// Thêm danh sách ảnh vào toolbar
	int i = 0;
	int idx = SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM) sizeof(tbBitmap[0]) / sizeof(TBADDBITMAP),
		(LPARAM)(LPTBADDBITMAP)&tbBitmap[0]);
	int size = sizeof(tbBitmap) / sizeof(TBADDBITMAP);
	do {
			SendMessage(hToolBarWnd, TB_ADDBITMAP, (WPARAM) sizeof(tbBitmap[i]) / sizeof(TBADDBITMAP),
			(LPARAM)(LPTBADDBITMAP)&tbBitmap[i]);
		userButtons[i].iBitmap += idx;
		i++;
	} while (i <= size);
	SendMessage(hToolBarWnd, TB_ADDBUTTONS, (WPARAM) sizeof(userButtons) / sizeof(TBBUTTON),
		(LPARAM)(LPTBBUTTON)&userButtons);

	return TRUE;
}

void OnCommand(HWND hwnd, int id, HWND hwndCtl, UINT codeNotify)
{
	switch (id) {
	case ID_CHOOSE_COLOR:
		ZeroMemory(&cc, sizeof(CHOOSECOLOR));
		cc.lStructSize = sizeof(CHOOSECOLOR);
		cc.hwndOwner = hwnd;
		cc.lpCustColors = (LPDWORD)acrCustClr;
		cc.rgbResult = rgbCurrent;
		cc.Flags = CC_FULLOPEN | CC_RGBINIT;
		if (ChooseColor(&cc))
		{
			hbrush = CreateSolidBrush(cc.rgbResult);
			rgbCurrent = cc.rgbResult;
		}
		break;
	case ID_CHOOSE_FONT:
		ZeroMemory(&cf, sizeof(CHOOSEFONT));
		cf.lStructSize = sizeof(CHOOSEFONT);
		cf.hwndOwner = hwnd;
		cf.lpLogFont = &lf;
		cf.Flags = CF_SCREENFONTS | CF_EFFECTS;

		if (ChooseFont(&cf) == TRUE)
		{
			hfont = CreateFontIndirect(cf.lpLogFont);
			SelectObject(hdc, hfont);
			rgbCurrent = cf.rgbColors;
			rgbPrev = SetTextColor(hdc, rgbCurrent);
		}
		break;
	case ID_DRAW_ELLIPSE:
		typeOfFigure = ID_cEllipse; break;
	case ID_DRAW_RECTANGLE:
		typeOfFigure = ID_cRectangle; break;
	case ID_DRAW_LINE:
		typeOfFigure = ID_Line; break; 
	}
}

void OnDestroy(HWND hwnd)
{
	PostQuitMessage(0);
}
void OnPaint(HWND hwnd)
{
	PAINTSTRUCT ps;
	hdc = BeginPaint(hwnd, &ps);

	ArrayFigs addedFigs;	
	if (ID_cEllipse == typeOfFigure)
	{
		Figure* figs = new cEllipse(Start, End, rgbCurrent);

		if (isPreview)
			figs->onDraw(ps, hdc);
		else
			addedFigs.addFigs(figs);
	}

	if (ID_cRectangle == typeOfFigure)
	{
		Figure* figs = new cRectangle(Start, End, rgbCurrent);

		if (isPreview)
			figs->onDraw(ps, hdc);
		else
			addedFigs.addFigs(figs);

	}

	if (ID_Line == typeOfFigure)
	{
		Figure* figs = new Line(Start, End, rgbCurrent);

		if (isPreview)
			figs->onDraw(ps, hdc);
		else
			addedFigs.addFigs(figs);
	}

	addedFigs.onDraw(ps, hdc);
	EndPaint(hwnd, &ps);
}

void OnLButtonDown(HWND hwnd, BOOL fDoubleClick, int x, int y, UINT keyFlags)
{
	isPreview = true;
	Start = Point(x, y);
}

void OnLButtonUp(HWND hwnd, int x, int y, UINT keyFlags)
{
	isPreview = false;
	End = Point(x, y);
	InvalidateRect(hwnd, NULL, TRUE);
}

void OnMouseMove(HWND hwnd, int x, int y, UINT keyFlags)
{
	if (isPreview) {
		End = Point(x, y);
		// Báo hiệu cần xóa đi toàn bộ màn hình
		InvalidateRect(hwnd, NULL, TRUE);
	}
}
