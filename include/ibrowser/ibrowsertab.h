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

#ifndef R_IBROWSER_IBROWSERTAB_H
#define R_IBROWSER_IBROWSERTAB_H

// ibrowser utils
#include "utils/messagebox.h"
#include "ibrowser/imainwindow.h"

// cef
#include <include/cef_app.h>
#include <include/utils/resource.h>

// Qt 
#include <QtGui/QWidget>
#include <QtGui/QLineEdit>
#include <QtGui/QHBoxLayout>

namespace ibrowser
{
	class	IBrowserTab
	{
	public :
		IBrowserTab(QWidget *parent);
		~IBrowserTab();

	public :
		bool			CreateTab();
		void			CreateBrowser(HWND tab_hWnd);
		bool			BrowserLoadUrl(const std::wstring &url);
		

	private : // non static member 
		QWidget			*m_parent_widget;
		QWidget			*m_sub_widget;
		QLineEdit		*m_edit_box;
		QHBoxLayout		*m_layout;


	private : // static member 
		

	};
}

#endif // R_IBROWSER_IBROWSERTAB_H