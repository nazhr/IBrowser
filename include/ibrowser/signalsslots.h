/****************************************************************************
 *  Copyright (C) 2014 by Jerry			                           		*
 *                                                                        	*
 *  This file is part of IBrowser.                                        	*
 *                                                                         	*
 *  IBrowser is private software.                                         	*
 *  program.  If not, see <https://github.com/jerrykk/IBrowser>.          	*
 *                                                                        	*
 *  IBrowser website: https://github.com/jerrykk/IBrowser                 	*
 ****************************************************************************/
/****************************************************************************
 *	This class is used to complete the cef and qt event communication .		*
 ****************************************************************************/

#ifndef R_IBROWSER_SIGNALSSLOTS_H
#define R_IBROWSER_SIGNALSSLOTS_H

// Qt
#include <QtCore/QObject>

// vc
#include <string>

// boost
#include <boost/thread/once.hpp>
#include <boost/scoped_ptr.hpp>
#include <boost/locale.hpp>

namespace ibrowser
{
	class SignalsSlots : public QObject
	{
	private :
		Q_OBJECT

	public : // Constructor
		SignalsSlots();
		~SignalsSlots();

	public : // static member function
		static void Init()
		{
			m_instance_ptr.reset(new SignalsSlots());
		}

		static SignalsSlots* GetCurrentSignals()
		{
			boost::call_once(SignalsSlots::Init, m_once_flag);
			return m_instance_ptr.get();
		}

	public : // member function
		void SetCurrentTittle(std::string tittle);

	signals : // signals method
		void CurrentTittle(std::string tittle);

	private : // static member variable
		static boost::once_flag								m_once_flag;
		static boost::scoped_ptr<ibrowser::SignalsSlots>	m_instance_ptr;

	};
}

#endif // R_IBROWSER_SIGNALSSLOTS_H