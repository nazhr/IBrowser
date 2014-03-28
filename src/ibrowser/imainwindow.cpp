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
#include "ibrowser/imainwindow.h"
#include "ibrowser/ibrowserhandler.h"
#include "ibrowser/ibrowsersingle.h"

// Qt
#include <QtGui>
#include <QtGui/QMessageBox>
#include <QtGui/QApplication>

// cef
#include <include/cef_base.h>
#include <include/utils/resource.h>

IMainwindow::IMainwindow(QWidget *parent, Qt::WFlags flags)
	:	QMainWindow(parent, flags), 
		m_qmess(parent),
		m_tabWidget(0)
{
	m_tabWidget.reset(new ibrowser::IBrowserTabWidget(this));
	QString		tittle = "IBrowser IMainWindow System Error : ";
	m_qmess.setWindowTitle(tittle);

	// init tab page
	m_tabWidget->setMovable(true);  
	m_tabWidget->setTabsClosable(true);  
	m_tabWidget->setTabShape(QTabWidget::Triangular);
	
	// set main window's sub window tab page(tabwidget)
	setCentralWidget(m_tabWidget.get());  

	// m_ui.setupUi(this);
	resize(880, 600);
	setWindowTitle(QApplication::translate("IBrowser", "IBrowser"));

	// 启动过滤器
	// this->installEventFilter(this);
}

IMainwindow::~IMainwindow()
{

}

// public method
void IMainwindow::Initialize()
{
	try
	{
		m_tabWidget->CreateBrowserTab();

	}
	catch(std::exception &e)
	{
		m_qmess.setText(e.what());
		m_qmess.show();
	}
}

// inherit method
/*
 * @ brief : close enent response
 */
void IMainwindow::closeEvent(QCloseEvent *event)
{
	try
	{
		CefRefPtr<ibrowser::IBrowserHandler>	handler = ibrowser::IBrowserHandler::getCurrentIBrowserHandler();
		if(handler.get())
		{
			handler->CloseAllBrowsers(true);
			CefQuitMessageLoop();
			exit(0);
		}
	}
	catch(std::exception &e)
	{
		m_qmess.setText(e.what());
		m_qmess.show();
	}
	
}

void IMainwindow::resizeEvent(QResizeEvent *event)
{
	try
	{
		// CefRefPtr<ibrowser::IBrowserHandler>	handler = ibrowser::IBrowserHandler::getCurrentIBrowserHandler();
		CefRefPtr<ibrowser::IBrowserHandler>	handler = IBrowserSingle
			::Instance().getCurrentIBrowserHandler();
		if(handler.get() && !handler->IsClosing())
		{
			CefRefPtr<CefBrowser>				browser = handler->GetBrowser();
			if(browser.get())
			{
				QSize							size;
				size = event->size();
				CefWindowHandle					hwnd = browser->GetHost()->GetWindowHandle();
				if(hwnd)
				{
					HDWP							hdwp = ::BeginDeferWindowPos(1);
					DeferWindowPos(hdwp, hwnd, NULL, 
						0, URLBAR_HEIGHT, size.width(), size.height() - URLBAR_HEIGHT, 
						SWP_NOZORDER);
					EndDeferWindowPos(hdwp);
				}
				
			}
			
		}
	}
	catch(std::exception &e)
	{
		m_qmess.setText(e.what());
		m_qmess.show();
	}
}

// 过滤器设计
/*
bool IMainwindow::eventFilter(QObject * target, QEvent *event)
{
	if(event->type() == QEvent::Resize)
	{

	}
	return QMainWindow::eventFilter(target,event);
}
*/

