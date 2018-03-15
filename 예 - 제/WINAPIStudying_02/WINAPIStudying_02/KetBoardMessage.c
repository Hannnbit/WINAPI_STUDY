#include <Windows.h>
#include <TCHAR.H>

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

	switch (iMsg)
	{
	case WM_CREATE:
		break;


	case WM_CHAR://아스키 코드가 인식하는데 까지.
		hdc = GetDC(hwnd);
		TextOut(hdc, 100, 100, _T("CHAR"), _tcslen(_T("CHAR")));
		ReleaseDC(hwnd, hdc);
		break;

	case WM_KEYDOWN://모든 키
		hdc = GetDC(hwnd);
		TextOut(hdc, 200, 100, _T("KEYDOWN"), _tcslen(_T("KEYDOWN")));
		ReleaseDC(hwnd, hdc);
		break;

	case WM_KEYUP:
		hdc = GetDC(hwnd);
		TextOut(hdc, 300, 100, _T("KEYUP"), _tcslen(_T("KEYUP")));
		ReleaseDC(hwnd, hdc);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}