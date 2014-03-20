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
#include "ibrowser/ibrowsersingle.h"
#include "ibrowser/ibrowsertab.h"
#include "ibrowser/ibrowserwindow.h"
#include "ibrowser/ibrowserhandler.h"

// cef
#include "include/cef_app.h"
#include "include/utils/resource.h"

static LRESULT				CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
static LRESULT				CALLBACK ChildWindowProc(HWND, UINT, WPARAM, LPARAM);
static INT_PTR CALLBACK		About(HWND, UINT, WPARAM, LPARAM);

static HWND					hMessageWnd = NULL;

// temp instance ibrowser tab
static ibrowser::IBrowserTab *ibrowser_tab = new ibrowser::IBrowserTab();
static WNDPROC editWndOldProc = NULL;

LRESULT CALLBACK WindowProc(HWND	hWnd, 
							UINT	message, 
							WPARAM	wParam, 
							LPARAM	lParam) 
{
	switch (message) {
		case WM_CREATE :
			{
				ibrowser::IBrowserSingle::Instance().setCurrentIBrowserHandler(new ibrowser::IBrowserHandler());
				ibrowser_tab->RegisterTabClass();
				bool status = ibrowser_tab->CreateTab(hWnd);
				if(!status)
					PostQuitMessage(0);
				return 0;
			}
		case WM_DESTROY:
			// PostQuitMessage(0);
			return 0;

		case WM_SIZE :
			{
				HWND tab = ibrowser_tab->GetTabHWnd();
				if(tab)
				{
					RECT rect;
					GetClientRect(hWnd, &rect);

					HDWP hdwp = BeginDeferWindowPos(1);

					// tab window ps

					hdwp = DeferWindowPos(hdwp, tab, NULL, 
						0, 0/*TAB_BTN_HEIGTH*/, rect.right - rect.left, rect.bottom/* - TAB_BTN_HEIGTH*/, SWP_NOZORDER);
					EndDeferWindowPos(hdwp);	
				}
			}

			break;

		case WM_ERASEBKGND :
			if (ibrowser::IBrowserSingle::Instance().getCurrentIBrowserHandler()) {
				// Dont erase the background if the browser window has been loaded
				// (this avoids flashing)
				return 0;
			}
			break;

		case WM_CLOSE :
			{
				try
				{
					if (ibrowser::IBrowserSingle::Instance().getCurrentIBrowserHandler() 
						&& !ibrowser::IBrowserSingle::Instance().getCurrentIBrowserHandler()->IsClosing()) 
					{
						CefRefPtr<CefBrowser> browser = ibrowser::IBrowserSingle::Instance().
							getCurrentIBrowserHandler()->GetBrowser();
						if (browser.get()) {
							// Let the browser window know we are about to destroy it.
							browser->GetHost()->CloseBrowser(false);
							//PostQuitMessage(0);
							return 0;
						}
					}
				}
				catch (std::exception &e)
				{
					MessageBoxA(NULL, e.what(), "IBrowser Window Called System Error : ", MB_OK);
				}
			}
			break;

		case WM_PAINT :
			PAINTSTRUCT ps;
			HDC hdc = BeginPaint(hWnd, &ps);
			EndPaint(hWnd, &ps);
			return 0;
		
	}
	

	return DefWindowProc(hWnd, message, wParam, lParam);	
}

/*
 * @brief : child window process
 */
LRESULT CALLBACK ChildWindowProc(	HWND	hWnd, 
									UINT	message, 
									WPARAM	wParam, 
									LPARAM	lParam) 
{
	HWND	editWnd = ibrowser_tab->GetEditHWnd();
	
	if(hWnd == editWnd)
	{
		switch(message)
		{
		case WM_CHAR : 
			{
				if (wParam == VK_RETURN && ibrowser::
					IBrowserSingle::Instance().getCurrentIBrowserHandler()) 
				{
					// When the user hits the enter key load the URL
					CefRefPtr<CefBrowser> browser = ibrowser::
						IBrowserSingle::Instance().getCurrentIBrowserHandler()->GetBrowser();
					wchar_t strPtr[MAX_URL_LENGTH + 1] = {0};
					*((LPWORD)strPtr) = MAX_URL_LENGTH;
					LRESULT strLen = SendMessage(hWnd, EM_GETLINE, 0, (LPARAM)strPtr);
					if (strLen > 0) {
						strPtr[strLen] = 0;
						browser->GetMainFrame()->LoadURL(strPtr);
					}

					return 0;
				}
			}
		}
		return (LRESULT)CallWindowProc(editWndOldProc, hWnd, message, wParam, lParam);

	}
	else
	{
		switch (message) {
			case WM_CREATE :
				{
					ibrowser::IBrowserSingle::Instance().setCurrentIBrowserHandler(new ibrowser::IBrowserHandler());
					ibrowser_tab->CreateTabMember(hWnd);
					return 0;
				}
			case WM_DESTROY:
				// PostQuitMessage(0);
				return 0;

			case WM_SIZE :
				if (ibrowser::IBrowserSingle::Instance().getCurrentIBrowserHandler()) 
				{
					// Resize the browser window and address bar to match the new frame
					// window size
					CefWindowHandle hwnd = ibrowser::IBrowserSingle::Instance().getCurrentIBrowserHandler()->
						GetBrowser()->GetHost()->GetWindowHandle();
					if(hwnd)
					{
						RECT rect;
						GetClientRect(hWnd, &rect);

						rect.top += URLBAR_HEIGHT;

						HDWP hdwp = BeginDeferWindowPos(1);

						// edit window ps
						hdwp = DeferWindowPos(hdwp, editWnd, NULL, rect.left, rect.top - URLBAR_HEIGHT, 
							rect.right -  rect.left, URLBAR_HEIGHT, SWP_NOZORDER);
						RECT rect_edit;
						GetClientRect(editWnd, &rect_edit);
						// browser window ps
						hdwp = DeferWindowPos(hdwp, hwnd, NULL,
							rect.left, rect.top, rect.right - rect.left, rect.bottom - rect.top, SWP_NOZORDER);
						EndDeferWindowPos(hdwp);
					}
				}
				break;

			case WM_ERASEBKGND :
				if (ibrowser::IBrowserSingle::Instance().getCurrentIBrowserHandler()) {
					// Dont erase the background if the browser window has been loaded
					// (this avoids flashing)
					return 0;
				}
				break;

			case WM_CLOSE :
				{
					try
					{
						if (ibrowser::IBrowserSingle::Instance().getCurrentIBrowserHandler() 
							&& !ibrowser::IBrowserSingle::Instance().getCurrentIBrowserHandler()->IsClosing()) 
						{
							CefRefPtr<CefBrowser> browser = ibrowser::IBrowserSingle::Instance().
								getCurrentIBrowserHandler()->GetBrowser();
							if (browser.get()) {
								// Let the browser window know we are about to destroy it.
								browser->GetHost()->CloseBrowser(false);
								//PostQuitMessage(0);
								return 0;
							}
						}
					}
					catch (std::exception &e)
					{
						MessageBoxA(NULL, e.what(), "IBrowser Window Called System Error : ", MB_OK);
					}
				}
				break;

			case WM_PAINT :
				PAINTSTRUCT ps;
				HDC hdc = BeginPaint(hWnd, &ps);
				EndPaint(hWnd, &ps);
				return 0;
			
		}
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