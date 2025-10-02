//
// Created by 邱姜铭 on 2023/12/13.
//
#include <map>
#include "AirwayBillSystem.h"

using namespace flight;

int main() {
    AirwayBillSystem &system = AirwayBillSystem::get_instance();
    system.run();
    return 0;
}