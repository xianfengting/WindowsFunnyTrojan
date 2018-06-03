// WindowsFunnyTrojan.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "WindowsFunnyTrojan.h"

#define MAX_LOADSTRING 100

// 全局变量: 
HINSTANCE hInst;								// 当前实例
TCHAR szTitle[MAX_LOADSTRING];					// 标题栏文本
TCHAR szWindowClass[MAX_LOADSTRING];			// 主窗口类名

// 系统图标。
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
// hIcons 的数量。
int hIconsCount = 9;
// 金坷垃图标。
HICON jinKeLaHIcon;
// 鼠标 x 与 y 的修正值。
int ix = GetSystemMetrics(SM_CXICON) / 2;
int iy = GetSystemMetrics(SM_CYICON) / 2;
// 桌面的 HWND 。
HWND desktop = GetDesktopWindow();
// 桌面的 HDC 。
HDC desktopHDc = GetWindowDC(desktop);
// 桌面的 desktopRect 。
RECT desktopRect;
// 桌面的宽。
int desktopWidth;
// 桌面的高。
int desktopHeight;

// 此代码模块中包含的函数的前向声明: 
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

 	// TODO:  在此放置代码。
	// 加载金坷垃图标。
	jinKeLaHIcon = ExtractIcon(hInstance, _T("JinKeLa.ico"), 0);
	// 初始化随机数生成器。
	srand(time(NULL));
	// 获取到桌面的 desktopRect 。
	GetWindowRect(desktop, &desktopRect);
	// 获取到桌面的宽与高。
	desktopWidth = desktopRect.right - desktopRect.left;
	desktopHeight = desktopRect.bottom - desktopRect.top;
	// 获取到桌面的 HWND 。
	desktop = GetDesktopWindow();
	// 获取到桌面的 HDC 。
	desktopHDc = GetWindowDC(desktop);

	DoIconsDrawing(hInstance);
	DoIconsDrawing(hInstance);

	return 0;

	MSG msg;
	HACCEL hAccelTable;

	// 初始化全局字符串
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_WINDOWSFUNNYTROJAN, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// 执行应用程序初始化: 
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_WINDOWSFUNNYTROJAN));

	// 主消息循环: 
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
//  函数:  MyRegisterClass()
//
//  目的:  注册窗口类。
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
//   函数:  InitInstance(HINSTANCE, int)
//
//   目的:  保存实例句柄并创建主窗口
//
//   注释: 
//
//        在此函数中，我们在全局变量中保存实例句柄并
//        创建和显示主程序窗口。
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // 将实例句柄存储在全局变量中

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
//  函数:  WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  目的:    处理主窗口的消息。
//
//  WM_COMMAND	- 处理应用程序菜单
//  WM_PAINT	- 绘制主窗口
//  WM_DESTROY	- 发送退出消息并返回
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
		// 分析菜单选择: 
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
		// TODO:  在此添加任意绘图代码...
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

// “关于”框的消息处理程序。
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
