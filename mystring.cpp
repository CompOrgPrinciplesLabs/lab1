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

// author Veronika Bahatyr-Zakharchenko
int compare_two_strings(const char* str1, const char* str2) {
    size_t l1 = std::strlen(str1);
    size_t l2 = std::strlen(str2);
    const size_t min_len = std::min(l1,l2);

    for (size_t i = 0; i < min_len; ++i) {
        if (str1[i] < str2[i]) {
            return -1;  // str1 < str2
        }
        if (str1[i] > str2[i]) {
            return 1;   // str1 > str2
        }
    }
    if (l1 < l2) {
        return -1;
    }
    if (l1 > l2) {
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

// author Veronika Bahatyr-Zakharchenko
my_str_t::my_str_t(const char* cstr) {
    size_m = strlen(cstr);
    capacity_m = calc_capacity(size_m);
    data_m = new char[capacity_m];
    for (size_t i = 0; i < size_m; i++) {
        data_m[i] = cstr[i];
    }
    data_m[size_m] = '\0';
}

// author Veronika Bahatyr-Zakharchenko
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

// author Veronika Bahatyr-Zakharchenko
my_str_t::my_str_t(const my_str_t& mystr) {
    size_m = mystr.size_m;
    capacity_m = mystr.capacity_m;
    data_m = new char[capacity_m];
    std::memcpy(data_m, mystr.data_m, size_m + 1); // новий блок памʼяті; блок, з якого копіюємо; кількість бітів + терм
}

// author Veronika Bahatyr-Zakharchenko
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

// author Veronika Bahatyr-Zakharchenko
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

// author Veronika Bahatyr-Zakharchenko
void my_str_t::resize(size_t new_size, char new_char) {
    if (new_size < size_m) {
        size_m = new_size;
    } else if (new_size <= capacity_m) {
        for (size_t i = size_m; i < new_size; ++i) {
            data_m[i] = new_char;
        }
        size_m = new_size;
    } else {
        reserve(new_size);
        for (size_t i = size_m; i < new_size; ++i) {
            data_m[i] = new_char;
        }
        size_m = new_size;
    }
    data_m[size_m] = '\0';
}

// author Veronika Bahatyr-Zakharchenko
my_str_t my_str_t::substr(size_t begin, size_t size) {
    if (begin > size_m) {
        throw std::out_of_range("index is out of range");
    }
    if (begin + size > size_m) {
        size = size_m - begin;
    }
    my_str_t result(size, ' ');
    for (size_t i = 0; i < size; ++i) {
        result[i] = data_m[begin + i];
    }
    result[size] = '\0';
    return result;
}

// author Vlad Vasylevych
void my_str_t::shrink_to_fit() {
    char* new_data_m = new char[size_m];
    std::memcpy(new_data_m, data_m, size_m);
    delete[] data_m;
    data_m = new_data_m;
}

// author Kassiia Tserkovna
void my_str_t::clear() {
    size_m = 0;
    shrink_to_fit();
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

    const size_t cstr_size = std::strlen(cstr);

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
    const size_t cstr_size = std::strlen(cstr);

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
size_t my_str_t::size() const noexcept{
    return size_m;
}

// author Vlad Vasylevych
size_t my_str_t::capacity() const noexcept{
    return capacity_m;
}

// author Vlad Vasylevych
const char* my_str_t::c_str() const {
    return data_m;
}

// author Vlad Vasylevych
size_t my_str_t::find(char c, size_t idx) {
    if (idx > size_m) {
        throw std::out_of_range("my_str_t::find");
    }

    for (size_t i = idx; i < size_m; i++) {
        if (data_m[i] == c) {
            return i;
        }
    }

    return not_found;

}

// author Vlad Vasylevych
size_t my_str_t::find(const std::string& s, size_t idx) {
    if (idx > size_m) {
        throw std::out_of_range("my_str_t::find");
    }

    const size_t s_len = s.length();

    for (size_t i = idx; i < size_m - s_len; i++) {
        bool is_same = true;
        for (size_t j = 0; j < s_len; j++) {
            if (data_m[i + j] == s[j]) {
                continue;
            }
            is_same = false;
            break;
        }
        if (is_same == true) {
            return i;
        }
    }

    return not_found;
}

// author Vlad Vasylevych
size_t my_str_t::find(const char* cstr, size_t idx) {
    if (idx > size_m) {
        throw std::out_of_range("my_str_t::find");
    }

    const size_t s_len = std::strlen(cstr);

    for (size_t i = idx; i < size_m - s_len; i++) {
        bool is_same = true;
        for (size_t j = 0; j < s_len; j++) {
            if (data_m[i + j] == cstr[j]) {
                continue;
            }
            is_same = false;
            break;
        }
        if (is_same == true) {
            return i;
        }
    }

    return not_found;
}

// author Veronika Bahatyr-Zakharchenko
char& my_str_t::operator[](size_t idx) {
    return data_m[idx];
}

// author Veronika Bahatyr-Zakharchenko
const char& my_str_t::operator[](size_t idx) const {
    return data_m[idx];
}

// author Kassiia Tserkovna
std::ostream& operator<<(std::ostream& stream, const my_str_t& str) {
    for (size_t i = 0; i < str.size_m; i++) {
        stream << str[i];
    }
    return stream;
}

// author Kassiia Tserkovna
std::istream& operator>>(std::istream& stream, my_str_t& str){
    str.clear();
    char temp;
    do {
        stream.get(temp);
    } while (isspace(temp));
    str.append(temp);
    do {
        stream.get(temp);
        str.append(temp);
    } while (!isspace(temp));
    return stream;
}


// author Veronika Bahatyr-Zakharchenko
bool operator==(const my_str_t& str1, const my_str_t& str2) {
    int rez = compare_two_strings(str1.data_m, str2.data_m);
    if (rez == 0) {
        return true;
    }
    return false;
}

// author Veronika Bahatyr-Zakharchenko
bool operator!=(const my_str_t& str1, const my_str_t& str2) {
    int rez = compare_two_strings(str1.data_m, str2.data_m);
    if (rez == 0) {
        return false;
    }
    return true;
}

// author Veronika Bahatyr-Zakharchenko
bool operator> (const my_str_t& str1, const my_str_t& str2) {
    int rez = compare_two_strings(str1.data_m, str2.data_m);
    if (rez == 1) {
        return true;
    }
    return false;
}

// author Veronika Bahatyr-Zakharchenko
bool operator>=(const my_str_t& str1, const my_str_t& str2) {
    int rez = compare_two_strings(str1.data_m, str2.data_m);
    if (rez == 0 || rez == 1) {
        return true;
    }
    return false;
}

// author Veronika Bahatyr-Zakharchenko
bool operator< (const my_str_t& str1, const my_str_t& str2) {
    int rez = compare_two_strings(str1.data_m, str2.data_m);
    if (rez == -1) {
        return true;
    }
    return false;
}

// author Veronika Bahatyr-Zakharchenko
bool operator<=(const my_str_t& str1, const my_str_t& str2) {
    int rez = compare_two_strings(str1.data_m, str2.data_m);
    if (rez == 0 || rez == -1) {
        return true;
    }
    return false;
}

// //! Same for the const char*

// author Veronika Bahatyr-Zakharchenko
bool operator==(const my_str_t& str1, const char* cstr2) {
    int rez = compare_two_strings(str1.data_m, cstr2);
    if (rez == 0) {
        return true;
    }
    return false;
}

// author Veronika Bahatyr-Zakharchenko
bool operator!=(const my_str_t& str1, const char* cstr2) {
    int rez = compare_two_strings(str1.data_m, cstr2);
    if (rez == 0) {
        return false;
    }
    return true;
}

// author Veronika Bahatyr-Zakharchenko
bool operator> (const my_str_t& str1, const char* cstr2) {
    int rez = compare_two_strings(str1.data_m, cstr2);
    if (rez == 1) {
        return true;
    }
    return false;
}

// author Veronika Bahatyr-Zakharchenko
bool operator>=(const my_str_t& str1, const char* cstr2) {
    int rez = compare_two_strings(str1.data_m, cstr2);
    if (rez == 0||rez == 1) {
        return true;
    }
    return false;
}

// author Veronika Bahatyr-Zakharchenko
bool operator< (const my_str_t& str1, const char* cstr2) {
    int rez = compare_two_strings(str1.data_m, cstr2);
    if (rez == -1) {
        return true;
    }
    return false;
}

// author Veronika Bahatyr-Zakharchenko
bool operator<=(const my_str_t& str1, const char* cstr2) {
    int rez = compare_two_strings(str1.data_m, cstr2);
    if (rez == 0||rez == -1) {
        return true;
    }
    return false;
}

// author Veronika Bahatyr-Zakharchenko
bool operator==(const char* cstr1, const my_str_t& str2) {
    int rez = compare_two_strings(cstr1, str2.data_m);
    if (rez == 0) {
        return true;
    }
    return false;
}

// author Veronika Bahatyr-Zakharchenko
bool operator!=(const char* cstr1, const my_str_t& str2) {
    int rez = compare_two_strings(cstr1, str2.data_m);
    if (rez == 0) {
        return false;
    }
    return true;
}

// author Veronika Bahatyr-Zakharchenko
bool operator> (const char* cstr1, const my_str_t& str2) {
    int rez = compare_two_strings(cstr1, str2.data_m);
    if (rez == 1) {
        return true;
    }
    return false;
}

// author Veronika Bahatyr-Zakharchenko
bool operator>=(const char* cstr1, const my_str_t& str2) {
    int rez = compare_two_strings(cstr1, str2.data_m);
    if (rez == 0||rez == 1) {
        return true;
    }
    return false;
}

// author Veronika Bahatyr-Zakharchenko
bool operator< (const char* cstr1, const my_str_t& str2) {
    int rez = compare_two_strings(cstr1, str2.data_m);
    if (rez == -1) {
        return true;
    }
    return false;
}

// author Veronika Bahatyr-Zakharchenko
bool operator<=(const char* cstr1, const my_str_t& str2) {
    int rez = compare_two_strings(cstr1, str2.data_m);
    if (rez == 0||rez == -1) {
        return true;
    }
    return false;
}

// author Kassiia Tserkovna
std::istream& readline(std::istream& stream, my_str_t& str) {
    str.clear();
    char temp;
    while (stream.peek() != '\n') {
        stream.get(temp);
        str.append(temp);
    }
    return stream;
}
