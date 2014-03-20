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

#ifndef R_BROWSER_IBROWSERWIN_H
#define R_BROWSER_IBROWSERWIN_H

// ibrowser
#include "ibrowser/ibrowserapp.h"
#include "ibrowser/ibrowserclient.h"
#include "ibrowser/ibrowserhandler.h"

// ibrowser utils
#include "utils/messagebox.h"

// cef
#include "include/cef_base.h"

// boost
#include "boost/scoped_ptr.hpp"
#include <boost/thread/once.hpp>


namespace ibrowser
{

const static wchar_t CLASS_NAME[]  = L"IBrowser";

	/*
	 * @brief : ibrowser window class
	 */
	class IBrowserWindow : public virtual MessageUtils
	{
	public :
		IBrowserWindow();
		virtual ~IBrowserWindow();
		
		static	IBrowserWindow &GetCurrentIBorwserWindow()
		{
			boost::call_once(IBrowserWindow::init, m_once_flag);
			return *m_instance_ptr;
		}
		static void init()
		{
			m_instance_ptr.reset(new IBrowserWindow);
		}

		static HINSTANCE GetCurrentAppHandler()		// get current app hInstance
		{
			return m_hInstance;	
		}

		static IBrowserApp *GetCurrentApp()
		{
			return m_ibrowser_app.get();	
		}

		bool initialize(HINSTANCE hinstance, LPSTR lpCmdLine, int nCmdShow);

		/*
		 *   函数: InitInstance(HINSTANCE, int)
		 *
		 *   目的: 保存实例句柄并创建主窗口
		 *
		 *   注释:
		 *
		 *        在此函数中，我们在全局变量中保存实例句柄并
		 *        创建和显示主程序窗口。
		 */
		bool CreateDefMainWindow();

		/*
		 *  函数: MyRegisterClass()
		 *
		 *  目的: 注册窗口类。
		 *
		 *  注释:
		 *
		 *    这样应用程序就可以获得关联的
		 *    "格式正确的"小图标。
		 */
		ATOM RegisterWindowClass();

		/*
		 * @brief : get main window handler
		 */
		inline HWND GetMainWindowHandler();
		
	private :
		LPSTR						m_lpCmdLine;
		int							m_nCmdShow;
		HWND						m_hWnd;

	private :
		static	CefRefPtr<ibrowser::IBrowserApp>				m_ibrowser_app;
		static	boost::scoped_ptr<ibrowser::IBrowserWindow>		m_instance_ptr;
		static	boost::once_flag								m_once_flag;
		static	HINSTANCE										m_hInstance;
		
	};

	inline HWND IBrowserWindow::GetMainWindowHandler()
	{
		return m_hWnd;
	}
}

#endif // R_BROWSER_IBROWSERWIN_H
