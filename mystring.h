#ifndef MYSTRING_H
#define MYSTRING_H

#include <cstddef>  // для size_t
#include <stdexcept>  // для std::out_of_range

class my_str_t {
private:
    // char* data_m;         // Вказівник на блок пам'яті
    // size_t capacity_m;    // Розмір блока
    // size_t size_m;        // Фактичний розмір стрічки

public:
    size_t capacity_m;    // Розмір блока
    size_t size_m;
    char* data_m;
    // Конструктор: створює стрічку із 'size' копій літери 'initial'
    my_str_t(size_t size, char initial);

    // Конструктор: копіює вміст C-стрічки
    my_str_t(const char* cstr);
    my_str_t(const std::string& str);
    // Конструктор копіювання
    my_str_t(const my_str_t& mystr);

    // Оператор присвоєння
    my_str_t& operator=(const my_str_t& mystr);

    // Деструктор
    ~my_str_t();

    // Оператор доступу за індексом (з можливістю модифікації)
    char& operator[](size_t idx);

    // Оператор доступу за індексом (без можливості модифікації)
    const char& operator[](size_t idx) const;

    // Метод отримання символа за індексом з перевіркою меж
    char& at(size_t idx);
    const char& at(size_t idx) const;

    // Збільшення резерву пам'яті
    void reserve(size_t new_capacity);

    // Зменшення резерву пам'яті
    void shrink_to_fit();

    // Зміна розміру стрічки
    void resize(size_t new_size, char new_char = ' ');

    // Очищення стрічки
    void clear();
};

#endif
