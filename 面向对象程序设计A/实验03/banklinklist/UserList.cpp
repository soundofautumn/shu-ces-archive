#include "UserList.h"

#include <iostream>
#include <fstream>

UserList::UserList(std::string file_name) {
    data = new LinkList<user>();
    data_name = std::move(file_name);
    read_from_file(data_name);
}

UserList::~UserList() {
    write_to_file(data_name);
    delete data;
}

void UserList::query_all() {
    data->print_all([](const user &u, std::ostream &out) {
        std::cout << "用户名：" << u.name << "\n";
        u.account->print_property();
    });
}

void UserList::insert_user(std::string name, Account *account) {
    user *u = new user();
    u->name = std::move(name);
    u->account = account;
    data->insert_node(u);
}

bool UserList::contain_user(std::string_view name) {
    static user *u = new user();
    u->name = name;
    return data->contain(u, compare_by_name);
}

UserList::user *UserList::find_user(std::string_view name) {
    static user *u = new user();
    u->name = name;
    return data->find(u, compare_by_name);
}

void UserList::delete_user(std::string_view name) {
    static user *u = new user();
    u->name = name;
    try {
        data->delete_node(u, compare_by_name);
    } catch (std::exception &e) {
        std::cout << "	没有找到此用户\n";
    }
}


void UserList::read_from_file(std::string_view file_name) {
    std::ifstream in(file_name.data(), std::ios::in);
    if (!in.is_open()) {
        // 尝试创建文件
        std::ofstream ofs(file_name.data(), std::ios::out);
        if (!ofs.is_open()) {
            // 文件创建失败
            std::cout << "	文件打开失败\n";
            return;
        }
        ofs.close();
        // 重新尝试打开文件
        in = std::ifstream(file_name.data(), std::ios::in);
        if (!in.is_open()) {
            std::cout << "	文件打开失败\n";
            return;
        }
    }
    std::string user_name, account_name, account_money;
    while (in >> user_name) {
        while (true) {
            in >> account_name >> account_money;
            if (account_name == DATA_FILE_SPLIT) {
                break;
            }
            if (contain_user(user_name)) {
                find_user(user_name)->account->insert(account_name, std::stod(account_money));
            } else {
                auto *account = new Account();
                account->insert(account_name, std::stod(account_money));
                insert_user(user_name, account);
            }
        }

    }
    in.close();
}

void UserList::write_to_file(std::string_view file_name) {
    std::ofstream ofs(file_name.data());
    if (!ofs.is_open()) {
        std::cout << "	文件打开失败\n";
        return;
    }
    ofs.clear();
    data->print_all([](const user &u, std::ostream &out) {
        out << u.name << "\n";
        u.account->print_property([](const Account::property &p, std::ostream &out) {
            out << p.name << " " << p.money << "\n";
        }, out);
        out << DATA_FILE_SPLIT << std::endl;
        out << DATA_FILE_SPLIT << std::endl;
    }, ofs);

    ofs.close();
}
