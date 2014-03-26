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
#include "imainwindow.h"
#include "ibrowser/ibrowsersingle.h"

// Qt
#include <QtGui/QMessageBox>
#include <QtGui/QApplication>

// cef
#include <include/cef_base.h>
#include <include/utils/resource.h>

// static 
boost::scoped_ptr<IMainwindow>		IMainwindow::m_instance_prt(0);
boost::once_flag					IMainwindow::m_once_flag = BOOST_ONCE_INIT;

IMainwindow::IMainwindow(QWidget *parent, Qt::WFlags flags)
	:	QMainWindow(parent, flags), 
		m_qmess(parent)
{
	QString		tittle = "IBrowser IMainWindow System Error : ";
	m_qmess.setWindowTitle(tittle);

	m_ui.setupUi(this);
	this->resize(880, 600);
	this->setWindowTitle(QApplication::translate("IBrowser", "IBrowser"));
}

IMainwindow::~IMainwindow()
{

}

// inherit method
/*
 * @ brief : close enent response
 */
void IMainwindow::closeEvent(QCloseEvent *event)
{
	try
	{
		CefRefPtr<ibrowser::IBrowserHandler>	handler = IBrowserSingle
			::Instance().getCurrentIBrowserHandler();
		if(handler.get() && !handler->IsClosing())
		{
			CefRefPtr<CefBrowser>				browser = handler->GetBrowser();
			if(browser.get())
			{
				browser->GetHost()->CloseBrowser(false);
				CefQuitMessageLoop();
				// this->close();
			}
		}

		// 启动过滤器
		// this->installEventFilter(this);
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


