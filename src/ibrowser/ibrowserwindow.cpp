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
#include "include/cef_app.h"

// vc
#include <Windows.h>

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
	
	int IBrowserWindow::initialize(HINSTANCE	hinstance, 
									LPSTR		lpCmdLine, 
									int			nCmdShow)
	{
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
			return exit_code;
		}

		// Specify CEF global settings here.
		CefSettings settings;

		// Initialize CEF.
		CefInitialize(main_args, settings, app.get());

		// Run the CEF message loop. This will block until CefQuitMessageLoop() is
		// called.
		CefRunMessageLoop();

		// Shut down CEF.
		CefShutdown();
		return 0;
	}

	ATOM IBrowserWindow::RegisterWinInfo(HINSTANCE hInstance) 
	{
		WNDCLASSEX wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style         = CS_HREDRAW | CS_VREDRAW;
		// wcex.lpfnWndProc   = windowProc;
		wcex.cbClsExtra    = 0;
		wcex.cbWndExtra    = 0;
		wcex.hInstance     = hInstance;
		wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszClassName = m_sz_windowClass;

		return RegisterClassEx(&wcex);
	}

	bool IBrowserWindow::RegisterWindow(HINSTANCE hInstance, int nCmdShow)
	{
		m_instance_app = hInstance;

		m_hwnd = CreateWindow(m_sz_windowClass, m_sz_title,
			WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, CW_USEDEFAULT, 0,
			CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

		if (!m_hwnd)
			return false;

		ShowWindow(m_hwnd, nCmdShow);
		UpdateWindow(m_hwnd);
		return true;
	}

	/*LRESULT CALLBACK IBrowserWindow::windowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam) 
	{
		
	}*/

}