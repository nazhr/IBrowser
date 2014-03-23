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

// cef
#include "include/cef_app.h"

namespace ibrowser
{
	class IBrowserApp:	public CefApp, 
						public CefBrowserProcessHandler,
						public CefRenderProcessHandler
	{
	public : 
		IBrowserApp();
		virtual ~IBrowserApp();

	private :	// cef		
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
		virtual void OnContextInitialized() OVERRIDE;
	
	private:
		// Include the default reference counting implementation.
		IMPLEMENT_REFCOUNTING(IBrowserApp);
	};

}

#endif // R_IBROWSER_IBROWSERAPP_H