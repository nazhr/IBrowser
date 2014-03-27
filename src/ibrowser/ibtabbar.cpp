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

#include "ibrowser/ibtabbar.h"

// Qt
#include <QtGui>  

IBTabBar::IBTabBar(QWidget *parent)
	:	QTabBar(parent), 
		pressFlag(false)  
{  

}  

void IBTabBar::mousePressEvent(QMouseEvent *event)  
{      
	if (event->button()==Qt::LeftButton)  
	{  
		pressFlag = true;  
	}  
	QTabBar::mousePressEvent(event);  
}  

void IBTabBar::mouseReleaseEvent(QMouseEvent *event)  
{  
	if(event->button() == Qt::LeftButton &&pressFlag )  
	{  
		pressFlag = false;       
		if(tabRect(currentIndex()).contains( event->pos()))  
			return;  
		emit sig_tabDrag(currentIndex(),event->pos());  
	}      
}  