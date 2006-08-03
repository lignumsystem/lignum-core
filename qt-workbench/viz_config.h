#ifndef VIZ_CONFIG_H
#define VIZ_CONFIG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

class Ui_VisualizationConfig
{
public:
    QWidget *layoutWidget;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout1;
    QPushButton *segmentButton;
    QPushButton *leafButton;
    QVBoxLayout *vboxLayout2;
    QLineEdit *segmentText;
    QLineEdit *leafText;
    QHBoxLayout *hboxLayout1;
    QVBoxLayout *vboxLayout3;
    QCheckBox *bspBox;
    QCheckBox *leaftexBox;
    QCheckBox *wireBox;
    QCheckBox *lightBox;
    QCheckBox *texBox;
    QSpacerItem *spacerItem;
    QSpacerItem *spacerItem1;
    QVBoxLayout *vboxLayout4;
    QHBoxLayout *hboxLayout2;
    QVBoxLayout *vboxLayout5;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QVBoxLayout *vboxLayout6;
    QSpinBox *spinBox;
    QSpinBox *spinBox_2;
    QSpinBox *spinBox_3;
    QSpacerItem *spacerItem2;
    QHBoxLayout *hboxLayout3;
    QSpacerItem *spacerItem3;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *VisualizationConfig)
    {
    VisualizationConfig->setObjectName(QString::fromUtf8("VisualizationConfig"));
    VisualizationConfig->resize(QSize(521, 336).expandedTo(VisualizationConfig->minimumSizeHint()));
    layoutWidget = new QWidget(VisualizationConfig);
    layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
    layoutWidget->setGeometry(QRect(14, 14, 491, 303));
    vboxLayout = new QVBoxLayout(layoutWidget);
    vboxLayout->setSpacing(6);
    vboxLayout->setMargin(0);
    vboxLayout->setObjectName(QString::fromUtf8("vboxLayout"));
    hboxLayout = new QHBoxLayout();
    hboxLayout->setSpacing(6);
    hboxLayout->setMargin(0);
    hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setSpacing(6);
    vboxLayout1->setMargin(0);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    segmentButton = new QPushButton(layoutWidget);
    segmentButton->setObjectName(QString::fromUtf8("segmentButton"));

    vboxLayout1->addWidget(segmentButton);

    leafButton = new QPushButton(layoutWidget);
    leafButton->setObjectName(QString::fromUtf8("leafButton"));

    vboxLayout1->addWidget(leafButton);


    hboxLayout->addLayout(vboxLayout1);

    vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setSpacing(6);
    vboxLayout2->setMargin(0);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    segmentText = new QLineEdit(layoutWidget);
    segmentText->setObjectName(QString::fromUtf8("segmentText"));
    segmentText->setReadOnly(false);

    vboxLayout2->addWidget(segmentText);

    leafText = new QLineEdit(layoutWidget);
    leafText->setObjectName(QString::fromUtf8("leafText"));
    leafText->setFrame(true);
    leafText->setReadOnly(false);

    vboxLayout2->addWidget(leafText);


    hboxLayout->addLayout(vboxLayout2);


    vboxLayout->addLayout(hboxLayout);

    hboxLayout1 = new QHBoxLayout();
    hboxLayout1->setSpacing(6);
    hboxLayout1->setMargin(0);
    hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
    vboxLayout3 = new QVBoxLayout();
    vboxLayout3->setSpacing(6);
    vboxLayout3->setMargin(0);
    vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
    bspBox = new QCheckBox(layoutWidget);
    bspBox->setObjectName(QString::fromUtf8("bspBox"));

    vboxLayout3->addWidget(bspBox);

    leaftexBox = new QCheckBox(layoutWidget);
    leaftexBox->setObjectName(QString::fromUtf8("leaftexBox"));

    vboxLayout3->addWidget(leaftexBox);

    wireBox = new QCheckBox(layoutWidget);
    wireBox->setObjectName(QString::fromUtf8("wireBox"));

    vboxLayout3->addWidget(wireBox);

    lightBox = new QCheckBox(layoutWidget);
    lightBox->setObjectName(QString::fromUtf8("lightBox"));
    lightBox->setChecked(true);

    vboxLayout3->addWidget(lightBox);

    texBox = new QCheckBox(layoutWidget);
    texBox->setObjectName(QString::fromUtf8("texBox"));
    texBox->setChecked(true);

    vboxLayout3->addWidget(texBox);

    spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout3->addItem(spacerItem);


    hboxLayout1->addLayout(vboxLayout3);

    spacerItem1 = new QSpacerItem(109, 179, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout1->addItem(spacerItem1);

    vboxLayout4 = new QVBoxLayout();
    vboxLayout4->setSpacing(6);
    vboxLayout4->setMargin(0);
    vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setMargin(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    vboxLayout5 = new QVBoxLayout();
    vboxLayout5->setSpacing(6);
    vboxLayout5->setMargin(0);
    vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
    label_4 = new QLabel(layoutWidget);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    vboxLayout5->addWidget(label_4);

    label_5 = new QLabel(layoutWidget);
    label_5->setObjectName(QString::fromUtf8("label_5"));

    vboxLayout5->addWidget(label_5);

    label_6 = new QLabel(layoutWidget);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    vboxLayout5->addWidget(label_6);


    hboxLayout2->addLayout(vboxLayout5);

    vboxLayout6 = new QVBoxLayout();
    vboxLayout6->setSpacing(6);
    vboxLayout6->setMargin(0);
    vboxLayout6->setObjectName(QString::fromUtf8("vboxLayout6"));
    spinBox = new QSpinBox(layoutWidget);
    spinBox->setObjectName(QString::fromUtf8("spinBox"));

    vboxLayout6->addWidget(spinBox);

    spinBox_2 = new QSpinBox(layoutWidget);
    spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));

    vboxLayout6->addWidget(spinBox_2);

    spinBox_3 = new QSpinBox(layoutWidget);
    spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));

    vboxLayout6->addWidget(spinBox_3);


    hboxLayout2->addLayout(vboxLayout6);


    vboxLayout4->addLayout(hboxLayout2);

    spacerItem2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout4->addItem(spacerItem2);


    hboxLayout1->addLayout(vboxLayout4);


    vboxLayout->addLayout(hboxLayout1);

    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setSpacing(6);
    hboxLayout3->setMargin(0);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    spacerItem3 = new QSpacerItem(231, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout3->addItem(spacerItem3);

    okButton = new QPushButton(layoutWidget);
    okButton->setObjectName(QString::fromUtf8("okButton"));

    hboxLayout3->addWidget(okButton);

    cancelButton = new QPushButton(layoutWidget);
    cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

    hboxLayout3->addWidget(cancelButton);


    vboxLayout->addLayout(hboxLayout3);

    retranslateUi(VisualizationConfig);

    QMetaObject::connectSlotsByName(VisualizationConfig);
    } // setupUi

    void retranslateUi(QDialog *VisualizationConfig)
    {
    VisualizationConfig->setWindowTitle(QApplication::translate("VisualizationConfig", "Visualization settings", 0, QApplication::UnicodeUTF8));
    segmentButton->setText(QApplication::translate("VisualizationConfig", "Segment texture...", 0, QApplication::UnicodeUTF8));
    leafButton->setText(QApplication::translate("VisualizationConfig", "Leaf texture...", 0, QApplication::UnicodeUTF8));
    bspBox->setText(QApplication::translate("VisualizationConfig", "Use BSP-tree", 0, QApplication::UnicodeUTF8));
    leaftexBox->setText(QApplication::translate("VisualizationConfig", "Use texture in leafs", 0, QApplication::UnicodeUTF8));
    wireBox->setText(QApplication::translate("VisualizationConfig", "Wireframe model", 0, QApplication::UnicodeUTF8));
    lightBox->setText(QApplication::translate("VisualizationConfig", "Lighting", 0, QApplication::UnicodeUTF8));
    texBox->setText(QApplication::translate("VisualizationConfig", "Texturing", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("VisualizationConfig", "Segment radius detail", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("VisualizationConfig", "Segment height detail", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("VisualizationConfig", "Leaf detail", 0, QApplication::UnicodeUTF8));
    okButton->setText(QApplication::translate("VisualizationConfig", "OK", 0, QApplication::UnicodeUTF8));
    cancelButton->setText(QApplication::translate("VisualizationConfig", "Cancel", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(VisualizationConfig);
    } // retranslateUi

};

namespace Ui {
    class VisualizationConfig: public Ui_VisualizationConfig {};
} // namespace Ui

#endif // VIZ_CONFIG_H
