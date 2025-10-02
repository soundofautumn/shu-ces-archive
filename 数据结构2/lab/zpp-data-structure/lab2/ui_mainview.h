/********************************************************************************
** Form generated from reading UI file 'mainview.ui'
**
** Created by: Qt User Interface Compiler version 6.6.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINVIEW_H
#define UI_MAINVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>
#include "graphview.h"

QT_BEGIN_NAMESPACE

class Ui_MainView
{
public:
    QHBoxLayout *horizontalLayout;
    GraphView *graphView;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QPushButton *min_tree;
    QPushButton *short_path;
    QPushButton *choose_file;
    QPushButton *read_file;

    void setupUi(QWidget *MainView)
    {
        if (MainView->objectName().isEmpty())
            MainView->setObjectName("MainView");
        MainView->resize(784, 624);
        MainView->setStyleSheet(QString::fromUtf8("background-color: white;"));
        horizontalLayout = new QHBoxLayout(MainView);
        horizontalLayout->setObjectName("horizontalLayout");
        graphView = new GraphView(MainView);
        graphView->setObjectName("graphView");
        graphView->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(graphView->sizePolicy().hasHeightForWidth());
        graphView->setSizePolicy(sizePolicy);
        graphView->setMinimumSize(QSize(600, 600));

        horizontalLayout->addWidget(graphView);

        groupBox = new QGroupBox(MainView);
        groupBox->setObjectName("groupBox");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox->sizePolicy().hasHeightForWidth());
        groupBox->setSizePolicy(sizePolicy1);
        groupBox->setMinimumSize(QSize(150, 0));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setObjectName("gridLayout");
        min_tree = new QPushButton(groupBox);
        min_tree->setObjectName("min_tree");
        QSizePolicy sizePolicy2(QSizePolicy::Policy::Maximum, QSizePolicy::Policy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(min_tree->sizePolicy().hasHeightForWidth());
        min_tree->setSizePolicy(sizePolicy2);
        min_tree->setMinimumSize(QSize(130, 40));
        min_tree->setLayoutDirection(Qt::LeftToRight);
        min_tree->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"color: black;"));

        gridLayout->addWidget(min_tree, 3, 5, 1, 1);

        short_path = new QPushButton(groupBox);
        short_path->setObjectName("short_path");
        sizePolicy2.setHeightForWidth(short_path->sizePolicy().hasHeightForWidth());
        short_path->setSizePolicy(sizePolicy2);
        short_path->setMinimumSize(QSize(130, 40));
        short_path->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"color: black;"));

        gridLayout->addWidget(short_path, 4, 5, 1, 1);

        choose_file = new QPushButton(groupBox);
        choose_file->setObjectName("choose_file");
        choose_file->setMinimumSize(QSize(130, 40));
        choose_file->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"color: black;"));

        gridLayout->addWidget(choose_file, 1, 5, 1, 1);

        read_file = new QPushButton(groupBox);
        read_file->setObjectName("read_file");
        read_file->setMinimumSize(QSize(130, 40));
        read_file->setStyleSheet(QString::fromUtf8("background-color: white;\n"
"color: black;"));

        gridLayout->addWidget(read_file, 2, 5, 1, 1);


        horizontalLayout->addWidget(groupBox);


        retranslateUi(MainView);

        QMetaObject::connectSlotsByName(MainView);
    } // setupUi

    void retranslateUi(QWidget *MainView)
    {
        MainView->setWindowTitle(QCoreApplication::translate("MainView", "\344\271\241\346\235\221\345\205\254\350\267\257\345\273\272\350\256\276\345\222\214\344\271\241\346\235\221\345\214\273\351\231\242\350\247\204\345\210\222", nullptr));
        groupBox->setTitle(QString());
        min_tree->setText(QCoreApplication::translate("MainView", "\346\234\200\345\260\217\347\224\237\346\210\220\346\240\221", nullptr));
        short_path->setText(QCoreApplication::translate("MainView", "\346\234\200\347\237\255\346\200\273\350\267\257\345\276\204", nullptr));
        choose_file->setText(QCoreApplication::translate("MainView", "\351\200\211\346\213\251\346\226\207\344\273\266", nullptr));
        read_file->setText(QCoreApplication::translate("MainView", "\350\257\273\345\217\226\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainView: public Ui_MainView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINVIEW_H
