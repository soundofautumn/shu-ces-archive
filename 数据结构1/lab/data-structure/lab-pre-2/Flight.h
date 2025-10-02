//
// Created by 邱姜铭 on 2023/12/13.
//

#ifndef DATA_STRUCTURE_FLIGHT_H
#define DATA_STRUCTURE_FLIGHT_H

#include <memory>
#include <string>
#include <iostream>
#include "SeqList.h"
#include "Queue.h"
#include "LinkedMap.h"
#include "Passenger.h"
#include "datetime.h"

namespace flight {

    struct FlightInfo {
        typedef std::string flight_number_type;
        typedef std::string place_type;
        typedef flight::datetime datetime;
        typedef double price_type;
        typedef int seat_count_type;
        flight_number_type flight_number;
        place_type departure_place;
        datetime departure_time;
        place_type destination_place;
        datetime destination_time;
        LinkedMap<FlightClass, price_type> price_map;
        LinkedMap<FlightClass, seat_count_type> seat_count_map;
        LinkedMap<FlightClass, seat_count_type> space_count_map;

        bool operator==(const FlightInfo &rhs) const;
    };


    class Flight {
    public:
        typedef std::shared_ptr<FlightInfo> flight_info_ptr;
        typedef std::shared_ptr<Passenger> passenger_ptr;
    private:
        std::shared_ptr<FlightInfo> info;
        typedef std::shared_ptr<SeqList<passenger_ptr>> passenger_list_type;
        typedef std::shared_ptr<Queue<passenger_ptr>> waiting_queue_type;
        typedef LinkedMap<PassengerInfo::priority_type, waiting_queue_type> waiting_queue_map_type;
        typedef struct {
            waiting_queue_map_type waiting_queue_map;
            passenger_list_type passenger_list;
        } seat_arrange_value_type;
    public:
        LinkedMap<FlightClass, seat_arrange_value_type> seat_arrange_map;

        Flight();

        explicit Flight(const std::shared_ptr<FlightInfo> &info);

        ~Flight();

        std::shared_ptr<FlightInfo> get_info() const;

        void set_info(std::shared_ptr<FlightInfo> info);

        void add_passenger(passenger_ptr passenger) const;

        void delete_passenger_by_id(const PassengerInfo::id_type& id);

        void delete_passenger(const passenger_ptr& passenger) const;

        void add_waiting_passenger(passenger_ptr passenger) const;

        void arrange_waiting_passenger();

        void rearrange_passenger(passenger_ptr passenger, FlightClass old_class) const;

        bool is_full() const;

        bool operator==(const Flight &rhs) const;

        std::ostream &operator<<(std::ostream &os) const;

        friend std::ostream &operator<<(std::ostream &os, const Flight &flight) {
            return flight.operator<<(os);
        }

        std::istream &operator>>(std::istream &is);

        friend std::istream &operator>>(std::istream &is, Flight &flight){
            return flight.operator>>(is);
        }
    };

}
#endif //DATA_STRUCTURE_FLIGHT_H
