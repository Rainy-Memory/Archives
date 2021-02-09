#include <iostream>

using namespace std;
const int month_days[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

class Date {
private:
    int _year;
    int _month;
    int _day;

public:
    Date() {
        _year = 1900;
        _month = 1;
        _day = 1;
    }
    
    Date(int yy, int mm, int dd) {
        bool judge = true, flag = true;
        if (mm <= 0 || mm > 12)judge = false;
        if (yy % 4 == 0 && yy % 100 != 0 || yy % 400 == 0) {
            if (mm == 2) {
                if (dd > 29 || dd <= 0) judge = false;
                else flag = false;
            }
        }
        if (flag) {
            if (dd > month_days[mm] || dd <= 0)judge = false;
        }
        if (judge) {
            _year = yy;
            _month = mm;
            _day = dd;
        }
        else {
            _year = 1900;
            _month = 1;
            _day = 1;
        }
    }
    
    bool is_leap_year() const {
        if (_year % 4 == 0 && _year % 100 != 0 || _year % 400 == 0)return true;
        else return false;
    }
    
    Date operator+(int x) {
        Date temp = *this;
        for (int i = 0; i < x; i++) {
            temp++;
        }
        return temp;
    }
    
    Date operator-(int x) {
        Date temp = *this;
        for (int i = 0; i < x; i++) {
            temp--;
        }
        return temp;
    }
    
    Date &operator++() {
        int mon_day = month_days[_month];
        if (is_leap_year() && _month == 2)mon_day++;
        if (mon_day == _day) {
            if (_month != 12) {
                _month++;
                _day = 1;
            }
            else {
                _year++;
                _month = 1;
                _day = 1;
            }
        }
        else {
            _day++;
        }
        return *this;
    }
    
    Date operator++(int) {
        Date temp = *this;
        int mon_day = month_days[_month];
        if (is_leap_year() && _month == 2)mon_day++;
        if (mon_day == _day) {
            if (_month != 12) {
                _month++;
                _day = 1;
            }
            else {
                _year++;
                _month = 1;
                _day = 1;
            }
        }
        else {
            _day++;
        }
        return temp;
    }
    
    Date &operator--() {
        if (_day == 1) {
            if (_month == 1) {
                _year--;
                _month = 12;
                _day = 31;
            }
            else {
                _month--;
                _day = (is_leap_year() && _month == 2) ? 29 : month_days[_month];
            }
        }
        else _day--;
        return *this;
    }
    
    Date operator--(int) {
        Date temp = *this;
        if (_day == 1) {
            if (_month == 1) {
                _year--;
                _month = 12;
                _day = 31;
            }
            else {
                _month--;
                _day = (is_leap_year() && _month == 2) ? 29 : month_days[_month];
            }
        }
        else _day--;
        return temp;
    }
    
    
    bool operator<(Date a) const {
        if (_year < a._year)return true;
        else if (_year > a._year)return false;
        else {
            if (_month < a._month)return true;
            else if (_month > a._month)return false;
            else {
                if (_day < a._day)return true;
                else return false;
            }
        }
    }
    
    int operator-(Date a) {
        int count = 0;
        Date big, small;
        if ((*this) < a) {
            big = a;
            small = *this;
        }
        else if (a < (*this)) {
            big = *this;
            small = a;
        }
        else return 0;
        while (small != big) {
            count++;
            small++;
        }
        return count;
    }
    
    friend ostream &operator<<(ostream &os, Date o);
    
    bool operator==(const Date &rhs) const {
        return _year == rhs._year &&
               _month == rhs._month &&
               _day == rhs._day;
    }
    
    bool operator!=(const Date &rhs) const {
        return !(rhs == *this);
    }
    
    bool operator>(const Date &rhs) const {
        return rhs < *this;
    }
    
    bool operator<=(const Date &rhs) const {
        return !(rhs < *this);
    }
    
    bool operator>=(const Date &rhs) const {
        return !(*this < rhs);
    }
};

ostream &operator<<(ostream &os, Date o) {
    os << o._year << "-" << o._month << "-" << o._day;
    return os;
}
