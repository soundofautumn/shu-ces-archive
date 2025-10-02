//
// Created by 邱姜铭 on 2023/12/13.
//

#ifndef DATA_STRUCTURE_AIRWAYBILLSYSTEM_H
#define DATA_STRUCTURE_AIRWAYBILLSYSTEM_H

#include "Flight.h"

namespace flight {

    enum Book_Status {
        SUCCESS, FULL
    };

    class AirwayBillSystem {
    public:
        typedef std::shared_ptr<Flight> flight_ptr;
        typedef std::shared_ptr<FlightInfo> flight_info_ptr;
        typedef std::shared_ptr<PassengerInfo> passenger_info_ptr;
        typedef std::shared_ptr<SeqList<flight_ptr>> flight_list_ptr;
        typedef std::shared_ptr<SeqList<passenger_info_ptr>> passenger_info_list_ptr;
    private:
        flight_list_ptr flight_list;
        passenger_info_list_ptr passenger_info_list;
        static const std::string flight_list_filename;
        static const std::string passenger_info_list_filename;

        AirwayBillSystem();

        const flight_list_ptr &query_all_flight();

        SeqList<flight_info_ptr> query_flight(
                const FlightInfo::place_type &departure_place,
                const FlightInfo::place_type &destination_place,
                const FlightInfo::datetime &departure_time,
                const FlightInfo::datetime &destination_time,
                const FlightInfo::flight_number_type &flight_number,
                const FlightInfo::price_type &price,
                FlightClass flight_class);

        const passenger_info_ptr &get_passenger_info(
                const PassengerInfo::name_type &name,
                const PassengerInfo::id_type &id,
                const PassengerInfo::phone_type &phone) noexcept(false);

        Book_Status book_flight(
                const FlightInfo::flight_number_type &flight_number,
                const passenger_info_ptr &passenger_info,
                FlightClass flight_class,
                bool is_waiting = false) noexcept(false);

        void cancel_flight(
                const FlightInfo::flight_number_type &flight_number,
                const passenger_info_ptr &passenger_info,
                FlightClass flight_class) noexcept(false);

        void add_flight(const flight_info_ptr &flight_info);

        void delete_flight(const FlightInfo::flight_number_type &flight_number) noexcept(false);

        void modify_flight(const flight_info_ptr &flight_info) noexcept(false);

        passenger_info_list_ptr query_all_passenger_info();

        void add_passenger_info(passenger_info_ptr &passenger_info);

        void delete_passenger_info(const PassengerInfo::id_type &passenger_id) noexcept(false);

        void modify_passenger_info(const passenger_info_ptr &passenger_info) noexcept(false);

        void read_from_file();

        void write_to_file();

        void system_management_menu();

        void flight_management_menu();

    public:
        ~AirwayBillSystem();

        AirwayBillSystem(const AirwayBillSystem &) = delete;

        AirwayBillSystem &operator=(const AirwayBillSystem &) = delete;

        static AirwayBillSystem &get_instance();

        void run();
    };
}

#endif //DATA_STRUCTURE_AIRWAYBILLSYSTEM_H
