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
#include "ibrowser/ibrowsertab.h"
#include "ibrowser/ibrowserwindow.h"
#include "ibrowser/ibrowsersingle.h"
// vc
#include <Windows.h>

namespace ibrowser
{
	// init static hwnd
	HWND						IBrowserTab::m_editWnd = NULL;
	/*// WNDPROC						IBrowserTab::m_editWndOldProc = NULL;
	HWND						IBrowserTab::m_backWnd = NULL;
	HWND						IBrowserTab::m_forwardWnd = NULL;
	HWND						IBrowserTab::m_reloadWnd = NULL;
	HWND						IBrowserTab::m_stopWnd = NULL;*/

	IBrowserTab::IBrowserTab(){}
	IBrowserTab::~IBrowserTab(){}

	/*
	 * @ brief : register tab window class
	 */
	ATOM IBrowserTab::RegisterTabClass()
	{
		HINSTANCE				hInstance = IBrowserWindow::GetCurrentAppHandler();
		// const static wchar_t	CLASS_NAME[]  = L"Tab";
		WNDCLASSEX		wcex;

		wcex.cbSize = sizeof(WNDCLASSEX);

		wcex.style         = CS_HREDRAW | CS_VREDRAW;
		wcex.lpfnWndProc   = ChildWindowProc;
		wcex.cbClsExtra    = 0;
		wcex.cbWndExtra    = 0;
		wcex.hInstance     = hInstance;
		wcex.hIcon         = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_CEFCLIENT));
		wcex.hCursor       = LoadCursor(NULL, IDC_ARROW);
		wcex.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
		wcex.lpszMenuName  = MAKEINTRESOURCE(IDC_CEFCLIENT);
		wcex.lpszClassName = L"Tab";
		wcex.hIconSm       = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

		return RegisterClassEx(&wcex);

	}

	/*
	 * @brief : create browser tab
	 */
	bool IBrowserTab::CreateTab(HWND child_hWnd)
	{
		try
		{
			IBrowserHandler *handler = ibrowser::IBrowserSingle::Instance().getCurrentIBrowserHandler();
			HINSTANCE		hInstance = IBrowserWindow::GetCurrentAppHandler();
			static WNDPROC	editWndOldProc = NULL;
			if(child_hWnd)
			{
				/*
				 * @brief : get root window size
				 */
				RECT		rect_root;
				::GetClientRect(child_hWnd, &rect_root);
				
				m_tab_hWnd = ::CreateWindowEx(	NULL, 
											L"Tab", NULL, 
											(WS_CHILD | WS_VISIBLE /*| WS_BORDER */| ES_LEFT |
											ES_AUTOVSCROLL | ES_AUTOHSCROLL), 
											0, 0, 
											rect_root.right - rect_root.left, 
											rect_root.bottom - rect_root.top,  
											child_hWnd, 
											NULL, 
											hInstance, 
											NULL);

				if(!m_tab_hWnd)
					return false;
				ShowWindow(m_tab_hWnd, 1/*m_nCmdShow*/);
				UpdateWindow(m_tab_hWnd);
				
			}

		}
		catch(std::exception &e)
		{
			MessageBoxDef(NULL, e.what(), "IBrowser Tab System Error : ");
		}
		return true;
	}

	/*
	 * @brief : create browser tab member
	 */
	void IBrowserTab::CreateTabMember(HWND tab_hWnd)
	{
		try
		{
			IBrowserHandler *handler = ibrowser::IBrowserSingle::Instance().getCurrentIBrowserHandler();
			HINSTANCE		hInstance = IBrowserWindow::GetCurrentAppHandler();
			handler->SetMainHwnd(tab_hWnd);

			RECT		rect_tab;
			::GetClientRect(tab_hWnd, &rect_tab);

			int			x = 0;

			m_editWnd = CreateWindowEx(	WS_EX_CLIENTEDGE, 
										L"EDIT", L"EDIT",
										(WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT |
										ES_AUTOVSCROLL | ES_AUTOHSCROLL),
										x, 0, rect_tab.right, URLBAR_HEIGHT, 
										tab_hWnd, 
										NULL, 
										hInstance, 
										NULL);

			if(!m_editWnd)
				return ;
			// set browser screen size 
			// set browser top pos
			rect_tab.top += URLBAR_HEIGHT;

			// Assign the edit window's WNDPROC to this function so that we can
			// capture the enter key
			editWndOldProc =
				reinterpret_cast<WNDPROC>(GetWindowLongPtr(m_editWnd, GWLP_WNDPROC));
			SetWindowLongPtr(m_editWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(ChildWindowProc));
			handler->SetEditHwnd(m_editWnd);
			// handler->SetButtonHwnds(m_backWnd, m_forwardWnd, m_reloadWnd, m_stopWnd);

			CefBrowserSettings browserSettings;
			CefString(&browserSettings.default_encoding) = "utf-8";
			browserSettings.file_access_from_file_urls = STATE_ENABLED;
			browserSettings.universal_access_from_file_urls = STATE_ENABLED;
			CefWindowInfo	info;
			info.SetAsChild(tab_hWnd, rect_tab);

			rect_tab.top += URLBAR_HEIGHT;

			CefBrowserHost::CreateBrowser(info, handler, handler->GetStartupURL(), browserSettings);
		}
		catch(std::exception &e)
		{
			MessageBoxDef(NULL, e.what(), "IBrowser Tab System Error : ");
		}
	}
	
}
