/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.13.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *settings;
    QWidget *centralWidget;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout;
    QGraphicsView *imageView;
    QLabel *label;
    QPushButton *start;
    QComboBox *id;
    QPushButton *stop;
    QPushButton *open;
    QPushButton *pause;
    QTextBrowser *textBrowser;
    QMenuBar *menuBar;
    QMenu *file;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1070, 706);
        settings = new QAction(MainWindow);
        settings->setObjectName(QString::fromUtf8("settings"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/iconImage/img/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
        settings->setIcon(icon);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_4 = new QGridLayout(centralWidget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        imageView = new QGraphicsView(centralWidget);
        imageView->setObjectName(QString::fromUtf8("imageView"));

        gridLayout->addWidget(imageView, 1, 0, 1, 3);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label, 0, 0, 1, 1);

        start = new QPushButton(centralWidget);
        start->setObjectName(QString::fromUtf8("start"));

        gridLayout->addWidget(start, 2, 0, 1, 1);

        id = new QComboBox(centralWidget);
        id->setObjectName(QString::fromUtf8("id"));

        gridLayout->addWidget(id, 0, 1, 1, 1);

        stop = new QPushButton(centralWidget);
        stop->setObjectName(QString::fromUtf8("stop"));

        gridLayout->addWidget(stop, 2, 2, 1, 1);

        open = new QPushButton(centralWidget);
        open->setObjectName(QString::fromUtf8("open"));

        gridLayout->addWidget(open, 0, 2, 1, 1);

        pause = new QPushButton(centralWidget);
        pause->setObjectName(QString::fromUtf8("pause"));

        gridLayout->addWidget(pause, 2, 1, 1, 1);

        textBrowser = new QTextBrowser(centralWidget);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        gridLayout->addWidget(textBrowser, 3, 0, 1, 3);

        gridLayout->setRowStretch(0, 1);
        gridLayout->setRowStretch(1, 6);
        gridLayout->setRowStretch(2, 2);
        gridLayout->setRowStretch(3, 1);

        gridLayout_4->addLayout(gridLayout, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1070, 23));
        file = new QMenu(menuBar);
        file->setObjectName(QString::fromUtf8("file"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(file->menuAction());
        file->addAction(settings);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        settings->setText(QCoreApplication::translate("MainWindow", "\350\256\276\347\275\256", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "camera id:", nullptr));
        start->setText(QCoreApplication::translate("MainWindow", "start", nullptr));
        stop->setText(QCoreApplication::translate("MainWindow", "stop", nullptr));
        open->setText(QCoreApplication::translate("MainWindow", "open", nullptr));
        pause->setText(QCoreApplication::translate("MainWindow", "pause", nullptr));
        file->setTitle(QCoreApplication::translate("MainWindow", "\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
