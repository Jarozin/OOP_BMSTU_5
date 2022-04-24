//
// Created by jarozin on 25.04.22.
//
/********************************************************************************
** Form generated from reading UI file 'window.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#include "main_window.h"
QT_BEGIN_NAMESPACE
void Ui_MainWindow::setupUi(QMainWindow *MainWindow)
{
    if (MainWindow->objectName().isEmpty())
        MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
    MainWindow->resize(929, 690);
    centralwidget = new QWidget(MainWindow);
    centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    canvas = new Canvas(centralwidget);
    canvas->setObjectName(QString::fromUtf8("canvas"));
    canvas->setGeometry(QRect(0, 0, 631, 651));

    QPalette pal = canvas->palette();
    pal.setColor(canvas->backgroundRole(), Qt::white);
    canvas->setPalette(pal);
    canvas->setAutoFillBackground(true);

    groupBox = new QGroupBox(centralwidget);
    groupBox->setObjectName(QString::fromUtf8("groupBox"));
    groupBox->setGeometry(QRect(630, 0, 291, 101));
    label = new QLabel(groupBox);
    label->setObjectName(QString::fromUtf8("label"));
    label->setGeometry(QRect(0, 40, 31, 17));
    label_2 = new QLabel(groupBox);
    label_2->setObjectName(QString::fromUtf8("label_2"));
    label_2->setGeometry(QRect(100, 40, 21, 17));
    dz = new QLineEdit(groupBox);
    dz->setObjectName(QString::fromUtf8("dz"));
    dz->setGeometry(QRect(210, 40, 61, 25));
    label_3 = new QLabel(groupBox);
    label_3->setObjectName(QString::fromUtf8("label_3"));
    label_3->setGeometry(QRect(190, 40, 21, 17));
    dy = new QLineEdit(groupBox);
    dy->setObjectName(QString::fromUtf8("dy"));
    dy->setGeometry(QRect(120, 40, 61, 25));
    dx = new QLineEdit(groupBox);
    dx->setObjectName(QString::fromUtf8("dx"));
    dx->setGeometry(QRect(20, 40, 61, 25));
    pushButton = new QPushButton(groupBox);
    pushButton->setObjectName(QString::fromUtf8("pushButton"));
    pushButton->setGeometry(QRect(190, 70, 89, 25));
    groupBox_2 = new QGroupBox(centralwidget);
    groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
    groupBox_2->setGeometry(QRect(630, 100, 291, 81));
    label_4 = new QLabel(groupBox_2);
    label_4->setObjectName(QString::fromUtf8("label_4"));
    label_4->setGeometry(QRect(0, 40, 31, 17));
    label_5 = new QLabel(groupBox_2);
    label_5->setObjectName(QString::fromUtf8("label_5"));
    label_5->setGeometry(QRect(100, 40, 21, 17));
    cz = new QLineEdit(groupBox_2);
    cz->setObjectName(QString::fromUtf8("cz"));
    cz->setGeometry(QRect(210, 40, 61, 25));
    label_6 = new QLabel(groupBox_2);
    label_6->setObjectName(QString::fromUtf8("label_6"));
    label_6->setGeometry(QRect(190, 40, 21, 17));
    cy = new QLineEdit(groupBox_2);
    cy->setObjectName(QString::fromUtf8("cy"));
    cy->setGeometry(QRect(120, 40, 61, 25));
    cx = new QLineEdit(groupBox_2);
    cx->setObjectName(QString::fromUtf8("cx"));
    cx->setGeometry(QRect(20, 40, 61, 25));
    groupBox_3 = new QGroupBox(centralwidget);
    groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
    groupBox_3->setGeometry(QRect(630, 180, 291, 101));
    label_7 = new QLabel(groupBox_3);
    label_7->setObjectName(QString::fromUtf8("label_7"));
    label_7->setGeometry(QRect(0, 40, 31, 17));
    label_8 = new QLabel(groupBox_3);
    label_8->setObjectName(QString::fromUtf8("label_8"));
    label_8->setGeometry(QRect(100, 40, 21, 17));
    kz = new QLineEdit(groupBox_3);
    kz->setObjectName(QString::fromUtf8("kz"));
    kz->setGeometry(QRect(210, 40, 61, 25));
    label_9 = new QLabel(groupBox_3);
    label_9->setObjectName(QString::fromUtf8("label_9"));
    label_9->setGeometry(QRect(190, 40, 21, 17));
    ky = new QLineEdit(groupBox_3);
    ky->setObjectName(QString::fromUtf8("ky"));
    ky->setGeometry(QRect(120, 40, 61, 25));
    kx = new QLineEdit(groupBox_3);
    kx->setObjectName(QString::fromUtf8("kx"));
    kx->setGeometry(QRect(20, 40, 61, 25));
    pushButton_2 = new QPushButton(groupBox_3);
    pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
    pushButton_2->setGeometry(QRect(190, 70, 91, 25));
    groupBox_4 = new QGroupBox(centralwidget);
    groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
    groupBox_4->setGeometry(QRect(630, 280, 291, 101));
    label_10 = new QLabel(groupBox_4);
    label_10->setObjectName(QString::fromUtf8("label_10"));
    label_10->setGeometry(QRect(0, 40, 31, 17));
    label_11 = new QLabel(groupBox_4);
    label_11->setObjectName(QString::fromUtf8("label_11"));
    label_11->setGeometry(QRect(100, 40, 21, 17));
    az = new QLineEdit(groupBox_4);
    az->setObjectName(QString::fromUtf8("az"));
    az->setGeometry(QRect(210, 40, 61, 25));
    label_12 = new QLabel(groupBox_4);
    label_12->setObjectName(QString::fromUtf8("label_12"));
    label_12->setGeometry(QRect(190, 40, 21, 17));
    ay = new QLineEdit(groupBox_4);
    ay->setObjectName(QString::fromUtf8("ay"));
    ay->setGeometry(QRect(120, 40, 61, 25));
    ax = new QLineEdit(groupBox_4);
    ax->setObjectName(QString::fromUtf8("ax"));
    ax->setGeometry(QRect(20, 40, 61, 25));
    pushButton_3 = new QPushButton(groupBox_4);
    pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
    pushButton_3->setGeometry(QRect(190, 70, 91, 25));
    MainWindow->setCentralWidget(centralwidget);
    statusbar = new QStatusBar(MainWindow);
    statusbar->setObjectName(QString::fromUtf8("statusbar"));
    MainWindow->setStatusBar(statusbar);

    retranslateUi(MainWindow);
    QObject::connect(pushButton, &QPushButton::clicked, (const Canvas*)canvas, &Canvas::move);
    QObject::connect(pushButton_2, &QPushButton::clicked, (const Canvas*)canvas, &Canvas::scale);
    QObject::connect(pushButton_3, &QPushButton::clicked, (const Canvas*)canvas, &Canvas::rotate);

    QMetaObject::connectSlotsByName(MainWindow);
} // setupUi

void Ui_MainWindow::retranslateUi(QMainWindow *MainWindow)
{
    MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
    groupBox->setTitle(QString());
    label->setText(QApplication::translate("MainWindow", "dx", nullptr));
    label_2->setText(QApplication::translate("MainWindow", "dy", nullptr));
    dz->setText(QString());
    label_3->setText(QApplication::translate("MainWindow", "dz", nullptr));
    pushButton->setText(QApplication::translate("MainWindow", "Move", nullptr));
    groupBox_2->setTitle(QString());
    label_4->setText(QApplication::translate("MainWindow", "cx", nullptr));
    label_5->setText(QApplication::translate("MainWindow", "cy", nullptr));
    label_6->setText(QApplication::translate("MainWindow", "cz", nullptr));
    groupBox_3->setTitle(QString());
    label_7->setText(QApplication::translate("MainWindow", "kx", nullptr));
    label_8->setText(QApplication::translate("MainWindow", "ky", nullptr));
    label_9->setText(QApplication::translate("MainWindow", "kz", nullptr));
    pushButton_2->setText(QApplication::translate("MainWindow", "Scale", nullptr));
    groupBox_4->setTitle(QString());
    label_10->setText(QApplication::translate("MainWindow", "ax", nullptr));
    label_11->setText(QApplication::translate("MainWindow", "ay", nullptr));
    az->setText(QApplication::translate("MainWindow", "30", nullptr));
    label_12->setText(QApplication::translate("MainWindow", "az", nullptr));
    ay->setText(QApplication::translate("MainWindow", "30", nullptr));
    ax->setText(QApplication::translate("MainWindow", "30", nullptr));
    pushButton_3->setText(QApplication::translate("MainWindow", "Rotate", nullptr));
} // retranslateUi



QT_END_NAMESPACE
