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

#ifndef R_IBROWSER_IBROWSERAPP_H
#define R_IBROWSER_IBROWSERAPP_H

// ibrowser
// #include "ibrowser/ibrowserrenderer.h"

// Qt
#include <QtGui/QApplication>
#include <QtGui/QMessageBox>

// VC
#include <map>
#include <set>
#include <string>
#include <utility>
#include <vector>

// cef
#include <include/cef_app.h>
#include <include/cef_base.h>
#include <include/cef_load_handler.h>
#include <include/utils/util.h>
#include <include/cef_browser.h>
#include <include/cef_command_line.h>

class IBrowserApp:	public CefApp, 
					public CefBrowserProcessHandler,
					public CefRenderProcessHandler
{
public : 
	IBrowserApp();
	virtual ~IBrowserApp();

public :
	class IBrowserDelegate : public virtual CefBase 
	{
	public:
		virtual void OnContextInitialized(CefRefPtr<IBrowserApp> app);

		virtual void OnBeforeChildProcessLaunch(
			CefRefPtr<IBrowserApp>		app,
			CefRefPtr<CefCommandLine>	command_line);

		virtual void OnRenderProcessThreadCreated(	
			CefRefPtr<IBrowserApp>	app,
			CefRefPtr<CefListValue> extra_info);
	};

	typedef std::set<CefRefPtr<IBrowserDelegate> > BrowserDelegateSet;
	// Interface for renderer delegates. All RenderDelegates must be returned via
	// CreateRenderDelegates. Do not perform work in the RenderDelegate
	// constructor. See CefRenderProcessHandler for documentation.
	class RenderDelegate : public virtual CefBase 
	{
	public:
		virtual void OnRenderThreadCreated(	
			CefRefPtr<IBrowserApp>	app,
			CefRefPtr<CefListValue>	extra_info);

		virtual void OnWebKitInitialized(CefRefPtr<IBrowserApp> app) ;

		virtual void OnBrowserCreated(	
			CefRefPtr<IBrowserApp>	app,
			CefRefPtr<CefBrowser>	browser);

		virtual void OnBrowserDestroyed(
			CefRefPtr<IBrowserApp>	app,
			CefRefPtr<CefBrowser>	browser);

		virtual CefRefPtr<CefLoadHandler> GetLoadHandler(CefRefPtr<IBrowserApp> app);

		virtual bool OnBeforeNavigation(
			CefRefPtr<IBrowserApp>	app,
			CefRefPtr<CefBrowser>	browser,
			CefRefPtr<CefFrame>		frame,
			CefRefPtr<CefRequest>	request,
			cef_navigation_type_t	navigation_type,
			bool					is_redirect);

		virtual void OnContextCreated(	
			CefRefPtr<IBrowserApp>	app,
			CefRefPtr<CefBrowser>	browser,
			CefRefPtr<CefFrame>		frame,
			CefRefPtr<CefV8Context>	context);

		virtual void OnContextReleased(	
			CefRefPtr<IBrowserApp>	app,
			CefRefPtr<CefBrowser>	browser,
			CefRefPtr<CefFrame>		frame,
			CefRefPtr<CefV8Context>	context);

		virtual void OnUncaughtException(	
			CefRefPtr<IBrowserApp>		app,
			CefRefPtr<CefBrowser>		browser,
			CefRefPtr<CefFrame>			frame,
			CefRefPtr<CefV8Context>		context,
			CefRefPtr<CefV8Exception>	exception,
			CefRefPtr<CefV8StackTrace>	stackTrace);

		virtual void OnFocusedNodeChanged(	
			CefRefPtr<IBrowserApp>	app,
			CefRefPtr<CefBrowser>	browser,
			CefRefPtr<CefFrame>		frame,
			CefRefPtr<CefDOMNode>	node);

		// Called when a process message is received. Return true if the message was
		// handled and should not be passed on to other handlers. RenderDelegates
		// should check for unique message names to avoid interfering with each
		// other.
		virtual bool OnProcessMessageReceived(	
			CefRefPtr<IBrowserApp>			app,
			CefRefPtr<CefBrowser>			browser,
			CefProcessId					source_process,
			CefRefPtr<CefProcessMessage>	message);
	};

	typedef std::set<CefRefPtr<RenderDelegate> > RenderDelegateSet;

private :	// cef		
	// Creates all of the IBrowserDelegate objects. Implemented in
	// client_app_delegates.
	static void CreateBrowserDelegates(BrowserDelegateSet& delegates);

	// Creates all of the RenderDelegate objects. Implemented in
	// client_app_delegates.
	static void CreateRenderDelegates(RenderDelegateSet& delegates);

	// CefApp methods:
	virtual CefRefPtr<CefBrowserProcessHandler> GetBrowserProcessHandler()
		OVERRIDE 
	{ 
		return this;
	}

	virtual CefRefPtr<CefRenderProcessHandler> GetRenderProcessHandler()
		OVERRIDE 
	{ 
		return this; 
	}

	// CefBrowserProcessHandler methods:
	virtual void OnContextInitialized();

private :
	// Set of supported BrowserDelegates.
	BrowserDelegateSet	browser_delegates_;

	// Set of supported RenderDelegates.
	RenderDelegateSet	render_delegates_;

private :
	// Include the default reference counting implementation.
	IMPLEMENT_REFCOUNTING(IBrowserApp);
};

#endif // R_IBROWSER_IBROWSERAPP_H