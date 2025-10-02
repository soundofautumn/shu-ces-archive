//
// Created by 邱姜铭 on 2024/3/18.
//

#ifndef ZPP_DATA_STRUCTURE_TREE_H
#define ZPP_DATA_STRUCTURE_TREE_H


#include <functional>
#include <string>
#include <vector>
#include <map>

class Tree {
private:
    std::string _name;
    Tree *_firstChild;
    Tree *_nextSibling;

    mutable std::map<std::string, int> name_to_index;
    mutable std::vector<std::string> graph;

    void calculate_graph() const;

public:
    explicit Tree(std::string name);

    void addChild(Tree *child);

    bool deleteChild(Tree *child);

    std::string getName() const;

    void setName(const std::string &name);

    void load(const std::string &filename);

    void save(const std::string &filename) const;

    typedef std::function<void(Tree *)> Visit;

    // 先根遍历
    void preOrder(const Visit &visit) const;

    // 后根遍历
    void postOrder(const Visit &visit) const;

    // 层次遍历
    void levelOrder(const Visit &visit) const;

    typedef std::function<void(const Tree *, int)> VisitWithHeight;

    void levelOrderWithHeight(const VisitWithHeight &visitWithHeight) const;

    void print(Tree *highlight = nullptr) const;

    Tree *find(const std::string &name) const;

    int height() const;

    int size() const;
};


#endif //ZPP_DATA_STRUCTURE_TREE_H
