#ifndef CONSOLE_WINDOW_H
#define CONSOLE_WINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_Console
{
public:
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout1;
    QLineEdit *console;
    QPushButton *runButton;
    QPushButton *killButton;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *Console)
    {
    Console->setObjectName(QString::fromUtf8("Console"));
    Console->resize(QSize(834, 441).expandedTo(Console->minimumSizeHint()));
    hboxLayout = new QHBoxLayout(Console);
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(9);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    vboxLayout = new QVBoxLayout();
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    console = new QLineEdit(Console);
    console->setObjectName(QString::fromUtf8("console"));

    hboxLayout1->addWidget(console);

    runButton = new QPushButton(Console);
    runButton->setObjectName(QString::fromUtf8("runButton"));

    hboxLayout1->addWidget(runButton);

    killButton = new QPushButton(Console);
    killButton->setObjectName(QString::fromUtf8("killButton"));

    hboxLayout1->addWidget(killButton);


    vboxLayout->addLayout(hboxLayout1);

    textBrowser = new QTextBrowser(Console);
    textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
    textBrowser->setMaximumSize(QSize(16777215, 16777215));

    vboxLayout->addWidget(textBrowser);


    hboxLayout->addLayout(vboxLayout);

    retranslateUi(Console);

    QMetaObject::connectSlotsByName(Console);
    } // setupUi

    void retranslateUi(QWidget *Console)
    {
    Console->setWindowTitle(QApplication::translate("Console", "Form", 0, QApplication::UnicodeUTF8));
    runButton->setText(QApplication::translate("Console", "Run", 0, QApplication::UnicodeUTF8));
    killButton->setText(QApplication::translate("Console", "Kill program", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(Console);
    } // retranslateUi

};

namespace Ui {
    class Console: public Ui_Console {};
} // namespace Ui

#endif // CONSOLE_WINDOW_H
