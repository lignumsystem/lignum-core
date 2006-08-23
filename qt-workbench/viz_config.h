#ifndef VIZ_CONFIG_H
#define VIZ_CONFIG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QCheckBox>
#include <QtGui/QDialog>
#include <QtGui/QDoubleSpinBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QVBoxLayout>

class Ui_VisualizationConfig
{
public:
    QHBoxLayout *hboxLayout;
    QVBoxLayout *vboxLayout;
    QHBoxLayout *hboxLayout1;
    QVBoxLayout *vboxLayout1;
    QPushButton *segmentButton;
    QPushButton *leafButton;
    QPushButton *foliageButton;
    QVBoxLayout *vboxLayout2;
    QLineEdit *segmentText;
    QLineEdit *leafText;
    QLineEdit *foliageText;
    QHBoxLayout *hboxLayout2;
    QVBoxLayout *vboxLayout3;
    QCheckBox *bspBox;
    QCheckBox *leaftexBox;
    QCheckBox *budBox;
    QCheckBox *wireBox;
    QCheckBox *lightBox;
    QCheckBox *texBox;
    QSpacerItem *spacerItem;
    QSpacerItem *spacerItem1;
    QVBoxLayout *vboxLayout4;
    QHBoxLayout *hboxLayout3;
    QVBoxLayout *vboxLayout5;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label;
    QLabel *label_2;
    QLabel *foliageLabe;
    QLabel *label_7;
    QLabel *label_3;
    QVBoxLayout *vboxLayout6;
    QSpinBox *srdetailBox;
    QSpinBox *shdetailBox;
    QSpinBox *ldetailBox;
    QSpinBox *budloBox;
    QSpinBox *budlaBox;
    QSpinBox *foliageBox;
    QDoubleSpinBox *fspacingBox;
    QSpinBox *petioleBox;
    QHBoxLayout *hboxLayout4;
    QSpacerItem *spacerItem2;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *VisualizationConfig)
    {
    VisualizationConfig->setObjectName(QString::fromUtf8("VisualizationConfig"));
    VisualizationConfig->resize(QSize(562, 593).expandedTo(VisualizationConfig->minimumSizeHint()));
    hboxLayout = new QHBoxLayout(VisualizationConfig);
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
    vboxLayout1 = new QVBoxLayout();
    vboxLayout1->setSpacing(6);
    vboxLayout1->setMargin(0);
    vboxLayout1->setObjectName(QString::fromUtf8("vboxLayout1"));
    segmentButton = new QPushButton(VisualizationConfig);
    segmentButton->setObjectName(QString::fromUtf8("segmentButton"));

    vboxLayout1->addWidget(segmentButton);

    leafButton = new QPushButton(VisualizationConfig);
    leafButton->setObjectName(QString::fromUtf8("leafButton"));

    vboxLayout1->addWidget(leafButton);

    foliageButton = new QPushButton(VisualizationConfig);
    foliageButton->setObjectName(QString::fromUtf8("foliageButton"));

    vboxLayout1->addWidget(foliageButton);


    hboxLayout1->addLayout(vboxLayout1);

    vboxLayout2 = new QVBoxLayout();
    vboxLayout2->setSpacing(6);
    vboxLayout2->setMargin(0);
    vboxLayout2->setObjectName(QString::fromUtf8("vboxLayout2"));
    segmentText = new QLineEdit(VisualizationConfig);
    segmentText->setObjectName(QString::fromUtf8("segmentText"));
    segmentText->setReadOnly(false);

    vboxLayout2->addWidget(segmentText);

    leafText = new QLineEdit(VisualizationConfig);
    leafText->setObjectName(QString::fromUtf8("leafText"));
    leafText->setFrame(true);
    leafText->setReadOnly(false);

    vboxLayout2->addWidget(leafText);

    foliageText = new QLineEdit(VisualizationConfig);
    foliageText->setObjectName(QString::fromUtf8("foliageText"));

    vboxLayout2->addWidget(foliageText);


    hboxLayout1->addLayout(vboxLayout2);


    vboxLayout->addLayout(hboxLayout1);

    hboxLayout2 = new QHBoxLayout();
    hboxLayout2->setSpacing(6);
    hboxLayout2->setMargin(0);
    hboxLayout2->setObjectName(QString::fromUtf8("hboxLayout2"));
    vboxLayout3 = new QVBoxLayout();
    vboxLayout3->setSpacing(6);
    vboxLayout3->setMargin(0);
    vboxLayout3->setObjectName(QString::fromUtf8("vboxLayout3"));
    bspBox = new QCheckBox(VisualizationConfig);
    bspBox->setObjectName(QString::fromUtf8("bspBox"));

    vboxLayout3->addWidget(bspBox);

    leaftexBox = new QCheckBox(VisualizationConfig);
    leaftexBox->setObjectName(QString::fromUtf8("leaftexBox"));

    vboxLayout3->addWidget(leaftexBox);

    budBox = new QCheckBox(VisualizationConfig);
    budBox->setObjectName(QString::fromUtf8("budBox"));

    vboxLayout3->addWidget(budBox);

    wireBox = new QCheckBox(VisualizationConfig);
    wireBox->setObjectName(QString::fromUtf8("wireBox"));

    vboxLayout3->addWidget(wireBox);

    lightBox = new QCheckBox(VisualizationConfig);
    lightBox->setObjectName(QString::fromUtf8("lightBox"));
    lightBox->setChecked(true);

    vboxLayout3->addWidget(lightBox);

    texBox = new QCheckBox(VisualizationConfig);
    texBox->setObjectName(QString::fromUtf8("texBox"));
    texBox->setChecked(true);

    vboxLayout3->addWidget(texBox);

    spacerItem = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

    vboxLayout3->addItem(spacerItem);


    hboxLayout2->addLayout(vboxLayout3);

    spacerItem1 = new QSpacerItem(109, 179, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout2->addItem(spacerItem1);

    vboxLayout4 = new QVBoxLayout();
    vboxLayout4->setSpacing(6);
    vboxLayout4->setMargin(0);
    vboxLayout4->setObjectName(QString::fromUtf8("vboxLayout4"));
    hboxLayout3 = new QHBoxLayout();
    hboxLayout3->setSpacing(6);
    hboxLayout3->setMargin(0);
    hboxLayout3->setObjectName(QString::fromUtf8("hboxLayout3"));
    vboxLayout5 = new QVBoxLayout();
    vboxLayout5->setSpacing(6);
    vboxLayout5->setMargin(0);
    vboxLayout5->setObjectName(QString::fromUtf8("vboxLayout5"));
    label_4 = new QLabel(VisualizationConfig);
    label_4->setObjectName(QString::fromUtf8("label_4"));

    vboxLayout5->addWidget(label_4);

    label_5 = new QLabel(VisualizationConfig);
    label_5->setObjectName(QString::fromUtf8("label_5"));

    vboxLayout5->addWidget(label_5);

    label_6 = new QLabel(VisualizationConfig);
    label_6->setObjectName(QString::fromUtf8("label_6"));

    vboxLayout5->addWidget(label_6);

    label = new QLabel(VisualizationConfig);
    label->setObjectName(QString::fromUtf8("label"));

    vboxLayout5->addWidget(label);

    label_2 = new QLabel(VisualizationConfig);
    label_2->setObjectName(QString::fromUtf8("label_2"));

    vboxLayout5->addWidget(label_2);

    foliageLabe = new QLabel(VisualizationConfig);
    foliageLabe->setObjectName(QString::fromUtf8("foliageLabe"));

    vboxLayout5->addWidget(foliageLabe);

    label_7 = new QLabel(VisualizationConfig);
    label_7->setObjectName(QString::fromUtf8("label_7"));

    vboxLayout5->addWidget(label_7);

    label_3 = new QLabel(VisualizationConfig);
    label_3->setObjectName(QString::fromUtf8("label_3"));

    vboxLayout5->addWidget(label_3);


    hboxLayout3->addLayout(vboxLayout5);

    vboxLayout6 = new QVBoxLayout();
    vboxLayout6->setSpacing(6);
    vboxLayout6->setMargin(0);
    vboxLayout6->setObjectName(QString::fromUtf8("vboxLayout6"));
    srdetailBox = new QSpinBox(VisualizationConfig);
    srdetailBox->setObjectName(QString::fromUtf8("srdetailBox"));

    vboxLayout6->addWidget(srdetailBox);

    shdetailBox = new QSpinBox(VisualizationConfig);
    shdetailBox->setObjectName(QString::fromUtf8("shdetailBox"));

    vboxLayout6->addWidget(shdetailBox);

    ldetailBox = new QSpinBox(VisualizationConfig);
    ldetailBox->setObjectName(QString::fromUtf8("ldetailBox"));

    vboxLayout6->addWidget(ldetailBox);

    budloBox = new QSpinBox(VisualizationConfig);
    budloBox->setObjectName(QString::fromUtf8("budloBox"));

    vboxLayout6->addWidget(budloBox);

    budlaBox = new QSpinBox(VisualizationConfig);
    budlaBox->setObjectName(QString::fromUtf8("budlaBox"));

    vboxLayout6->addWidget(budlaBox);

    foliageBox = new QSpinBox(VisualizationConfig);
    foliageBox->setObjectName(QString::fromUtf8("foliageBox"));

    vboxLayout6->addWidget(foliageBox);

    fspacingBox = new QDoubleSpinBox(VisualizationConfig);
    fspacingBox->setObjectName(QString::fromUtf8("fspacingBox"));

    vboxLayout6->addWidget(fspacingBox);

    petioleBox = new QSpinBox(VisualizationConfig);
    petioleBox->setObjectName(QString::fromUtf8("petioleBox"));

    vboxLayout6->addWidget(petioleBox);


    hboxLayout3->addLayout(vboxLayout6);


    vboxLayout4->addLayout(hboxLayout3);


    hboxLayout2->addLayout(vboxLayout4);


    vboxLayout->addLayout(hboxLayout2);

    hboxLayout4 = new QHBoxLayout();
    hboxLayout4->setSpacing(6);
    hboxLayout4->setMargin(0);
    hboxLayout4->setObjectName(QString::fromUtf8("hboxLayout4"));
    spacerItem2 = new QSpacerItem(231, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

    hboxLayout4->addItem(spacerItem2);

    okButton = new QPushButton(VisualizationConfig);
    okButton->setObjectName(QString::fromUtf8("okButton"));

    hboxLayout4->addWidget(okButton);

    cancelButton = new QPushButton(VisualizationConfig);
    cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

    hboxLayout4->addWidget(cancelButton);


    vboxLayout->addLayout(hboxLayout4);


    hboxLayout->addLayout(vboxLayout);

    label_4->setBuddy(srdetailBox);
    label_5->setBuddy(shdetailBox);
    label_6->setBuddy(ldetailBox);
    label->setBuddy(budloBox);
    label_2->setBuddy(budlaBox);
    retranslateUi(VisualizationConfig);

    QMetaObject::connectSlotsByName(VisualizationConfig);
    } // setupUi

    void retranslateUi(QDialog *VisualizationConfig)
    {
    VisualizationConfig->setWindowTitle(QApplication::translate("VisualizationConfig", "Visualization settings", 0, QApplication::UnicodeUTF8));
    segmentButton->setText(QApplication::translate("VisualizationConfig", "Segment texture...", 0, QApplication::UnicodeUTF8));
    leafButton->setText(QApplication::translate("VisualizationConfig", "Leaf texture...", 0, QApplication::UnicodeUTF8));
    foliageButton->setText(QApplication::translate("VisualizationConfig", "Foliage texture...", 0, QApplication::UnicodeUTF8));
    bspBox->setText(QApplication::translate("VisualizationConfig", "Use BSP-tree", 0, QApplication::UnicodeUTF8));
    leaftexBox->setText(QApplication::translate("VisualizationConfig", "Use texture in leafs", 0, QApplication::UnicodeUTF8));
    budBox->setText(QApplication::translate("VisualizationConfig", "Show buds", 0, QApplication::UnicodeUTF8));
    wireBox->setText(QApplication::translate("VisualizationConfig", "Wireframe model", 0, QApplication::UnicodeUTF8));
    lightBox->setText(QApplication::translate("VisualizationConfig", "Lighting", 0, QApplication::UnicodeUTF8));
    texBox->setText(QApplication::translate("VisualizationConfig", "Texturing", 0, QApplication::UnicodeUTF8));
    label_4->setText(QApplication::translate("VisualizationConfig", "Segment radius detail", 0, QApplication::UnicodeUTF8));
    label_5->setText(QApplication::translate("VisualizationConfig", "Segment height detail", 0, QApplication::UnicodeUTF8));
    label_6->setText(QApplication::translate("VisualizationConfig", "Leaf detail", 0, QApplication::UnicodeUTF8));
    label->setText(QApplication::translate("VisualizationConfig", "Bud longitude detail", 0, QApplication::UnicodeUTF8));
    label_2->setText(QApplication::translate("VisualizationConfig", "Bud latitude detail", 0, QApplication::UnicodeUTF8));
    foliageLabe->setText(QApplication::translate("VisualizationConfig", "Folige detail", 0, QApplication::UnicodeUTF8));
    label_7->setText(QApplication::translate("VisualizationConfig", "Foliage spacing", 0, QApplication::UnicodeUTF8));
    label_3->setText(QApplication::translate("VisualizationConfig", "Petiole detail", 0, QApplication::UnicodeUTF8));
    okButton->setText(QApplication::translate("VisualizationConfig", "OK", 0, QApplication::UnicodeUTF8));
    cancelButton->setText(QApplication::translate("VisualizationConfig", "Cancel", 0, QApplication::UnicodeUTF8));
    Q_UNUSED(VisualizationConfig);
    } // retranslateUi

};

namespace Ui {
    class VisualizationConfig: public Ui_VisualizationConfig {};
} // namespace Ui

#endif // VIZ_CONFIG_H
