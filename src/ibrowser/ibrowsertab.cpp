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
#include "ibrowser/ibrowsertab.h"
#include "ibrowser/ibrowsersingle.h"
#include "ibrowser/ibrowserhandler.h"

// Qt
#include <QtGui/QWidget>
#include <QtGui/QMessageBox>
#include <QtGui/QApplication>
#include <QtGui/QLineEdit>
#include <QtCore/QSize>

// cef
#include <include/cef_base.h>
#include <include/utils/resource.h>

namespace ibrowser 
{
	IBrowserTab::IBrowserTab(QWidget *parent)
		:	m_parent_widget(parent), 
			m_sub_widget(0)
	{

	}
	IBrowserTab::~IBrowserTab(){}

	bool IBrowserTab::CreateTab()
	{
		try
		{
			// ibrowser and cef handler
			CefRefPtr<ibrowser::IBrowserHandler> handler = new IBrowserHandler();
			IBrowserSingle::Instance().setCurrentIBrowserHandler(handler.get());

			QSize		size = m_parent_widget->size();

			// create sub window
			m_sub_widget = new QWidget(m_parent_widget);
			// sub window setting
			m_sub_widget->resize(size.width(), size.height());
			// edit box setting
			m_edit_box = new QLineEdit(m_sub_widget);
			m_edit_box->resize(size.width(), URLBAR_HEIGHT);
			// hwnd window
			HWND		tab_hWnd = m_sub_widget->winId();
			
			CreateBrowser(tab_hWnd);

			m_layout = new QHBoxLayout(m_parent_widget);
			m_layout->addWidget(m_sub_widget);
			m_parent_widget->setLayout(m_layout);
			m_parent_widget->show();

		}
		catch(std::exception &e)
		{
			QMessageBox qmess;
			qmess.setWindowTitle(QApplication::translate("IBrowser Tab System Error : ", 
				"IBrowser IMainWindow System Error : "));
			qmess.setText(QApplication::translate(e.what(), e.what()));
			qmess.show();
		}
		return 1;
	}

	void	IBrowserTab::CreateBrowser(HWND tab_hWnd)
	{
		try
		{
			// crate window
			CefRefPtr<ibrowser::IBrowserHandler> handler = IBrowserSingle::
				Instance().getCurrentIBrowserHandler();
			RECT		rect_tab;
			::GetClientRect(tab_hWnd, &rect_tab);

			// set browser screen size 
			// set browser top pos
			rect_tab.top += URLBAR_HEIGHT;

			CefBrowserSettings browserSettings;
			CefString(&browserSettings.default_encoding) = "utf-8";
			browserSettings.file_access_from_file_urls = STATE_ENABLED;
			browserSettings.universal_access_from_file_urls = STATE_ENABLED;
			CefWindowInfo	info;
			info.SetAsChild(tab_hWnd, rect_tab);

			CefBrowserHost::CreateBrowser(info, handler.get(), handler->GetStartupURL(), browserSettings);
			
		}
		catch(std::exception &e)
		{
			QMessageBox qmess;
			qmess.setWindowTitle(QApplication::translate("IBrowser Tab System Error : ", 
				"IBrowser IMainWindow System Error : "));
			qmess.setText(QApplication::translate(e.what(), e.what()));
			qmess.show();
		}
	}

	bool IBrowserTab::BrowserLoadUrl(const std::wstring &url)
	{
		IBrowserHandler				*handler = IBrowserSingle::
									Instance().getCurrentIBrowserHandler();
		if(!url.empty() && handler)
		{
			CefRefPtr<CefBrowser>	browser = handler->GetBrowser();
			browser->GetMainFrame()->LoadURL(url);
			return true;
		}	
		return false;
	}
}
