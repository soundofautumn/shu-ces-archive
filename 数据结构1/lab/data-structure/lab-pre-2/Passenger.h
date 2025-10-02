//
// Created by 邱姜铭 on 2023/12/13.
//

#ifndef DATA_STRUCTURE_PASSENGER_H
#define DATA_STRUCTURE_PASSENGER_H

#include <memory>
#include <string>
#include <iostream>
#include "datetime.h"

namespace flight {
    enum FlightClass {
        ECONOMY,
        BUSINESS,
        FIRST
    };

    struct PassengerInfo {
        typedef std::string name_type;
        typedef std::string id_type;
        typedef std::string phone_type;
        typedef date birthday_type;
        typedef enum {
            MALE, FEMALE
        } sex_type;
        typedef int priority_type;
        std::string name;
        std::string id;
        std::string phone;
        birthday_type birthday;
        sex_type sex;
        priority_type priority;
    };

    class Passenger {
    public:
        std::shared_ptr<PassengerInfo> info;
        FlightClass flight_class;

        Passenger() = default;

        Passenger(std::shared_ptr<PassengerInfo> info, FlightClass flight_class);

        PassengerInfo::id_type get_id() const;

        PassengerInfo::priority_type get_priority() const;

        FlightClass get_flight_class() const;

        bool operator==(const Passenger &rhs) const;

        bool operator!=(const Passenger &rhs) const {
            return !(rhs == *this);
        }

    };

}

#endif //DATA_STRUCTURE_PASSENGER_H
