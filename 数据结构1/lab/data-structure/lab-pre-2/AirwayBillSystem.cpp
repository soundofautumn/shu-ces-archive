//
// Created by 邱姜铭 on 2023/12/13.
//

#include <fstream>
#include "AirwayBillSystem.h"

using namespace flight;

using flight_list_ptr = AirwayBillSystem::flight_list_ptr;
using flight_info_ptr = AirwayBillSystem::flight_info_ptr;
using passenger_info_ptr = AirwayBillSystem::passenger_info_ptr;

const std::string AirwayBillSystem::flight_list_filename = "flight_list.txt";
const std::string AirwayBillSystem::passenger_info_list_filename = "passenger_info_list.txt";

std::istream &operator>>(std::istream &is, PassengerInfo::sex_type &sex);

std::ostream &operator<<(std::ostream &os, PassengerInfo::sex_type &sex);

AirwayBillSystem::AirwayBillSystem() {
    flight_list = std::unique_ptr<SeqList<flight_ptr>>(new SeqList<flight_ptr>);
    passenger_info_list = std::unique_ptr<SeqList<passenger_info_ptr>>(new SeqList<passenger_info_ptr>);
    // 判断数据文件是否存在，不存在则创建
    std::fstream file;
    file.open(flight_list_filename, std::ios::in);
    if (!file.is_open()) {
        file.open(flight_list_filename, std::ios::out);
    }
    file.close();

    file.open(passenger_info_list_filename, std::ios::in);
    if (!file.is_open()) {
        file.open(passenger_info_list_filename, std::ios::out);
    }
    file.close();
}

AirwayBillSystem::~AirwayBillSystem() {
    flight_list->clear();
    passenger_info_list->clear();
}

AirwayBillSystem &AirwayBillSystem::get_instance() {
    static AirwayBillSystem *instance = nullptr;
    if (instance == nullptr) {
        instance = new AirwayBillSystem();
    }
    return *instance;
}


const flight_list_ptr &AirwayBillSystem::query_all_flight() {
    return flight_list;
}

SeqList<flight_info_ptr> AirwayBillSystem::query_flight(
        const FlightInfo::place_type &departure_place,
        const FlightInfo::place_type &destination_place,
        const FlightInfo::datetime &departure_time,
        const FlightInfo::datetime &destination_time,
        const FlightInfo::flight_number_type &flight_number,
        const FlightInfo::price_type &price,
        FlightClass flight_class) {
    auto result = new SeqList<flight_info_ptr>;
    for (const auto &flight: *flight_list) {
        auto flight_info = flight->get_info();
        // 不为空且不相等才跳过
        if (!departure_time.empty() && flight_info->departure_time != departure_time) continue;
        if (!departure_place.empty() && flight_info->departure_place != departure_place) continue;
        if (!destination_time.empty() && flight_info->destination_time != destination_time) continue;
        if (!destination_place.empty() && flight_info->destination_place != destination_place) continue;
        if (!flight_number.empty() && flight_info->flight_number != flight_number) continue;
        if (price != 0 && flight_info->price_map.get(flight_class) != price) continue;
        result->insert(std::move(flight_info));
    }
    return *result;
}

const passenger_info_ptr &AirwayBillSystem::get_passenger_info(
        const PassengerInfo::name_type &name,
        const PassengerInfo::id_type &id,
        const PassengerInfo::phone_type &phone) noexcept(false) {
    for (const auto &passengerInfo: *passenger_info_list) {
        if (!name.empty() && passengerInfo->name != name) continue;
        if (!id.empty() && passengerInfo->id != id)continue;
        if (!phone.empty() && passengerInfo->phone != phone) continue;
        return passengerInfo;
    }
    throw invalid_argument("No such passenger");
}

Book_Status AirwayBillSystem::book_flight(
        const FlightInfo::flight_number_type &flight_number,
        const std::shared_ptr<PassengerInfo> &passenger_info,
        FlightClass flight_class,
        bool is_waiting) noexcept(false) {
    for (auto &flight: *flight_list) {
        if (flight->get_info()->flight_number != flight_number) continue;
        if (flight->get_info()->space_count_map.get(flight_class) == 0) {
            if (is_waiting) {
                flight->add_waiting_passenger(std::make_shared<Passenger>(passenger_info, flight_class));
                return SUCCESS;
            }
            return FULL;
        }
        flight->get_info()->space_count_map.insert(flight_class,
                                                   flight->get_info()->space_count_map.get(flight_class) - 1);
        flight->add_passenger(std::make_shared<Passenger>(passenger_info, flight_class));
        return SUCCESS;
    }
    throw invalid_argument("No such flight");
}

void AirwayBillSystem::cancel_flight(const FlightInfo::flight_number_type &flight_number,
                                     const std::shared_ptr<PassengerInfo> &passenger_info,
                                     FlightClass flight_class) noexcept(false) {
    for (auto &flight: *flight_list) {
        if (flight->get_info()->flight_number != flight_number) continue;
        flight->get_info()->space_count_map.insert(flight_class,
                                                   flight->get_info()->space_count_map.get(flight_class) + 1);
        try {
            flight->delete_passenger_by_id(passenger_info->id);
        } catch (out_of_range &e) {
            throw invalid_argument("No such passenger");
        }
        flight->arrange_waiting_passenger();
        return;
    }
}

void AirwayBillSystem::add_flight(const flight_info_ptr &flight_info) {
    std::unique_ptr<Flight> flight(new Flight(flight_info));
    flight_list->insert(std::move(flight));
}

