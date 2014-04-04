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
			// add button
			m_addbtn = QSharedPointer<QPushButton>(new QPushButton("+"));
			m_addbtn->setStyleSheet("QPushButton \
													{ \
														background-color: PowderBlue; \
														color: MediumPurple; \
														font: bold 14px; \
													}"
									);
			m_addbtn->setFixedSize(18, 18);
			setCornerWidget(m_addbtn.data());

			// signals connect
			InitConnect();
			
			// add tab page
			QSharedPointer<IBWidget>	subWidget = QSharedPointer<IBWidget>(new IBWidget());
			m_widgetList_.push_back(subWidget);
			subWidget->resize(this->size());
			this->addTab(subWidget.data(), "New Page");
			HWND						browserHWnd = subWidget->winId();
			std::string					default_url = "about:blank";
			
			m_parent->show();
			m_client->Initialize(browserHWnd, default_url);

		}
		catch(std::exception &e)
		{
			m_qmess.setText(e.what());
			m_qmess.show();
		}
	}

	void IBrowserTabWidget::InitConnect()
	{
		try
		{
			// signals connect
			// connect(m_ibtabbar, SIGNAL(sig_tabDrag(int, QPoint)), this, SLOT(slot_tabDrag(int, QPoint)));  
			// close tab page siginal
			connect(this, SIGNAL(tabCloseRequested(int)), this, SLOT(Slot_closeTab(int)));  
			// mouse click tab page set current tab page siginal
			connect(this, SIGNAL(currentChanged(int)), this, SLOT(setCurrentIndex(int)));
			// new tab page set current tab page siginal
			connect(this, SIGNAL(SenderCurrentIndex(int)), this,SLOT(setCurrentIndex(int)));
			// new tab page siginal
			connect(m_addbtn.data(), SIGNAL(released()), this,SLOT(AddTabPage()));
			// set current tab title
			connect(SignalsSlots::GetCurrentSignals(), SIGNAL(CurrentTittle(std::string)), 
				this, SLOT(SetTabTittle(std::string)));
		}
		catch(std::exception &e)
		{
			m_qmess.setText(e.what());
			m_qmess.show();
		}
	}

	void IBrowserTabWidget::SetTabTittle(std::string tittle)
	{
		// string utf8 to qt code utf8
		QString		text = QString::fromUtf8(tittle.c_str());
		setTabText(currentIndex(), text);
	}

	void IBrowserTabWidget::AddTabPage()
	{
		QSharedPointer<IBWidget>	subWidget = QSharedPointer<IBWidget>(new IBWidget());
		m_widgetList_.push_back(subWidget);
		subWidget->resize(this->size());
		this->addTab(subWidget.data(), "New Page");
		HWND						browserHWnd = subWidget->winId();
		std::string					default_url = "about:blank";
		m_client->CreateBrowser(browserHWnd, default_url);

		// set current tab page
		int							index = currentIndex();
		emit SenderCurrentIndex(index + 1);
		subWidget->SetBrowserId(index);
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
		m_client->CloseBrowser();
		removeTab(index);  
		delete		draged;
		int counts = count();
		if(!counts)
		{
			// m_parent->close();
		}
	}
	
}
