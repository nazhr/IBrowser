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

#ifndef R_BROWSER_IBROWSERCLIENT_H
#define R_BROWSER_IBROWSERCLIENT_H

// cef
#include "include/cef_base.h"

// boost
#include "boost/scoped_ptr.hpp"
#include <boost/thread/once.hpp>


namespace ibrowser
{
	class IBrowserClient
	{
	public :
		IBrowserClient();
		virtual ~IBrowserClient();
		
	};
}

#endif // R_BROWSER_IBROWSERCLIENT_H
