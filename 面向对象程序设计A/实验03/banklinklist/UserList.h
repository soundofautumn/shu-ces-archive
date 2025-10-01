#pragma once

#include "Account.h"
#include "LinkList.h"

class UserList {

public:
    struct user {
        std::string name;
        Account *account;
    };

    explicit UserList(std::string file_name = "user.txt");

    ~UserList();

    void query_all();

    void insert_user(std::string name, Account *account);

    bool contain_user(std::string_view name);

    user *find_user(std::string_view name);

    void delete_user(std::string_view name);

    void read_from_file(std::string_view file_name);

    void write_to_file(std::string_view file_name);

private:

    std::string data_name;

#define DATA_FILE_SPLIT "===================="

    LinkList<user> *data;

    static bool compare_by_name(const user& a, const user &b) { return a.name == b.name; }
};

