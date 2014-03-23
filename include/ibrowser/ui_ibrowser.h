/********************************************************************************
** Form generated from reading UI file 'ibrowser.ui'
**
** Created by: Qt User Interface Compiler version 4.8.5
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IBROWSER_H
#define UI_IBROWSER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_imainwindowClass
{
public:
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QWidget *centralWidget;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *imainwindowClass)
    {
        if (imainwindowClass->objectName().isEmpty())
            imainwindowClass->setObjectName(QString::fromUtf8("imainwindowClass"));
        imainwindowClass->resize(600, 400);
        menuBar = new QMenuBar(imainwindowClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        imainwindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(imainwindowClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        imainwindowClass->addToolBar(mainToolBar);
        centralWidget = new QWidget(imainwindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        imainwindowClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(imainwindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        imainwindowClass->setStatusBar(statusBar);

        retranslateUi(imainwindowClass);

        QMetaObject::connectSlotsByName(imainwindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *imainwindowClass)
    {
        imainwindowClass->setWindowTitle(QApplication::translate("imainwindowClass", "imainwindow", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class imainwindowClass: public Ui_imainwindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IBROWSER_H
