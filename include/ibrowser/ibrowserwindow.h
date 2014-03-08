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

#ifndef R_BROWSER_IBROWSERWIN_H
#define R_BROWSER_IBROWSERWIN_H

// ibrowser
#include "ibrowser/ibrowserapp.h"
#include "ibrowser/ibrowserclient.h"
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

	/*
	 * @brief : single ibrowser
	 */
	class IBrowserSingle
	{
	public :
		IBrowserSingle()
			:	m_ibrowser_app(new IBrowserApp), 
				m_ibrowser_client(new IBrowserClient),
				m_ibrowser_handler(new IBrowserHandler)
		{
			
		}
		~IBrowserSingle()
		{
			m_ibrowser_app.reset();
			m_ibrowser_client.reset();
			m_ibrowser_handler.reset();
		}

		// static
		static IBrowserSingle& Instance()
		{
			boost::call_once(IBrowserSingle::init, IBrowserSingle::m_once_flag);
			return *m_ibrowser_sinlge;
		}
		static void init()
		{
			m_ibrowser_sinlge.reset(new IBrowserSingle);
		}

		IBrowserApp& getIBrowserApp()
		{
			return *m_ibrowser_app;
		}

		IBrowserClient& getIBrowserClient()
		{
			return *m_ibrowser_client;	
		}

		IBrowserHandler& getIBrowserHandler()
		{
			return *m_ibrowser_handler;	
		}

	/*
	 * @brief : ibrowser ptr
	 */
	private : 
		boost::scoped_ptr<ibrowser::IBrowserApp>			m_ibrowser_app;
		boost::scoped_ptr<ibrowser::IBrowserClient>			m_ibrowser_client;
		boost::scoped_ptr<ibrowser::IBrowserHandler>		m_ibrowser_handler;

	private :
		static boost::scoped_ptr<ibrowser::IBrowserSingle>	m_ibrowser_sinlge;
		static boost::once_flag								m_once_flag;
	};

	/*
	 * @brief : ibrowser window class
	 */
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

#endif // R_BROWSER_IBROWSERWIN_H
