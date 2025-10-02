//
// Created by 邱姜铭 on 2023/12/20.
//
#include <iomanip>
#include "AirwayBillSystem.h"

using namespace flight;
using namespace std;

using flight_list_ptr = AirwayBillSystem::flight_list_ptr;
using flight_ptr = AirwayBillSystem::flight_ptr;
using flight_info_ptr = AirwayBillSystem::flight_info_ptr;
using passenger_info_ptr = AirwayBillSystem::passenger_info_ptr;


#ifdef _WIN32
#define PAUSE system("pause");
#define CLEAR system("cls");
#endif
#if defined( __APPLE__) || defined(__linux__)
#define PAUSE cout<<"Please press any key to continue..."<<endl;\
            system("read");
#define CLEAR system("clear");
#endif

#ifdef _WIN32
#include "windows.h"
#define print_red(str) "";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED); std::cout << str; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);std::cout
#define print_green(str) "";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN); std::cout << str; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);std::cout
#define print_yellow(str) "";SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN); std::cout << str; SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);std::cout
#else
#define print_red(str) "\033[31m" << (str) << "\033[0m"
#define print_green(str) "\033[32m" << (str) << "\033[0m"
#define print_yellow(str) "\033[33m" << (str) << "\033[0m"
#endif

#define PRINT_SPACE_LINE cout<<"\n";
#define PRINT_SPLIT_LINE cout << "----------------------------------------" << endl;
#define PRINT_MENU(i, info) cout << static_cast<int>(i) << ". " << (info) << endl;

template<class T>
void input(T &data, const string &msg);

int choice_input();

void print_flight_info(const flight_info_ptr &flight_info);

void print_seat_arrange(const flight_info_ptr &flight_info);

void print_passenger_info(const passenger_info_ptr &passenger_info);

std::istream &operator>>(std::istream &is, PassengerInfo::sex_type &sex);

std::ostream &operator<<(std::ostream &os, PassengerInfo::sex_type &sex);

void print_flight_info(const flight_info_ptr &flight_info) {
    cout << endl;
    cout << "Flight number: " << print_green(flight_info->flight_number) << endl;
    cout << "Departure place: " << print_green(flight_info->departure_place) << endl;
    cout << "Departure time: " << print_green(flight_info->departure_time) << endl;
    cout << "Destination place: " << print_green(flight_info->destination_place) << endl;
    cout << "Destination time: " << print_green(flight_info->destination_time) << endl;
    PRINT_SPACE_LINE
#define SET_W << setw(10) << setfill(' ')
    cout << "            |   ECONOMY   BUSINESS      FIRST" << endl;
    cout << "Price:      |"
         SET_W << flight_info->price_map.get(FlightClass::ECONOMY) << " "
         SET_W << flight_info->price_map.get(FlightClass::BUSINESS) << " "
         SET_W << flight_info->price_map.get(FlightClass::FIRST) << endl;
    cout << "Seat count: |"
         SET_W << flight_info->seat_count_map.get(FlightClass::ECONOMY) << " "
         SET_W << flight_info->seat_count_map.get(FlightClass::BUSINESS) << " "
         SET_W << flight_info->seat_count_map.get(FlightClass::FIRST) << endl;
    cout << "Space count:|"
         SET_W << flight_info->space_count_map.get(FlightClass::ECONOMY) << " "
         SET_W << flight_info->space_count_map.get(FlightClass::BUSINESS) << " "
         SET_W << flight_info->space_count_map.get(FlightClass::FIRST) << endl;
#undef SET_W
    PRINT_SPACE_LINE
}

void print_seat_arrange(const flight_ptr &flight) {
    PRINT_SPACE_LINE
    cout << print_green("ECONOMY: ") << endl;
    cout << "Waiting queue: " << endl;
    for (const auto &item: flight->seat_arrange_map.get(FlightClass::ECONOMY).waiting_queue_map) {
        cout << "Priority: " << item.key << endl;
        for (const auto &passenger: *item.value) {
            cout << "    " << passenger->info->name << endl;
        }
    }
    cout << "Passenger list: " << endl;
    for (const auto &passenger: *flight->seat_arrange_map.get(FlightClass::ECONOMY).passenger_list) {
        cout << "    " << passenger->info->name << endl;
    }
    PRINT_SPACE_LINE
    cout << print_green("BUSINESS: ") << endl;
    cout << "Waiting queue: " << endl;
    for (const auto &item: flight->seat_arrange_map.get(FlightClass::BUSINESS).waiting_queue_map) {
        cout << "Priority: " << item.key << endl;
        for (const auto &passenger: *item.value) {
            cout << "    " << passenger->info->name << endl;
        }
    }
    cout << "Passenger list: " << endl;
    for (const auto &passenger: *flight->seat_arrange_map.get(FlightClass::BUSINESS).passenger_list) {
        cout << "    " << passenger->info->name << endl;
    }
    PRINT_SPACE_LINE
    cout << print_green("FIRST: ") << endl;
    cout << "Waiting queue: " << endl;
    for (const auto &item: flight->seat_arrange_map.get(FlightClass::FIRST).waiting_queue_map) {
        cout << "Priority: " << item.key << endl;
        for (const auto &passenger: *item.value) {
            cout << "    " << passenger->info->name << endl;
        }
    }
    cout << "Passenger list: " << endl;
    for (const auto &passenger: *flight->seat_arrange_map.get(FlightClass::FIRST).passenger_list) {
        cout << "    " << passenger->info->name << endl;
    }
}

