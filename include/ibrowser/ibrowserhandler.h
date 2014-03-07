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

#ifndef R_IBROWSER_IBROWSERHANDLER_H
#define R_IBROWSER_IBROWSERHANDLER_H

//boost
#include "boost/scope_exit.hpp"
#include "boost/scoped_ptr.hpp"
#include "boost/thread/once.hpp"

// cef
#include "include/cef_client.h"

// vc
#include <list>

namespace ibrowser
{
	class IBrowserHandler : public CefClient,
							public CefDisplayHandler,
							public CefLifeSpanHandler,
							public CefLoadHandler
	{
	public:
		IBrowserHandler();
		~IBrowserHandler();

		// Provide access to the single global instance of this object.
		static IBrowserHandler& Instance();

		// reset ibrowserhandler
		static void init();

		// CefClient methods:
		virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler() OVERRIDE 
		{
			return this;
		}
		virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler() OVERRIDE 
		{
			return this;
		}
		virtual CefRefPtr<CefLoadHandler> GetLoadHandler() OVERRIDE 
		{
			return this;
		}

		// CefDisplayHandler methods:
		virtual void OnTitleChange(CefRefPtr<CefBrowser> browser,
			const CefString& title) OVERRIDE;

		// CefLifeSpanHandler methods:
		virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser) OVERRIDE;
		virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser) OVERRIDE;

		// CefLoadHandler methods:
		virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			ErrorCode errorCode,
			const CefString& errorText,
			const CefString& failedUrl) OVERRIDE;

		// Request that all existing browser windows close.
		void CloseAllBrowsers(bool force_close);

		// private
	public :
		CefRefPtr<CefBrowser>						GetBrowser();
		CefRefPtr<IBrowserHandler>					GetHandler();
		void										SetMainHwnd(CefWindowHandle hwnd);
		bool										IsClosing();

	private :
		static boost::scoped_ptr<IBrowserHandler>	m_instance_ptr;
		static boost::once_flag						m_once_flag;
		static CefRefPtr<IBrowserHandler>			m_handler;
		CefRefPtr<CefBrowser>						m_browser;
		int											m_browserId;
		// The main frame window handle
		CefWindowHandle								m_mainhwnd;
		// True if the main browser window is currently closing.
		bool										m_bIsClosing;
	
	private:
		// List of existing browser windows. Only accessed on the CEF UI thread.
		typedef std::list<CefRefPtr<CefBrowser> >	BrowserList;
		BrowserList									browser_list_;
	
		// Include the default reference counting implementation.
		IMPLEMENT_REFCOUNTING(ibrowser::IBrowserHandler);
		// Include the default locking implementation.
		IMPLEMENT_LOCKING(ibrowser::IBrowserHandler);
	};
}

#endif // R_IBROWSER_IBROWSERHANDLER_H
