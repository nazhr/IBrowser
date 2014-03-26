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
#include "ibrowser/ibrowserclient.h"
#include "ibrowser/ibrowsertab.h"
#include "ibrowser/ibrowsersingle.h"

// Qt
#include <QtGui/QWidget>
#include <QtGui/QMessageBox>
#include <QtGui/QApplication>

namespace ibrowser 
{
	// static member init
	HINSTANCE				IBrowserClient::m_hInstance = NULL;
	CefRefPtr<IBrowserApp>	IBrowserClient::m_cef_app(0);

	IBrowserClient::IBrowserClient()
	{

	}

	IBrowserClient::~IBrowserClient(){}


	int IBrowserClient::Initialize(QWidget *parent)
	{
		try
		{
			HINSTANCE				hInstance = (HINSTANCE)GetModuleHandle(NULL);
			
			// cef
			CefMainArgs				main_args(hInstance);
			CefRefPtr<IBrowserApp>	m_cef_app = new IBrowserApp;
			int						exit_code = CefExecuteProcess(main_args, m_cef_app.get());
			if (exit_code >= 0) 
			{
				return 0;
			}
			CefSettings				settings;

			AppGetSettings(settings);

			// create sub process
			CefString(&settings.browser_subprocess_path).FromASCII("subprocess.exe");

			// cef init
			CefInitialize(main_args, settings, m_cef_app.get());

			m_ibrowser_tab = new IBrowserTab(parent);
			m_ibrowser_tab->CreateTab();

			// cef message loop
			CefRunMessageLoop();

			CefShutdown();
			
		}
		catch(std::exception &e)
		{
			QMessageBox qmess;
			qmess.setWindowTitle(QApplication::translate("IBrowser IMainWindow System Error : ", 
				"IBrowser IMainWindow System Error : "));
			qmess.setText(QApplication::translate(e.what(), e.what()));
			qmess.show();
		}
		return 1;
	}
}
