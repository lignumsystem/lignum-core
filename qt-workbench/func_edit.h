#ifndef FUNC_EDIT_H
#define FUNC_EDIT_H

#include "FunctionPainter.h"
#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_FunctionEditor
{
public:
    QAction *actionOpen;
    QAction *actionQuit;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionNew;
    QWidget *centralwidget;
    QHBoxLayout *hboxLayout;
    QHBoxLayout *hboxLayout1;
    QVBoxLayout *vboxLayout;
    FunctionPainter *f_painter;
    QHBoxLayout *hboxLayout2;
    QVBoxLayout *vboxLayout1;
    QHBoxLayout *hboxLayout3;
    QLabel *label_6;
    QDoubleSpinBox *xtickBox;
    QHBoxLayout *hboxLayout4;
    QLabel *label_5;
    QDoubleSpinBox *yticBox;
    QVBoxLayout *vboxLayout2;
    QHBoxLayout *hboxLayout5;
    QLabel *label_3;
    QDoubleSpinBox *minXBox;
    QHBoxLayout *hboxLayout6;
    QLabel *label_4;
    QDoubleSpinBox *maxXBox;
    QVBoxLayout *vboxLayout3;
    QHBoxLayout *hboxLayout7;
    QLabel *label;
    QDoubleSpinBox *minYBox;
    QHBoxLayout *hboxLayout8;
    QLabel *label_2;
    QDoubleSpinBox *maxYBo;
    QTextEdit *textEdit;
    QMenuBar *menubar;
    QMenu *menuFile;
    QStatusBar *statusbar;
    QToolBar *toolBar;

    void setupUi(QMainWindow *FunctionEditor)
    {
    FunctionEditor->setObjectName(QString::fromUtf8("FunctionEditor"));
    FunctionEditor->resize(QSize(874, 691).expandedTo(FunctionEditor->minimumSizeHint()));
    actionOpen = new QAction(FunctionEditor);
    actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
    actionQuit = new QAction(FunctionEditor);
    actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
    actionSave = new QAction(FunctionEditor);
    actionSave->setObjectName(QString::fromUtf8("actionSave"));
    actionSave_as = new QAction(FunctionEditor);
    actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
    actionNew = new QAction(FunctionEditor);
    actionNew->setObjectName(QString::fromUtf8("actionNew"));
    centralwidget = new QWidget(FunctionEditor);
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
    f_painter = new FunctionPainter(centralwidget);
    f_painter->setObjectName(QString::fromUtf8("f_painter"));
    QSizePolicy sizePolicy(static_cast<QSizePolicy::Policy>(7), static_cast<QSizePolicy::Policy>(7));
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(f_painter->sizePolicy().hasHeightForWidth());
    f_painter->setSizePolicy(sizePolicy);
    f_painter->setAutoFillBackground(false);

    vboxLayout->addWidget(f_painter);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setMargin(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setSpacing(6);
    vboxLayout1->setMargin(0);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setSpacing(6);
    hboxLayout3->setMargin(0);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    label_6 = new QLabel(centralwidget);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    hboxLayout3->addWidget(label_6);

    xtickBox = new QDoubleSpinBox(centralwidget);
    xtickBox->setObjectName(QString::fromUtf8("xtickBox"));
    xtickBox->setMinimum(0.1);
    xtickBox->setSingleStep(0.1);

    hboxLayout3->addWidget(xtickBox);


    vboxLayout1->addLayout(hboxLayout3);

    hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setSpacing(6);
    hboxLayout4->setMargin(0);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    label_5 = new QLabel(centralwidget);
    label_5->setObjectName(QString::fromUtf8("label_5"));

    hboxLayout4->addWidget(label_5);

    yticBox = new QDoubleSpinBox(centralwidget);
    yticBox->setObjectName(QString::fromUtf8("yticBox"));
    yticBox->setMinimum(0.1);
    yticBox->setSingleStep(0.1);

    hboxLayout4->addWidget(yticBox);


    vboxLayout1->addLayout(hboxLayout4);


    hboxLayout2->addLayout(vboxLayout1);

    vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setSpacing(6);
    vboxLayout2->setMargin(0);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    hboxLayout5 = new QHBoxLayout();
    hboxLayout5->setSpacing(6);
    hboxLayout5->setMargin(0);
    hboxLayout5->setObjectName(QString::fromUtf8("hboxLayout5"));
    label_3 = new QLabel(centralwidget);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    hboxLayout5->addWidget(label_3);

    minXBox = new QDoubleSpinBox(centralwidget);
    minXBox->setObjectName(QString::fromUtf8("minXBox"));
    minXBox->setMaximum(1e+07);
    minXBox->setMinimum(-1e+07);
    minXBox->setSingleStep(0.1);
    minXBox->setValue(0);

    hboxLayout5->addWidget(minXBox);


    vboxLayout2->addLayout(hboxLayout5);

    hboxLayout6 = new QHBoxLayout();
    hboxLayout6->setSpacing(6);
    hboxLayout6->setMargin(0);
    hboxLayout6->setObjectName(QString::fromUtf8("hboxLayout6"));
    label_4 = new QLabel(centralwidget);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    hboxLayout6->addWidget(label_4);

    maxXBox = new QDoubleSpinBox(centralwidget);
    maxXBox->setObjectName(QString::fromUtf8("maxXBox"));
    maxXBox->setMaximum(1e+08);
    maxXBox->setMinimum(-1e+07);
    maxXBox->setSingleStep(0.1);

    hboxLayout6->addWidget(maxXBox);


    vboxLayout2->addLayout(hboxLayout6);


    hboxLayout2->addLayout(vboxLayout2);

    vboxLayout3 = new QVBoxLayout();
    vboxLayout3->setSpacing(6);
    vboxLayout3->setMargin(0);
    vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
    hboxLayout7 = new QHBoxLayout();
    hboxLayout7->setSpacing(6);
    hboxLayout7->setMargin(0);
    hboxLayout7->setObjectName(QString::fromUtf8("hboxLayout7"));
    label = new QLabel(centralwidget);
    label->setObjectName(QString::fromUtf8("label"));

    hboxLayout7->addWidget(label);

    minYBox = new QDoubleSpinBox(centralwidget);
    minYBox->setObjectName(QString::fromUtf8("minYBox"));
    minYBox->setMaximum(1e+07);
    minYBox->setMinimum(-1e+07);
    minYBox->setSingleStep(0.1);

    hboxLayout7->addWidget(minYBox);


    vboxLayout3->addLayout(hboxLayout7);

    hboxLayout8 = new QHBoxLayout();
    hboxLayout8->setSpacing(6);
    hboxLayout8->setMargin(0);
    hboxLayout8->setObjectName(QString::fromUtf8("hboxLayout8"));
    label_2 = new QLabel(centralwidget);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    hboxLayout8->addWidget(label_2);

    maxYBo = new QDoubleSpinBox(centralwidget);
    maxYBo->setObjectName(QString::fromUtf8("maxYBo"));
    maxYBo->setMaximum(1e+07);
    maxYBo->setMinimum(-1e+07);
    maxYBo->setSingleStep(0.1);

    hboxLayout8->addWidget(maxYBo);


    vboxLayout3->addLayout(hboxLayout8);


    hboxLayout2->addLayout(vboxLayout3);


    vboxLayout->addLayout(hboxLayout2);


    hboxLayout1->addLayout(vboxLayout);

    textEdit = new QTextEdit(centralwidget);
    textEdit->setObjectName(QString::fromUtf8("textEdit"));
    textEdit->setMinimumSize(QSize(0, 400));

    hboxLayout1->addWidget(textEdit);


    hboxLayout->addLayout(hboxLayout1);

    FunctionEditor->setCentralWidget(centralwidget);
    menubar = new QMenuBar(FunctionEditor);
    menubar->setObjectName(QString::fromUtf8("menubar"));
    menubar->setGeometry(QRect(0, 0, 874, 26));
    menuFile = new QMenu(menubar);
    menuFile->setObjectName(QString::fromUtf8("menuFile"));
    FunctionEditor->setMenuBar(menubar);
    statusbar = new QStatusBar(FunctionEditor);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    FunctionEditor->setStatusBar(statusbar);
    toolBar = new QToolBar(FunctionEditor);
    toolBar->setObjectName(QString::fromUtf8("toolBar"));
    toolBar->setOrientation(Qt::Horizontal);
    FunctionEditor->addToolBar(static_cast<Qt::ToolBarArea>(4), toolBar);
    label_6->setBuddy(xtickBox);
    label_5->setBuddy(yticBox);
    label_3->setBuddy(minXBox);
    label_4->setBuddy(maxXBox);
    label->setBuddy(minYBox);
    label_2->setBuddy(maxYBo);

    menubar->addAction(menuFile->menuAction());
    menuFile->addAction(actionNew);
    menuFile->addAction(actionOpen);
    menuFile->addSeparator();
    menuFile->addAction(actionSave);
    menuFile->addAction(actionSave_as);
    menuFile->addSeparator();
    menuFile->addAction(actionQuit);
    toolBar->addAction(actionNew);
    toolBar->addAction(actionOpen);
    toolBar->addSeparator();
    toolBar->addAction(actionSave);
    toolBar->addAction(actionSave_as);
    retranslateUi(FunctionEditor);
    QObject::connect(xtickBox, SIGNAL(valueChanged(double)), f_painter, SLOT(setXTicks(double)));
    QObject::connect(yticBox, SIGNAL(valueChanged(double)), f_painter, SLOT(setYTicks(double)));
    QObject::connect(minXBox, SIGNAL(valueChanged(double)), f_painter, SLOT(setMinX(double)));
    QObject::connect(maxXBox, SIGNAL(valueChanged(double)), f_painter, SLOT(setMaxX(double)));
    QObject::connect(minYBox, SIGNAL(valueChanged(double)), f_painter, SLOT(setMinY(double)));
    QObject::connect(maxYBo, SIGNAL(valueChanged(double)), f_painter, SLOT(setMaxY(double)));
    QObject::connect(f_painter, SIGNAL(xTicksChanged(double)), xtickBox, SLOT(setValue(double)));
    QObject::connect(f_painter, SIGNAL(yTicksChanged(double)), yticBox, SLOT(setValue(double)));
    QObject::connect(f_painter, SIGNAL(minXChanged(double)), minXBox, SLOT(setValue(double)));
    QObject::connect(f_painter, SIGNAL(maxXChanged(double)), maxXBox, SLOT(setValue(double)));
    QObject::connect(f_painter, SIGNAL(minYChanged(double)), minYBox, SLOT(setValue(double)));
    QObject::connect(f_painter, SIGNAL(maxYChanged(double)), maxYBo, SLOT(setValue(double)));

    QMetaObject::connectSlotsByName(FunctionEditor);
    } // setupUi

    void retranslateUi(QMainWindow *FunctionEditor)
    {
    FunctionEditor->setWindowTitle(QApplication::translate("FunctionEditor", "Function Editor", 0, QApplication::UnicodeUTF8));
    actionOpen->setText(QApplication::translate("FunctionEditor", "Open...", 0, QApplication::UnicodeUTF8));
    actionQuit->setText(QApplication::translate("FunctionEditor", "Quit", 0, QApplication::UnicodeUTF8));
    actionSave->setText(QApplication::translate("FunctionEditor", "Save", 0, QApplication::UnicodeUTF8));
    actionSave_as->setText(QApplication::translate("FunctionEditor", "Save as...", 0, QApplication::UnicodeUTF8));
    actionNew->setText(QApplication::translate("FunctionEditor", "New", 0, QApplication::UnicodeUTF8));
    f_painter->setToolTip(QApplication::translate("FunctionEditor", "Function painter for Lignum", 0, QApplication::UnicodeUTF8));
    f_painter->setWhatsThis(QApplication::translate("FunctionEditor", " Function painter for Lignum", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("FunctionEditor", "X ticks:", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("FunctionEditor", "Y ticks:", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("FunctionEditor", "Min X:", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("FunctionEditor", "Max X:", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("FunctionEditor", "Min Y:", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("FunctionEditor", "Max Y:", 0, QApplication::UnicodeUTF8));
    menuFile->setTitle(QApplication::translate("FunctionEditor", "File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class FunctionEditor: public Ui_FunctionEditor {};
} // namespace Ui

#endif // FUNC_EDIT_H
