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

#ifndef R_IBROWSER_SINGLETON_H
#define R_IBROWSER_SINGLETON_H

// vc
#if WIN32
#include <Windows.h>
#endif

// boost
#include "boost/utility.hpp"
#include "boost/scoped_ptr.hpp"
#include "boost/thread/once.hpp"

namespace ibrowser
{
	template <typename T>
	class Singleton : private boost::noncopyable
	{
	public :

		static void Init()
		{
			m_instance_ptr.reset(new T);	
		}

		static T& Instance()
		{
			boost::call_once(Init, m_once_flag);
			return *m_instance_ptr;
		}
	protected:
		Singleton() {}
		~Singleton() {}

	private :
		static boost::once_flag		m_once_flag;
		static boost::scoped_ptr<T>	m_instance_ptr;

	};

	template <typename T>
	boost::once_flag				Singleton<T>::m_once_flag = BOOST_ONCE_INIT;
	template <typename T>
	boost::scoped_ptr<T>			Singleton<T>::m_instance_ptr(0);
}

#endif // R_IBROWSER_SINGLETON_H