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
#include "ibrowser/global.h"
#include "ibrowser/ibrowserwindow.h"
#include "ibrowser/ibrowserhandler.h"

// cef
#include "include/cef_app.h"
#include "include/utils/resource.h"

// vc
#include <Windows.h>

#include "boost/thread/once.hpp"
#include "boost/scoped_ptr.hpp"

namespace ibrowser
{
	/*
	 * @brief : ibrowser single static init .
	 */
	boost::scoped_ptr<ibrowser::IBrowserSingle> IBrowserSingle::m_ibrowser_sinlge(0);
	boost::once_flag							IBrowserSingle::m_once_flag = BOOST_ONCE_INIT;

	/*
	 * @brief : ibrowser window
	 */
	IBrowserWindow::IBrowserWindow()
	{

	}

	IBrowserWindow::~IBrowserWindow(){}

	boost::scoped_ptr<ibrowser::IBrowserWindow>	IBrowserWindow::m_instance_ptr(0);
	boost::once_flag							IBrowserWindow::m_once_flag = BOOST_ONCE_INIT;
	CefRefPtr<ibrowser::IBrowserApp>			IBrowserWindow::m_ibrowser_app(0);
	HINSTANCE									IBrowserWindow::m_hInstance = NULL;
	
	bool IBrowserWindow::initialize(HINSTANCE	hinstance, 
									LPSTR		lpCmdLine, 
									int			nCmdShow)
	{
		try
		{
			m_hInstance		= hinstance;
			m_lpCmdLine		= lpCmdLine;
			m_nCmdShow		= nCmdShow;

			// Provide CEF with command-line arguments.
			CefMainArgs main_args(hinstance);

			// App implements application-level callbacks. It will create the first
			// browser instance in OnContextInitialized() after CEF has initialized.
			m_ibrowser_app = new ibrowser::IBrowserApp;

			// CEF applications have multiple sub-processes (render, plugin, GPU, etc)
			// that share the same executable. This function checks the command-line and,
			// if this is a sub-process, executes the appropriate logic.
			int exit_code = CefExecuteProcess(main_args, m_ibrowser_app.get());
			if (exit_code >= 0) {
				// The sub-process has completed so return here.
				return 0;
			}

			// Specify CEF global settings here.
			CefSettings		settings;

			// Initialize CEF.
			CefInitialize(main_args, settings, m_ibrowser_app.get());
			
			HACCEL			hAccelTable;

			TCHAR			szTitle[MAX_LOADSTRING];  // The title bar text
			TCHAR			szWindowClass[MAX_LOADSTRING];  // the main window class name
			TCHAR			szOSRWindowClass[MAX_LOADSTRING];  // the OSR window class name
			// Initialize global strings
			LoadString(hinstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
			LoadString(hinstance, IDC_CEFCLIENT, szWindowClass, MAX_LOADSTRING);
			LoadString(hinstance, IDS_OSR_WIDGET_CLASS, szOSRWindowClass, MAX_LOADSTRING);

			RegisterWindowClass();
			if(!CreateDefMainWindow())
			{
				return 0;
			}

			hAccelTable = LoadAccelerators(hinstance, MAKEINTRESOURCE(IDC_CEFCLIENT));

			/*
			RECT			rect;
			::GetClientRect(hWnd, &rect);
			CefBrowserSettings browserSettings;
			CefString(&browserSettings.default_encoding) = "utf-8";
			browserSettings.file_access_from_file_urls = STATE_ENABLED;
			browserSettings.universal_access_from_file_urls = STATE_ENABLED;
			CefWindowInfo	info;
			info.SetAsChild(hWnd, rect);
			// IBrowserHandler::Instance().SetMainHwnd(hWnd);
			IBrowserSingle::Instance().getCurrentIBrowserHandler()->SetMainHwnd(hWnd);

			std::string		url = "www.google.com.hk";
			// CefBrowserHost::CreateBrowser(info, IBrowserHandler::Instance().GetHandler().get(), url, browserSettings);
			CefBrowserHost::CreateBrowser(info, IBrowserSingle::Instance().getCurrentIBrowserHandler(), 
				url, browserSettings);
			*/
			// Run the CEF message loop. This will block until CefQuitMessageLoop() is
			// called.
			CefRunMessageLoop();

			// Shut down CEF.
			CefShutdown();
		}
		catch(std::exception &e)
		{
			::MessageBoxA(m_hWnd, e.what(), "IBrowser System Error :", MB_OK);
		}
		return 1;
	}	

	bool IBrowserWindow::CreateDefMainWindow()
	{
		const wchar_t	class_name[] = L"IBrowser";

		m_hWnd = CreateWindow(class_name, L"IBrowser",
			WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, CW_USEDEFAULT, 0,
			CW_USEDEFAULT, 0, NULL, NULL, m_hInstance, NULL);

		if (!m_hWnd)
		{
			return FALSE;
		}

		ShowWindow(m_hWnd, m_nCmdShow);
		UpdateWindow(m_hWnd);

		return TRUE;
	}

	ATOM IBrowserWindow::RegisterWindowClass()
	{
		const wchar_t CLASS_NAME[]  = L"IBrowser";
		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style         = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc   = WindowProc;
		wcex.cbClsExtra    = 0;
		wcex.cbWndExtra    = 0;
		wcex.hInstance     = m_hInstance;
		wcex.hIcon         = LoadIcon(m_hInstance, MAKEINTRESOURCE(IDI_CEFCLIENT));
		wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName  = MAKEINTRESOURCE(IDC_CEFCLIENT);
		wcex.lpszClassName = CLASS_NAME;
		wcex.hIconSm       = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		return RegisterClassEx(&wcex);
	}

}
