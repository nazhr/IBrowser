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

// window and box size
#define		MAX_LOADSTRING	100
#define		MAX_URL_LENGTH  255
#define		URLBAR_HEIGHT	24
#define		TAB_BTN_WIDTH	124
#define		TAB_BTN_HEIGTH	24

class	IBrowserTab
{
public :
	IBrowserTab();
	~IBrowserTab();

public :
	bool			CreateTab(QWidget *parent);
	void			CreateBrowser(HWND tab_hWnd);
	bool			BrowserLoadUrl(const std::wstring &url);
	

private : // non static member 
	QWidget			*m_parent_window;

private : // static member 
	

};

#endif // R_IBROWSER_IBROWSERTAB_H