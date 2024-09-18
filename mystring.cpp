// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "mystring.h"
#include <string>
#include <cstring>
#include <stdexcept>
#include <algorithm>
#include <iostream>
#include <ostream>

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
    // std::memcpy(data_m, &str, size_m); // why not?
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

// author Vlad Vasylevych
void my_str_t::swap(my_str_t& mystr) noexcept{
    const size_t tmp_size = size_m;
    const size_t tmp_cap = capacity_m;
    char* tmp_data_m = data_m;

    size_m = mystr.size_m;
    capacity_m = mystr.capacity_m;
    data_m = mystr.data_m;

    mystr.size_m = tmp_size;
    mystr.capacity_m = tmp_cap;
    mystr.data_m = tmp_data_m;
}

// author Vlad Vasylevych
char &my_str_t::at(size_t idx) {
    if (idx >= size_m) {
        throw std::out_of_range("my_str_t::at");
    }
    return data_m[idx];
}

// author Vlad Vasylevych
const char &my_str_t::at(size_t idx) const{
    if (idx >= size_m) {
        throw std::out_of_range("my_str_t::at");
    }
    return data_m[idx];
}

// author Vlad Vasylevych
void my_str_t::reserve(size_t new_capacity) {
    if (new_capacity < capacity_m) {
        return;
    }
    capacity_m = new_capacity;

    char* new_data_m = new char[capacity_m];
    std::memcpy(new_data_m, data_m, size_m);
    delete[] data_m;
    data_m = new_data_m;
}

// author Vlad Vasylevych
void my_str_t::shrink_to_fit() {
    char* new_data_m = new char[size_m];
    std::memcpy(new_data_m, data_m, size_m);
    delete[] data_m;
    data_m = new_data_m;
}

// author Vlad Vasylevych
void my_str_t::clear() {
    size_m = 0;
    delete[] data_m; // not sure I should delete
}

// author Vlad Vasylevych
void my_str_t::insert(size_t idx, const my_str_t &str) {
    if (idx > size_m) {
        throw std::out_of_range("my_str_t::insert");
    }

    if (size_m + str.size_m > capacity_m) {
        const size_t new_cap = (size_m + str.size_m) * 2;
        reserve(new_cap);
    }

    // insert logic
    std::memmove(data_m + idx + str.size_m, data_m + idx, size_m - idx);
    std::memmove(data_m + idx, str.data_m, str.size_m);

    size_m = size_m + str.size_m;

}

// author Vlad Vasylevych
void my_str_t::insert(size_t idx, char c) {
    if (idx > size_m) {
        throw std::out_of_range("my_str_t::insert");
    }

    if (size_m + 1 > capacity_m) {
        const size_t new_cap = (size_m + 1) * 2;
        reserve(new_cap);
    }

    // insert logic
    std::memmove(data_m + idx + 1, data_m + idx, size_m - idx);
    std::memmove(data_m + idx, &c, 1);

    size_m = size_m + 1;
}

// author Vlad Vasylevych
void my_str_t::insert(size_t idx, const char *cstr) {
    if (idx > size_m) {
        throw std::out_of_range("my_str_t::insert");
    }

    const size_t cstr_size = strlen(cstr);

    if (size_m + cstr_size > capacity_m) {
        const size_t new_cap = (size_m + cstr_size) * 2;
        reserve(new_cap);
    }

    // insert logic
    std::memmove(data_m + idx + cstr_size, data_m + idx, size_m - idx);
    std::memmove(data_m + idx, cstr, cstr_size);

    size_m = size_m + cstr_size;
}

// author Vlad Vasylevych
void my_str_t::append(const my_str_t &str) {
    if (size_m + str.size_m > capacity_m) {
        const size_t new_cap = (size_m + str.size_m) * 2;
        reserve(new_cap);
    }

    std::memcpy(data_m + size_m, str.data_m, str.size_m);

    size_m = size_m + str.size_m;
}

// author Vlad Vasylevych
void my_str_t::append(char c) {
    if (size_m + 1 > capacity_m) {
        const size_t new_cap = (size_m + 1) * 2;
        reserve(new_cap);
    }

    std::memcpy(data_m + size_m, &c, 1);

    size_m = size_m + 1;
}

// author Vlad Vasylevych
void my_str_t::append(const char* cstr) {
    const size_t cstr_size = strlen(cstr);

    if (size_m + cstr_size > capacity_m) {
        const size_t new_cap = (size_m + cstr_size) * 2;
        reserve(new_cap);
    }

    std::memcpy(data_m + size_m, cstr, cstr_size);

    size_m = size_m + cstr_size;
}

// author Vlad Vasylevych
void my_str_t::erase(size_t begin, size_t size) {
    if (begin > size_m) {
        throw std::out_of_range("my_str_t::erase");
    }

    const size_t right_size = std::min(size, size_m - begin);

    std::memcpy(data_m + begin, data_m + begin + right_size, size_m - begin - right_size);
    size_m = size_m - right_size;
}

// author Vlad Vasylevych
size_t my_str_t::size() const {
    return size_m;
}

// author Vlad Vasylevych
size_t my_str_t::capacity() const {
    return capacity_m;
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

