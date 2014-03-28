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

// ibrowser
#include "ibrowser/ibrowserhandler.h"
#include "ibrowser/global.h"

// vc
#include <sstream>
#include <string>

// cef
#include <include/utils/util.h>
#include <include/cef_app.h>
#include <include/cef_runnable.h>

//boost
#include <boost/scope_exit.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/thread/once.hpp>

namespace ibrowser 
{
	// co
	IBrowserHandler::IBrowserHandler() 
		:	m_mainhwnd(NULL), 
			m_browser(NULL),
			m_browserId(0),
			m_bIsClosing(false),
			browser_list_(NULL),
			m_handler(0)
	{
		CefRefPtr<CefCommandLine>	cmd = CefCommandLine::GetGlobalCommandLine();
		if (cmd->HasSwitch("url"))
			m_startupURL = cmd->GetSwitchValue("url");
		if (m_startupURL.empty())
			m_startupURL = "http://www.google.com/";
	}

	IBrowserHandler::~IBrowserHandler() 
	{
		
	}

	void IBrowserHandler::OnAfterCreated(CefRefPtr<CefBrowser> browser) 
	{
		REQUIRE_UI_THREAD();
		
		AutoLock lock_scope(this);
		if (!m_browser.get())   {
			// We need to keep the main child window, but not popup windows
			m_browser = browser;
			m_browserId = browser->GetIdentifier();
		} else if (browser->IsPopup()) {
			// Add to the list of popup browsers.
			browser_list_.push_back(browser);
		}

		// Add to the list of existing browsers.
		browser_list_.push_back(browser);
		
		// set current browser
		SetMainBrowser(browser);
		
	}

	void IBrowserHandler::OnAddressChange(	CefRefPtr<CefBrowser>	browser, 
											CefRefPtr<CefFrame>		frame, 
											const CefString			&url)
	{
		REQUIRE_UI_THREAD();

		if(m_browserId == browser->GetIdentifier() && frame->IsMain())
		{
			::SetWindowText(m_editHwnd, std::wstring(url).c_str());
		}
	}

	void IBrowserHandler::OnTitleChange(CefRefPtr<CefBrowser> browser,
									  const CefString& title) 
	{
		REQUIRE_UI_THREAD();

		CefWindowHandle hwnd = browser->GetHost()->GetWindowHandle();
		if(m_browserId == browser->GetIdentifier())
		{
			hwnd = ::GetParent(::GetParent(hwnd));
		}
		::SetWindowText(hwnd, std::wstring(title).c_str());
	}

	bool IBrowserHandler::DoClose(CefRefPtr<CefBrowser> browser)
	{
		REQUIRE_UI_THREAD();

		// Closing the main window requires special handling. See the DoClose()
		// documentation in the CEF header for a detailed destription of this
		// process.

		if(m_browserId == browser->GetIdentifier())
		{
			// Notify the browser that the parent window is about to close.
			browser->GetHost()->ParentWindowWillClose();

			// Set a flag to indicate that the window close should be allowed.
			m_bIsClosing = true;
		}
		return false;
	}

	void IBrowserHandler::OnBeforeClose(CefRefPtr<CefBrowser> browser) 
	{
		REQUIRE_UI_THREAD();
		
		if(m_browserId == browser->GetIdentifier())
		{
			// Free the browser pointer so that the browser can be destroyed
			m_browser = NULL;	
		}
		// Remove from the list of existing browsers.
		BrowserList::iterator bit = browser_list_.begin();
		for (; bit != browser_list_.end(); ++bit) 
		{
			if ((*bit)->IsSame(browser)) 
			{
				browser_list_.erase(bit);
				break;
			}
		}

		if (browser_list_.empty()) 
		{
			// All browser windows have closed. Quit the application message loop.
			this->m_bIsClosing = true;
			CefQuitMessageLoop();
		}
	}

	void IBrowserHandler::OnLoadError(	CefRefPtr<CefBrowser>	browser,
										CefRefPtr<CefFrame>		frame,
										ErrorCode				errorCode,
										const CefString			&errorText,
										const CefString			&failedUrl) 
	{
		REQUIRE_UI_THREAD();

		// Don't display an error for downloaded files.
		if (errorCode == ERR_ABORTED)
			return;

		// Display a load error message.
		std::stringstream ss;
		ss << "<html><body bgcolor=\"white\">"
			"<h2>Failed to load URL " << std::string(failedUrl) <<
			" with error " << std::string(errorText) << " (" << errorCode <<
			").</h2></body></html>";
		frame->LoadString(ss.str(), failedUrl);
	}

	void IBrowserHandler::CloseAllBrowsers(bool force_close) 
	{
		if (!CefCurrentlyOn(TID_UI)) {
			// Execute on the UI thread.
			CefPostTask(TID_UI,
				NewCefRunnableMethod(this, &IBrowserHandler::CloseAllBrowsers,
				force_close));
			return;
		}

		if (browser_list_.empty())
			return;

		BrowserList::const_iterator it = browser_list_.begin();
		for (; it != browser_list_.end(); ++it)
			(*it)->GetHost()->CloseBrowser(force_close);
	}

	void IBrowserHandler::SetEditHwnd(CefWindowHandle hwnd) {
		AutoLock lock_scope(this);
		m_editHwnd = hwnd;
	}

	void IBrowserHandler::SetButtonHwnds(	CefWindowHandle backHwnd,
											CefWindowHandle forwardHwnd,
											CefWindowHandle reloadHwnd,
											CefWindowHandle stopHwnd) 
	{
			AutoLock lock_scope(this);
			m_backHwnd = backHwnd;
			m_forwardHwnd = forwardHwnd;
			m_reloadHwnd = reloadHwnd;
			m_stopHwnd = stopHwnd;
	}

}
