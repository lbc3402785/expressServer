/********************************************************************************
** Form generated from reading UI file 'dialog.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_H
#define UI_DIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QTabWidget *tabWidget;
    QWidget *General;
    QGroupBox *groupBox_2;
    QLabel *intervalInfo;
    QLabel *portInfo;
    QLabel *intervalInfo_2;
    QLineEdit *BFMModel;
    QLineEdit *BFMKeyIndexes;
    QLabel *intervalInfo_3;
    QLineEdit *G8M2BFM;
    QLineEdit *BFM2G8M;
    QLabel *intervalInfo_4;
    QLabel *intervalInfo_5;
    QLineEdit *DlibModel;
    QLabel *intervalInfo_6;
    QLineEdit *port;
    QLineEdit *interval;
    QGroupBox *groupBox;
    QLabel *portInfo_3;
    QLabel *portInfo_4;
    QLineEdit *width;
    QLineEdit *height;
    QWidget *tab_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *reset;
    QSpacerItem *horizontalSpacer;
    QPushButton *cancel;
    QPushButton *save;
    QWidget *layoutWidget1;
    QGridLayout *gridLayout;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(434, 502);
        tabWidget = new QTabWidget(Dialog);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 10, 411, 411));
        General = new QWidget();
        General->setObjectName(QString::fromUtf8("General"));
        groupBox_2 = new QGroupBox(General);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 20, 381, 241));
        intervalInfo = new QLabel(groupBox_2);
        intervalInfo->setObjectName(QString::fromUtf8("intervalInfo"));
        intervalInfo->setGeometry(QRect(33, 68, 108, 16));
        portInfo = new QLabel(groupBox_2);
        portInfo->setObjectName(QString::fromUtf8("portInfo"));
        portInfo->setGeometry(QRect(33, 42, 60, 16));
        intervalInfo_2 = new QLabel(groupBox_2);
        intervalInfo_2->setObjectName(QString::fromUtf8("intervalInfo_2"));
        intervalInfo_2->setGeometry(QRect(33, 94, 60, 16));
        BFMModel = new QLineEdit(groupBox_2);
        BFMModel->setObjectName(QString::fromUtf8("BFMModel"));
        BFMModel->setGeometry(QRect(147, 94, 133, 20));
        BFMKeyIndexes = new QLineEdit(groupBox_2);
        BFMKeyIndexes->setObjectName(QString::fromUtf8("BFMKeyIndexes"));
        BFMKeyIndexes->setGeometry(QRect(147, 120, 133, 20));
        intervalInfo_3 = new QLabel(groupBox_2);
        intervalInfo_3->setObjectName(QString::fromUtf8("intervalInfo_3"));
        intervalInfo_3->setGeometry(QRect(33, 120, 96, 16));
        G8M2BFM = new QLineEdit(groupBox_2);
        G8M2BFM->setObjectName(QString::fromUtf8("G8M2BFM"));
        G8M2BFM->setGeometry(QRect(147, 172, 133, 20));
        BFM2G8M = new QLineEdit(groupBox_2);
        BFM2G8M->setObjectName(QString::fromUtf8("BFM2G8M"));
        BFM2G8M->setGeometry(QRect(147, 146, 133, 20));
        intervalInfo_4 = new QLabel(groupBox_2);
        intervalInfo_4->setObjectName(QString::fromUtf8("intervalInfo_4"));
        intervalInfo_4->setGeometry(QRect(33, 146, 54, 16));
        intervalInfo_5 = new QLabel(groupBox_2);
        intervalInfo_5->setObjectName(QString::fromUtf8("intervalInfo_5"));
        intervalInfo_5->setGeometry(QRect(33, 172, 54, 16));
        DlibModel = new QLineEdit(groupBox_2);
        DlibModel->setObjectName(QString::fromUtf8("DlibModel"));
        DlibModel->setGeometry(QRect(147, 198, 133, 20));
        intervalInfo_6 = new QLabel(groupBox_2);
        intervalInfo_6->setObjectName(QString::fromUtf8("intervalInfo_6"));
        intervalInfo_6->setGeometry(QRect(33, 198, 66, 16));
        port = new QLineEdit(groupBox_2);
        port->setObjectName(QString::fromUtf8("port"));
        port->setGeometry(QRect(147, 42, 133, 20));
        interval = new QLineEdit(groupBox_2);
        interval->setObjectName(QString::fromUtf8("interval"));
        interval->setGeometry(QRect(147, 68, 133, 20));
        groupBox = new QGroupBox(General);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 270, 381, 111));
        portInfo_3 = new QLabel(groupBox);
        portInfo_3->setObjectName(QString::fromUtf8("portInfo_3"));
        portInfo_3->setGeometry(QRect(34, 31, 84, 16));
        portInfo_4 = new QLabel(groupBox);
        portInfo_4->setObjectName(QString::fromUtf8("portInfo_4"));
        portInfo_4->setGeometry(QRect(34, 57, 84, 16));
        width = new QLineEdit(groupBox);
        width->setObjectName(QString::fromUtf8("width"));
        width->setGeometry(QRect(124, 31, 133, 20));
        height = new QLineEdit(groupBox);
        height->setObjectName(QString::fromUtf8("height"));
        height->setGeometry(QRect(124, 57, 133, 20));
        tabWidget->addTab(General, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QString::fromUtf8("layoutWidget"));
        layoutWidget->setGeometry(QRect(10, 460, 381, 25));
        horizontalLayout_2 = new QHBoxLayout(layoutWidget);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(0, 0, 0, 0);
        reset = new QPushButton(layoutWidget);
        reset->setObjectName(QString::fromUtf8("reset"));

        horizontalLayout_2->addWidget(reset);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        cancel = new QPushButton(layoutWidget);
        cancel->setObjectName(QString::fromUtf8("cancel"));

        horizontalLayout_2->addWidget(cancel);

        save = new QPushButton(layoutWidget);
        save->setObjectName(QString::fromUtf8("save"));

        horizontalLayout_2->addWidget(save);

        layoutWidget1 = new QWidget(Dialog);
        layoutWidget1->setObjectName(QString::fromUtf8("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(0, 0, 2, 2));
        gridLayout = new QGridLayout(layoutWidget1);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        layoutWidget2 = new QWidget(Dialog);
        layoutWidget2->setObjectName(QString::fromUtf8("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(0, 0, 2, 2));
        verticalLayout = new QVBoxLayout(layoutWidget2);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);

        retranslateUi(Dialog);

        tabWidget->setCurrentIndex(0);
        save->setDefault(true);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Dialog", "server", nullptr));
        intervalInfo->setText(QCoreApplication::translate("Dialog", "\351\207\207\346\240\267\351\227\264\351\232\224\357\274\210\346\257\253\347\247\222\357\274\211\357\274\232", nullptr));
        portInfo->setText(QCoreApplication::translate("Dialog", "\347\233\221\345\220\254\347\253\257\345\217\243\357\274\232", nullptr));
        intervalInfo_2->setText(QCoreApplication::translate("Dialog", "BFM Model:", nullptr));
        BFMKeyIndexes->setText(QString());
        intervalInfo_3->setText(QCoreApplication::translate("Dialog", "BFM Key Indexes:", nullptr));
        G8M2BFM->setText(QString());
        intervalInfo_4->setText(QCoreApplication::translate("Dialog", "BFM->G8M:", nullptr));
        intervalInfo_5->setText(QCoreApplication::translate("Dialog", "G8M->BFM:", nullptr));
        DlibModel->setText(QString());
        intervalInfo_6->setText(QCoreApplication::translate("Dialog", "Dlib Model:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Dialog", "camera", nullptr));
        portInfo_3->setText(QCoreApplication::translate("Dialog", "\345\210\206\350\276\250\347\216\207\357\274\210\345\256\275\357\274\211\357\274\232", nullptr));
        portInfo_4->setText(QCoreApplication::translate("Dialog", "\345\210\206\350\276\250\347\216\207\357\274\210\351\253\230\357\274\211\357\274\232", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(General), QCoreApplication::translate("Dialog", "Tab 1", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("Dialog", "Tab 2", nullptr));
        reset->setText(QCoreApplication::translate("Dialog", "Reset", nullptr));
        cancel->setText(QCoreApplication::translate("Dialog", "Cancel", nullptr));
        save->setText(QCoreApplication::translate("Dialog", "Save", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_H
