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
#include <QtWidgets/QColorDialog>
#include <QtWidgets/QDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QLabel>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Form : public QDialog
{
public:
    QGridLayout *vLayout;
	QColor *kcfg_borderColor;
	QPushButton *btn_borderColor;
	QLabel *lbl_borderWidth;
    QSpinBox *kcfg_borderWidth;
	QLabel *lbl_Opacity;
    QSpinBox *kcfg_Opacity;
    QCheckBox *kcfg_followFocus;

    void setupUi(QWidget *Form)
    {
        if (Form->objectName().isEmpty())
            Form->setObjectName(QString::fromUtf8("Form"));
        Form->resize(658, 592);
        Form->setMinimumSize(QSize(400, 0));
        vLayout = new QGridLayout(Form);
        vLayout->setObjectName(QString::fromUtf8("vLayout"));

        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);

        btn_borderColor = new QPushButton(Form);
		btn_borderColor->setText("Border color");
		btn_borderColor->connect(btn_borderColor, &QPushButton::clicked,this,&Ui_Form::chooseColor);
        vLayout->addWidget(btn_borderColor,0,0);

        kfcg_borderColor = new QLabel(Form);
		kfcg_borderColor->setText("");
        vLayout->addWidget(kcfg_borderColor,0,1);

        lbl_borderWidth = new QLabel(Form);
		lbl_borderWidth->setText("Border width");
        vLayout->addWidget(lbl_borderWidth,1,0);
        kcfg_borderWidth = new QSpinBox(Form);
        kcfg_borderWidth->setObjectName(QString::fromUtf8("kcfg_borderWidth"));
        sizePolicy.setHeightForWidth(kcfg_borderWidth->sizePolicy().hasHeightForWidth());
        kcfg_borderWidth->setSizePolicy(sizePolicy);
        vLayout->addWidget(kcfg_borderWidth,1,1);

        lbl_Opacity = new QLabel(Form);
		lbl_Opacity->setText("Opacity");
        vLayout->addWidget(lbl_Opacity,2,0);
        kcfg_Opacity = new QSpinBox(Form);
        kcfg_Opacity->setObjectName(QString::fromUtf8("kcfg_Opacity"));
        kcfg_Opacity->setSizePolicy(sizePolicy);
        vLayout->addWidget(kcfg_Opacity,2,1);

        kcfg_followFocus = new QCheckBox(Form);
        kcfg_followFocus->setObjectName(QString::fromUtf8("kcfg_followFocus"));
        vLayout->addWidget(kcfg_followFocus,3,0);


        retranslateUi(Form);


        QMetaObject::connectSlotsByName(Form);
    } // setupUi

    void retranslateUi(QWidget *Form)
    {
        Form->setWindowTitle(QCoreApplication::translate("Form", "Form", nullptr));

        kcfg_followFocus->setText(QCoreApplication::translate("Form", "Mouse follow focus", nullptr));
    } // retranslateUi
public slots:
	QColor chooseColor()
	{
		QColor color;
		color=QColorDialog::getColor(Qt::white,NULL, "Choose border color");
		if (color.isValid())
		{
			kcfg_borderColor=&color;
		}
		return(color);
	}

};

namespace Ui {
    class Form: public Ui_Form {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FOCUSTRACKKCM_H
