#ifndef FUNC_EDIT_H
#define FUNC_EDIT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QWidget>

class Ui_FunctionEditor
{
public:
    QAction *actionOpen;
    QAction *actionQuit;
    QAction *actionSave;
    QAction *actionSave_as;
    QWidget *centralwidget;
    QTextEdit *textEdit;
    QPushButton *updateButton;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *FunctionEditor)
    {
    FunctionEditor->setObjectName(QString::fromUtf8("FunctionEditor"));
    FunctionEditor->resize(QSize(800, 600).expandedTo(FunctionEditor->minimumSizeHint()));
    actionOpen = new QAction(FunctionEditor);
    actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
    actionQuit = new QAction(FunctionEditor);
    actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
    actionSave = new QAction(FunctionEditor);
    actionSave->setObjectName(QString::fromUtf8("actionSave"));
    actionSave_as = new QAction(FunctionEditor);
    actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
    centralwidget = new QWidget(FunctionEditor);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    textEdit = new QTextEdit(centralwidget);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));
    textEdit->setGeometry(QRect(420, 40, 331, 451));
    updateButton = new QPushButton(centralwidget);
    updateButton->setObjectName(QString::fromUtf8("updateButton"));
    updateButton->setGeometry(QRect(390, 520, 87, 26));
    FunctionEditor->setCentralWidget(centralwidget);
    menubar = new QMenuBar(FunctionEditor);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 800, 26));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    FunctionEditor->setMenuBar(menubar);
    statusbar = new QStatusBar(FunctionEditor);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    FunctionEditor->setStatusBar(statusbar);

    menubar->addAction(menuFile->menuAction());
    menuFile->addAction(actionOpen);
    menuFile->addSeparator();
    menuFile->addAction(actionSave);
    menuFile->addAction(actionSave_as);
    menuFile->addSeparator();
    menuFile->addAction(actionQuit);
    retranslateUi(FunctionEditor);

    QMetaObject::connectSlotsByName(FunctionEditor);
    } // setupUi

    void retranslateUi(QMainWindow *FunctionEditor)
    {
    FunctionEditor->setWindowTitle(QApplication::translate("FunctionEditor", "Function Editor", 0, QApplication::UnicodeUTF8));
    actionOpen->setText(QApplication::translate("FunctionEditor", "Open...", 0, QApplication::UnicodeUTF8));
    actionQuit->setText(QApplication::translate("FunctionEditor", "Quit", 0, QApplication::UnicodeUTF8));
    actionSave->setText(QApplication::translate("FunctionEditor", "Save", 0, QApplication::UnicodeUTF8));
    actionSave_as->setText(QApplication::translate("FunctionEditor", "Save as...", 0, QApplication::UnicodeUTF8));
    updateButton->setText(QApplication::translate("FunctionEditor", "Update", 0, QApplication::UnicodeUTF8));
    menuFile->setTitle(QApplication::translate("FunctionEditor", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FunctionEditor: public Ui_FunctionEditor {};
} // namespace Ui

#endif // FUNC_EDIT_H
