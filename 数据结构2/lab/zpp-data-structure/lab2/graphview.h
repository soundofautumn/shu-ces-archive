//
// Created by 邱姜铭 on 2024/4/2.
//

#ifndef ZPP_DATA_STRUCTURE_GRAPHVIEW_H
#define ZPP_DATA_STRUCTURE_GRAPHVIEW_H

#include <QWidget>
#include <set>
#include "Graph.h"


QT_BEGIN_NAMESPACE
namespace Ui { class GraphView; }
QT_END_NAMESPACE

class GraphView : public QWidget {
Q_OBJECT

private:
    typedef Graph<int, std::wstring> graph_type;

public:
    explicit GraphView(QWidget *parent = nullptr);

    ~GraphView() override;

    // 从文件读取
    void readFromFile(const std::string &filename);

    // 最小生成树
    void minimumSpanningTree();

    // 最短路径
    void shortestPath();

    // 重置最小生成树
    void resetMinimumSpanningTree();

    // 重置最短路径
    void resetShortestPath();

protected:
    void paintEvent(QPaintEvent *event) override;

    void mousePressEvent(QMouseEvent *event) override;

    void mouseReleaseEvent(QMouseEvent *event) override;

    void mouseMoveEvent(QMouseEvent *event) override;

private:

    // 点的半径
    const int POINT_RADIUS = 10;

    // 距离边缘的距离
    const int MARGIN = 40;

    // 选中的点
    int _selected = -1;

    Ui::GraphView *ui;

    // 图
    graph_type *_graph = nullptr;

    // 最小生成树
    graph_type *_minSpanningTree = nullptr;

    // 最短总路径的点
    graph_type::point_type *_shortestPathPoint = nullptr;

    // 最短总路径的总权重
    int _shortestPathWeight = 0;

};


#endif //ZPP_DATA_STRUCTURE_GRAPHVIEW_H
