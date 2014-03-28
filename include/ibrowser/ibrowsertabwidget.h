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

#ifndef R_IBROWSER_IBROWSERTABWIDGET_H
#define R_IBROWSER_IBROWSERTABWIDGET_H

// ibrowser
#include "ibrowser/ibrowserclient.h"
#include "ibrowser/ibtabbar.h"
#include "ibrowser/ibwidget.h"

// cef
#include <include/cef_app.h>
#include <include/utils/resource.h>

// Qt 
#include <QtGui>
#include <QtGui/QWidget>
#include <QtGui/QLineEdit>
#include <QtGui/QHBoxLayout>
#include <QtGui/QTabWidget>

namespace ibrowser
{
	class IBrowserTabWidget : public QTabWidget
	{
		Q_OBJECT
	public :
		IBrowserTabWidget(QWidget *parent = 0);
		virtual ~IBrowserTabWidget();

	public :
		void CreateBrowserTab();

	public : // inherit QTabWidget

	public :
		IBTabBar		*m_ibtabbar;

	signals : // default signals
		void SenderCurrentIndex(int);

	private slots : // Qt slots event
		// virtual void Slot_tabBarDoubleClicked();           
		// virtual void Slot_tabDrag(int index, QPoint point); 
		virtual void Slot_closeTab(int);
		virtual void AddTabPage();

	private : // non static member 
		QWidget										*m_parent;
		QMessageBox									m_qmess;
		boost::scoped_ptr<ibrowser::IBrowserClient>	m_client;

	private : // static member 
		

	};
}

#endif // R_IBROWSER_IBROWSERTABWIDGET_H