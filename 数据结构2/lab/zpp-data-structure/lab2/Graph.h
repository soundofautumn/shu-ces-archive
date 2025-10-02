//
// Created by 邱姜铭 on 2024/4/1.
//

#ifndef ZPP_DATA_STRUCTURE_GRAPH_H
#define ZPP_DATA_STRUCTURE_GRAPH_H


#include <string>
#include <vector>
#include <utility>
#include <algorithm>
#include <limits>
#include "Assistant.h"
#include "UnionFind.h"

using std::pair;
using std::vector;

// 无向图
template<class W, class T>
class Graph {
public:
    // 权重类型
    typedef W weight_type;
    // 数据类型
    typedef T data_type;
    // 顶点类型
    typedef struct Point {
        data_type name;
        int x;
        int y;
    } point_type;
    // 边类型
    typedef pair<weight_type, int> edge_type;
private:
    // 顶点数
    int n;
    // 边数
    int m;
    // 邻接表 adj[u] = {v1, v2, ...}
    vector<vector<edge_type>> adj;
    // 顶点名
    vector<point_type> points;
public:
    Graph() : n(0), m(0) {}

    explicit Graph(vector<data_type> data) : n(data.size()), m(0), adj(n), points(n) {
        for (int i = 0; i < n; i++) {
            points[i].name = data[i];
        }
    }

    explicit Graph(vector<point_type> points) : n(points.size()), m(0), adj(n), points(points) {}

    ~Graph() = default;

    void addEdge(int u, int v, weight_type w) {
        adj[u].emplace_back(w, v);
        adj[v].emplace_back(w, u);
        m++;
    }

    vector<point_type> &getPoints() {
        return points;
    }

    vector<pair<int, int>> getEdges() {
        vector<pair<int, int>> edges;
        for (int u = 0; u < n; u++) {
            for (auto &edge: adj[u]) {
                int v = edge.second;
                if (u < v) {
                    edges.emplace_back(u, v);
                }
            }
        }
        return edges;
    }

    bool hasEdge(int u, int v) {
        for (auto &edge: adj[u]) {
            if (edge.second == v) {
                return true;
            }
        }
        return false;
    }

    weight_type getWeight(int u, int v) {
        for (auto &edge: adj[u]) {
            if (edge.second == v) {
                return edge.first;
            }
        }
        return 0;
    }

    // 返回顶点数
    [[nodiscard]] int V() const {
        return n;
    }

    // 返回边数
    [[nodiscard]] int E() const {
        return m;
    }

    //克鲁斯克尔算法
    Graph<W, T> *kruskal() {
        // 生成最小生成树
        auto tree = new Graph<W, T>(points);
        // 边集
        vector<pair<W, pair<int, int>>> edges;
        for (int u = 0; u < n; u++) {
            for (auto &edge: adj[u]) {
                int v = edge.second;
                if (u < v) {
                    edges.emplace_back(edge.first, std::make_pair(u, v));
                }
            }
        }
        // 按权重排序
        std::sort(edges.begin(), edges.end());
        // 并查集
        UnionFind uf(n);
        // 遍历边集
        for (auto &edge: edges) {
            int u = edge.second.first;
            int v = edge.second.second;
            // 如果 u 和 v 不连通
            if (!uf.connected(u, v)) {
                // 添加边
                tree->addEdge(u, v, edge.first);
                // 合并 u 和 v
                uf.merge(u, v);
            }
        }
        return tree;
    }

    // 弗洛伊德算法
    vector<vector<weight_type>> floyd() {
        // 无穷大
        const auto weight_inf = std::numeric_limits<weight_type>::max();
        // 距离矩阵
        vector<vector<weight_type>> dist(n, vector<weight_type>(n, weight_inf));
        // 初始化
        for (int i = 0; i < n; i++) {
            dist[i][i] = 0;
        }
        for (int u = 0; u < n; u++) {
            for (auto &edge: adj[u]) {
                int v = edge.second;
                dist[u][v] = edge.first;
            }
        }
        // 弗洛伊德算法
        for (int k = 0; k < n; k++) {
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < n; j++) {
                    if (dist[i][k] != weight_inf &&
                        dist[k][j] != weight_inf) {
                        dist[i][j] = std::min(dist[i][j], dist[i][k] + dist[k][j]);
                    }
                }
            }
        }
        return dist;
    }
};


#endif //ZPP_DATA_STRUCTURE_GRAPH_H
