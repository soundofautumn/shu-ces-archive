//
// Created by 邱姜铭 on 2023/12/13.
//

#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Flight.h"


using namespace flight;


Flight::Flight()
        : info(new FlightInfo), seat_arrange_map() {
    for (auto F_class: {ECONOMY, BUSINESS, FIRST}) {
        const auto seat_count = this->info->seat_count_map.get(F_class);
        seat_arrange_map.insert(F_class, {waiting_queue_map_type(),
                                          passenger_list_type(new SeqList<passenger_ptr>(seat_count))});
        info->space_count_map.insert(F_class, seat_count);
    }
}

Flight::Flight(const std::shared_ptr<FlightInfo> &info)
        : info(info), seat_arrange_map() {
    for (auto F_class: {ECONOMY, BUSINESS, FIRST}) {
        const auto seat_count = this->info->seat_count_map.get(F_class);
        seat_arrange_map.insert(F_class, {waiting_queue_map_type(),
                                          passenger_list_type(new SeqList<passenger_ptr>(seat_count))});
        info->space_count_map.insert(F_class, seat_count);
    }
}

Flight::~Flight() = default;

std::shared_ptr<FlightInfo> Flight::get_info() const {
    return info;
}

void Flight::set_info(std::shared_ptr<FlightInfo> new_info) {
    this->info = std::move(new_info);
}

void Flight::add_passenger(passenger_ptr passenger) const {
    seat_arrange_map.get(passenger->get_flight_class()).passenger_list->insert(std::move(passenger));
}

void Flight::delete_passenger_by_id(const PassengerInfo::id_type &id) {
    for (const auto &item: seat_arrange_map) {
        auto &passenger_list = item.value.passenger_list;
        for (auto &passenger: *passenger_list) {
            if (passenger->get_id() == id) {
                passenger_list->remove(passenger_list->locate(passenger));
                return;
            }
        }
    }
}

void Flight::delete_passenger(const passenger_ptr &passenger) const {
    auto &list = seat_arrange_map.get(passenger->get_flight_class()).passenger_list;
    list->remove(list->locate(passenger));
}

void Flight::add_waiting_passenger(passenger_ptr passenger) const {
    auto &waiting_queue_map = seat_arrange_map.get(passenger->get_flight_class()).waiting_queue_map;
    if (waiting_queue_map.contains(passenger->get_priority())) {
        auto &waiting_queue = waiting_queue_map.get(passenger->get_priority());
        waiting_queue->enqueue(std::move(passenger));
        return;
    }
    auto waiting_queue = std::unique_ptr<Queue<passenger_ptr>>(new Queue<passenger_ptr>);
    auto priority = passenger->get_priority();
    waiting_queue->enqueue(std::move(passenger));
    waiting_queue_map.insert(priority, std::move(waiting_queue));
}

void Flight::arrange_waiting_passenger() {
    for (auto &item: seat_arrange_map) {
        auto &waiting_queue_map = item.value.waiting_queue_map;
        auto &passenger_list = item.value.passenger_list;
        for (int i = 0; i < 10; ++i) {
            if (!waiting_queue_map.contains(i)){
                continue;
            }
            auto &waiting_queue = waiting_queue_map.get(i);
            while (!waiting_queue->is_empty() && !passenger_list->is_full()) {
                passenger_list->insert(std::move(waiting_queue->dequeue()));
            }
        }
    }
}

void Flight::rearrange_passenger(passenger_ptr passenger, FlightClass old_class) const {
    auto &list = seat_arrange_map.get(old_class).passenger_list;
    list->remove(list->locate(passenger));
    add_passenger(std::move(passenger));
}

bool Flight::is_full() const {
    return seat_arrange_map.get(FlightClass::ECONOMY).passenger_list->is_full() &&
           seat_arrange_map.get(FlightClass::BUSINESS).passenger_list->is_full() &&
           seat_arrange_map.get(FlightClass::FIRST).passenger_list->is_full();
}

bool FlightInfo::operator==(const FlightInfo &rhs) const {
    return flight_number == rhs.flight_number &&
           departure_place == rhs.departure_place &&
           departure_time == rhs.departure_time &&
           destination_place == rhs.destination_place &&
           destination_time == rhs.destination_time &&
           price_map == rhs.price_map &&
           seat_count_map == rhs.seat_count_map &&
           space_count_map == rhs.space_count_map;
}

bool Flight::operator==(const Flight &rhs) const {
    return info == rhs.info;
}

std::ostream &Flight::operator<<(std::ostream &os) const {
    os << "info: " << info;
    return os;
}

std::istream &Flight::operator>>(std::istream &is) {
    return is;
}