void print_passenger_info(const passenger_info_ptr &passenger_info) {
    cout << endl;
    cout << "Name: " << passenger_info->name << endl;
    cout << "Id: " << passenger_info->id << endl;
    cout << "Phone: " << passenger_info->phone << endl;
    cout << "Birthday: " << passenger_info->birthday << endl;
    cout << "Sex: " << passenger_info->sex << endl;
    cout << "Priority: " << passenger_info->priority << endl;
}

std::istream &operator>>(std::istream &is, PassengerInfo::sex_type &sex) {
    int tmp;
    if (is >> tmp) {
        sex = static_cast<PassengerInfo::sex_type>(tmp);
    }
    return is;
}

std::ostream &operator<<(std::ostream &os, PassengerInfo::sex_type &sex) {
    os << static_cast<int>(sex);
    return os;
}

enum MENU_CHOICE {
    SYSTEM_MANAGEMENT = 1,
    FLIGHT_MANAGEMENT,
    EXIT_PROGRAM
};

void AirwayBillSystem::run() {
    this->read_from_file();
    while (true) {
        cout << "Welcome to XXX Airway Bill System !" << endl;
        PRINT_MENU(SYSTEM_MANAGEMENT, "system management")
        PRINT_MENU(FLIGHT_MANAGEMENT, "flight management")
        PRINT_MENU(EXIT_PROGRAM, "exit program")
        switch (choice_input()) {
            case SYSTEM_MANAGEMENT: {
                system_management_menu();
                break;
            }
            case FLIGHT_MANAGEMENT: {
                flight_management_menu();
                break;
            }
            case EXIT_PROGRAM:
            default:
                cout << "Bye" << endl;
                return;
        }
        PAUSE
        CLEAR
    }
}

enum SYSTEM_MANAGEMENT_MENU_CHOICE {
    QUERY_ALL_FLIGHT = 1,
    ADD_FLIGHT,
    DELETE_FLIGHT,
    MODIFY_FLIGHT,
    QUERY_ALL_PASSENGER,
    ADD_PASSENGER,
    DELETE_PASSENGER,
    MODIFY_PASSENGER,
    WRITE_TO_FILE,
    EXIT_SYSTEM_MANAGEMENT
};

int choice_input() {
    cout << "Please input your choice: ";
    int choice;
    cin >> choice;
    return choice;
}

template<class T>
void input(T &data, const string &msg) {
    cout << "Please input " << msg << ": ";
    cin >> data;
}

template<>
void input(FlightInfo::datetime &data, const string &msg) {
    cout << "Please input " << msg << " (yyyy-mm-dd hh:mm:ss): ";
    cin >> data;
}

template<>
void input(PassengerInfo::birthday_type &data, const string &msg) {
    cout << "Please input " << msg << " (yyyy-mm-dd): ";
    cin >> data;
}

template<>
void input(PassengerInfo::sex_type &data, const string &msg) {
    cout << "Please input " << msg << " (0:male, 1:female): ";
    cin >> data;
}

template<>
void input(FlightClass &data, const string &msg) {
    cout << "Please input " << msg << " (0:economy 1:business 2:first): ";
    int tmp;
    cin >> tmp;
    data = static_cast<FlightClass>(tmp);
}

template<class T>
void input(LinkedMap<FlightClass, T> &data, const string &msg) {
    cout << "Please input " << msg << " (economy business first): ";
    T price;
    cin >> price;
    data.insert(ECONOMY, price);
    cin >> price;
    data.insert(BUSINESS, price);
    cin >> price;
    data.insert(FIRST, price);
}

