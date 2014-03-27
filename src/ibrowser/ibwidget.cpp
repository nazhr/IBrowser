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

#include "ibrowser/ibwidget.h"

// Qt
#include <QtGui>

IBWidget::IBWidget(QWidget *parent)
	:	QWidget(parent)  
{  

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