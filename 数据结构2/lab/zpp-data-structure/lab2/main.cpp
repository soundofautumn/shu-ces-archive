//
// Created by 邱姜铭 on 2024/4/1.
//
#include <QApplication>

#include "mainview.h"

using namespace std;


int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainView mainView;
    mainView.show();
    return QApplication::exec();
}
