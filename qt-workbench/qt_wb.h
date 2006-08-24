#ifndef QT_WB_H
#define QT_WB_H

#include "GLDrawer.h"
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionVisualization_settings;
    QAction *actionFree_roam;
    QAction *actionOrbit;
    QAction *actionMove_center;
    QAction *actionWorking_directory;
    QAction *actionFunction_editor;
    QAction *actionXML_Viewer;
    QWidget *centralwidget;
    QHBoxLayout *hboxLayout;
    QHBoxLayout *hboxLayout1;
    QVBoxLayout *vboxLayout;
    QWidget *widget;
    QHBoxLayout *hboxLayout2;
    QWidget *widget1;
    QVBoxLayout *vboxLayout1;
    GLDrawer *gldrawer;
    QHBoxLayout *hboxLayout3;
    QLineEdit *console;
    QPushButton *runButton;
    QPushButton *killButton;
    QHBoxLayout *hboxLayout4;
    QTextBrowser *textBrowser;
    QMenuBar *menubar;
    QMenu *menuValikko;
    QMenu *menuOptions;
    QMenu *menuTools;
    QMenu *menuFile;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *MainWindow)
    {
    MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(QSize(1022, 661).expandedTo(MainWindow->minimumSizeHint()));
    MainWindow->setMouseTracking(false);
    actionQuit = new QAction(MainWindow);
    actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
    actionQuit->setIcon(QIcon(QString::fromUtf8("../../../Qt-4.1.4/bin/maple_texture.png")));
    actionVisualization_settings = new QAction(MainWindow);
    actionVisualization_settings->setObjectName(QString::fromUtf8("actionVisualization_settings"));
    actionFree_roam = new QAction(MainWindow);
    actionFree_roam->setObjectName(QString::fromUtf8("actionFree_roam"));
    actionFree_roam->setCheckable(true);
    actionFree_roam->setChecked(true);
    actionOrbit = new QAction(MainWindow);
    actionOrbit->setObjectName(QString::fromUtf8("actionOrbit"));
    actionOrbit->setCheckable(true);
    actionOrbit->setChecked(false);
    actionMove_center = new QAction(MainWindow);
    actionMove_center->setObjectName(QString::fromUtf8("actionMove_center"));
    actionMove_center->setCheckable(true);
    actionWorking_directory = new QAction(MainWindow);
    actionWorking_directory->setObjectName(QString::fromUtf8("actionWorking_directory"));
    actionFunction_editor = new QAction(MainWindow);
    actionFunction_editor->setObjectName(QString::fromUtf8("actionFunction_editor"));
    actionXML_Viewer = new QAction(MainWindow);
    actionXML_Viewer->setObjectName(QString::fromUtf8("actionXML_Viewer"));
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    hboxLayout = new QHBoxLayout(centralwidget);
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(9);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    vboxLayout = new QVBoxLayout();
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    widget = new QWidget(centralwidget);
    widget->setObjectName(QString::fromUtf8("widget"));
    hboxLayout2 = new QHBoxLayout(widget);
    hboxLayout2->setSpacing(6);
    hboxLayout2->setMargin(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    widget1 = new QWidget(widget);
    widget1->setObjectName(QString::fromUtf8("widget1"));
    vboxLayout1 = new QVBoxLayout(widget1);
    vboxLayout1->setSpacing(6);
    vboxLayout1->setMargin(0);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    gldrawer = new GLDrawer(widget1);
    gldrawer->setObjectName(QString::fromUtf8("gldrawer"));
    QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(7), static_cast<QSizePolicy::Policy>(7));
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(gldrawer->sizePolicy().hasHeightForWidth());
    gldrawer->setSizePolicy(sizePolicy);
    gldrawer->setAcceptDrops(true);

    vboxLayout1->addWidget(gldrawer);


    hboxLayout2->addWidget(widget1);


    vboxLayout->addWidget(widget);

    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setSpacing(6);
    hboxLayout3->setMargin(0);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    console = new QLineEdit(centralwidget);
    console->setObjectName(QString::fromUtf8("console"));

    hboxLayout3->addWidget(console);

    runButton = new QPushButton(centralwidget);
    runButton->setObjectName(QString::fromUtf8("runButton"));

    hboxLayout3->addWidget(runButton);

    killButton = new QPushButton(centralwidget);
    killButton->setObjectName(QString::fromUtf8("killButton"));

    hboxLayout3->addWidget(killButton);


    vboxLayout->addLayout(hboxLayout3);

    hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setSpacing(6);
    hboxLayout4->setMargin(0);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    textBrowser = new QTextBrowser(centralwidget);
    textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
    textBrowser->setMaximumSize(QSize(16777215, 120));

    hboxLayout4->addWidget(textBrowser);


    vboxLayout->addLayout(hboxLayout4);


    hboxLayout1->addLayout(vboxLayout);


    hboxLayout->addLayout(hboxLayout1);

    MainWindow->setCentralWidget(centralwidget);
    menubar = new QMenuBar(MainWindow);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 1022, 26));
    menuValikko = new QMenu(menubar);
    menuValikko->setObjectName(QString::fromUtf8("menuValikko"));
    menuOptions = new QMenu(menubar);
    menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
    menuTools = new QMenu(menubar);
    menuTools->setObjectName(QString::fromUtf8("menuTools"));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    MainWindow->setMenuBar(menubar);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    MainWindow->setStatusBar(statusbar);
    toolBar = new QToolBar(MainWindow);
    toolBar->setObjectName(QString::fromUtf8("toolBar"));
    toolBar->setOrientation(Qt::Horizontal);
    MainWindow->addToolBar(static_cast<Qt::ToolBarArea>(4), toolBar);

    menubar->addAction(menuFile->menuAction());
    menubar->addAction(menuOptions->menuAction());
    menubar->addAction(menuTools->menuAction());
    menuOptions->addAction(actionVisualization_settings);
    menuOptions->addAction(actionWorking_directory);
    menuTools->addAction(actionXML_Viewer);
    menuTools->addAction(actionFunction_editor);
    menuFile->addAction(actionQuit);
    toolBar->addAction(actionOrbit);
    toolBar->addAction(actionMove_center);
    toolBar->addAction(actionFree_roam);
    retranslateUi(MainWindow);
    QObject::connect(gldrawer, SIGNAL(textOutput(QString)), textBrowser, SLOT(append(QString)));

    QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Lignum Workbench", 0, QApplication::UnicodeUTF8));
    actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
    actionVisualization_settings->setText(QApplication::translate("MainWindow", "Visualization settings...", 0, QApplication::UnicodeUTF8));
    actionFree_roam->setText(QApplication::translate("MainWindow", "Free roam", 0, QApplication::UnicodeUTF8));
    actionOrbit->setText(QApplication::translate("MainWindow", "Orbit", 0, QApplication::UnicodeUTF8));
    actionMove_center->setText(QApplication::translate("MainWindow", "Move center", 0, QApplication::UnicodeUTF8));
    actionWorking_directory->setText(QApplication::translate("MainWindow", "Change working directory...", 0, QApplication::UnicodeUTF8));
    actionFunction_editor->setText(QApplication::translate("MainWindow", "Function editor...", 0, QApplication::UnicodeUTF8));
    actionXML_Viewer->setText(QApplication::translate("MainWindow", "XML Viewer...", 0, QApplication::UnicodeUTF8));
    gldrawer->setToolTip(QApplication::translate("MainWindow", "OpenGL visualization for Lignum", 0, QApplication::UnicodeUTF8));
    gldrawer->setWhatsThis(QApplication::translate("MainWindow", " Visualization for Lignum", 0, QApplication::UnicodeUTF8));
    runButton->setText(QApplication::translate("MainWindow", "Run", 0, QApplication::UnicodeUTF8));
    killButton->setText(QApplication::translate("MainWindow", "Kill program", 0, QApplication::UnicodeUTF8));
    menuValikko->setTitle(QApplication::translate("MainWindow", "valikko", 0, QApplication::UnicodeUTF8));
    menuOptions->setTitle(QApplication::translate("MainWindow", "Options", 0, QApplication::UnicodeUTF8));
    menuTools->setTitle(QApplication::translate("MainWindow", "Tools", 0, QApplication::UnicodeUTF8));
    menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

#endif // QT_WB_H
