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
#include "ibrowser/ibrowserhandler.h"
#include "ibrowser/ibrowserwindow.h"

// cef
#include "include/cef_app.h"
#include "include/utils/resource.h"

LRESULT				CALLBACK WindowProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

HWND				hMessageWnd = NULL;

LRESULT CALLBACK WindowProc(HWND	hWnd, 
							UINT	message, 
							WPARAM	wParam, 
							LPARAM	lParam) 
{
	static HWND backWnd = NULL, forwardWnd = NULL, reloadWnd = NULL,
		stopWnd = NULL, editWnd = NULL;
	static WNDPROC editWndOldProc = NULL;
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
					ibrowser::IBrowserHandler *handler = ibrowser::IBrowserSingle::Instance().getCurrentIBrowserHandler();
					handler->SetMainHwnd(hWnd);

					RECT			rect;
					::GetClientRect(hWnd, &rect);
					
					int x = 0;

					editWnd = CreateWindow(L"EDIT", 0,
						WS_CHILD | WS_VISIBLE | WS_BORDER | ES_LEFT |
						ES_AUTOVSCROLL | ES_AUTOHSCROLL /*| WS_DISABLED*/,
						x, 0, rect.right,
						URLBAR_HEIGHT, hWnd, 0, ibrowser::IBrowserWindow::GetCurrentAppHandler(), 0);

					// set browser screen size 
					// set browser top pos
					rect.top += URLBAR_HEIGHT;

					// Assign the edit window's WNDPROC to this function so that we can
					// capture the enter key
					editWndOldProc =
						reinterpret_cast<WNDPROC>(GetWindowLongPtr(editWnd, GWLP_WNDPROC));
					SetWindowLongPtr(editWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(WindowProc));
					handler->SetEditHwnd(editWnd);
					handler->SetButtonHwnds(backWnd, forwardWnd, reloadWnd, stopWnd);

					CefBrowserSettings browserSettings;
					CefString(&browserSettings.default_encoding) = "utf-8";
					browserSettings.file_access_from_file_urls = STATE_ENABLED;
					browserSettings.universal_access_from_file_urls = STATE_ENABLED;
					CefWindowInfo	info;
					info.SetAsChild(hWnd, rect);

					rect.top += URLBAR_HEIGHT;
					
					CefBrowserHost::CreateBrowser(info, handler, handler->GetStartupURL(), browserSettings);
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