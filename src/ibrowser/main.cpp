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
#include "ibrowser/ibrowserapp.h"

// vc
#include <windows.h>

// Set to 0 to disable sandbox support.
#define CEF_ENABLE_SANDBOX 1

// Entry point function for all processes.
int APIENTRY wWinMain(HINSTANCE hInstance,
					  HINSTANCE hPrevInstance,
					  LPTSTR    lpCmdLine,
					  int       nCmdShow) {
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// Provide CEF with command-line arguments.
	CefMainArgs main_args(hInstance);

	// SimpleApp implements application-level callbacks. It will create the first
	// browser instance in OnContextInitialized() after CEF has initialized.
	CefRefPtr<ibrowser::IBrowserApp> app(new ibrowser::IBrowserApp);

	// CEF applications have multiple sub-processes (render, plugin, GPU, etc)
	// that share the same executable. This function checks the command-line and,
	// if this is a sub-process, executes the appropriate logic.
	int exit_code = CefExecuteProcess(main_args, app.get());
	if (exit_code >= 0) {
	  // The sub-process has completed so return here.
	  return exit_code;
	}

	// Specify CEF global settings here.
	CefSettings settings;

	// Initialize CEF.
	CefInitialize(main_args, settings, app.get());

	// Run the CEF message loop. This will block until CefQuitMessageLoop() is
	// called.
	CefRunMessageLoop();

	// Shut down CEF.
	CefShutdown();

	return 0;
}