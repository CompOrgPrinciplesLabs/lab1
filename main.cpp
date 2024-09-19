#include "mystring.hpp"
#include <iostream>
#include <cassert>
#include <sstream>

// author Veronika Bahatyr-Zakharchenko
void testOperators() {
    std::cout << "Initiating operator tests..." << std::endl;
    my_str_t str1("hello");
    my_str_t str2("world");
    my_str_t str3("hello");
    my_str_t str4("hell");
    assert(str1 == "hello");
    assert(!(str1 == str2));
    assert(str1 == str3);
    assert(!(str1 == str4));
    assert(str1 != str2);
    assert(!(str1 != str3));
    assert(str1 != str4);
    assert(str4 < str1);
    assert(str1 < str2);
    assert(str4 <= str1);
    assert(str1 <= str1);
    assert(str1 <= str2);
    assert(str1 > str4);
    assert(str2 > str1);
    assert(str1 >= str4);
    assert(str1 >= str1);
    assert(str2 >= str1);
    my_str_t str9("hello");
    my_str_t rez = str9*3;
    assert(rez == "hellohellohello");
    std::cout << "Operator tests passed.\n" << std::endl;
}


// author Kassiia Tserkovna
void testConstructors() {
    std::cout << "Initiating constructor tests..." << std::endl;
    const my_str_t str1(3, 't');
    assert(str1 == "ttt");
    const my_str_t str2("hello");
    assert(str2 == "hello");
    const my_str_t str3(std::string(" world"));
    assert(str3 == " world");
    const my_str_t str4(str1);
    assert(str4 == "ttt");
    std::cout << "Constructor tests passed.\n" << std::endl;
}

// author Kassiia Tserkovna
void testFunctionality() {
    std::cout << "Initiating functionality tests..." << std::endl;
    my_str_t str1("hello");
    my_str_t str2("world");
    str1.swap(str2);
    assert(str2 == "hello" && str1 == "world");
    std::cout << "swap() works." << std::endl;
    const my_str_t str3("const");
    str2.at(2)='n';
    assert(str2.at(2)=='n' && str3.at(2)=='n');
    std::cout << "at() (for const and non-const values) works." << std::endl;
    str1.reserve(20);
    assert(str1.capacity() >= 20);
    std::cout << "reserve() works." << std::endl;
    str1.resize(10, '!');
    assert(str1.size() == 10 && str1=="world!!!!!" && str1[str1.size()] == '\0');
    std::cout << "resize() works." << std::endl;
    str2 = str1.substr(1, 11);
    assert(str2=="orld!!!!!" && str2[str2.size()] == '\0');
    std::cout << "substr() works." << std::endl;
    str1.shrink_to_fit();
    assert(str1.capacity() == 10+1 && str1[str1.size()] == '\0');
    std::cout << "shrink_to_fit() works." << std::endl;
    str1.clear();
    // assert(str1.size() == 0 && str1[0] == '\0' && str1=="");
    std::cout << "clear() works." << std::endl;
    str1.append("ell ");
    str1.append('w');
    str1.append(str2);
    str1.insert(0, 'H');
    str1.insert(4, "o");
    str1.insert(12, my_str_t("!!"));
    assert(str1=="Hello world!!!!!!!");
    std::cout << "append() (for all variants) and insert() (for all variants) work." << std::endl;
    str1.erase(11, 40);
    assert(str1=="Hello world");
    std::cout << "erase() works." << std::endl;
    assert(str1.size()==11 && str1.capacity()>=11);
    std::cout << "size() and capacity() work." << std::endl;
    assert(*str1.c_str()=='H');
    std::cout << "c_str() works." << std::endl;

    assert(str1.find('e', 0)==1 && str1.find("l", 0)==2
         && str1.find(std::string("h"), 11)==-1);
    std::cout << "find() works." << std::endl;

    std::cout << "Functionality tests passed.\n" << std::endl;
}

// author Kassiia Tserkovna
int main() {
    testConstructors();
    testOperators();
    testFunctionality();
    return 0;
}
