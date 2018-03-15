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
	HDC hdc;//화면 입력을 허락받는 키값.
	PAINTSTRUCT ps;//출력 영역을 받아온다.
	RECT rt = { 0,0,1000,1000 };//문자열이 이 사각형 안에서만 출력된당..... 한계를 극복해보장..
	static int cnt = 0;//배열의 현재 포인터
	static TCHAR str[10000] = { 0 };//문자가 실제 저장될 배열
	static SIZE size;//캐럿을 출력할 위치를 구하기 위해 문자열의 x,y길이를 뽑아와 저장할 구조체이다.


	switch (iMsg)
	{
	case WM_CREATE://윈도우가 만들어질때
		CreateCaret(hwnd, NULL, 5, 15);//2번째 인자값은 비트맵의 여부고, 3,4,번째는 캐럿의 x,y 길이다.
		ShowCaret(hwnd);//hwnd는 윈도우 핸들이다.
		break;

	case WM_PAINT://윈도우가 화면에 출력될때, 다른 윈도우에 가렸다가 출력될 때도 포함이다.
		hdc = BeginPaint(hwnd, &ps);//ps에 출력영역(디바이스 콘텍스트)정보를 저장함과 동시에 hdc값, 즉 접근 비밀번호 값을 얻어온다.
		GetTextExtentPoint(hdc, str, _tcslen(str), &size);//문자열의 가로 세로 픽셀 길이를 알아내 size 구조체에 담는다.
		TextOut(hdc, 0, 0, str, _tcslen(str));//0,0픽셀부터 문자열 출력
		SetCaretPos(size.cx, 0);
		EndPaint(hwnd, &ps);//다시 그 ps 값을 반환한다.
		break;

	case WM_CHAR://ASCII코드 값 내의 문자가 입력될때(가상키 포함)
		if (wParam == VK_BACK && cnt > 0)//백 스페이스가 입력되면 지워준다.
		{
			cnt--;
		}
		else//그렇지 않다면 문자열에 wParam에 저장되온 문자를 넣어준다.
		{
			str[cnt++] = wParam;
		}
		str[cnt] = NULL;//NULL문자를 문자가 입력된 포인터의 다음 지점에 넣어 문자열의 마지막을 표시해준다.
		InvalidateRgn(hwnd, NULL, TRUE);//WM_PAINT를 발생시키며 3번쨰 인자의 값이 True라면 화면 전체를 다시그리고, False라면 수정한 부분만 다시 그린다.

		break;


	case WM_DESTROY://윈도도우가 종료될떄..
		HideCaret(hwnd);//캐럿 숨기기
		DestroyCaret();//캐럿 파괴
		PostQuitMessage(0);//WinMain의 GetMessage함수의 반환값을 0으로 만들어 버린다.
		break;
	}

	return DefWindowProc(hwnd, iMsg, wParam, lParam);//우리가 Switch-case문으로 처리하지 않은 나머지 값들을 커널이 처리해준다.
}