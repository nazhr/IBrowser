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

// ibrowser
#include "ibrowser/global.h"
#include "ibrowser/ibrowsersingle.h"

// Qt
#include <QtGui>
#include <QtGui/QWidget>
#include <QtGui/QLineEdit>

// boost
#include <boost/scoped_ptr.hpp>

class IBWidget : public QWidget  
{  
	Q_OBJECT  
public:  
	IBWidget(QWidget* = 0);
	~IBWidget(); 

public :
	int GetBrowserId()
	{
		return m_browserId;
	}

	void SetBrowserId(int browserId)
	{
		m_browserId = browserId;
	}

private :
	void Init();

private slots :
	void LETextChanged(const QString &text);
	void LEReturnPressed();

private :
	boost::scoped_ptr<QLineEdit>	m_edit;
	int								m_browserId;

protected:  
	bool event(QEvent *);  

signals:  
	void sig_doubleClickedTitleBar();
};  

#endif	// R_IBROWSER_IBWIDGET_H  