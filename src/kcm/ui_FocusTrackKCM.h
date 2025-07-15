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
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form
{
public:
    QVBoxLayout *vLayout;
    QLineEdit *kcfg_borderWidth;
    QCheckBox *kcfg_followFocus;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(658, 592);
        Form->setMinimumSize(QSize(400, 0));
        vLayout = new QVBoxLayout(Form);
        vLayout->setObjectName(QString::fromUtf8("vLayout"));
        kcfg_borderWidth = new QLineEdit(Form);
        kcfg_borderWidth->setObjectName(QString::fromUtf8("kcfg_borderWidth"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(kcfg_borderWidth->sizePolicy().hasHeightForWidth());
        kcfg_borderWidth->setSizePolicy(sizePolicy);

        vLayout->addWidget(kcfg_borderWidth);

        kcfg_followFocus = new QCheckBox(Form);
        kcfg_followFocus->setObjectName(QString::fromUtf8("kcfg_followFocus"));

        vLayout->addWidget(kcfg_followFocus);


        retranslateUi(Form);


        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));

        kcfg_followFocus->setText(QCoreApplication::translate("Form", "Mouse follow focus", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FOCUSTRACKKCM_H
