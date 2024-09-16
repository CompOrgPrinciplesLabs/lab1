#include "mystring.h"
#include <iostream>
#include <cassert>

void testOperators() {
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

    std::cout << "ok" << std::endl;
}

int main() {
    testOperators();
    return 0;
}
