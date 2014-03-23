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
#include "imainwindow.h"

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
	: QMainWindow(parent, flags)
{
	this->resize(880, 600);
	this->setWindowTitle(QApplication::translate("IBrowser", "IBrowser"));
	ui.setupUi(this);
}

IMainwindow::~IMainwindow()
{

}

