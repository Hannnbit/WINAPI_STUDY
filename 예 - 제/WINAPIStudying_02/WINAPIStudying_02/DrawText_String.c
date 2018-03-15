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
	HDC hdc;//ȭ�� �Է��� ����޴� Ű��.
	PAINTSTRUCT ps;//��� ������ �޾ƿ´�.
	RECT rt = { 0,0,1000,1000 };//���ڿ��� �� �簢�� �ȿ����� ��µȴ�..... �Ѱ踦 �غ��غ���..
	static int cnt = 0;//�迭�� ���� ������
	static TCHAR str[10000] = { 0 };//���ڰ� ���� ����� �迭
	static SIZE size;//ĳ���� ����� ��ġ�� ���ϱ� ���� ���ڿ��� x,y���̸� �̾ƿ� ������ ����ü�̴�.


	switch (iMsg)
	{
	case WM_CREATE://�����찡 ���������
		CreateCaret(hwnd, NULL, 5, 15);//2��° ���ڰ��� ��Ʈ���� ���ΰ�, 3,4,��°�� ĳ���� x,y ���̴�.
		ShowCaret(hwnd);//hwnd�� ������ �ڵ��̴�.
		break;

	case WM_PAINT://�����찡 ȭ�鿡 ��µɶ�, �ٸ� �����쿡 ���ȴٰ� ��µ� ���� �����̴�.
		hdc = BeginPaint(hwnd, &ps);//ps�� ��¿���(����̽� ���ؽ�Ʈ)������ �����԰� ���ÿ� hdc��, �� ���� ��й�ȣ ���� ���´�.
		GetTextExtentPoint(hdc, str, _tcslen(str), &size);//���ڿ��� ���� ���� �ȼ� ���̸� �˾Ƴ� size ����ü�� ��´�.
		TextOut(hdc, 0, 0, str, _tcslen(str));//0,0�ȼ����� ���ڿ� ���
		SetCaretPos(size.cx, 0);
		EndPaint(hwnd, &ps);//�ٽ� �� ps ���� ��ȯ�Ѵ�.
		break;

	case WM_CHAR://ASCII�ڵ� �� ���� ���ڰ� �Էµɶ�(����Ű ����)
		if (wParam == VK_BACK && cnt > 0)//�� �����̽��� �ԷµǸ� �����ش�.
		{
			cnt--;
		}
		else//�׷��� �ʴٸ� ���ڿ��� wParam�� ����ǿ� ���ڸ� �־��ش�.
		{
			str[cnt++] = wParam;
		}
		str[cnt] = NULL;//NULL���ڸ� ���ڰ� �Էµ� �������� ���� ������ �־� ���ڿ��� �������� ǥ�����ش�.
		InvalidateRgn(hwnd, NULL, TRUE);//WM_PAINT�� �߻���Ű�� 3���� ������ ���� True��� ȭ�� ��ü�� �ٽñ׸���, False��� ������ �κи� �ٽ� �׸���.

		break;


	case WM_DESTROY://�������찡 ����ɋ�..
		HideCaret(hwnd);//ĳ�� �����
		DestroyCaret();//ĳ�� �ı�
		PostQuitMessage(0);//WinMain�� GetMessage�Լ��� ��ȯ���� 0���� ����� ������.
		break;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);//�츮�� Switch-case������ ó������ ���� ������ ������ Ŀ���� ó�����ش�.
}