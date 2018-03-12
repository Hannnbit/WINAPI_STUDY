#include <Windows.h>
#include <TCHAR.H>
#include <stdlib.h>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS WndClass;

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;//프로시저 함수
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDC_ARROW);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("Window1");

	RegisterClass(&WndClass);

	hwnd = CreateWindow(_T("Window1"), _T("Window Title Name"), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		CW_USEDEFAULT, CW_USEDEFAULT, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return  (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	static TCHAR str[2] = { 0, 0 };
	static TCHAR* Rstr = NULL;
	static int cnt = 0;

	switch (iMsg)
	{
	case WM_CREATE:
		cnt = 0;
		Rstr = (TCHAR*)calloc(lstrlen(str), sizeof(TCHAR));
		Rstr[0] = NULL;
		break;

	case WM_PAINT://without this case structure, when I make my window minimize than the string which I had wrote erased....
		hdc = BeginPaint(hwnd, &ps);
		TextOut(hdc, 100, 100, Rstr, lstrlen(Rstr));//_tcslen(Rstr));
		EndPaint(hwnd, &ps);
		break;

	case WM_CHAR:
		hdc = GetDC(hwnd);
		Rstr[cnt++] = wParam;
		Rstr[cnt] = NULL;

		TextOut(hdc, 100, 100, Rstr, lstrlen(Rstr));
		ReleaseDC(hwnd, hdc);

		Rstr = (WCHAR*)realloc(Rstr, lstrlen(Rstr) * sizeof(TCHAR) + sizeof(TCHAR));
		break;


	case WM_DESTROY:
		free(Rstr);
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}