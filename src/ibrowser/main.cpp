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
#include "ibrowser/imainwindow.h"
#include "ibrowser/ibrowserclient.h"

// vc
#include <Windows.h>

// Qt
#include <QtGui/QApplication>
#include <QtGui/QWidget>

int main(int argc, char **argv)
{
	QApplication				app(argc, argv);
	IBrowserClient				ibrowser_client;
	IMainwindow					parent;
	int							result = 1;
	bool						message_loop = true;

	result = ibrowser_client.Initialize(&parent);

	// Qt 消息循环
	/*
	while(result)
	{
		result = ibrowser_client.Initialize(&parent);
		CefDoMessageLoopWork();
		if(message_loop)
		{
			message_loop = true;
			result = app.exec();	
		}
	}
	*/

	result = app.exec();

	ibrowser_client.Quit();

	return result;
}