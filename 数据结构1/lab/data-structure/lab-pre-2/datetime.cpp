//
// Created by 邱姜铭 on 2023/12/19.
//
#include <iomanip>
#include <sstream>
#include "datetime.h"

using namespace flight;


date::date() : year(0), month(0), day(0) {

}

date::date(const std::string &date_str) {
    try {
        year = std::stoi(date_str.substr(0, 4));
        month = std::stoi(date_str.substr(5, 2));
        day = std::stoi(date_str.substr(8, 2));
    } catch (std::out_of_range &e) {
        throw std::invalid_argument("Invalid date");
    }
}

void date::read(std::istream &is) {
    std::string date_str;
    is >> date_str;
    try {
        *this = date(date_str);
    } catch (std::invalid_argument &e) {
        is.setstate(std::ios::failbit);
    }
}

void date::write(std::ostream &os) const {
    // yyyy-mm-dd
    os << std::setfill('0')
       << std::setw(4) << year << "-"
       << std::setw(2) << month << "-"
       << std::setw(2) << day;
}

bool date::empty() const {
    return year == 0 && month == 0 && day == 0;
}

bool date::operator==(const date &rhs) const {
    return year == rhs.year &&
           month == rhs.month &&
           day == rhs.day;
}

bool date::operator!=(const date &rhs) const {
    return !(rhs == *this);
}

date::operator std::string() const {
    // yyyy-mm-dd
    std::stringstream ss;
    this->write(ss);
    return ss.str();
}

time::time() : hour(0), minute(0), second(0) {

}

time::time(const std::string &time_str) {
    try {
        hour = std::stoi(time_str.substr(0, 2));
        minute = std::stoi(time_str.substr(3, 2));
        second = std::stoi(time_str.substr(6, 2));
    } catch (std::out_of_range &e) {
        throw std::invalid_argument("Invalid time");
    }
}

void time::read(std::istream &is) {
    std::string time_str;
    is >> time_str;
    try {
        *this = time(time_str);
    } catch (std::invalid_argument &e) {
        is.setstate(std::ios::failbit);
    }
}

void time::write(std::ostream &os) const {
    // hh:mm:ss
    os << std::setfill('0')
       << std::setw(2) << hour << ":"
       << std::setw(2) << minute << ":"
       << std::setw(2) << second;
}

bool time::empty() const {
    return hour == 0 && minute == 0 && second == 0;
}

bool time::operator==(const time &rhs) const {
    return hour == rhs.hour &&
           minute == rhs.minute &&
           second == rhs.second;
}

bool time::operator!=(const time &rhs) const {
    return !(rhs == *this);
}

time::operator std::string() const {
    // hh:mm:ss
    std::stringstream ss;
    this->write(ss);
    return ss.str();
}

datetime::datetime() : _date(), _time() {

}

datetime::datetime(const std::string &datetime_str) {
    // yyyy-mm-dd hh:mm:ss
    try {
        _date = flight::date(datetime_str.substr(0, 10));
        _time = flight::time(datetime_str.substr(11, 8));
    } catch (std::invalid_argument &e) {
        throw std::invalid_argument("Invalid datetime");
    }
}

datetime::datetime(const std::string &date_str, const std::string &time_str) : _date(date_str), _time(time_str) {

}

void datetime::read(std::istream &is) {
    std::string date_str,time_str;
    is >> date_str >> time_str;
    try {
        *this = datetime(date_str, time_str);
    } catch (std::invalid_argument &e) {
        is.setstate(std::ios::failbit);
    }
}

void datetime::write(std::ostream &os) const {
    // yyyy-mm-dd hh:mm:ss
    _date.write(os);
    os << " ";
    _time.write(os);
}

bool datetime::empty() const {
    return _date.empty() && _time.empty();
}

datetime& datetime::operator=(const datetime &rhs) {
    _date = rhs._date;
    _time = rhs._time;
    return *this;
}

bool datetime::operator==(const datetime &rhs) const {
    return _date == rhs._date &&
            _time == rhs._time;
}

bool datetime::operator!=(const datetime &rhs) const {
    return !(rhs == *this);
}

datetime::operator std::string() const {
    // yyyy-mm-dd hh:mm:ss
    std::stringstream ss;
    this->write(ss);
    return ss.str();
}





