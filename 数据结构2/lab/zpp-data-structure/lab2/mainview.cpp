//
// Created by 邱姜铭 on 2024/4/3.
//

// You may need to build the project (run Qt uic code generator) to get "ui_MainView.h" resolved

#include <QFileDialog>
#include <QMessageBox>
#include "mainview.h"
#include "ui_mainview.h"


MainView::MainView(QWidget *parent) :
        QWidget(parent), ui(new Ui::MainView) {
    ui->setupUi(this);
    // 绑定按钮事件
    QObject::connect(ui->read_file, &QPushButton::clicked, this, &MainView::readFromFile);
    QObject::connect(ui->min_tree, &QPushButton::clicked, this, &MainView::minTree);
    QObject::connect(ui->short_path, &QPushButton::clicked, this, &MainView::shortestPath);
    QObject::connect(ui->choose_file, &QPushButton::clicked, this, &MainView::chooseFile);
}

MainView::~MainView() {
    delete ui;
}

void MainView::chooseFile() {
    _filename = QFileDialog::getOpenFileName(this, "选择文件", "", "文本文件(*.txt)").toStdString();
    // 选择文件后，将文件名显示在按钮上 仅显示文件名
    auto pos = _filename.find_last_of('/');
    if (pos != std::string::npos) {
        ui->choose_file->setText(QString::fromStdString(_filename.substr(pos + 1)));
    } else {
        ui->choose_file->setText("选择文件");
    }
}

void MainView::readFromFile() {
    if (this->_filename.empty()) {
        QMessageBox::warning(this, "错误", "请先选择文件");
        return;
    }
    ui->graphView->readFromFile(_filename);
}

void MainView::minTree() {
    static bool flag = false;
    if (!flag) {
        ui->graphView->minimumSpanningTree();
        ui->min_tree->setText("重置");
        flag = true;
    } else {
        ui->graphView->resetMinimumSpanningTree();
        ui->min_tree->setText("最小生成树");
        flag = false;
    }
}

void MainView::shortestPath() {
    static bool flag = false;
    if (!flag) {
        ui->graphView->shortestPath();
        ui->short_path->setText("重置");
        flag = true;
    } else {
        ui->graphView->resetShortestPath();
        ui->short_path->setText("最短总路径");
        flag = false;
    }
}
