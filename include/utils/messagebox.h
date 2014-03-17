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

#ifndef R_IBROWSER_MESSAGEBOX_H
#define R_IBROWSER_MESSAGEBOX_H

// vc
#if WIN32
#include <Windows.h>
#endif

// boost
#include "boost/assert.hpp"

namespace ibrowser
{
	class MessageUtils
	{
	public :
		MessageUtils(){}
		virtual ~MessageUtils(){}
		void MessageBoxDef(HWND hWnd = NULL, const char *content = NULL, const char *title = "IBrowser System Error : ")
		{
			BOOST_ASSERT(content && "content is NULL !");
#if WIN32
			MessageBoxA(hWnd, content, title, MB_OK);
#endif
		}
	};
}

#endif // R_IBROWSER_MESSAGEBOX_H