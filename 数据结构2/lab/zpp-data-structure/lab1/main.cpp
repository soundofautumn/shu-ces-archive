//
// Created by 邱姜铭 on 2024/3/18.
//

#include <iostream>
#include <thread>
#include "Tree.h"
#include "Assistant.cpp"

using namespace std;

int main() {
    Tree tree("root");
    tree.load("tree.txt");
    while (true) {
        tree.print();
        cout << "0. Exit" << endl;
        cout << "1. Show traversal" << endl;
        cout << "2. Add a node" << endl;
        cout << "3. Modify a node" << endl;
        cout << "4. Delete a node" << endl;
        int choice;
        string name;
        string parent;
        Tree *node;
        function<void(Tree *)> animate = [&](Tree *node) {
            tree.print(node);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
            CLEAR
        };
        cin >> choice;
        switch (choice) {
            case 1:
                CLEAR
                cout << "PreOrder" << endl;
                PAUSE
                CLEAR
                tree.preOrder(animate);
                cout << endl;
                cout << "PostOrder" << endl;
                PAUSE
                CLEAR
                tree.postOrder(animate);
                cout << endl;
                cout << "LevelOrder" << endl;
                PAUSE
                CLEAR
                tree.levelOrder(animate);
                cout << endl;
                break;
            case 2:
                cout << "Enter the name of the node" << endl;
                cin >> name;
                cout << "Enter the name of the parent node" << endl;
                cin >> parent;
                node = tree.find(parent);
                if (node == nullptr) {
                    cout << print_red("Parent node not found") << endl;
                    break;
                }
                node->addChild(new Tree(name));
                break;
            case 3:
                cout << "Enter the name of the node" << endl;
                cin >> name;
                cout << "Enter the new name of the node" << endl;
                cin >> parent;
                tree.find(name)->setName(parent);
                break;
            case 4:
                cout << "Enter the name of the node" << endl;
                cin >> name;
                node = tree.find(name);
                if (node == nullptr) {
                    cout << print_red("Parent node not found") << endl;
                    break;
                }
                if (tree.deleteChild(node)) {
                    cout << print_green("Delete successfully") << endl;
                } else {
                    cout << print_red("Delete failed") << endl;
                }
                break;
            case 0:
                tree.save("tree.txt");
                return 0;
            default:
                cout << print_red("Invalid choice") << endl;
        }
        PAUSE
        CLEAR
    }
}
