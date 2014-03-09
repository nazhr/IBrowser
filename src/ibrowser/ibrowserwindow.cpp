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

			// App implements application-level callbacks. It will create the first
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
			if(!InitInstance(hinstance, nCmdShow))
			{
				return 0;
			}

			hAccelTable = LoadAccelerators(hinstance, MAKEINTRESOURCE(IDC_CEFCLIENT));

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

}
