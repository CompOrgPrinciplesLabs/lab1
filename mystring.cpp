//
// // Created by Вероника Багатырь-Захарченко on 12.09.2024.
// //
#include "mystring.h"
#include <string>
#include <cstring>
#include <stdexcept>
#include <algorithm>

size_t calc_capacity(size_t size) {
    return size*2+1 ;
}

int compare_two_strings(const char* str1, const char* str2) {
    size_t l1 = std::strlen(str1);
    size_t l2 = std::strlen(str2);
    for (size_t i = 0; i < std::min(l1, l2); ++i) {
        if (str1[i] < str2[i]) {
            return -1;  // str1 < str2
        } else if (str1[i] > str2[i]) {
            return 1;   // str1 > str2
        }
    }
    if (l1 < l2) {
        return -1;
    } else if (l1 > l2) {
        return 1;
    }
    return 0; //рівні
}

my_str_t::my_str_t(size_t size, char initial) {
    capacity_m = calc_capacity(size);
    size_m = size;
    data_m = new char[capacity_m];
    for (size_t i = 0; i < size; i++) {
        data_m[i] = initial;
    }
    data_m[size] = '\0';
}
my_str_t::my_str_t(const char* cstr) {
    size_m = strlen(cstr);
    capacity_m = calc_capacity(size_m);
    data_m = new char[capacity_m];
    for (size_t i = 0; i < size_m; i++) {
        data_m[i] = cstr[i];
    }
    data_m[size_m] = '\0';
}

my_str_t::my_str_t(const std::string& str) {
    size_m = str.size();
    capacity_m = calc_capacity(size_m);
    data_m = new char[capacity_m];
    for (size_t i = 0; i < size_m; i++) {
        data_m[i] = str[i];
    }
    data_m[size_m] = '\0';
}

my_str_t::my_str_t(const my_str_t& mystr) {
    size_m = mystr.size_m;
    capacity_m = mystr.capacity_m;
    data_m = new char[capacity_m];
    std::memcpy(data_m, mystr.data_m, size_m + 1); // новий блок памʼяті; блок, з якого копіюємо; кількість бітів + терм
}

my_str_t& my_str_t::operator=(const my_str_t& mystr) {
    if (this != &mystr) {
        delete[] data_m;
        size_m = mystr.size_m;
        capacity_m = mystr.capacity_m;
        data_m = new char[capacity_m];
        std::memcpy(data_m, mystr.data_m, size_m + 1);
    }
    return *this;
}

my_str_t::~my_str_t() {
    delete[] data_m;
}

char& my_str_t::operator[](size_t idx) {
    return data_m[idx];
}

const char& my_str_t::operator[](size_t idx) const {
    return data_m[idx];
}

bool operator==(const my_str_t& str1, const my_str_t& str2) {
    int rez = compare_two_strings(str1.data_m, str2.data_m);
    if (rez == 0) {
        return true;
    }
    return false;
}

bool operator!=(const my_str_t& str1, const my_str_t& str2) {
    int rez = compare_two_strings(str1.data_m, str2.data_m);
    if (rez == 0) {
        return false;
    }
    return true;
}

bool operator> (const my_str_t& str1, const my_str_t& str2) {
    int rez = compare_two_strings(str1.data_m, str2.data_m);
    if (rez == 1) {
        return true;
    }
    return false;
}

bool operator>=(const my_str_t& str1, const my_str_t& str2) {
    int rez = compare_two_strings(str1.data_m, str2.data_m);
    if (rez == 0 || rez == 1) {
        return true;
    }
    return false;
}

bool operator< (const my_str_t& str1, const my_str_t& str2) {
    int rez = compare_two_strings(str1.data_m, str2.data_m);
    if (rez == -1) {
        return true;
    }
    return false;
}
bool operator<=(const my_str_t& str1, const my_str_t& str2) {
    int rez = compare_two_strings(str1.data_m, str2.data_m);
    if (rez == 0 || rez == -1) {
        return true;
    }
    return false;
}
// //! Same for the const char*
bool operator==(const my_str_t& str1, const char* cstr2) {
    int rez = compare_two_strings(str1.data_m, cstr2);
    if (rez == 0) {
        return true;
    }
    return false;
}

bool operator!=(const my_str_t& str1, const char* cstr2) {
    int rez = compare_two_strings(str1.data_m, cstr2);
    if (rez == 0) {
        return false;
    }
    return true;
}

bool operator> (const my_str_t& str1, const char* cstr2) {
    int rez = compare_two_strings(str1.data_m, cstr2);
    if (rez == 1) {
        return true;
    }
    return false;
}
bool operator>=(const my_str_t& str1, const char* cstr2) {
    int rez = compare_two_strings(str1.data_m, cstr2);
    if (rez == 0||rez == 1) {
        return true;
    }
    return false;
}
bool operator< (const my_str_t& str1, const char* cstr2) {
    int rez = compare_two_strings(str1.data_m, cstr2);
    if (rez == -1) {
        return true;
    }
    return false;
}
bool operator<=(const my_str_t& str1, const char* cstr2) {
    int rez = compare_two_strings(str1.data_m, cstr2);
    if (rez == 0||rez == -1) {
        return true;
    }
    return false;
}

bool operator==(const char* cstr1, const my_str_t& str2) {
    int rez = compare_two_strings(cstr1, str2.data_m);
    if (rez == 0) {
        return true;
    }
    return false;
}
bool operator!=(const char* cstr1, const my_str_t& str2) {
    int rez = compare_two_strings(cstr1, str2.data_m);
    if (rez == 0) {
        return false;
    }
    return true;
}
bool operator> (const char* cstr1, const my_str_t& str2) {
    int rez = compare_two_strings(cstr1, str2.data_m);
    if (rez == 1) {
        return true;
    }
    return false;
}
bool operator>=(const char* cstr1, const my_str_t& str2) {
    int rez = compare_two_strings(cstr1, str2.data_m);
    if (rez == 0||rez == 1) {
        return true;
    }
    return false;
}
bool operator< (const char* cstr1, const my_str_t& str2) {
    int rez = compare_two_strings(cstr1, str2.data_m);
    if (rez == -1) {
        return true;
    }
    return false;
}
bool operator<=(const char* cstr1, const my_str_t& str2) {
    int rez = compare_two_strings(cstr1, str2.data_m);
    if (rez == 0||rez == -1) {
        return true;
    }
    return false;
}

