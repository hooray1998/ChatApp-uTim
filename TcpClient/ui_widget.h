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
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QTabWidget *tabWidget;
    QWidget *tab;
    QVBoxLayout *verticalLayout_5;
    QLabel *nameLabel;
    QWidget *tab_2;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_2;
    QLineEdit *lineEdit_2;
    QPushButton *connectPushButton;
    QSplitter *splitter_2;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLabel *chatNameLabel;
    QTextEdit *textEditRead;
    QTextEdit *textEditWrite;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *sendFilePushButton;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *acceptFilePushButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButton_3;
    QProgressBar *progressBar;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->resize(1096, 741);
        Widget->setStyleSheet(QStringLiteral(""));
        verticalLayout_4 = new QVBoxLayout(Widget);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        tabWidget = new QTabWidget(Widget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy);
        tabWidget->setMinimumSize(QSize(257, 110));
        tabWidget->setMaximumSize(QSize(257, 110));
        tabWidget->setTabPosition(QTabWidget::North);
        tabWidget->setIconSize(QSize(16, 8));
        tabWidget->setTabBarAutoHide(true);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        verticalLayout_5 = new QVBoxLayout(tab);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        nameLabel = new QLabel(tab);
        nameLabel->setObjectName(QStringLiteral("nameLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(nameLabel->sizePolicy().hasHeightForWidth());
        nameLabel->setSizePolicy(sizePolicy1);
        nameLabel->setMinimumSize(QSize(0, 50));
        QFont font;
        font.setFamily(QStringLiteral("Agency FB"));
        font.setPointSize(36);
        nameLabel->setFont(font);

        verticalLayout_5->addWidget(nameLabel);

        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        verticalLayout_6 = new QVBoxLayout(tab_2);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(tab_2);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout->addWidget(label);

        lineEdit = new QLineEdit(tab_2);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QStringLiteral("label_2"));

        horizontalLayout_2->addWidget(label_2);

        lineEdit_2 = new QLineEdit(tab_2);
        lineEdit_2->setObjectName(QStringLiteral("lineEdit_2"));

        horizontalLayout_2->addWidget(lineEdit_2);

        connectPushButton = new QPushButton(tab_2);
        connectPushButton->setObjectName(QStringLiteral("connectPushButton"));

        horizontalLayout_2->addWidget(connectPushButton);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_6->addLayout(verticalLayout);

        tabWidget->addTab(tab_2, QString());

        verticalLayout_3->addWidget(tabWidget);

        splitter_2 = new QSplitter(Widget);
        splitter_2->setObjectName(QStringLiteral("splitter_2"));
        sizePolicy.setHeightForWidth(splitter_2->sizePolicy().hasHeightForWidth());
        splitter_2->setSizePolicy(sizePolicy);
        splitter_2->setMinimumSize(QSize(257, 0));
        splitter_2->setMaximumSize(QSize(16777215, 16777215));
        QFont font1;
        font1.setFamily(QString::fromUtf8("\351\232\266\344\271\246"));
        splitter_2->setFont(font1);
        splitter_2->setOrientation(Qt::Vertical);

        verticalLayout_3->addWidget(splitter_2);


        horizontalLayout_5->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        chatNameLabel = new QLabel(Widget);
        chatNameLabel->setObjectName(QStringLiteral("chatNameLabel"));
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(chatNameLabel->sizePolicy().hasHeightForWidth());
        chatNameLabel->setSizePolicy(sizePolicy2);
        chatNameLabel->setMinimumSize(QSize(0, 55));
        chatNameLabel->setMaximumSize(QSize(16777215, 49));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\344\273\277\345\256\213"));
        font2.setPointSize(36);
        chatNameLabel->setFont(font2);

        horizontalLayout_3->addWidget(chatNameLabel);


        verticalLayout_2->addLayout(horizontalLayout_3);

        textEditRead = new QTextEdit(Widget);
        textEditRead->setObjectName(QStringLiteral("textEditRead"));
        textEditRead->setMinimumSize(QSize(0, 0));
        QFont font3;
        font3.setFamily(QString::fromUtf8("\345\215\216\346\226\207\344\273\277\345\256\213"));
        font3.setPointSize(14);
        textEditRead->setFont(font3);
        textEditRead->setStyleSheet(QStringLiteral(""));
        textEditRead->setReadOnly(true);

        verticalLayout_2->addWidget(textEditRead);

        textEditWrite = new QTextEdit(Widget);
        textEditWrite->setObjectName(QStringLiteral("textEditWrite"));
        textEditWrite->setMaximumSize(QSize(16777215, 250));
        textEditWrite->setFont(font3);

        verticalLayout_2->addWidget(textEditWrite);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        sendFilePushButton = new QPushButton(Widget);
        sendFilePushButton->setObjectName(QStringLiteral("sendFilePushButton"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(sendFilePushButton->sizePolicy().hasHeightForWidth());
        sendFilePushButton->setSizePolicy(sizePolicy3);
        sendFilePushButton->setMinimumSize(QSize(0, 40));

        horizontalLayout_4->addWidget(sendFilePushButton);

        horizontalSpacer_3 = new QSpacerItem(20, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        acceptFilePushButton = new QPushButton(Widget);
        acceptFilePushButton->setObjectName(QStringLiteral("acceptFilePushButton"));
        acceptFilePushButton->setMinimumSize(QSize(0, 40));

        horizontalLayout_4->addWidget(acceptFilePushButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        pushButton_2 = new QPushButton(Widget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pushButton_2->sizePolicy().hasHeightForWidth());
        pushButton_2->setSizePolicy(sizePolicy4);
        pushButton_2->setMinimumSize(QSize(100, 40));
        pushButton_2->setMaximumSize(QSize(100, 40));

        horizontalLayout_4->addWidget(pushButton_2);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        pushButton_3 = new QPushButton(Widget);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setMinimumSize(QSize(100, 40));
        pushButton_3->setMaximumSize(QSize(100, 40));

        horizontalLayout_4->addWidget(pushButton_3);


        verticalLayout_2->addLayout(horizontalLayout_4);


        horizontalLayout_5->addLayout(verticalLayout_2);


        verticalLayout_4->addLayout(horizontalLayout_5);

        progressBar = new QProgressBar(Widget);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setValue(24);

        verticalLayout_4->addWidget(progressBar);


        retranslateUi(Widget);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Widget", Q_NULLPTR));
#ifndef QT_NO_TOOLTIP
        tabWidget->setToolTip(QApplication::translate("Widget", "<html><head/><body><p>\351\205\215\347\275\256</p></body></html>", Q_NULLPTR));
#endif // QT_NO_TOOLTIP
        nameLabel->setText(QApplication::translate("Widget", "TextLabel", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab), QApplication::translate("Widget", "\344\277\241\346\201\257", Q_NULLPTR));
        label->setText(QApplication::translate("Widget", "IP  \357\274\232", Q_NULLPTR));
        lineEdit->setText(QApplication::translate("Widget", "127.0.0.1", Q_NULLPTR));
        label_2->setText(QApplication::translate("Widget", "\347\253\257\345\217\243\357\274\232", Q_NULLPTR));
        lineEdit_2->setText(QApplication::translate("Widget", "8888", Q_NULLPTR));
        connectPushButton->setText(QApplication::translate("Widget", "\346\234\252\350\277\236\346\216\245", Q_NULLPTR));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QApplication::translate("Widget", "\351\205\215\347\275\256", Q_NULLPTR));
        chatNameLabel->setText(QApplication::translate("Widget", "\350\256\250\350\256\272\347\273\204", Q_NULLPTR));
        sendFilePushButton->setText(QApplication::translate("Widget", "\346\226\207\344\273\266\345\217\221\351\200\201", Q_NULLPTR));
        acceptFilePushButton->setText(QApplication::translate("Widget", "\346\226\207\344\273\266\346\216\245\346\224\266", Q_NULLPTR));
        pushButton_2->setText(QApplication::translate("Widget", "\345\217\221\351\200\201", Q_NULLPTR));
        pushButton_3->setText(QApplication::translate("Widget", "\345\205\263\351\227\255", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
