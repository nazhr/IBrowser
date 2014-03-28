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
#include "ibrowser/global.h"
#include "ibrowser/imainwindow.h"
#include "ibrowser/ibrowserclient.h"

// vc
#include <Windows.h>

// Qt
#include <QtGui/QApplication>
#include <QtGui/QWidget>
#include <QtGui/QCleanlooksStyle> 

int main(int argc, char **argv)
{
	g_qApplication = new QApplication(argc, argv);
	QApplication::setStyle(new QCleanlooksStyle);  
	QTextCodec::setCodecForTr(QTextCodec::codecForName("utf-8"));

	IMainwindow					parent;
	parent.Initialize();

	// result = g_qApplication->exec();

	return 1;
}