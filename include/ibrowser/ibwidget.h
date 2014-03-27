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

#ifndef R_IBROWSER_IBWIDGET_H  
#define R_IBROWSER_IBWIDGET_H

#include "ibrowser/global.h"

// Qt
#include <QtGui>
#include <QtGui/QWidget>
#include <QtGui/QLineEdit>

class IBWidget : public QWidget  
{  
	Q_OBJECT  
public:  
	IBWidget(QWidget* = 0);
	~IBWidget();  

private :
	QHBoxLayout		*m_layout;
	QLineEdit		*m_edit;
protected:  
	bool event(QEvent *);  
signals:  
	void sig_doubleClickedTitleBar();
};  

#endif	// R_IBROWSER_IBWIDGET_H  