void AirwayBillSystem::system_management_menu() {
    while (true) {
        PRINT_MENU(QUERY_ALL_FLIGHT, "query all flight")
        PRINT_MENU(ADD_FLIGHT, "add flight")
        PRINT_MENU(DELETE_FLIGHT, "delete flight")
        PRINT_MENU(MODIFY_FLIGHT, "modify flight")
        PRINT_MENU(QUERY_ALL_PASSENGER, "query all passenger")
        PRINT_MENU(ADD_PASSENGER, "add passenger")
        PRINT_MENU(DELETE_PASSENGER, "delete passenger")
        PRINT_MENU(MODIFY_PASSENGER, "modify passenger")
        PRINT_MENU(WRITE_TO_FILE, "write to file")
        PRINT_MENU(EXIT_SYSTEM_MANAGEMENT, "exit")
        switch (choice_input()) {
            case QUERY_ALL_FLIGHT: {
                auto &result = query_all_flight();
                for (const auto &flight: *result) {
                    CLEAR
                    print_flight_info(flight->get_info());
                    print_seat_arrange(flight);
                    PAUSE
                }
                CLEAR
                break;
            }
            case ADD_FLIGHT: {
                flight_info_ptr flight_info = std::make_shared<FlightInfo>();
                input(flight_info->flight_number, "flight number");
                input(flight_info->departure_place, "departure place");
                input(flight_info->departure_time, "departure time");
                input(flight_info->destination_place, "destination place");
                input(flight_info->destination_time, "destination time");
                input(flight_info->price_map, "price");
                input(flight_info->seat_count_map, "seat count");
                add_flight(flight_info);
                cout << print_green("Add success") << endl;
                break;
            }
            case DELETE_FLIGHT: {
                FlightInfo::flight_number_type flight_number;
                input(flight_number, "flight number");
                try {
                    delete_flight(flight_number);
                }
                catch (invalid_argument &e) {
                    cout << print_red(e.what()) << endl;
                    break;
                }
                cout << print_green("Delete success") << endl;
                break;
            }
            case MODIFY_FLIGHT: {
                flight_info_ptr flight_info = make_shared<FlightInfo>();
                input(flight_info->flight_number, "flight number");
                input(flight_info->departure_place, "departure place");
                input(flight_info->departure_time, "departure time");
                input(flight_info->destination_place, "destination place");
                input(flight_info->destination_time, "destination time");
                input(flight_info->price_map, "price");
                input(flight_info->seat_count_map, "seat count");
                modify_flight(flight_info);
                cout << print_green("Modify success") << endl;
                break;
            }
            case QUERY_ALL_PASSENGER: {
                const auto &result = query_all_passenger_info();
                if (result->is_empty()) {
                    cout << print_yellow("No result") << endl;
                    break;
                }
                for (const auto &info: *result) {
                    print_passenger_info(info);
                }
                break;
            }
            case ADD_PASSENGER: {
                passenger_info_ptr passenger_info = make_shared<PassengerInfo>();
                input(passenger_info->name, "passenger name");
                input(passenger_info->id, "passenger id");
                input(passenger_info->phone, "passenger phone");
                input(passenger_info->birthday, "passenger birthday");
                input(passenger_info->sex, "passenger sex");
                input(passenger_info->priority, "passenger priority");
                add_passenger_info(passenger_info);
                cout << print_green("Add success") << endl;
                break;
            }
            case DELETE_PASSENGER: {
                PassengerInfo::id_type passenger_id;
                input(passenger_id, "passenger id");
                delete_passenger_info(passenger_id);
                cout << print_green("Delete success") << endl;
                break;
            }
            case MODIFY_PASSENGER: {
                passenger_info_ptr passenger_info = make_shared<PassengerInfo>();
                input(passenger_info->name, "passenger name");
                input(passenger_info->id, "passenger id");
                input(passenger_info->phone, "passenger phone");
                input(passenger_info->birthday, "passenger birthday");
                input(passenger_info->sex, "passenger sex");
                input(passenger_info->priority, "passenger priority");
                modify_passenger_info(passenger_info);
                cout << print_green("Modify success") << endl;
                break;
            }
            case WRITE_TO_FILE: {
                write_to_file();
                cout << print_green("Write success") << endl;
                break;
            }
            case EXIT_SYSTEM_MANAGEMENT:
            default:
                write_to_file();
                return;
        }
    }
}

enum FLIGHT_MANAGEMENT_MENU_CHOICE {
    QUERY_FLIGHT = 1,
    BOOK_FLIGHT,
    CANCEL_FLIGHT,
    EXIT_FLIGHT_MANAGEMENT
};

