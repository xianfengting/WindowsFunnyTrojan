// WindowsFunnyTrojan.cpp : ����Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include "WindowsFunnyTrojan.h"

#define MAX_LOADSTRING 100

// ȫ�ֱ���: 
HINSTANCE hInst;								// ��ǰʵ��
TCHAR szTitle[MAX_LOADSTRING];					// �������ı�
TCHAR szWindowClass[MAX_LOADSTRING];			// ����������

// ϵͳͼ�ꡣ
HICON hIcons[] = {
	LoadIcon(NULL, IDI_ERROR),
	LoadIcon(NULL, IDI_WARNING),
	LoadIcon(NULL, IDI_QUESTION),
	LoadIcon(NULL, IDI_APPLICATION),
	LoadIcon(NULL, IDI_SHIELD),
	LoadIcon(NULL, IDI_ASTERISK),
	LoadIcon(NULL, IDI_EXCLAMATION),
	LoadIcon(NULL, IDI_INFORMATION),
	LoadIcon(NULL, IDI_WINLOGO)
};
// hIcons ��������
int hIconsCount = 9;
// �����ͼ�ꡣ
HICON jinKeLaHIcon;
// ��� x �� y ������ֵ��
int ix = GetSystemMetrics(SM_CXICON) / 2;
int iy = GetSystemMetrics(SM_CYICON) / 2;
// ����� HWND ��
HWND desktop = GetDesktopWindow();
// ����� HDC ��
HDC desktopHDc = GetWindowDC(desktop);
// ����� desktopRect ��
RECT desktopRect;
// ����Ŀ�
int desktopWidth;
// ����ĸߡ�
int desktopHeight;

// �˴���ģ���а����ĺ�����ǰ������: 
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);

void DoIconsDrawing(HINSTANCE hInstance)
{
	srand(time(NULL));
	{
		LONG tmp2 = desktopRect.top;
		do
		{
			LONG tmp = desktopRect.left;
			do
			{
				DrawIcon(desktopHDc, tmp, tmp2, jinKeLaHIcon);
				Sleep(1);
			} while ((tmp += 20) <= desktopRect.right);
		} while ((tmp2 += 20) <= desktopRect.bottom);
	}

	{
		HICON icon = LoadIcon(NULL, IDI_ERROR);
		//HICON icon2 = LoadIcon(NULL, IDI_SHIELD);
		HICON icon2 = hIcons[rand() % hIconsCount];

		// I want to use the IsWindows10OrGreater() function.
		// But here isn't the IsWindows10OrGreater() function.
		// So I use the IsWindows8Point1OrGreater() function.
		// Here may be some bugs, but I can't fix it.
		// If you can help me with the bugs, you can open a pull request to help me.
		// Thanks so much!
		if (IsWindows8Point1OrGreater())
		{
			if (rand() % 2)
			{
				icon2 = hIcons[rand() % hIconsCount];
			}
			else
			{
				icon2 = ExtractIcon(hInstance, _T("imageres.dll"), rand() % 412);
			}
		}
		else
		{
			icon2 = hIcons[rand() % hIconsCount];
		}

		for (LONG iconXOffset = 0; iconXOffset <= desktopWidth; iconXOffset += 30)
		{
			LONG iconX = 0, iconY = 0;
			do
			{
				DrawIcon(desktopHDc, iconX + iconXOffset, iconY, icon);
				Sleep(10);
				iconX += 10;
				iconY += 10;
			} while (((iconX + iconXOffset) <= desktopHeight) && (iconY <= desktopWidth));
		}
		for (LONG iconYOffset = 0; iconYOffset <= desktopWidth; iconYOffset += 30)
		{
			LONG iconX = 0, iconY = 0;
			do
			{
				DrawIcon(desktopHDc, iconX, iconY + iconYOffset, icon2);
				Sleep(10);
				iconX += 10;
				iconY += 10;
			} while ((iconX <= desktopHeight) && ((iconY + iconYOffset) <= desktopWidth));
		}
	}

	{
		HICON icon = LoadIcon(NULL, IDI_INFORMATION);
		LONG iconX = 0, iconY = 0;
		LONG tmp = desktopRect.left;
		do
		{
			DrawIcon(desktopHDc, tmp, desktopRect.top, icon);
			Sleep(50);
		} while ((tmp += 20) <= desktopRect.right);
		tmp = desktopRect.top;
		do
		{
			DrawIcon(desktopHDc, desktopRect.right, tmp, icon);
			Sleep(50);
		} while ((tmp += 20) <= desktopRect.bottom);
		tmp = desktopRect.right;
		do
		{
			DrawIcon(desktopHDc, tmp, desktopRect.bottom, icon);
			Sleep(50);
		} while ((tmp -= 20) >= desktopRect.left);
		tmp = desktopRect.bottom;
		do
		{
			DrawIcon(desktopHDc, desktopRect.left, tmp, icon);
			Sleep(50);
		} while ((tmp -= 20) >= desktopRect.top);
	}
}

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO:  �ڴ˷��ô��롣
	// ���ؽ����ͼ�ꡣ
	jinKeLaHIcon = ExtractIcon(hInstance, _T("JinKeLa.ico"), 0);
	// ��ʼ���������������
	srand(time(NULL));
	// ��ȡ������� desktopRect ��
	GetWindowRect(desktop, &desktopRect);
	// ��ȡ������Ŀ���ߡ�
	desktopWidth = desktopRect.right - desktopRect.left;
	desktopHeight = desktopRect.bottom - desktopRect.top;
	// ��ȡ������� HWND ��
	desktop = GetDesktopWindow();
	// ��ȡ������� HDC ��
	desktopHDc = GetWindowDC(desktop);

	DoIconsDrawing(hInstance);
	DoIconsDrawing(hInstance);

	return 0;

	MSG msg;
	HACCEL hAccelTable;

	// ��ʼ��ȫ���ַ���
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WINDOWSFUNNYTROJAN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// ִ��Ӧ�ó����ʼ��: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSFUNNYTROJAN));

	// ����Ϣѭ��: 
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	return (int) msg.wParam;
}



//
//  ����:  MyRegisterClass()
//
//  Ŀ��:  ע�ᴰ���ࡣ
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_WINDOWSFUNNYTROJAN));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_WINDOWSFUNNYTROJAN);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   ����:  InitInstance(HINSTANCE, int)
//
//   Ŀ��:  ����ʵ�����������������
//
//   ע��: 
//
//        �ڴ˺����У�������ȫ�ֱ����б���ʵ�������
//        ��������ʾ�����򴰿ڡ�
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // ��ʵ������洢��ȫ�ֱ�����

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  ����:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  Ŀ��:    ���������ڵ���Ϣ��
//
//  WM_COMMAND	- ����Ӧ�ó���˵�
//  WM_PAINT	- ����������
//  WM_DESTROY	- �����˳���Ϣ������
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// �����˵�ѡ��: 
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		// TODO:  �ڴ���������ͼ����...
		EndPaint(hWnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// �����ڡ������Ϣ�������
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
