#include "Account.h"

#include<iostream>


void Account::insert(std::string name, double money) {
    if (data == nullptr) {
        data = new LinkList<property>();
    }
    auto *p = new property();
    p->name = std::move(name);
    p->money = money;
    data->insert_node(p);
}

void Account::delete_by_name(std::string_view name) {
    if (data == nullptr) {
        std::cout << "    没有找到此账户\n";
        return;
    }
    static auto *p = new property();
    p->name = name;
    try {
        data->delete_node(p, compare_by_name);
    }
    catch (std::exception &e) {
        std::cout << "	没有找到此账户\n";
    }
}

void Account::change_by_name(std::string_view name, double delta_money, bool save_or_draw) {
    if (data == nullptr) {
        std::cout << "	没有找到此账户\n";
        return;
    }
    static auto *p = new property();
    p->name = name;
    try {
        data->find(p, compare_by_name)
                ->money += ((save_or_draw ? 1 : -1) * delta_money);
    } catch (std::exception &e) {
        std::cout << "	没有找到此账户\n";
    }


}

void Account::print_property(print_ptr print, std::ostream &out) {
    if (data == nullptr) {
        out << "	此用户没有资产\n";
        return;
    }
    data->print_all(print, out);
}

