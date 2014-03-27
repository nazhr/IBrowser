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

#ifndef R_IBROWSER_IBTABBAR_H
#define R_IBROWSER_IBTABBAR_H

// Qt
#include <QtGui>
#include <QtGui/QTabBar>  

class IBTabBar :public QTabBar  
{  
	Q_OBJECT  
public:  
	IBTabBar(QWidget* =0);  
	virtual ~IBTabBar(){};  
protected:  
	void mousePressEvent(QMouseEvent *event);  
	void mouseReleaseEvent(QMouseEvent *event); 
private:  
	bool pressFlag;  
signals:  
	void sig_tabDrag(int, QPoint);  
};  

#endif	// R_IBROWSER_IBTABBAR_H