void AirwayBillSystem::delete_flight(const FlightInfo::flight_number_type &flight_number) noexcept(false) {
    int i = -1;
    for (const auto &flight: *flight_list) {
        if (flight->get_info()->flight_number != flight_number) continue;
        i = flight_list->locate(flight);
        break;
    }
    if (i != -1) {
        flight_list->remove(i);
        return;
    }
    throw invalid_argument("No such flight");
}

void AirwayBillSystem::modify_flight(const flight_info_ptr &flight_info) noexcept(false) {
    for (auto &flight: *flight_list) {
        if (flight->get_info()->flight_number != flight_info->flight_number) continue;
        flight->set_info(flight_info);
        return;
    }
    throw invalid_argument("No such flight");
}

AirwayBillSystem::passenger_info_list_ptr AirwayBillSystem::query_all_passenger_info() {
    return passenger_info_list;
}

void AirwayBillSystem::add_passenger_info(passenger_info_ptr &passenger_info) {
    passenger_info_list->insert(std::move(passenger_info));
}

void AirwayBillSystem::modify_passenger_info(const passenger_info_ptr &new_passenger_info) noexcept(false) {
    for (auto &passenger_info: *passenger_info_list) {
        if (passenger_info->id != new_passenger_info->id)continue;
        passenger_info = new_passenger_info;
        return;
    }
    throw invalid_argument("No such passenger");
}

void AirwayBillSystem::delete_passenger_info(const PassengerInfo::id_type &passenger_id) noexcept(false) {
    for (auto &passenger_info: *passenger_info_list) {
        if (passenger_info->id != passenger_id)continue;
        passenger_info_list->remove(passenger_info_list->locate(passenger_info));
        return;
    }
    throw invalid_argument("No such passenger");
}


void AirwayBillSystem::read_from_file() {
    // 读取航班信息
    std::fstream file;
    file.open(flight_list_filename, std::ios::in);
    if (!file.is_open()) {
        throw std::invalid_argument("No such file");
    }
    if (file.peek() == EOF) {
        return;
    }
    flight_info_ptr flight_info = std::make_shared<FlightInfo>();
    while (file >> flight_info->flight_number
                >> flight_info->departure_place >> flight_info->departure_time
                >> flight_info->destination_place >> flight_info->destination_time
                >> flight_info->price_map.getOrPut(FlightClass::ECONOMY, 0)
                >> flight_info->price_map.getOrPut(FlightClass::BUSINESS, 0)
                >> flight_info->price_map.getOrPut(FlightClass::FIRST, 0)
                >> flight_info->seat_count_map.getOrPut(FlightClass::ECONOMY, 0)
                >> flight_info->seat_count_map.getOrPut(FlightClass::BUSINESS, 0)
                >> flight_info->seat_count_map.getOrPut(FlightClass::FIRST, 0)
                >> flight_info->space_count_map.getOrPut(FlightClass::ECONOMY, 0)
                >> flight_info->space_count_map.getOrPut(FlightClass::BUSINESS, 0)
                >> flight_info->space_count_map.getOrPut(FlightClass::FIRST, 0)) {
        std::unique_ptr<Flight> flight(new Flight(flight_info));
        flight_list->insert(std::move(flight));
        flight_info = std::make_shared<FlightInfo>();
    }
    file.close();
    // 读取乘客信息
    file.open(passenger_info_list_filename, std::ios::in);
    if (!file.is_open()) {
        throw std::invalid_argument("No such file");
    }
    if (file.peek() == EOF) {
        return;
    }
    passenger_info_ptr passenger_info = std::make_shared<PassengerInfo>();
    while (file >> passenger_info->name >> passenger_info->id >> passenger_info->phone
                >> passenger_info->birthday >> passenger_info->sex >> passenger_info->priority) {
        passenger_info_list->insert(std::move(passenger_info));
        passenger_info = std::make_shared<PassengerInfo>();
    }
    file.close();
}

void AirwayBillSystem::write_to_file() {
    // 写入航班信息
    std::fstream file;
    file.open(flight_list_filename, std::ios::out);
    if (!file.is_open()) {
        throw std::invalid_argument("No such file");
    }
    for (const auto &flight: *flight_list) {
        const flight_info_ptr info = flight->get_info();
        file << info->flight_number << " ";
        file << info->departure_place << " ";
        file << info->departure_time << " ";
        file << info->destination_place << " ";
        file << info->destination_time << " ";
        file << info->price_map.get(FlightClass::ECONOMY) << " ";
        file << info->price_map.get(FlightClass::BUSINESS) << " ";
        file << info->price_map.get(FlightClass::FIRST) << " ";
        file << info->seat_count_map.get(FlightClass::ECONOMY) << " ";
        file << info->seat_count_map.get(FlightClass::BUSINESS) << " ";
        file << info->seat_count_map.get(FlightClass::FIRST) << " ";
        file << info->space_count_map.get(FlightClass::ECONOMY) << " ";
        file << info->space_count_map.get(FlightClass::BUSINESS) << " ";
        file << info->space_count_map.get(FlightClass::FIRST) << " ";
        file << std::endl;
    }
    file.close();
    // 写入乘客信息
    file.open(passenger_info_list_filename, std::ios::out);
    if (!file.is_open()) {
        throw std::invalid_argument("No such file");
    }
    for (const auto &passenger_info: *passenger_info_list) {
        file << passenger_info->name << " ";
        file << passenger_info->id << " ";
        file << passenger_info->phone << " ";
        file << passenger_info->birthday << " ";
        file << passenger_info->sex << " ";
        file << passenger_info->priority << " ";
        file << std::endl;
    }
    file.close();

}
