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

// ibrowser
#include "ibrowser/ibrowsersingle.h"

// boost
#include "boost/thread/once.hpp"
#include "boost/scoped_ptr.hpp"

/*
 * @brief : ibrowser single static init .
 */
boost::scoped_ptr<IBrowserSingle>		IBrowserSingle::m_ibrowser_sinlge(0);
boost::once_flag						IBrowserSingle::m_once_flag = BOOST_ONCE_INIT;

