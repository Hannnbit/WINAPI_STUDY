#include <Windows.h>
#include <TCHAR.H>

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpszCmdLine, int nCmdShow)
{
	HWND hwnd;
	MSG msg;
	WNDCLASS WndClass;

	WndClass.style = CS_HREDRAW | CS_VREDRAW;
	WndClass.lpfnWndProc = WndProc;//���ν��� �Լ�
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
	RECT �ҿ�;
	switch (iMsg)
	{
	case WM_CREATE://�����찡 ��������
		break;

	case WM_PAINT://�����찡 ȭ�鿡 ��Ÿ����....
		hdc = GetDC(hwnd);
		TextOut(hdc, 500,500, _T("test01"), _tcslen(_T("test01")));
		ReleaseDC(hwnd, hdc);

		�ҿ�.bottom = 200;
		�ҿ�.right = 200;
		�ҿ�.top = 100;
		�ҿ�.left = 9;

		hdc = BeginPaint(hwnd, &ps);
		DrawText(hdc, _T("���� 19���̴�."), _tcslen(_T("���� 19���̴�.")), &�ҿ�, DT_SINGLELINE|DT_CENTER);
		EndPaint(hwnd, &ps);
		break;
		
	case WM_DESTROY://�����찡 ������
		PostQuitMessage(0);
		break;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}