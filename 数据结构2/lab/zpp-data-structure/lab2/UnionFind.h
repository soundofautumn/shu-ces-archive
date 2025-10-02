//
// Created by 邱姜铭 on 2024/4/2.
//

#ifndef ZPP_DATA_STRUCTURE_UNIONFIND_H
#define ZPP_DATA_STRUCTURE_UNIONFIND_H


class UnionFind {
private:
    int *parent;
    int *rank;
public:
    explicit UnionFind(int n) {
        parent = new int[n];
        rank = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            rank[i] = 0;
        }
    }

    ~UnionFind() {
        delete[] parent;
        delete[] rank;
    }

    int find(int x) {
        if (x != parent[x]) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    void merge(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX == rootY) {
            return;
        }
        if (rank[rootX] < rank[rootY]) {
            parent[rootX] = rootY;
        } else if (rank[rootX] > rank[rootY]) {
            parent[rootY] = rootX;
        } else {
            parent[rootX] = rootY;
            rank[rootY]++;
        }
    }

    bool connected(int x, int y) {
        return find(x) == find(y);
    }
};

#endif //ZPP_DATA_STRUCTURE_UNIONFIND_H
