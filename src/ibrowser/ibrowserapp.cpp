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
#include "ibrowser/ibrowserapp.h"
#include "ibrowser/ibrowserhandler.h"

// vc
#include <string>

// cef
#include <include/utils/util.h>
#include <include/cef_browser.h>
#include <include/cef_command_line.h>

// Qt
#include <QtGui/QApplication>
#include <QtGui/QMessageBox>

// ibrowserapp
IBrowserApp::IBrowserApp()
{
	CreateBrowserDelegates(browser_delegates_);
	CreateRenderDelegates(render_delegates_);
}

IBrowserApp::~IBrowserApp(){}

// public member IBrowserDelegate : public member function
void IBrowserApp::IBrowserDelegate::OnContextInitialized(CefRefPtr<IBrowserApp> app) 
{}

void IBrowserApp::IBrowserDelegate::OnBeforeChildProcessLaunch(
	CefRefPtr<IBrowserApp>		app,
	CefRefPtr<CefCommandLine>	command_line) 
{}

void IBrowserApp::IBrowserDelegate::OnRenderProcessThreadCreated(	
	CefRefPtr<IBrowserApp>	app,
	CefRefPtr<CefListValue> extra_info) 
{}

// public member RenderDelegate : public member function
void IBrowserApp::RenderDelegate::OnRenderThreadCreated(
	CefRefPtr<IBrowserApp>	app,
	CefRefPtr<CefListValue>	extra_info) 
{}

void IBrowserApp::RenderDelegate::OnWebKitInitialized(CefRefPtr<IBrowserApp> app) 
{}

void IBrowserApp::RenderDelegate::OnBrowserCreated(	
	CefRefPtr<IBrowserApp>	app,
	CefRefPtr<CefBrowser>	browser) 
{}

void IBrowserApp::RenderDelegate::OnBrowserDestroyed(	
	CefRefPtr<IBrowserApp>	app,
	CefRefPtr<CefBrowser>	browser) 
{}

CefRefPtr<CefLoadHandler> IBrowserApp::RenderDelegate::GetLoadHandler(
	CefRefPtr<IBrowserApp>	app) 
{
	return NULL;
}

bool IBrowserApp::RenderDelegate::OnBeforeNavigation(	
	CefRefPtr<IBrowserApp>	app,
	CefRefPtr<CefBrowser>	browser,
	CefRefPtr<CefFrame>		frame,
	CefRefPtr<CefRequest>	request,
	cef_navigation_type_t	navigation_type,
	bool					is_redirect) 
{
	return false;  // Allow the navigation to proceed.
}

void IBrowserApp::RenderDelegate::OnContextCreated(	
	CefRefPtr<IBrowserApp>		app,
	CefRefPtr<CefBrowser>		browser,
	CefRefPtr<CefFrame>			frame,
	CefRefPtr<CefV8Context>		context) 
{}

void IBrowserApp::RenderDelegate::OnContextReleased(
	CefRefPtr<IBrowserApp>	app,
	CefRefPtr<CefBrowser>	browser,
	CefRefPtr<CefFrame>		frame,
	CefRefPtr<CefV8Context>	context) 
{}

void IBrowserApp::RenderDelegate::OnUncaughtException(	
	CefRefPtr<IBrowserApp>		app,
	CefRefPtr<CefBrowser>		browser,
	CefRefPtr<CefFrame>			frame,
	CefRefPtr<CefV8Context>		context,
	CefRefPtr<CefV8Exception>	exception,
	CefRefPtr<CefV8StackTrace>	stackTrace) 
{}

void IBrowserApp::RenderDelegate::OnFocusedNodeChanged(	
	CefRefPtr<IBrowserApp>	app,
	CefRefPtr<CefBrowser>	browser,
	CefRefPtr<CefFrame>		frame,
	CefRefPtr<CefDOMNode>	node) 
{}

bool IBrowserApp::RenderDelegate::OnProcessMessageReceived(	
	CefRefPtr<IBrowserApp>			app,
	CefRefPtr<CefBrowser>			browser,
	CefProcessId					source_process,
	CefRefPtr<CefProcessMessage>	message) 
{
	return false;
}

// private static member function
// static
void IBrowserApp::CreateBrowserDelegates(IBrowserApp::BrowserDelegateSet& delegates) 
{
}

// static
void IBrowserApp::CreateRenderDelegates(IBrowserApp::RenderDelegateSet& delegates) 
{
	// ibrowserrenderer::CreateRenderDelegates(delegates);
}

// CefBrowserProcessHandler methods:
void IBrowserApp::OnContextInitialized() 
{
	QMessageBox qmess;
	qmess.setWindowTitle(QApplication::translate("IBrowser IMainWindow System Error : ", 
		"IBrowser IMainWindow System Error : "));
	qmess.setText(QApplication::translate("tst", "test"));
	qmess.show();
}

// 
