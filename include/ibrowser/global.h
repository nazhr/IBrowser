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

/*
 * ibrowser global function
 */

#ifndef R_IBROWSER_GLOBAL_H
#define R_IBROWSER_GLOBAL_H

// cef
#include <include/cef_app.h>
#include <include/cef_base.h>
#include <include/utils/resource.h>
#include <include/cef_browser.h>
#include <include/cef_command_line.h>
#include <include/cef_frame.h>
#include <include/cef_runnable.h>

// Qt
#include <QString>
#include <QApplication>


// boost
#include <boost/scoped_ptr.hpp>

// window info
// window and box size
#define		MAX_LOADSTRING	100
#define		MAX_URL_LENGTH  255
#define		URLBAR_HEIGHT	24
#define		TAB_BTN_WIDTH	124
#define		TAB_BTN_HEIGTH	24

// QApplication global
static	QApplication *g_qApplication = NULL;

/*
 * @brief : Returns the application working directory.
 */
QString AppGetWorkingDirectory();

/*
 * @brief : Returns the application settings based on command line arguments.
 */
void AppGetSettings(CefSettings& settings);

#endif // R_IBROWSER_GLOBAL_H