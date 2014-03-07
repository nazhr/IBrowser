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
		static IBrowserHandler* GetInstance();

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
		CefRefPtr<CefBrowser>			GetBrowser();
		CefRefPtr<IBrowserHandler>		GetHandler();
		void							SetMainHwnd(CefWindowHandle hwnd);
		bool							IsClosing();

	private :
		static IBrowserHandler*				m_instance;
		static CefRefPtr<IBrowserHandler>	m_handler;
		CefRefPtr<CefBrowser>				m_browser;
		int									m_browserId;
		// The main frame window handle
		CefWindowHandle						m_mainhwnd;
		// True if the main browser window is currently closing.
		bool								m_bIsClosing;
	
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
