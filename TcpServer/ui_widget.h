/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.9.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QLineEdit *ipLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label_2;
    QLineEdit *portLineEdit;
    QPushButton *boundPushButton;
    QTextEdit *textEditRead;
    QTextEdit *textEditWrite;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButtonSend;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonClose;
    QSpacerItem *horizontalSpacer_3;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(304, 798);
        verticalLayout_2 = new QVBoxLayout(Widget);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label = new QLabel(Widget);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_2->addWidget(label);

        ipLineEdit = new QLineEdit(Widget);
        ipLineEdit->setObjectName(QStringLiteral("ipLineEdit"));

        horizontalLayout_2->addWidget(ipLineEdit);


        verticalLayout->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        label_2 = new QLabel(Widget);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_3->addWidget(label_2);

        portLineEdit = new QLineEdit(Widget);
        portLineEdit->setObjectName(QStringLiteral("portLineEdit"));

        horizontalLayout_3->addWidget(portLineEdit);

        boundPushButton = new QPushButton(Widget);
        boundPushButton->setObjectName(QStringLiteral("boundPushButton"));

        horizontalLayout_3->addWidget(boundPushButton);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_2->addLayout(verticalLayout);

        textEditRead = new QTextEdit(Widget);
        textEditRead->setObjectName(QStringLiteral("textEditRead"));
        textEditRead->setReadOnly(true);

        verticalLayout_2->addWidget(textEditRead);

        textEditWrite = new QTextEdit(Widget);
        textEditWrite->setObjectName(QStringLiteral("textEditWrite"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(textEditWrite->sizePolicy().hasHeightForWidth());
        textEditWrite->setSizePolicy(sizePolicy);
        textEditWrite->setMaximumSize(QSize(16777215, 150));

        verticalLayout_2->addWidget(textEditWrite);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(30, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        pushButtonSend = new QPushButton(Widget);
        pushButtonSend->setObjectName(QStringLiteral("pushButtonSend"));

        horizontalLayout->addWidget(pushButtonSend);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonClose = new QPushButton(Widget);
        pushButtonClose->setObjectName(QStringLiteral("pushButtonClose"));

        horizontalLayout->addWidget(pushButtonClose);

        horizontalSpacer_3 = new QSpacerItem(30, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_3);


        verticalLayout_2->addLayout(horizontalLayout);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "IP  \357\274\232", Q_NULLPTR));
        ipLineEdit->setText(QApplication::translate("Widget", "127.0.0.1", Q_NULLPTR));
        label_2->setText(QApplication::translate("Widget", "\347\253\257\345\217\243\357\274\232", Q_NULLPTR));
        portLineEdit->setText(QApplication::translate("Widget", "8888", Q_NULLPTR));
        boundPushButton->setText(QApplication::translate("Widget", "\347\273\221\345\256\232", Q_NULLPTR));
        pushButtonSend->setText(QApplication::translate("Widget", "Send", Q_NULLPTR));
        pushButtonClose->setText(QApplication::translate("Widget", "Close", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
