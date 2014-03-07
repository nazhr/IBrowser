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

// ibrowser
#include "ibrowser/ibrowserwindow.h"
#include "ibrowser/ibrowserhandler.h"
#include "ibrowser/resource.h"

// cef
#include "include/cef_app.h"

// vc
#include <Windows.h>

ATOM MyRegisterClass(HINSTANCE hInstance);
LRESULT CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);

namespace ibrowser
{
	IBrowserWindow::IBrowserWindow()
		: m_ibrowser_app(NULL)
	{

	}

	IBrowserWindow::~IBrowserWindow(){}

	boost::scoped_ptr<ibrowser::IBrowserWindow>	IBrowserWindow::m_instance_ptr(0);
	boost::once_flag							IBrowserWindow::m_once_flag = BOOST_ONCE_INIT;
	CefRefPtr<ibrowser::IBrowserHandler>		IBrowserWindow::m_ibrowser_handler(0);
	
	bool IBrowserWindow::initialize(HINSTANCE	hinstance, 
									LPSTR		lpCmdLine, 
									int			nCmdShow)
	{
		try
		{
			m_instance_app = hinstance;
			m_lpCmdLine = lpCmdLine;

			// Provide CEF with command-line arguments.
			CefMainArgs main_args(hinstance);

			// SimpleApp implements application-level callbacks. It will create the first
			// browser instance in OnContextInitialized() after CEF has initialized.
			CefRefPtr<ibrowser::IBrowserApp> app(new ibrowser::IBrowserApp);

			// CEF applications have multiple sub-processes (render, plugin, GPU, etc)
			// that share the same executable. This function checks the command-line and,
			// if this is a sub-process, executes the appropriate logic.
			int exit_code = CefExecuteProcess(main_args, app.get());
			if (exit_code >= 0) {
				// The sub-process has completed so return here.
				return 0;
			}

			// Specify CEF global settings here.
			CefSettings settings;

			// Initialize CEF.
			CefInitialize(main_args, settings, app.get());
			
			HACCEL hAccelTable;

			TCHAR szTitle[MAX_LOADSTRING];  // The title bar text
			TCHAR szWindowClass[MAX_LOADSTRING];  // the main window class name
			TCHAR szOSRWindowClass[MAX_LOADSTRING];  // the OSR window class name
			// Initialize global strings
			LoadString(hinstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
			LoadString(hinstance, IDC_CEFCLIENT, szWindowClass, MAX_LOADSTRING);
			LoadString(hinstance, IDS_OSR_WIDGET_CLASS, szOSRWindowClass, MAX_LOADSTRING);

			MyRegisterClass(hinstance);
			if(!RegisterWindow(hinstance, nCmdShow))
			{
				return 0;
			}

			hAccelTable = LoadAccelerators(hinstance, MAKEINTRESOURCE(IDC_CEFCLIENT));

			RECT			rect;
			::GetClientRect(m_hwnd, &rect);
			CefBrowserSettings browserSettings;
			CefString(&browserSettings.default_encoding) = "utf-8";
			browserSettings.file_access_from_file_urls = STATE_ENABLED;
			browserSettings.universal_access_from_file_urls = STATE_ENABLED;
			CefWindowInfo	info;
			info.SetAsChild(m_hwnd, rect);
			IBrowserHandler ibrowerhandler;
			ibrowerhandler.SetMainHwnd(m_hwnd);

			std::string		url = "www.google.com.hk";
			CefBrowserHost::CreateBrowser(info, ibrowerhandler.GetHandler().get(), url, browserSettings);

			// Run the CEF message loop. This will block until CefQuitMessageLoop() is
			// called.
			CefRunMessageLoop();

			// Shut down CEF.
			CefShutdown();
		}
		catch(std::exception &e)
		{
			::MessageBoxA(m_hwnd, e.what(), "IBrowser System Error :", MB_OK);
		}
		return 1;
	}

	bool IBrowserWindow::RegisterWindow(HINSTANCE hInstance, int nCmdShow)
	{
		const wchar_t CLASS_NAME[]  = L"IBrowser";
		m_hwnd = CreateWindow(CLASS_NAME, L"IBrowser",
			WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, CW_USEDEFAULT, 0,
			CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

		if (!m_hwnd)
			return false;

		ShowWindow(m_hwnd, nCmdShow);
		UpdateWindow(m_hwnd);
		return true;
	}
	

}

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
	wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName  = MAKEINTRESOURCE(IDC_CEFCLIENT);
	wcex.lpszClassName = CLASS_NAME;
	wcex.hIconSm       = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
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