//
// // Created by Вероника Багатырь-Захарченко on 12.09.2024.
// //
#include "mystring.h"
#include <string>
#include <cstring>
#include <stdexcept>
#include <algorithm>

size_t calc_capacity(size_t size) {
    return (size+1)*2;
}

my_str_t::my_str_t(size_t size, char initial) {
    capacity_m = calc_capacity(size);
    size_m = size;

    data_m = new char[capacity_m];

    for (size_t i = 0; i < size; i++) {
        data_m[i] = initial;
    }
}
my_str_t::my_str_t(const char* cstr) {
    // capacity_m = strlen(cstr)*2;
    size_m = strlen(cstr);
    capacity_m = calc_capacity(size_m);

    data_m = new char[capacity_m];
    for (size_t i = 0; i < size_m; i++) {
        data_m[i] = cstr[i];
    }
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

char& my_str_t::operator[](unsigned long index) {
    return data_m[index];
}


//
// bool operator==(const my_str_t& str1, const my_str_t& str2) {
//     if (str1.size_m != str2.size_m) {
//         return false;
//     }
//     for (size_t i = 0; i < str1.size_m; i++) {
//         if (str1.data_m[i]!=str2.data_m[i]) {
//             return false;
//         }
//     }
//     return true;
// }
// bool operator!=(const my_str_t& str1, const my_str_t& str2) {
//     if (str1.size_m == str2.size_m) {
//         return false;
//     }
//     for (size_t i = 0; i < str1.size_m; ++i) {
//         if (str1.data_m[i] != str2.data_m[i]) {
//             return true;
//         }
//     }
//     return false;
// }
// bool operator> (const my_str_t& str1, const my_str_t& str2) {
//     return str1.size_m > str2.size_m;
// }
// bool operator>=(const my_str_t& str1, const my_str_t& str2) {
//     return str1.size_m >= str2.size_m;
// }
// bool operator< (const my_str_t& str1, const my_str_t& str2) {
//     return str1.size_m < str2.size_m;
// }
// bool operator<=(const my_str_t& str1, const my_str_t& str2) {
//     return str1.size_m <= str2.size_m;
// }
// // //! Same for the const char*
// bool operator==(const my_str_t& str1, const char* cstr2) {
//     size_t cstr_length = std::strlen(cstr2);
//     if (str1.size_m != cstr_length) {
//         return false;
//     }
//     for (size_t i = 0; i < str1.size_m; ++i) {
//         if (str1.data_m[i] != cstr2[i]) {
//             return false;
//         }
//     }
//     return true;
// }
//
// bool operator!=(const my_str_t& str1, const char* cstr2) {
//     size_t cstr_length = std::strlen(cstr2);
//     if (str1.size_m == cstr_length) {
//         return false;
//     }
//     for (size_t i = 0; i < str1.size_m; ++i) {
//         if (str1.data_m[i] != cstr2[i]) {
//             return true;
//         }
//     }
//     return false;
// }
//
// bool operator> (const my_str_t& str1, const char* cstr2) {
//     return str1.size_m > strlen(cstr2);
// }
// bool operator>=(const my_str_t& str1, const char* cstr2) {
//     return str1.size_m >= strlen(cstr2);
// }
// bool operator< (const my_str_t& str1, const char* cstr2) {
//     return str1.size_m < strlen(cstr2);
// }
// bool operator<=(const my_str_t& str1, const char* cstr2) {
//     return str1.size_m <= strlen(cstr2);
// }
// bool operator==(const char* cstr1, const my_str_t& str2) {
//     if (std::strlen(cstr1) != str2.size_m) {
//         return false;
//     }
//     for (size_t i = 0; i < str2.size_m; ++i) {
//         if (cstr1[i] != str2[i]) {
//             return false;
//         }
//     }
//     return true;
// }
// bool operator!=(const char* cstr1, const my_str_t& str2) {
//     if (std::strlen(cstr1) != str2.size_m) {
//         return true;
//     }
//     for (size_t i = 0; i < str2.size_m; ++i) {
//         if (cstr1[i] != str2[i]) {
//             return true;
//         }
//     }
//     return false;
// }
// bool operator> (const char* cstr1, const my_str_t& str2) {
//     size_t cstr_length = std::strlen(cstr1);
//     size_t minlength = std::min(cstr_length, str2.size_m);
//     for (size_t i = 0; i < minlength; ++i) {
//         if (cstr1[i] > str2.data_m[i]) {
//             return true;
//         } else if (cstr1[i] < str2.data_m[i]) {
//             return false;
//         }
//     }
//     return cstr_length > str2.size_m;
// }
// bool operator>=(const char* cstr1, const my_str_t& str2) {
//     size_t cstr_length = std::strlen(cstr1);
//     size_t minlength = std::min(cstr_length, str2.size_m);
//     for (size_t i = 0; i < minlength; ++i) {
//         if (cstr1[i] > str2.data_m[i]) {
//             return true;
//         } else if (cstr1[i] < str2.data_m[i]) {
//             return false;
//         }
//     }
//     return cstr_length >= str2.size_m;
// }
// bool operator< (const char* cstr1, const my_str_t& str2) {
//     size_t cstr_length = std::strlen(cstr1);
//     size_t minlength = std::min(cstr_length, str2.size_m);
//     for (size_t i = 0; i < minlength; ++i) {
//         if (cstr1[i] < str2.data_m[i]) {
//             return true;
//         } else if (cstr1[i] > str2.data_m[i]) {
//             return false;
//         }
//     }
//     return cstr_length < str2.size_m;
// }
// bool operator<=(const char* cstr1, const my_str_t& str2) {
//     size_t cstr_length = std::strlen(cstr1);
//     size_t minlength = std::min(cstr_length, str2.size_m);
//     for (size_t i = 0; i < minlength; ++i) {
//         if (cstr1[i] < str2.data_m[i]) {
//             return true;
//         } else if (cstr1[i] > str2.data_m[i]) {
//             return false;
//         }
//     }
//     return cstr_length <= str2.size_m;
// }

