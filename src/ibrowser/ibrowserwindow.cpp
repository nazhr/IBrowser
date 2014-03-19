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

			// Initialize global strings
			/*
			LoadString(hinstance, IDS_APP_TITLE, m_sz_title, MAX_LOADSTRING);
			LoadString(hinstance, IDC_CEFCLIENT, m_sz_windowClass, MAX_LOADSTRING);
			*/

			RegisterWindowClass();
			if(!CreateDefMainWindow())
			{
				return 0;
			}

			hAccelTable = LoadAccelerators(hinstance, MAKEINTRESOURCE(IDC_CEFCLIENT));

			// Run the CEF message loop. This will block until CefQuitMessageLoop() is
			// called.
			CefRunMessageLoop();

			// Shut down CEF.
			CefShutdown();
		}
		catch(std::exception &e)
		{
			MessageUtils::MessageBoxDef(m_hWnd, e.what(), "IBrowser Window System Error : ");
		}
		return 1;
	}	

	bool IBrowserWindow::CreateDefMainWindow()
	{
		try{
			m_hWnd = CreateWindow(CLASS_NAME, CLASS_NAME,
				WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, CW_USEDEFAULT, 0,
				CW_USEDEFAULT, 0, NULL, NULL, m_hInstance, NULL);

			if (!m_hWnd)
			{
				return false;
			}

			ShowWindow(m_hWnd, m_nCmdShow);
			UpdateWindow(m_hWnd);

		}
		catch(std::exception &e)
		{
			MessageUtils::MessageBoxDef(m_hWnd, e.what(), "IBrowser Window System Error : ");
		}
		return true;
	}

	ATOM IBrowserWindow::RegisterWindowClass()
	{
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
