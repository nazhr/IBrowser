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
#include "ibrowser/signalsslots.h"

namespace ibrowser
{
	// static member variable init
	boost::once_flag							SignalsSlots::m_once_flag = BOOST_ONCE_INIT;
	boost::scoped_ptr<ibrowser::SignalsSlots>	SignalsSlots::m_instance_ptr(0);

	// Constructor function
	SignalsSlots::SignalsSlots(){}
	SignalsSlots::~SignalsSlots(){}

	// public member function
	void SignalsSlots::SetCurrentTittle(std::string tittle)
	{
		std::string title_temp = boost::locale::conv::utf_to_utf<char>(tittle);
		emit CurrentTittle(title_temp);
	}

}