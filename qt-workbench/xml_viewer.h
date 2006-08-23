#ifndef XML_VIEWER_H
#define XML_VIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>
#include "XMLViewer.h"

class Ui_TreeViewer
{
public:
    QAction *actionAdd_tree;
    QAction *actionQuit;
    QAction *actionUpdate_visualization;
    QWidget *centralwidget;
    QHBoxLayout *hboxLayout;
    XMLViewer *xml_viewer;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *TreeViewer)
    {
    TreeViewer->setObjectName(QString::fromUtf8("TreeViewer"));
    TreeViewer->resize(QSize(800, 600).expandedTo(TreeViewer->minimumSizeHint()));
    actionAdd_tree = new QAction(TreeViewer);
    actionAdd_tree->setObjectName(QString::fromUtf8("actionAdd_tree"));
    actionQuit = new QAction(TreeViewer);
    actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
    actionUpdate_visualization = new QAction(TreeViewer);
    actionUpdate_visualization->setObjectName(QString::fromUtf8("actionUpdate_visualization"));
    centralwidget = new QWidget(TreeViewer);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    hboxLayout = new QHBoxLayout(centralwidget);
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(9);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    xml_viewer = new XMLViewer(centralwidget);
    xml_viewer->setObjectName(QString::fromUtf8("xml_viewer"));

    hboxLayout->addWidget(xml_viewer);

    TreeViewer->setCentralWidget(centralwidget);
    menubar = new QMenuBar(TreeViewer);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 800, 31));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    TreeViewer->setMenuBar(menubar);
    statusbar = new QStatusBar(TreeViewer);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    TreeViewer->setStatusBar(statusbar);
    toolBar = new QToolBar(TreeViewer);
    toolBar->setObjectName(QString::fromUtf8("toolBar"));
    toolBar->setOrientation(Qt::Horizontal);
    TreeViewer->addToolBar(static_cast<Qt::ToolBarArea>(4), toolBar);

    menubar->addAction(menuFile->menuAction());
    menuFile->addAction(actionAdd_tree);
    menuFile->addSeparator();
    menuFile->addAction(actionQuit);
    toolBar->addAction(actionAdd_tree);
    toolBar->addSeparator();
    toolBar->addAction(actionUpdate_visualization);
    retranslateUi(TreeViewer);

    QMetaObject::connectSlotsByName(TreeViewer);
    } // setupUi

    void retranslateUi(QMainWindow *TreeViewer)
    {
    TreeViewer->setWindowTitle(QApplication::translate("TreeViewer", "MainWindow", 0, QApplication::UnicodeUTF8));
    actionAdd_tree->setText(QApplication::translate("TreeViewer", "Add tree...", 0, QApplication::UnicodeUTF8));
    actionQuit->setText(QApplication::translate("TreeViewer", "Quit", 0, QApplication::UnicodeUTF8));
    actionUpdate_visualization->setText(QApplication::translate("TreeViewer", "Update visualization", 0, QApplication::UnicodeUTF8));
    xml_viewer->setToolTip(QApplication::translate("TreeViewer", "Function painter for Lignum", 0, QApplication::UnicodeUTF8));
    xml_viewer->setWhatsThis(QApplication::translate("TreeViewer", " Function painter for Lignum", 0, QApplication::UnicodeUTF8));
    menuFile->setTitle(QApplication::translate("TreeViewer", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TreeViewer: public Ui_TreeViewer {};
} // namespace Ui

#endif // XML_VIEWER_H
