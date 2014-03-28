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

#ifndef R_IBROWSER_IMAINWINDOW_H
#define R_IBROWSER_IMAINWINDOW_H

// ibrowser
#include "ibrowser/ui_ibrowser.h"
#include "ibrowser/ibrowsertabwidget.h"

// Qt
#include <QtGui/QMainWindow>
#include <QtGui/QCloseEvent>
#include <QtGui/QMessageBox>
#include <QtGui/QResizeEvent>

// Boost
#include <boost/thread/once.hpp>
#include <boost/scoped_ptr.hpp>

// cef
#include <include/cef_base.h>
#include <include/utils/resource.h>


class IMainwindow : public QMainWindow
{
	Q_OBJECT

public:
	IMainwindow(QWidget *parent = 0, Qt::WFlags flags = 0);
	~IMainwindow();

public : // inherit function
	virtual void closeEvent(QCloseEvent *event);
	virtual void resizeEvent(QResizeEvent *event);
	// virtual bool eventFilter(QObject *, QEvent *);
	void Initialize();

public : // non static inline function
	ibrowser::IBrowserTabWidget *tabWidget()
	{
		return m_tabWidget.get();
	}

public : // non staic function member

public : // staic function member
	static	void Init()
	{
		m_instance_prt.reset(new IMainwindow());
	}

	static	IMainwindow &GetCurrenMainWindow()
	{
		boost::call_once(IMainwindow::Init, m_once_flag);
		return *m_instance_prt;
	}

private :// static member
	static	boost::scoped_ptr<IMainwindow>			m_instance_prt;
	static	boost::once_flag						m_once_flag;

private: // qt
	Ui::imainwindowClass							m_ui;
	QMessageBox										m_qmess;
	boost::scoped_ptr<ibrowser::IBrowserTabWidget>	m_tabWidget;

};

#endif // R_IBROWSER_IMAINWINDOW_H
