//
// Created by 邱姜铭 on 2024/3/18.
//

#include <fstream>
#include <sstream>
#include <iostream>
#include <queue>
#include <cassert>
#include <algorithm>

#include "Tree.h"
#include "Assistant.cpp"

Tree::Tree(std::string name) : _name(std::move(name)), _firstChild(nullptr), _nextSibling(nullptr) {}

void Tree::addChild(Tree *child) {
    if (this->_firstChild == nullptr) {
        this->_firstChild = child;
    } else {
        Tree *node = this->_firstChild;
        while (node->_nextSibling != nullptr) {
            node = node->_nextSibling;
        }
        node->_nextSibling = child;
    }
}

bool Tree::deleteChild(Tree *child) {
    std::function<bool(Tree *)> deleteChild = [&](Tree *node) {
        if (node == nullptr) return false;
        if (node->_firstChild == child) {
            node->_firstChild = child->_nextSibling;
            return true;
        }
        if (node->_nextSibling == child) {
            node->_nextSibling = child->_nextSibling;
            return true;
        }
        return deleteChild(node->_firstChild) || deleteChild(node->_nextSibling);
    };
    return deleteChild(this);
}

std::string Tree::getName() const {
    return _name;
}

void Tree::setName(const std::string &name) {
    _name = name;
}

void Tree::preOrder(const Visit &visit) const {
    visit(const_cast<Tree *>(this));
    Tree *node = _firstChild;
    while (node != nullptr) {
        node->preOrder(visit);
        node = node->_nextSibling;
    }
}

void Tree::postOrder(const Visit &visit) const {
    Tree *node = _firstChild;
    while (node != nullptr) {
        node->postOrder(visit);
        node = node->_nextSibling;
    }
    visit(const_cast<Tree *>(this));
}

void Tree::levelOrder(const Visit &visit) const {
    std::vector<Tree *> nodes;
    nodes.push_back(const_cast<Tree *>(this));
    for (int i = 0; i < nodes.size(); i++) {
        visit(nodes[i]);
        Tree *node = nodes[i]->_firstChild;
        while (node != nullptr) {
            nodes.push_back(node);
            node = node->_nextSibling;
        }
    }
}

void Tree::levelOrderWithHeight(const Tree::VisitWithHeight &visitWithHeight) const {
    std::queue<const Tree *> nodes;
    nodes.emplace(this);
    // h是当前节点的高度
    int h = 0;
    while (!nodes.empty()) {
        int len = nodes.size();
        for (int i = 0; i < len; ++i) {
            const Tree *node = nodes.front();
            nodes.pop();
            visitWithHeight(node, h);
            Tree *child = node->_firstChild;
            while (child != nullptr) {
                nodes.emplace(child);
                child = child->_nextSibling;
            }
        }
        ++h;
    }
}

Tree *Tree::find(const std::string &name) const {
    Tree *result = nullptr;
    preOrder([&](Tree *node) {
        if (node->getName() == name)
            result = node;
    });
    return result;
}

int Tree::height() const {
    int h = 0;
    std::function<void(Tree *, int)> get_height = [&](Tree *node, int height) {
        if (height > h) {
            h = height;
        }
        Tree *child = node->_firstChild;
        while (child != nullptr) {
            get_height(child, height + 1);
            child = child->_nextSibling;
        }
    };
    get_height(const_cast<Tree *>(this), 1);
    return h;
}

int Tree::size() const {
    int size_ = 0;
    preOrder([&](Tree *node) { size_++; });
    return size_;
}