enum QUERY_FLIGHT_MENU_CHOICE {
    QUERY_BY_DEPARTURE_PLACE = 1,
    QUERY_BY_DESTINATION_PLACE,
    QUERY_BY_DEPARTURE_TIME,
    QUERY_BY_DESTINATION_TIME,
    QUERY_BY_FLIGHT_NUMBER,
    QUERY_BY_PRICE,
    QUERY_BY_FLIGHT_CLASS,
};

void AirwayBillSystem::flight_management_menu() {
    while (true) {
        PRINT_MENU(QUERY_FLIGHT, "query flight")
        PRINT_MENU(BOOK_FLIGHT, "book flight")
        PRINT_MENU(CANCEL_FLIGHT, "cancel flight")
        PRINT_MENU(EXIT_FLIGHT_MANAGEMENT, "exit")
        switch (choice_input()) {
            case QUERY_FLIGHT: {
                string departure_place, destination_place, flight_number;
                datetime departure_time, destination_time;
                double price = 0;
                FlightClass flight_class;
                bool query_flag = true;
                while (query_flag) {
                    PRINT_MENU(QUERY_BY_DEPARTURE_PLACE, "query by departure place")
                    PRINT_MENU(QUERY_BY_DESTINATION_PLACE, "query by destination place")
                    PRINT_MENU(QUERY_BY_DEPARTURE_TIME, "query by departure time")
                    PRINT_MENU(QUERY_BY_DESTINATION_TIME, "query by destination time")
                    PRINT_MENU(QUERY_BY_FLIGHT_NUMBER, "query by flight number")
                    PRINT_MENU(QUERY_BY_PRICE, "query by price")
                    PRINT_MENU(QUERY_BY_FLIGHT_CLASS, "query by flight class")
                    switch (choice_input()) {
                        case 1:
                            input(departure_place, "departure place");
                            break;
                        case 2:
                            input(destination_place, "destination place");
                            break;
                        case 3:
                            input(departure_time, "departure time");
                            break;
                        case 4:
                            input(destination_time, "destination time");
                            break;
                        case 5:
                            input(flight_number, "flight number");
                            break;
                        case 6:
                            input(price, "price");
                            break;
                        case 7:
                            input(flight_class, "flight class");
                            break;
                        default:
                            query_flag = false;
                            break;
                    }
                    CLEAR
                }
                auto result = query_flight(departure_place, destination_place, departure_time,
                                           destination_time, flight_number, price,
                                           flight_class);
                if (result.is_empty()) {
                    cout << print_yellow("No result") << endl;
                    break;
                }
                for (const auto &flight: result) {
                    CLEAR
                    print_flight_info(flight);
                    PAUSE
                }
                break;
            }
            case BOOK_FLIGHT: {
                string flight_number, name, id, phone;
                FlightClass flight_class;
                input(flight_number, "flight number");
                input(name, "passenger name");
                input(id, "passenger id");
                input(phone, "passenger phone");
                input(flight_class, "flight class");
                try {
                    auto status = book_flight(flight_number,
                                              get_passenger_info(name, id, phone),
                                              flight_class);
                    if (status == SUCCESS) {
                        cout << print_green("Book success") << endl;
                    } else if (status == FULL) {
                        cout << print_yellow(
                                "The flight is full. Would you mind adding you to the waiting queue? (y/n)") << endl;
                        char c;
                        cin >> c;
                        if (c == 'Y' || c == 'y') {
                            status = book_flight(flight_number, get_passenger_info(name, id, phone),
                                                 flight_class, true);
                            if (status == SUCCESS) {
                                cout << print_green("You've been added to the waiting list.") << endl;
                            }
                        } else
                            break;
                    }
                } catch (invalid_argument &e) {
                    cout << print_red(e.what()) << endl;
                }
                break;
            }
            case CANCEL_FLIGHT: {
                string flight_number, name, id, phone;
                FlightClass flight_class;
                input(flight_number, "flight number");
                input(name, "passenger name");
                input(id, "passenger id");
                input(phone, "passenger phone");
                input(flight_class, "flight class");
                try {
                    cancel_flight(flight_number, get_passenger_info(name, id, phone),
                                  flight_class);
                    cout << print_green("Cancel success") << endl;
                } catch (invalid_argument &e) {
                    cout << print_red(e.what()) << endl;
                }
                break;
            }
            case EXIT_FLIGHT_MANAGEMENT:
            default:
                return;
        }
    }

}

#undef PRINT_MENU
#undef PRINT_SPLIT_LINE
#undef CLEAR
#undef PAUSE