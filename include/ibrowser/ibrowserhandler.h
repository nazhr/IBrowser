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
#include <boost/scope_exit.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/thread/once.hpp>

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

	public :
		/*
		 * @brief : cef inherit
		 */
		// CefClient methods:
		virtual CefRefPtr<CefDisplayHandler> GetDisplayHandler()			OVERRIDE 
		{
			return this;
		}
		virtual CefRefPtr<CefLifeSpanHandler> GetLifeSpanHandler()			OVERRIDE 
		{
			return this;
		}
		virtual CefRefPtr<CefLoadHandler> GetLoadHandler()					OVERRIDE 
		{
			return this;
		}

		// CefDisplayHandler methods : address change
		virtual void OnAddressChange(	CefRefPtr<CefBrowser>	browser, 
										CefRefPtr<CefFrame>		frame, 
										const CefString			&url)		OVERRIDE;

		// CefDisplayHandler methods:
		virtual void OnTitleChange(	CefRefPtr<CefBrowser>	browser,
									const CefString			&title)			OVERRIDE;

		// CefLifeSpanHandler methods:
		virtual void OnAfterCreated(CefRefPtr<CefBrowser> browser)			OVERRIDE;
		virtual bool DoClose(CefRefPtr<CefBrowser> browser)					OVERRIDE;
		virtual void OnBeforeClose(CefRefPtr<CefBrowser> browser)			OVERRIDE;

		// CefLoadHandler methods:
		virtual void OnLoadError(CefRefPtr<CefBrowser> browser,
			CefRefPtr<CefFrame> frame,
			ErrorCode errorCode,
			const CefString& errorText,
			const CefString& failedUrl)										OVERRIDE;

		// Request that all existing browser windows close.
		void CloseAllBrowsers(bool force_close);

		// private
	public :
		CefWindowHandle GetMainHwnd() { return m_mainHwnd; }
		void SetEditHwnd(CefWindowHandle hwnd);
		void SetButtonHwnds(CefWindowHandle backHwnd,
							CefWindowHandle forwardHwnd,
							CefWindowHandle reloadHwnd,
							CefWindowHandle stopHwnd);
		inline CefRefPtr<CefBrowser>				GetBrowser();
		inline CefRefPtr<IBrowserHandler>			GetCefPtrHandler();
		inline void									SetMainHwnd(CefWindowHandle hwnd);
		// Returns the startup URL.
		inline std::string							GetStartupURL();
		inline bool									IsClosing();

	private : // static member

	private :
		CefRefPtr<IBrowserHandler>					m_handler;
		CefRefPtr<CefBrowser>						m_browser;
		CefWindowHandle								m_mainHwnd;
		int											m_browserId;
		// The startup URL.
		std::string									m_startupURL;
		// The main frame window handle
		CefWindowHandle								m_mainhwnd;
		// The edit window handle
		CefWindowHandle								m_editHwnd;
		// The button window handles
		CefWindowHandle								m_backHwnd;
		CefWindowHandle								m_forwardHwnd;
		CefWindowHandle								m_stopHwnd;
		CefWindowHandle								m_reloadHwnd;
		// True if the main browser window is currently closing.
		bool										m_bIsClosing;

	private:
		// List of existing browser windows. Only accessed on the CEF UI thread.
		typedef std::list<CefRefPtr<CefBrowser> >	BrowserList;
		BrowserList									browser_list_;

		// Include the default reference counting implementation.
		IMPLEMENT_REFCOUNTING(IBrowserHandler);
		// Include the default locking implementation.
		IMPLEMENT_LOCKING(IBrowserHandler);
	};

	inline CefRefPtr<IBrowserHandler> 
		IBrowserHandler::GetCefPtrHandler()
	{
		return this;
	}

	inline CefRefPtr<CefBrowser> 
		IBrowserHandler::GetBrowser() 
	{ 
		return m_browser; 
	}

	// Returns the startup URL.
	inline std::string IBrowserHandler::GetStartupURL() 
	{ 
		return m_startupURL;
	}

	inline void IBrowserHandler::SetMainHwnd(CefWindowHandle hwnd) 
	{
		AutoLock lock_scope(this);
		m_mainhwnd = hwnd;
	}

	inline bool IBrowserHandler::IsClosing()
	{
		return m_bIsClosing;
	}
}

#endif // R_IBROWSER_IBROWSERHANDLER_H
