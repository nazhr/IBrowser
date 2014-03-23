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
	ibrowser::IBrowserClient	ibrowser_client;
	IMainwindow					parent;
	int							result = ibrowser_client.Initialize(&parent);

	result = app.exec();

	ibrowser_client.Quit();

	return result;
}