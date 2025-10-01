#pragma once

#include <string>
#include "LinkList.h"


class Account {

public:
    struct property {
        std::string name;
        double money = 0;
    };

    typedef void print_ptr(const property&, std::ostream &);

    Account() = default;

    ~Account() = default;

    void insert(std::string name, double money);

    void delete_by_name(std::string_view name);

    void change_by_name(std::string_view name, double delta_money, bool save_or_draw);

    void print_property(print_ptr print = [](const property& p, std::ostream &out) {
        std::cout << "	" << p.name << "	" << p.money << "\n";
    }, std::ostream &out = std::cout);

private:


    LinkList<property> *data;

    static bool compare_by_name(const property& a, const property& b) { return a.name == b.name; }


};

