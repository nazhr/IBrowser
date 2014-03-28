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
#include "ibrowser/ibwidget.h"

// cef
#include <include/cef_app.h>

// vc
#include <string>

IBWidget::IBWidget(QWidget *parent)
	:	QWidget(parent)  
{
	QSize size = this->size();
	m_edit.reset(new QLineEdit(this));
	m_edit->resize(size.width(), URLBAR_HEIGHT);
	connect(m_edit.get(), SIGNAL(textChanged(const QString& )), this, SLOT(LETextChanged(const QString& )));
	connect(m_edit.get(), SIGNAL(returnPressed()), this, SLOT(LEReturnPressed()));
}  

IBWidget::~IBWidget()  
{  

}  

bool IBWidget::event(QEvent *event)  
{  
#ifdef unix  
	if(event->type() == QEvent::MouseButtonDblClick){   
		emit sig_doubleClickedTitleBar();  
		return true;  
	}  
#endif     
	if (event->type() == QEvent::NonClientAreaMouseButtonDblClick)  
	{  
		emit sig_doubleClickedTitleBar();  
		return true;  
	}  
	return QWidget::event(event);  
}  

// private slots
// get edit box text
void IBWidget::LETextChanged(const QString &text)
{
	
}

// response enter events
void IBWidget::LEReturnPressed()
{
	CefRefPtr<ibrowser::IBrowserHandler> handler = IBrowserSingle::
		Instance().GetCurrentIBrowserHandler();
	if(handler.get())
	{
		std::string text = m_edit->text().toUtf8().constData();
		CefRefPtr<CefBrowser>	browser = handler->GetBrowser();
		if(browser.get())
		{
			CefRefPtr<CefFrame>		frame = browser->GetFocusedFrame();
			if(frame.get())
			{
				frame->LoadURL(text);
			}
		}
		
	}
	
}