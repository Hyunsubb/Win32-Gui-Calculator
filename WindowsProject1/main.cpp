#include <windows.h>
#include <stdio.h>
#include "define.h"
#include "resource.h"
#include "convert.h"


LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
HINSTANCE g_hInst;
LPCTSTR IpszClass = TEXT("Calculator");


int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR IpszCmdParam, int nCmdShow)
{
	HWND hWnd;
	MSG Message;
	WNDCLASS WndClass;
	g_hInst = hInstance;

	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hbrBackground = CreateSolidBrush(RGB(255, 255, 255));
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hIcon = LoadIcon(NULL, NULL);
	WndClass.hInstance = hInstance;
	WndClass.lpfnWndProc = WndProc;
	WndClass.lpszClassName = IpszClass;
	WndClass.lpszMenuName = IpszClass;
	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	RegisterClass(&WndClass);

	hWnd = CreateWindow(IpszClass, IpszClass, WS_OVERLAPPEDWINDOW, CW_USEDEFAULT,
		CW_USEDEFAULT, 380, 590, NULL, (HMENU)NULL, hInstance, NULL);
	ShowWindow(hWnd, nCmdShow);

	while (GetMessage(&Message, NULL, 0, 0)) {
			TranslateMessage(&Message);
			DispatchMessage(&Message);
	}
	return (int)Message.wParam;
}

