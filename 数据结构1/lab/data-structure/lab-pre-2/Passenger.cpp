//
// Created by 邱姜铭 on 2023/12/13.
//

#include "Passenger.h"

#include <utility>

using namespace flight;

Passenger::Passenger(std::shared_ptr<PassengerInfo> info, FlightClass flight_class)
        : info(std::move(info)), flight_class(flight_class) {

}

PassengerInfo::id_type Passenger::get_id() const {
    return info->id;
}

PassengerInfo::priority_type Passenger::get_priority() const {
    return info->priority;
}

FlightClass Passenger::get_flight_class() const {
    return flight_class;
}

bool Passenger::operator==(const Passenger &rhs) const {
    return info == rhs.info &&
           flight_class == rhs.flight_class;
}


