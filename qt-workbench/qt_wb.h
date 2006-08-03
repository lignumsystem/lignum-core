#ifndef QT_WB_H
#define QT_WB_H

#include "GLDrawer.h"
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_MainWindow
{
public:
    QAction *actionQuit;
    QAction *actionLoad_tree;
    QAction *actionVisualization_settings;
    QWidget *centralwidget;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QWidget *widget;
    QHBoxLayout *hboxLayout1;
    QWidget *widget1;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout2;
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *pushButton;
    GLDrawer *gldrawer;
    QVBoxLayout *vboxLayout2;
    QVBoxLayout *vboxLayout3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QHBoxLayout *hboxLayout3;
    QLabel *label_2;
    QSpinBox *spinBox;
    QHBoxLayout *hboxLayout4;
    QLabel *label_3;
    QSpinBox *spinBox_2;
    QHBoxLayout *hboxLayout5;
    QLabel *label_4;
    QSpinBox *spinBox_3;
    QCheckBox *checkBox;
    QCheckBox *checkBox_2;
    QSpacerItem *spacerItem;
    QHBoxLayout *hboxLayout6;
    QTextBrowser *textBrowser;
    QSpacerItem *spacerItem1;
    QMenuBar *menubar;
    QMenu *menuValikko;
    QMenu *menuFile;
    QMenu *menuOptions;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
    MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(QSize(818, 543).expandedTo(MainWindow->minimumSizeHint()));
    MainWindow->setMouseTracking(false);
    actionQuit = new QAction(MainWindow);
    actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
    actionQuit->setIcon(QIcon(QString::fromUtf8("../../../Qt-4.1.4/bin/maple_texture.png")));
    actionLoad_tree = new QAction(MainWindow);
    actionLoad_tree->setObjectName(QString::fromUtf8("actionLoad_tree"));
    actionVisualization_settings = new QAction(MainWindow);
    actionVisualization_settings->setObjectName(QString::fromUtf8("actionVisualization_settings"));
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    hboxLayout = new QHBoxLayout(centralwidget);
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(9);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    vboxLayout = new QVBoxLayout();
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    widget = new QWidget(centralwidget);
    widget->setObjectName(QString::fromUtf8("widget"));
    hboxLayout1 = new QHBoxLayout(widget);
    hboxLayout1->setSpacing(6);
    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    widget1 = new QWidget(widget);
    widget1->setObjectName(QString::fromUtf8("widget1"));
    vboxLayout1 = new QVBoxLayout(widget1);
    vboxLayout1->setSpacing(6);
    vboxLayout1->setMargin(0);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setMargin(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    label = new QLabel(widget1);
    label->setObjectName(QString::fromUtf8("label"));

    hboxLayout2->addWidget(label);

    lineEdit = new QLineEdit(widget1);
    lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

    hboxLayout2->addWidget(lineEdit);

    pushButton = new QPushButton(widget1);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));

    hboxLayout2->addWidget(pushButton);


    vboxLayout1->addLayout(hboxLayout2);

    gldrawer = new GLDrawer(widget1);
    gldrawer->setObjectName(QString::fromUtf8("gldrawer"));

    vboxLayout1->addWidget(gldrawer);


    hboxLayout1->addWidget(widget1);

    vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setSpacing(6);
    vboxLayout2->setMargin(0);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    vboxLayout3 = new QVBoxLayout();
    vboxLayout3->setSpacing(6);
    vboxLayout3->setMargin(0);
    vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
    pushButton_2 = new QPushButton(widget);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));

    vboxLayout3->addWidget(pushButton_2);

    pushButton_3 = new QPushButton(widget);
    pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));

    vboxLayout3->addWidget(pushButton_3);

    pushButton_4 = new QPushButton(widget);
    pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));

    vboxLayout3->addWidget(pushButton_4);

    pushButton_5 = new QPushButton(widget);
    pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));

    vboxLayout3->addWidget(pushButton_5);


    vboxLayout2->addLayout(vboxLayout3);

    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setSpacing(6);
    hboxLayout3->setMargin(0);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    label_2 = new QLabel(widget);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    hboxLayout3->addWidget(label_2);

    spinBox = new QSpinBox(widget);
    spinBox->setObjectName(QString::fromUtf8("spinBox"));
    spinBox->setMinimum(3);
    spinBox->setValue(10);

    hboxLayout3->addWidget(spinBox);


    vboxLayout2->addLayout(hboxLayout3);

    hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setSpacing(6);
    hboxLayout4->setMargin(0);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    label_3 = new QLabel(widget);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    hboxLayout4->addWidget(label_3);

    spinBox_2 = new QSpinBox(widget);
    spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
    spinBox_2->setMinimum(1);
    spinBox_2->setValue(1);

    hboxLayout4->addWidget(spinBox_2);


    vboxLayout2->addLayout(hboxLayout4);

    hboxLayout5 = new QHBoxLayout();
    hboxLayout5->setSpacing(6);
    hboxLayout5->setMargin(0);
    hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
    label_4 = new QLabel(widget);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    hboxLayout5->addWidget(label_4);

    spinBox_3 = new QSpinBox(widget);
    spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
    spinBox_3->setMinimum(4);
    spinBox_3->setSingleStep(2);
    spinBox_3->setValue(10);

    hboxLayout5->addWidget(spinBox_3);


    vboxLayout2->addLayout(hboxLayout5);

    checkBox = new QCheckBox(widget);
    checkBox->setObjectName(QString::fromUtf8("checkBox"));
    checkBox->setChecked(false);

    vboxLayout2->addWidget(checkBox);

    checkBox_2 = new QCheckBox(widget);
    checkBox_2->setObjectName(QString::fromUtf8("checkBox_2"));

    vboxLayout2->addWidget(checkBox_2);

    spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout2->addItem(spacerItem);


    hboxLayout1->addLayout(vboxLayout2);


    vboxLayout->addWidget(widget);

    hboxLayout6 = new QHBoxLayout();
    hboxLayout6->setSpacing(6);
    hboxLayout6->setMargin(0);
    hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
    textBrowser = new QTextBrowser(centralwidget);
    textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
    textBrowser->setMaximumSize(QSize(16777215, 100));

    hboxLayout6->addWidget(textBrowser);

    spacerItem1 = new QSpacerItem(201, 21, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout6->addItem(spacerItem1);


    vboxLayout->addLayout(hboxLayout6);


    hboxLayout->addLayout(vboxLayout);

    MainWindow->setCentralWidget(centralwidget);
    menubar = new QMenuBar(MainWindow);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 818, 22));
    menuValikko = new QMenu(menubar);
    menuValikko->setObjectName(QString::fromUtf8("menuValikko"));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    menuOptions = new QMenu(menubar);
    menuOptions->setObjectName(QString::fromUtf8("menuOptions"));
    MainWindow->setMenuBar(menubar);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    MainWindow->setStatusBar(statusbar);

    menubar->addAction(menuFile->menuAction());
    menubar->addAction(menuOptions->menuAction());
    menuFile->addAction(actionLoad_tree);
    menuFile->addAction(actionQuit);
    menuOptions->addAction(actionVisualization_settings);
    retranslateUi(MainWindow);
    QObject::connect(lineEdit, SIGNAL(textChanged(QString)), gldrawer, SLOT(setTreeFile(QString)));
    QObject::connect(pushButton, SIGNAL(clicked()), gldrawer, SLOT(changeTree()));
    QObject::connect(pushButton_2, SIGNAL(clicked()), gldrawer, SLOT(toggleWireModel()));
    QObject::connect(pushButton_3, SIGNAL(clicked()), gldrawer, SLOT(toggleLights()));
    QObject::connect(pushButton_4, SIGNAL(clicked()), gldrawer, SLOT(toggleTexturing()));
    QObject::connect(spinBox, SIGNAL(valueChanged(int)), gldrawer, SLOT(setCylinderRDetail(int)));
    QObject::connect(spinBox_2, SIGNAL(valueChanged(int)), gldrawer, SLOT(setCylinderHDetail(int)));
    QObject::connect(pushButton_5, SIGNAL(clicked()), gldrawer, SLOT(resetCamera()));
    QObject::connect(checkBox, SIGNAL(toggled(bool)), gldrawer, SLOT(useBSP(bool)));
    QObject::connect(gldrawer, SIGNAL(textOutput(QString)), textBrowser, SLOT(append(QString)));
    QObject::connect(checkBox_2, SIGNAL(toggled(bool)), gldrawer, SLOT(useLeafTextures(bool)));
    QObject::connect(spinBox_3, SIGNAL(valueChanged(int)), gldrawer, SLOT(setLeafDetail(int)));

    QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Lignum Workbench", 0, QApplication::UnicodeUTF8));
    actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
    actionLoad_tree->setText(QApplication::translate("MainWindow", "Load tree...", 0, QApplication::UnicodeUTF8));
    actionVisualization_settings->setText(QApplication::translate("MainWindow", "Visualization settings...", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("MainWindow", "Tree file:", 0, QApplication::UnicodeUTF8));
    pushButton->setText(QApplication::translate("MainWindow", "Change tree", 0, QApplication::UnicodeUTF8));
    gldrawer->setToolTip(QApplication::translate("MainWindow", "OpenGL visualization for Lignum", 0, QApplication::UnicodeUTF8));
    gldrawer->setWhatsThis(QApplication::translate("MainWindow", " Visualization for Lignum", 0, QApplication::UnicodeUTF8));
    pushButton_2->setText(QApplication::translate("MainWindow", "Wireframe on/off", 0, QApplication::UnicodeUTF8));
    pushButton_3->setText(QApplication::translate("MainWindow", "Lights on/off", 0, QApplication::UnicodeUTF8));
    pushButton_4->setText(QApplication::translate("MainWindow", "Textures on/off", 0, QApplication::UnicodeUTF8));
    pushButton_5->setText(QApplication::translate("MainWindow", "Reset Camera", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("MainWindow", "Segment radius detail", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("MainWindow", "Segment height detail", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("MainWindow", "Leaf detail", 0, QApplication::UnicodeUTF8));
    checkBox->setText(QApplication::translate("MainWindow", "Use BSP", 0, QApplication::UnicodeUTF8));
    checkBox_2->setText(QApplication::translate("MainWindow", "Use textures in leafs", 0, QApplication::UnicodeUTF8));
    menuValikko->setTitle(QApplication::translate("MainWindow", "valikko", 0, QApplication::UnicodeUTF8));
    menuFile->setTitle(QApplication::translate("MainWindow", "File", 0, QApplication::UnicodeUTF8));
    menuOptions->setTitle(QApplication::translate("MainWindow", "Options", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

#endif // QT_WB_H
