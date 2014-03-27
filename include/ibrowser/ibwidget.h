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

// Qt
#include <QtGui/QWidget>  

class IBWidget : public QWidget  
{  
	Q_OBJECT  
public:  
	IBWidget(QWidget* = 0);
	~IBWidget();  
protected:  
	bool event(QEvent *);  
signals:  
	void sig_doubleClickedTitleBar();
};  

#endif	// R_IBROWSER_IBWIDGET_H  