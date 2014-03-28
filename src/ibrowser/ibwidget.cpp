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

IBWidget::IBWidget(QWidget *parent)
	:	QWidget(parent)  
{
	QSize size = this->size();
	m_edit.reset(new QLineEdit(this));
	m_edit->resize(size.width(), URLBAR_HEIGHT);
	connect(m_edit.get(), SIGNAL(textChanged(const QString& )), this, SLOT(LETextChanged(const QString& )));
	connect(m_edit.get(), SIGNAL(returnPressed()), this, SLOT(LEReturnPressed()));
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


// private slots
// get edit box text
void IBWidget::LETextChanged(const QString &text)
{
	
}

// response enter events
void IBWidget::LEReturnPressed()
{
	/*ibrowser::IBrowserHandler *handler = 
	QString text = m_edit->text();*/
}