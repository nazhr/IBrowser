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

#ifndef R_BROWSER_IBROWSERCLIENT_H
#define R_BROWSER_IBROWSERCLIENT_H

// ibrowser
#include "ibrowser/ibrowserapp.h"
#include "ibrowser/ibrowserhandler.h"

// cef
#include "include/cef_base.h"

// boost
#include "boost/scoped_ptr.hpp"
#include <boost/thread/once.hpp>


namespace ibrowser
{

#define MAX_LOADSTRING 100
#define MAX_LOADSTRING 100
#define MAX_URL_LENGTH  255
#define BUTTON_WIDTH 72
#define URLBAR_HEIGHT  24

	class IBrowserWindow
	{
	public :
		IBrowserWindow();
		virtual ~IBrowserWindow();
		
		static	IBrowserWindow &instance()
		{
			boost::call_once(IBrowserWindow::init, m_once_flag);
			return *m_instance_ptr;
		}
		static void init()
		{
			m_instance_ptr.reset(new IBrowserWindow);
		}

		bool initialize(HINSTANCE hinstance, LPSTR lpCmdLine, int nCmdShow);
		
		IBrowserHandler *getHandler()
		{
			return m_ibrowser_handler.get();			
		}

		ATOM RegisterWinInfo(HINSTANCE hInstance);
		bool RegisterWindow(HINSTANCE hInstance, int nCmdShow);
		// LRESULT CALLBACK windowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
		
	private :
		CefRefPtr<IBrowserApp>		m_ibrowser_app;
		HINSTANCE					m_instance_app;
		LPSTR						m_lpCmdLine;
		int							m_nCmdShow;
		TCHAR						m_sz_title[MAX_LOADSTRING];  
		TCHAR						m_sz_windowClass[MAX_LOADSTRING];
		HWND						m_hwnd;

	private :
		static	boost::scoped_ptr<ibrowser::IBrowserWindow>		m_instance_ptr;
		static	CefRefPtr<ibrowser::IBrowserHandler>			m_ibrowser_handler;
		static	boost::once_flag								m_once_flag;
	};
}

#endif // R_BROWSER_IBROWSERCLIENT_H
