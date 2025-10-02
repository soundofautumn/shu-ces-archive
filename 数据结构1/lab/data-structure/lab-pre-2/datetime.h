//
// Created by 邱姜铭 on 2023/12/19.
//

#ifndef DATA_STRUCTURE_DATETIME_H
#define DATA_STRUCTURE_DATETIME_H

#include <string>
#include <iostream>

namespace flight {

    struct date {
        int year;
        int month;
        int day;

        date();

        explicit date(const std::string& date_str);

        void read(std::istream &is = std::cin);

        void write(std::ostream &os = std::cout) const;

        bool empty() const;

        friend std::ostream &operator<<(std::ostream &os, const date &date) {
            date.write(os);
            return os;
        }

        friend std::istream &operator>>(std::istream &is, date &date) {
            date.read(is);
            return is;
        }

        bool operator==(const date &rhs) const;

        bool operator!=(const date &rhs) const;

        explicit operator std::string() const;
    };

    struct time {
        int hour;
        int minute;
        int second;

        time();

        explicit time(const std::string& time_str);

        void read(std::istream &is = std::cin);

        void write(std::ostream &os = std::cout) const;

        bool empty() const;


        friend std::ostream &operator<<(std::ostream &os, const time &time) {
            time.write(os);
            return os;
        }

        friend std::istream &operator>>(std::istream &is, time &time) {
            time.read(is);
            return is;
        }

        bool operator==(const time &rhs) const;

        bool operator!=(const time &rhs) const;

        explicit operator std::string() const;
    };

    struct datetime {
        date _date;
        time _time;

        int &year = _date.year;
        int &month = _date.month;
        int &day = _date.day;
        int &hour = _time.hour;
        int &minute = _time.minute;
        int &second = _time.second;

        datetime();

        datetime(const std::string &datetime_str);

        datetime(const std::string &date_str, const std::string &time_str);

        void read(std::istream &is = std::cin);

        void write(std::ostream &os = std::cout) const;

        bool empty() const;

        friend std::ostream &operator<<(std::ostream &os, const datetime &datetime) {
            datetime.write(os);
            return os;
        }

        friend std::istream &operator>>(std::istream &is, datetime &datetime) {
            datetime.read(is);
            return is;
        }

        bool operator==(const datetime &rhs) const;

        bool operator!=(const datetime &rhs) const;

        datetime &operator=(const datetime &);

        explicit operator std::string() const;
    };
}


#endif //DATA_STRUCTURE_DATETIME_H
