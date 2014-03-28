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

#ifndef R_IBROWSER_IBROWSERSINGLE_H
#define R_IBROWSER_IBROWSERSINGLE_H

// ibrowser
#include "ibrowser/ibrowserapp.h"
#include "ibrowser/ibrowserhandler.h"

// boost
#include "boost/thread/once.hpp"
#include "boost/scoped_ptr.hpp"

/*
 * @brief : single ibrowser
 */
class IBrowserSingle
{
public :
	IBrowserSingle()
		:	m_ibrowser_app(NULL), 
			// m_ibrowser_client(new IBrowserClient),
			m_ibrowser_handler(NULL)
	{
		
	}
	~IBrowserSingle()
	{
		
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

	IBrowserApp* GetCurrentIBrowserApp()
	{
		return m_ibrowser_app.get();
	}

	/*IBrowserClient* getCurrentIBrowserClient()
	{
		return m_ibrowser_client.get();	
	}*/

	ibrowser::IBrowserHandler* GetCurrentIBrowserHandler()
	{
		return m_ibrowser_handler.get();	
	}

	void SetCurrentIBrowserHandler(ibrowser::IBrowserHandler *handler)
	{
		// m_ibrowser_handler->Release();
		m_ibrowser_handler = handler;
	}

/*
 * @brief : ibrowser ptr
 */
private : 
	CefRefPtr<IBrowserApp>						m_ibrowser_app;
	// CefRefPtr<IBrowserClient>				m_ibrowser_client;
	CefRefPtr<ibrowser::IBrowserHandler>		m_ibrowser_handler;

private :
	static boost::scoped_ptr<IBrowserSingle>	m_ibrowser_sinlge;
	static boost::once_flag						m_once_flag;
};

#endif // R_IBROWSER_IBROWSERSINGLE_H