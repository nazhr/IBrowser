/****************************************************************************
 *   Copyright (C) 2014 by Jerry			                           		*
 *                                                                        	*
 *   This file is part of IBrowser.                                        	*
 *                                                                         	*
 *   IBrowser is private software.                                         	*
 *   program.  If not, see <https://github.com/jerrykk/IBrowser>.          	*
 *                                                                         	*
 *   IBrowser website: https://github.com/jerrykk/IBrowser                 	*
 ****************************************************************************/
/*
 * ibrowser global function
 */

#ifndef R_IBROWSER_GLOBAL_H
#define R_IBROWSER_GLOBAL_H

// ibrowser
#include "ibrowser/global.h"
#include "ibrowser/ibrowserhandler.h"

// cef
#include "include/cef_app.h"
#include "include/utils/resource.h"

/*
BOOL				InitInstance(HINSTANCE, int);
ATOM				MyRegisterClass(HINSTANCE hInstance);
*/
LRESULT				CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

// public
HINSTANCE			hInst;
HWND				hWnd;
HWND				hMessageWnd = NULL;

/*
 *  函数: MyRegisterClass()
 *
 *  目的: 注册窗口类。
 *
 *  注释:
 *
 *    仅当希望
 *    此代码与添加到 Windows 95 中的"RegisterClassEx"
 *    函数之前的 Win32 系统兼容时，才需要此函数及其用法。调用此函数十分重要，
 *    这样应用程序就可以获得关联的
 *    "格式正确的"小图标。
 */
ATOM MyRegisterClass(HINSTANCE hInstance) 
{
	const wchar_t CLASS_NAME[]  = L"IBrowser";
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style         = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc   = WindowProc;
	wcex.cbClsExtra    = 0;
	wcex.cbWndExtra    = 0;
	wcex.hInstance     = hInstance;
	wcex.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CEFCLIENT));
	wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wcex.lpszMenuName  = MAKEINTRESOURCE(IDC_CEFCLIENT);
	wcex.lpszClassName = CLASS_NAME;
	wcex.hIconSm       = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

/*
 *   函数: InitInstance(HINSTANCE, int)
 *
 *   目的: 保存实例句柄并创建主窗口
 *
 *   注释:
 *
 *        在此函数中，我们在全局变量中保存实例句柄并
 *        创建和显示主程序窗口。
 */
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
	const wchar_t	class_name[] = L"IBrowser";
	// HWND			hWnd;

	hInst = hInstance; // 将实例句柄存储在全局变量中

	hWnd = CreateWindow(class_name, L"IBrowser",
		WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, CW_USEDEFAULT, 0,
		CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd)
	{
		return FALSE;
	}

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}

LRESULT CALLBACK WindowProc(HWND hWnd, 
	UINT message, 
	WPARAM wParam, 
	LPARAM lParam) 
{
	switch (message) {
		case WM_DESTROY:
			PostQuitMessage(0);
			return 0;

		case WM_SIZE:
			if (ibrowser::IBrowserHandler::GetInstance()->GetHandler().get()) {
				// Resize the browser window and address bar to match the new frame
				// window size
				RECT rect;
				GetClientRect(hWnd, &rect);

				HDWP hdwp = BeginDeferWindowPos(1);
				hdwp = DeferWindowPos(hdwp, ibrowser::IBrowserHandler::GetInstance()->
					GetHandler().get()->GetBrowser()->GetHost()->GetWindowHandle(), NULL,
					rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top,
					SWP_NOZORDER);
				EndDeferWindowPos(hdwp);
			}
			break;

		case WM_ERASEBKGND:
			if (ibrowser::IBrowserHandler::GetInstance()->GetHandler().get()) {
				// Dont erase the background if the browser window has been loaded
				// (this avoids flashing)
				return 0;
			}
			break;

		case WM_CLOSE:
			{
				if (ibrowser::IBrowserHandler::GetInstance() && !ibrowser::IBrowserHandler::GetInstance()->IsClosing()) {
					CefRefPtr<CefBrowser> browser = ibrowser::IBrowserHandler::GetInstance()->GetBrowser();
					if (browser.get()) {
						// Let the browser window know we are about to destroy it.
						browser->GetHost()->CloseBrowser(false);
						return 0;
					}
				}
			}
			break;

		case WM_PAINT:
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			return 0;

	}

	return DefWindowProc(hWnd, message, wParam, lParam);	
}

/*
 * "关于"框的消息处理程序。
 */
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

#endif // R_IBROWSER_GLOBAL_H