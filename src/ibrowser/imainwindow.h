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
#include "ibrowser/ibrowserapp.h"
#include "ibrowser/ibrowserhandler.h"

// Qt
#include <QtGui/QMainWindow>

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
	static	boost::scoped_ptr<IMainwindow>		m_instance_prt;
	static	boost::once_flag					m_once_flag;

private: // qt
	Ui::imainwindowClass ui;
};

#endif // R_IBROWSER_IMAINWINDOW_H