bool CALLBACK SetFont(HWND Child, LPARAM font) {
	SendMessage(Child, WM_SETFONT, font, TRUE);
	return true;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT iMessage, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;
	static RECT rtf = { 0,0,400,590 };
	TCHAR str[30] = L"Calculator";
	static TCHAR NumLine[128] = { NULL, };
	TCHAR ch[2] = { NULL, };
	static Convert convert;
	HFONT NewFont;
	HFONT OldFont;
	HFONT font;
	HBRUSH hbr;
	int sum = 0;

	switch (iMessage) {
	case WM_CREATE:
		font = CreateFont(35, 0, 0, 0, 600, 0, 0, 0, HANGEUL_CHARSET,
			0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("맑은 고딕"));


		CreateWindow(TEXT("static"), NumLine, WS_CHILD |
			WS_VISIBLE | SS_RIGHT, 15, 25, 335, 95, hWnd, (HMENU)ID_STATIC, g_hInst, NULL);

		CreateWindow(TEXT("Button"), TEXT("CE"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 29, 162, 70, 70, hWnd, (HMENU)0, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("C"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 107, 162, 70, 70, hWnd, (HMENU)ID_CLEAR, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("←"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 185, 162, 70, 70, hWnd, (HMENU)ID_REMOVE, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("%"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 263, 162, 70, 70, hWnd, (HMENU)ID_DIV, g_hInst, NULL);


		CreateWindow(TEXT("Button"), TEXT("7"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 29, 239, 70, 70, hWnd, (HMENU)ID_NUM_7, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("8"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 107, 239, 70, 70, hWnd, (HMENU)ID_NUM_8, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("9"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 185, 239, 70, 70, hWnd, (HMENU)ID_NUM_9, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("X"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 263, 239, 70, 70, hWnd, (HMENU)ID_MUF, g_hInst, NULL);


		CreateWindow(TEXT("Button"), TEXT("4"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 29, 316, 70, 70, hWnd, (HMENU)ID_NUM_4, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("5"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 107, 316, 70, 70, hWnd, (HMENU)ID_NUM_5, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("6"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 185, 316, 70, 70, hWnd, (HMENU)ID_NUM_6, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("-"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 263, 316, 70, 70, hWnd, (HMENU)ID_MINUS, g_hInst, NULL);


		CreateWindow(TEXT("Button"), TEXT("1"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 29, 393, 70, 70, hWnd, (HMENU)ID_NUM_1, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("2"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 107, 393, 70, 70, hWnd, (HMENU)ID_NUM_2, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("3"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 185, 393, 70, 70, hWnd, (HMENU)ID_NUM_3, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("+"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 263, 393, 70, 70, hWnd, (HMENU)ID_PLUS, g_hInst, NULL);


		CreateWindow(TEXT("Button"), TEXT("0"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 107, 470, 70, 70, hWnd, (HMENU)ID_NUM_0, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("."), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 185, 470, 70, 70, hWnd, (HMENU)1, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT("="), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 263, 470, 70, 70, hWnd, (HMENU)ID_RESULT, g_hInst, NULL);

		CreateWindow(TEXT("Button"), TEXT("("), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 29, 470, 34, 70, hWnd, (HMENU)ID_OPEN, g_hInst, NULL);
		CreateWindow(TEXT("Button"), TEXT(")"), WS_CHILD |
			WS_VISIBLE | BS_PUSHBUTTON, 65, 470, 34, 70, hWnd, (HMENU)ID_CLOSE, g_hInst, NULL);

		EnumChildWindows(hWnd, (WNDENUMPROC)SetFont, (LPARAM)font);

		return 0;

	case WM_COMMAND:
		switch (LOWORD(wParam)) {
		case ID_CLEAR:
			memset(NumLine, NULL, sizeof(NumLine));
			SetDlgItemText(hWnd, ID_STATIC, NumLine);
			break;
		case ID_NUM_0:
			ch[0] = '0';
			lstrcat(NumLine, ch);
			SetDlgItemText(hWnd, ID_STATIC, NumLine);
			break;
		case ID_NUM_1:
			ch[0] = '1';
			lstrcat(NumLine, ch);
			SetDlgItemText(hWnd, ID_STATIC, NumLine);
			break;
		case ID_NUM_2:
			ch[0] = '2';
			lstrcat(NumLine, ch);
			SetDlgItemText(hWnd, ID_STATIC, NumLine);
			break;
		case ID_NUM_3:
			ch[0] = '3';
			lstrcat(NumLine, ch);
			SetDlgItemText(hWnd, ID_STATIC, NumLine);
			break;
		case ID_NUM_4:
			ch[0] = '4';
			lstrcat(NumLine, ch);
			SetDlgItemText(hWnd, ID_STATIC, NumLine);
			break;
		case ID_NUM_5:
			ch[0] = '5';
			lstrcat(NumLine, ch);
			SetDlgItemText(hWnd, ID_STATIC, NumLine);
			break;
		case ID_NUM_6:
			ch[0] = '6';
			lstrcat(NumLine, ch);
			SetDlgItemText(hWnd, ID_STATIC, NumLine);
			break;
		case ID_NUM_7:
			ch[0] = '7';
			lstrcat(NumLine, ch);
			SetDlgItemText(hWnd, ID_STATIC, NumLine);
			break;
		case ID_NUM_8:
			ch[0] = '8';
			lstrcat(NumLine, ch);
			SetDlgItemText(hWnd, ID_STATIC, NumLine);
			break;
		case ID_NUM_9:
			ch[0] = '9';
			lstrcat(NumLine, ch);
			SetDlgItemText(hWnd, ID_STATIC, NumLine);
			break;
		case ID_PLUS:
			ch[0] = '+';
			lstrcat(NumLine, ch);
			SetDlgItemText(hWnd, ID_STATIC, NumLine);
			break;
		case ID_MINUS:
			ch[0] = '-';
			lstrcat(NumLine, ch);
			SetDlgItemText(hWnd, ID_STATIC, NumLine);
			break;
		case ID_DIV:
			ch[0] = '/';
			lstrcat(NumLine, ch);
			SetDlgItemText(hWnd, ID_STATIC, NumLine);
			break;
		case ID_MUF:
			ch[0] = '*';
			lstrcat(NumLine, ch);
			SetDlgItemText(hWnd, ID_STATIC, NumLine);
			break;
		case ID_OPEN:
			ch[0] = '(';
			lstrcat(NumLine, ch);
			SetDlgItemText(hWnd, ID_STATIC, NumLine);
			break;
		case ID_CLOSE:
			ch[0] = ')';
			lstrcat(NumLine, ch);
			SetDlgItemText(hWnd, ID_STATIC, NumLine);
			break;
		case ID_REMOVE:
			if (lstrlen(NumLine)) {
				NumLine[lstrlen(NumLine) - 1] = NULL;
				SetDlgItemText(hWnd, ID_STATIC, NumLine);
			}
			break;
		case ID_RESULT:
			convert.ConvToRPNExp(NumLine);
			sum = convert.EvalRPNExp(NumLine);
			wsprintf(str, L"%d", sum);
			SetDlgItemText(hWnd, ID_STATIC, str);
			break;
		}
		return 0;

	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		NewFont = CreateFont(25, 0, 0, 0, 600, 0, 0, 0, HANGEUL_CHARSET,
			0, 0, 0, VARIABLE_PITCH | FF_ROMAN, TEXT("Segoe UI"));
		hbr = CreateSolidBrush(RGB(230, 230, 240));
		FillRect(hdc, &rtf, hbr);
		OldFont = (HFONT)SelectObject(hdc, NewFont);
		SetBkColor(hdc, RGB(230, 230, 240));
		TextOut(hdc, 140, 128, str, lstrlen(str));
		SelectObject(hdc, OldFont);
		DeleteObject(NewFont);
		DeleteObject(hbr);
		EndPaint(hWnd, &ps);
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}
	return (DefWindowProc(hWnd, iMessage, wParam, lParam));
}