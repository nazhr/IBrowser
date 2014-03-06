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

//ibrowser
#include "ibrowser/util.h"
#include "ibrowser/ibrowserapp.h"
#include "ibrowser/ibrowserhandler.h"

// vc
#include <string>

// cef
#include "include/cef_browser.h"
#include "include/cef_command_line.h"

namespace ibrowser
{


	IBrowserApp::IBrowserApp() {}
	IBrowserApp::~IBrowserApp() {}

	void IBrowserApp::OnContextInitialized() {
		REQUIRE_UI_THREAD();

		// Information used when creating the native window.
		CefWindowInfo window_info;

#if defined(OS_WIN)
		// On Windows we need to specify certain flags that will be passed to
		// CreateWindowEx().
		window_info.SetAsPopup(NULL, "ibrowser");
#endif

		// SimpleHandler implements browser-level callbacks.
		CefRefPtr<IBrowserHandler> handler(new IBrowserHandler());

		// Specify CEF browser settings here.
		CefBrowserSettings browser_settings;

		std::string url;

		// Check if a "--url=" value was provided via the command-line. If so, use
		// that instead of the default URL.
		CefRefPtr<CefCommandLine> command_line =
			CefCommandLine::GetGlobalCommandLine();
		url = command_line->GetSwitchValue("url");
		if (url.empty())
			url = "http://www.google.com.hk";

		// Create the first browser window.
		CefBrowserHost::CreateBrowserSync(window_info, handler.get(), url, browser_settings);
	}
}