void Tree::calculate_graph() const {
    const int graph_height = this->height() * 4 - 3;
    name_to_index.clear();
    /**
     * dfs计算每个节点的位置
     *
     * @param node 当前节点
     * @param index 当前节点的位置
     * @return 这颗树的宽度
     */
    std::function<int(const Tree *, int)> calculate_index = [&](const Tree *node, int index) {
        if (node == nullptr) return 0;
        name_to_index.insert({node->getName(), index});
        int length = 0;
        Tree *sibling = node->_firstChild;
        while (sibling != nullptr) {
            length += std::max(calculate_index(sibling, index + length),
                    // 2是为了保证节点之间至少有一个空格
                               static_cast<int>(sibling->getName().length() + 2));
            sibling = sibling->_nextSibling;
        }
        return length;
    };
    graph.clear();
    graph.resize(graph_height, std::string(calculate_index(this, 0), ' '));
    // bfs
    levelOrderWithHeight([&](const Tree *node, int h) {
        const int index = name_to_index[node->getName()];
        const int g_h = h * 4;
        graph[g_h] = graph[g_h].replace(name_to_index[node->getName()], node->getName().length(), node->getName());
        // 节点上方竖线
        if (g_h != 0) {
            graph[g_h - 2][index] = '|';
            graph[g_h - 1][index] = '|';
            // 兄弟节点之间的横线
            if (node->_nextSibling != nullptr) {
                int next_index = name_to_index[node->_nextSibling->getName()];
                for (int j = index + 1; j < next_index; ++j) {
                    graph[g_h - 2][j] = '-';
                }
            }
        }
        // 节点下方竖线
        if (node->_firstChild != nullptr && g_h != graph_height - 1) {
            graph[g_h + 1][index] = '|';
        }
    });

}

void Tree::print(Tree *highlight) const {
    this->calculate_graph();
    if (highlight == nullptr) {
        // 一般情况下的显示
        for (const std::string &line: graph) {
            std::cout << line << std::endl;
        }
        std::cout << std::endl;
        std::cout << "height: " << this->height() << std::endl;
        std::cout << "size: " << this->size() << std::endl;
        std::cout << std::endl;
        return;
    }
    // 高亮显示
    int highlight_h;
    // 计算高亮节点的高度
    levelOrderWithHeight([&](const Tree *node, int h) {
        if (node == highlight)highlight_h = h;
    });
    int highlight_index = name_to_index[highlight->getName()];
    for (int i = 0; i < graph.size(); ++i) {
        if (highlight_h * 4 == i) {
            // 高亮节点所在的那一行特殊处理
            for (int j = 0; j < highlight_index; ++j) {
                std::cout << graph[i][j];
            }
            std::cout << print_red(highlight->getName());
            for (int j = highlight_index + highlight->getName().length(); j < graph[i].size(); ++j) {
                std::cout << graph[i][j];
            }
            std::cout << std::endl;
        } else {
            // 其他行正常显示
            std::cout << graph[i] << std::endl;
        }
    }
}

struct Node {
    Tree *tree;
    int parent;
};

void Tree::load(const std::string &filename) {
    std::ifstream file(filename);
    std::string line;
    std::vector<Node *> nodes;
    bool is_root = true;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string name;
        int parent;
        iss >> name >> parent;
        if (is_root) {
            // 根节点读取
            assert(parent == -1);
            setName(name);
            is_root = false;
            nodes.push_back(new Node{this, -1});
            continue;
        }
        assert(parent < nodes.size() && parent >= 0);
        Tree *tree = new Tree(name);
        nodes[parent]->tree->addChild(tree);
        nodes.push_back(new Node{tree, parent});
    }
}

void Tree::save(const std::string &filename) const {
    std::ofstream file(filename);
    std::vector<Node *> nodes;
    levelOrder([&](Tree *tree) {
        nodes.push_back(new Node{tree});
    });
    std::function<int(Tree *)> find_parent = [&](Tree *x) {
        if (x == nodes[0]->tree) return -1;
        int parent_index = 0;
        while (parent_index < nodes.size()) {
            Tree *sibling = nodes[parent_index]->tree->_firstChild;
            while (sibling != x) {
                if (sibling == nullptr) {
                    ++parent_index;
                    break;
                }
                sibling = sibling->_nextSibling;
            }
            if (sibling == x)
                return parent_index;
        }
        return -1;
    };
    for (auto &node: nodes) {
        file << node->tree->getName() << " " << find_parent(node->tree) << std::endl;
    }
}