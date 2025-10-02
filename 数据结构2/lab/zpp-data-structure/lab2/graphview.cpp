//
// Created by 邱姜铭 on 2024/4/2.
//

// You may need to build the project (run Qt uic code generator) to get "ui_GraphView.h" resolved

#include <QPainter>
#include <QMouseEvent>
#include <string>
#include <fstream>
#include <algorithm>
#include "Assistant.h"
#include "graphview.h"
#include "ui_graphview.h"


GraphView::GraphView(QWidget *parent) :
        QWidget(parent), ui(new Ui::GraphView) {
    ui->setupUi(this);
}

GraphView::~GraphView() {
    delete ui;
}

void GraphView::paintEvent(QPaintEvent *event) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.setPen(QPen(Qt::black, 2));
    // 设置边框
    painter.drawRect(0, 0, width(), height());
    if (_graph == nullptr) {
        return;
    }
    // 绘制点
    auto points = _graph->getPoints();
    for (auto &point: points) {
        // 判断当前点是否选中
        const bool selected = _selected != -1 && point.name == points[_selected].name;
        // 判断当前点是否为最短路径点
        const bool shortestPath = _shortestPathPoint && point.name == _shortestPathPoint->name;
        if (shortestPath) {
            // 如果是最短路径点，设置为红色
            painter.setBrush(Qt::red);
        } else if (selected) {
            // 如果是选中点，设置为蓝色
            painter.setBrush(Qt::blue);
        } else {
            // 否则设置为灰色
            painter.setBrush(Qt::lightGray);
        }
        // 绘制点
        painter.drawEllipse(point.x - POINT_RADIUS, point.y - POINT_RADIUS, 2 * POINT_RADIUS, 2 * POINT_RADIUS);
        painter.setBrush(Qt::NoBrush);
        // 绘制点的名字
        painter.drawText(point.x + 10, point.y + 10, QString::fromStdWString(point.name));
        if (shortestPath) {
            // 如果是最短路径点，绘制最短路径的总权重
            painter.drawText(point.x + 10, point.y + 30, QString::number(_shortestPathWeight));
        }
    }
    // 绘制边
    auto edges = _graph->getEdges();
    for (auto &edge: edges) {
        // 判断当前边是否为最小生成树的边
        if (_minSpanningTree && !_minSpanningTree->hasEdge(edge.first, edge.second)) {
            // 如果不是最小生成树的边，设置为灰色
            painter.setPen(QPen(Qt::gray, 1));
        } else {
            // 否则设置为黑色
            painter.setPen(QPen(Qt::black, 2));
        }
        painter.drawLine(points[edge.first].x, points[edge.first].y, points[edge.second].x, points[edge.second].y);
        painter.drawText((points[edge.first].x + points[edge.second].x) / 2,
                         (points[edge.first].y + points[edge.second].y) / 2,
                         QString::number(_graph->getWeight(edge.first, edge.second)));
    }
}

void GraphView::mousePressEvent(QMouseEvent *event) {
    if (_graph == nullptr) {
        return;
    }
    // 获取当前鼠标位置
    const QPoint pos = event->pos();
    // 获取所有点
    auto points = _graph->getPoints();
    // 遍历所有点
    for (int i = 0; i < points.size(); i++) {
        // 判断当前点是否被选中
        if (QRect(points[i].x - POINT_RADIUS,
                  points[i].y - POINT_RADIUS,
                  2 * POINT_RADIUS,
                  2 * POINT_RADIUS).contains(pos)) {
            // 如果被选中，设置选中点的索引
            _selected = i;
            break;
        }
    }
}

void GraphView::mouseReleaseEvent(QMouseEvent *event) {
    // 重置选中点的索引
    _selected = -1;
    update();
}

void GraphView::mouseMoveEvent(QMouseEvent *event) {
    if (_selected == -1) {
        return;
    }
    // 判断鼠标是否在边界内
    if (event->pos().x() < MARGIN || event->pos().x() > width() - MARGIN ||
        event->pos().y() < MARGIN || event->pos().y() > height() - MARGIN) {
//        _selected = -1;
        return;
    }
    auto &points = _graph->getPoints();
    // 更新选中点的位置
    points[_selected].x = event->pos().x();
    points[_selected].y = event->pos().y();
    update();
}

#ifdef _WIN32
#include <locale>
std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> utf8_to_utf16_converter;
#endif

void GraphView::readFromFile(const std::string &filename) {
    using namespace std;
    wfstream file;
    // 设置文件编码
    file.imbue(utf8_locale);
#ifdef WIN32
    // windows下要把filename转成utf16的wstring
    file.open(utf8_to_utf16_converter.from_bytes(filename).c_str(), ios::in);
#else
    file.open(filename, ios::in);
#endif
    wstring line;
    vector<wstring> country_names;

    // 读取国家名
    while (file >> line) {
        if (line == DELIMITER) {
            break;
        }
        country_names.push_back(line);
    }

    auto graph = new Graph<int, wstring>(country_names);

    // 读取边
    wstring u, v;
    int w;

    while (file >> u >> v >> w) {
        const auto &_begin = country_names.begin();
        const auto &_end = country_names.end();
        graph->addEdge(distance(_begin, std::find(_begin, _end, u)),
                       distance(_begin, std::find(_begin, _end, v)),
                       w);
    }
    // 设置点的位置
    // 以圆心为中心，均匀分布
    const double delta = 2 * M_PI / graph->V();
    QPoint center(width() / 2, height() / 2);
    for (int i = 0; i < graph->V(); i++) {
        graph->getPoints()[i].x = center.x() + cos(i * delta) * (center.x() - MARGIN);
        graph->getPoints()[i].y = center.y() + sin(i * delta) * (center.y() - MARGIN);
    }
    _graph = graph;
    update();
}

void GraphView::minimumSpanningTree() {
    if (_graph == nullptr) {
        return;
    }
    // 计算最小生成树
    _minSpanningTree = _graph->kruskal();
    update();
}

void GraphView::shortestPath() {
    if (_graph == nullptr) {
        return;
    }
    // 计算所有点的最短路径
    const auto &dist = _graph->floyd();
    // 找到最短路径的起点
    // 计算最短路径的总权重
    const int n = _graph->V();
    int min = std::numeric_limits<int>::max();
    int index = 0;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = 0; j < n; j++) {
            sum += dist[i][j];
        }
        if (sum < min) {
            min = sum;
            index = i;
        }
    }
    // 设置最短路径的起点和总权重
    _shortestPathWeight = min;
    _shortestPathPoint = &_graph->getPoints()[index];
    update();
}

void GraphView::resetMinimumSpanningTree() {
    // 重置最小生成树
    _minSpanningTree = nullptr;
    update();
}

void GraphView::resetShortestPath() {
    // 重置最短路径
    _shortestPathPoint = nullptr;
    _shortestPathWeight = 0;
    update();
}
