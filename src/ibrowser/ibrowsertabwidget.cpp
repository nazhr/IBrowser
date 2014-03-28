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
#include "ibrowser/ibrowsertabwidget.h"

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
	IBrowserTabWidget::IBrowserTabWidget(QWidget *parent)
		:	QTabWidget(parent),
			m_qmess(parent)
	{
		// message box 
		QString		tittle = "IBrowser IMainWindow System Error : ";
		m_qmess.setWindowTitle(tittle);

		m_client.reset(new ibrowser::IBrowserClient());
		// init
		m_parent = parent;
		m_ibtabbar = new IBTabBar();  
		setTabBar(m_ibtabbar);   
	}
	IBrowserTabWidget::~IBrowserTabWidget(){}

	void IBrowserTabWidget::CreateBrowserTab()
	{
		try
		{
			IBWidget *m_subWidget = new IBWidget();
			this->addTab(m_subWidget, "page");
			HWND browserHWnd = m_subWidget->winId();
			std::string default_url = "www.google.com.hk";
			
			m_parent->show();
			m_client->Initialize(browserHWnd, default_url);

		}
		catch(std::exception &e)
		{
			m_qmess.setText(e.what());
			m_qmess.show();
		}
	}

	// Qt Slots
	/*
	void IBrowserTabWidget::Slot_tabDrag(int index, QPoint point)  
	{  
		IBWidget	*widget = new IBWidget();  
		QWidget		*draged = this->widget(index);  
		QString		windowName = tabText(index);  
		removeTab(index);  
		connect(widget, SIGNAL(sig_doubleClickedTitleBar()), this, SLOT(slot_tabBarDoubleClicked()));  

		QGridLayout *layout = new QGridLayout;  
		layout->addWidget(draged);  
		widget->setLayout(layout);  
		widget->resize(600,400);  
		widget->move(point+pos() + this->pos());  
		widget->setWindowTitle(windowName);  
		widget->show();  
		draged->show();  
	}  

	void IBrowserTabWidget::Slot_tabBarDoubleClicked()  
	{  
		IBWidget	*widget = qobject_cast<IBWidget*>(sender());  
		QObjectList list = widget->children();  
		QTextEdit	*edit = NULL;  

		for(int i = 0;i<list.count();++i)  
		{  
			if(list[i]->inherits("QTextEdit"))  
			{  
				edit = qobject_cast<QTextEdit*>(list[i]);  
				break;  
			}  
		}  
		if(edit == NULL)  
		{  
			return ;  
		}  

		edit->setParent(this);  
		addTab(edit,widget->windowTitle());  
		delete widget;  
	} 
	*/ 

	void IBrowserTabWidget::Slot_closeTab(int index)  
	{  
		QWidget		*draged = widget(index);  
		removeTab(index);  
		delete		draged;
		int counts = count();
		if(!counts)
		{
			// m_parent->close();
			// this->close();
			exit(0);
		}

	}
	
}
