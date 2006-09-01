#ifndef HELP_H
#define HELP_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

class Ui_HelpWindow
{
public:
    QAction *actionQuit;
    QWidget *centralwidget;
    QHBoxLayout *hboxLayout;
    QTextEdit *helpText;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *HelpWindow)
    {
    HelpWindow->setObjectName(QString::fromUtf8("HelpWindow"));
    HelpWindow->resize(QSize(475, 567).expandedTo(HelpWindow->minimumSizeHint()));
    actionQuit = new QAction(HelpWindow);
    actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
    centralwidget = new QWidget(HelpWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    hboxLayout = new QHBoxLayout(centralwidget);
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(9);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    helpText = new QTextEdit(centralwidget);
    helpText->setObjectName(QString::fromUtf8("helpText"));

    hboxLayout->addWidget(helpText);

    HelpWindow->setCentralWidget(centralwidget);
    menubar = new QMenuBar(HelpWindow);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 475, 26));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    HelpWindow->setMenuBar(menubar);
    statusbar = new QStatusBar(HelpWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    HelpWindow->setStatusBar(statusbar);

    menubar->addAction(menuFile->menuAction());
    menuFile->addAction(actionQuit);
    retranslateUi(HelpWindow);

    QMetaObject::connectSlotsByName(HelpWindow);
    } // setupUi

    void retranslateUi(QMainWindow *HelpWindow)
    {
    HelpWindow->setWindowTitle(QApplication::translate("HelpWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
    actionQuit->setText(QApplication::translate("HelpWindow", "Quit", 0, QApplication::UnicodeUTF8));
    menuFile->setTitle(QApplication::translate("HelpWindow", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class HelpWindow: public Ui_HelpWindow {};
} // namespace Ui

#endif // HELP_H
