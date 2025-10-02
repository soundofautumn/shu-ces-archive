//
// Created by 邱姜铭 on 2024/4/3.
//

#ifndef ZPP_DATA_STRUCTURE_MAINVIEW_H
#define ZPP_DATA_STRUCTURE_MAINVIEW_H

#include <QWidget>
#include "Graph.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainView; }
QT_END_NAMESPACE

class MainView : public QWidget {
Q_OBJECT

public:
    explicit MainView(QWidget *parent = nullptr);

    ~MainView() override;

private slots:

    void chooseFile();

    void minTree();

    void shortestPath();

    void readFromFile();

private:
    std::string _filename;

    Ui::MainView *ui;
};


#endif //ZPP_DATA_STRUCTURE_MAINVIEW_H
