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
#include "ibrowser/ibrowsertab.h"

// cef
#include <include/cef_base.h>
#include <include/utils/resource.h>

// boost
#include "boost/scoped_ptr.hpp"
#include <boost/thread/once.hpp>

// Qt
#include <QtGui/QWidget>
#include <QtGui/QMessageBox>

namespace ibrowser 
{
	class IBrowserClient
	{
	public :
		IBrowserClient();
		virtual ~IBrowserClient();

	public : // non staic function member
		int		Initialize(QWidget *parent);
		void	Quit()
		{
			// cef close borwser
			CefShutdown();
		}

	private : // static member
		static	HINSTANCE								m_hInstance;
		static	CefRefPtr</*ibrowser::*/IBrowserApp>	m_cef_app;

	private :
		IBrowserTab										*m_ibrowser_tab;
		
	};
}

#endif // R_BROWSER_IBROWSERCLIENT_H
