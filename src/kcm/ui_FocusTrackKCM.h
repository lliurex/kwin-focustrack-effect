/********************************************************************************
** Form generated from reading UI file 'FocusTrackKCM.ui'
**
** Created by: Qt User Interface Compiler version 5.15.10
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FOCUSTRACKKCM_H
#define UI_FOCUSTRACKKCM_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *vLayout;
    QComboBox *kcfg_colorCorrectionFilter;
    QCheckBox *kcfg_applyFocusTrack;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(658, 592);
        Form->setMinimumSize(QSize(400, 0));
        vLayout = new QVBoxLayout(Form);
        vLayout->setObjectName(QString::fromUtf8("vLayout"));
        kcfg_colorCorrectionFilter = new QComboBox(Form);
        kcfg_colorCorrectionFilter->addItem(QString());
        kcfg_colorCorrectionFilter->addItem(QString());
        kcfg_colorCorrectionFilter->addItem(QString());
        kcfg_colorCorrectionFilter->addItem(QString());
        kcfg_colorCorrectionFilter->addItem(QString());
        kcfg_colorCorrectionFilter->addItem(QString());
        kcfg_colorCorrectionFilter->addItem(QString());
        kcfg_colorCorrectionFilter->addItem(QString());
        kcfg_colorCorrectionFilter->addItem(QString());
        kcfg_colorCorrectionFilter->addItem(QString());
        kcfg_colorCorrectionFilter->addItem(QString());
        kcfg_colorCorrectionFilter->setObjectName(QString::fromUtf8("kcfg_colorCorrectionFilter"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(kcfg_colorCorrectionFilter->sizePolicy().hasHeightForWidth());
        kcfg_colorCorrectionFilter->setSizePolicy(sizePolicy);

        vLayout->addWidget(kcfg_colorCorrectionFilter);

        kcfg_applyFocusTrack = new QCheckBox(Form);
        kcfg_applyFocusTrack->setObjectName(QString::fromUtf8("kcfg_applyFocusTrack"));

        vLayout->addWidget(kcfg_applyFocusTrack);


        retranslateUi(Form);

        kcfg_colorCorrectionFilter->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));
        kcfg_colorCorrectionFilter->setItemText(0, QCoreApplication::translate("Form", "Protanopia", nullptr));
        kcfg_colorCorrectionFilter->setItemText(1, QCoreApplication::translate("Form", "Protanopia (Alt. 1)", nullptr));
        kcfg_colorCorrectionFilter->setItemText(2, QCoreApplication::translate("Form", "Protanopia (Alt. 2)", nullptr));
        kcfg_colorCorrectionFilter->setItemText(3, QCoreApplication::translate("Form", "Deuteranopia", nullptr));
        kcfg_colorCorrectionFilter->setItemText(4, QCoreApplication::translate("Form", "Deuteranopia (Alt. 1)", nullptr));
        kcfg_colorCorrectionFilter->setItemText(5, QCoreApplication::translate("Form", "Deuteranopia (Alt. 2)", nullptr));
        kcfg_colorCorrectionFilter->setItemText(6, QCoreApplication::translate("Form", "Tritanopia", nullptr));
        kcfg_colorCorrectionFilter->setItemText(7, QCoreApplication::translate("Form", "Tritanopia (Alt. 1)", nullptr));
        kcfg_colorCorrectionFilter->setItemText(8, QCoreApplication::translate("Form", "Tritanopia (Alt. 2)", nullptr));
        kcfg_colorCorrectionFilter->setItemText(9, QCoreApplication::translate("Form", "Achromatopsia", nullptr));
        kcfg_colorCorrectionFilter->setItemText(10, QCoreApplication::translate("Form", "Achromatopsia (Alt. 1)", nullptr));

        kcfg_applyFocusTrack->setText(QCoreApplication::translate("Form", "Boost effect", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FOCUSTRACKKCM_H
