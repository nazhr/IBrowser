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
#include "ibrowser/global.h"

//cef
#include <include/cef_base.h>
#include <include/utils/resource.h>

void AppGetSettings(CefSettings& settings) 
{

	// Store cache data will on disk.
	// std::string cache_path = AppGetWorkingDirectory().toStdString() + "/.cache";
	// CefString(&settings.cache_path) = CefString(cache_path);
	// Completely disable logging.
	settings.log_severity = LOGSEVERITY_DISABLE;
	// The resources(cef.pak and/or devtools_resources.pak) directory.
	CefString(&settings.resources_dir_path) = CefString();
	// The locales directory.
	CefString(&settings.locales_dir_path) = CefString();
	// Enable remote debugging on the specified port.
	settings.remote_debugging_port = 8088;
	// Ignore errors related to invalid SSL certificates.
	//settings.ignore_certificate_errors = true;
}