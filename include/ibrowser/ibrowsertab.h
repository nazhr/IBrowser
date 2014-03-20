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

// cef
#include "include/cef_app.h"
#include "include/utils/resource.h"

namespace ibrowser
{

// window and box size
#define		MAX_LOADSTRING	100
#define		MAX_URL_LENGTH  255
#define		URLBAR_HEIGHT	24
#define		TAB_BTN_WIDTH	124
#define		TAB_BTN_HEIGTH	24

	class	IBrowserTab : public virtual MessageUtils
	{
	public :
		IBrowserTab();
		~IBrowserTab();

	public :
		bool			CreateTab(HWND hWnd);
		void			CreateTabMember(HWND tab_hWnd);
		ATOM			RegisterTabClass();

		inline	HWND	GetEditHWnd();
		inline	HWND	GetTabHWnd();
		// inline	WNDPROC GetEditWndOldProc();

	private : // non static member 
		HWND			m_tab_hWnd;
		// HWND			m_editWnd;
		HWND			m_backWnd;
		HWND			m_forwardWnd;
		HWND			m_reloadWnd;
		HWND			m_stopWnd;

	private : // static member 
		static HWND						m_editWnd;
		/*// static WNDPROC					m_editWndOldProc;
		static HWND						m_backWnd;
		static HWND						m_forwardWnd;
		static HWND						m_reloadWnd;
		static HWND						m_stopWnd;*/

	};

	inline HWND IBrowserTab::GetEditHWnd()
	{
		return m_editWnd;
	}

	inline HWND IBrowserTab::GetTabHWnd()
	{
		return m_tab_hWnd;
	}
	/*

	inline WNDPROC IBrowserTab::GetEditWndOldProc()
	{
		return m_editWndOldProc;
	}
	*/

}

#endif // R_IBROWSER_IBROWSERTAB_H