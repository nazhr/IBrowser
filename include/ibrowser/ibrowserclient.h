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
#include "ibrowser/global.h"
#include "ibrowser/ibrowsersingle.h"
#include "ibrowser/ibrowserhandler.h"
#include "ibrowser/ibrowserapp.h"

// cef
#include <include/cef_base.h>
#include <include/utils/resource.h>

// boost
#include "boost/scoped_ptr.hpp"
#include <boost/thread/once.hpp>

// Qt
#include <QtGui/QWidget>
#include <QtGui/QMessageBox>

// vc
#include <string>

namespace ibrowser 
{
	class IBrowserClient
	{
	public :
		IBrowserClient();
		virtual ~IBrowserClient();

	public : // non staic function member
		int		Initialize(HWND &hWnd, std::string &url);
		void	CreateBrowser(HWND &hWnd, std::string &url);
		bool	BrowserLoadUrl(const std::wstring &url);
		void	CloseBrowser();
		void	Quit()
		{
			// cef close borwser
			CefShutdown();
		}

	private : // static member
		static	HINSTANCE									m_hInstance;
		static	CefRefPtr</*ibrowser::*/IBrowserApp>		m_cef_app;
		// static	boost::scoped_ptr<ibrowser::IBrowserClient>

	private :
		
	};
}

#endif // R_BROWSER_IBROWSERCLIENT_H
