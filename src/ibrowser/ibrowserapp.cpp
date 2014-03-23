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

namespace ibrowser
{


	IBrowserApp::IBrowserApp() {}
	IBrowserApp::~IBrowserApp() {}

	void IBrowserApp::OnContextInitialized() 
	{
		QMessageBox qmess;
		qmess.setWindowTitle(QApplication::translate("IBrowser IMainWindow System Error : ", 
			"IBrowser IMainWindow System Error : "));
		qmess.setText(QApplication::translate("tst", "test"));
	}
}
