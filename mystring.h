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

    void swap(my_str_t& mystr) noexcept;

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

    //! Вставляє передану стрічку типу my_str_t, чи літеру,
    //! чи С-стрічку, починаючи з літери idx,
    //! зсуваючи літеру з позиції idx і правіше праворуч.
    //! Обробка помилок:
    //! Якщо idx > size_m -- кидає виключення std::out_of_range
    void insert(size_t idx, const my_str_t& str);

    //! Ця функція -- служить для оптимізації, щоб не
    //! довелося спочатку створювати із літери c стрічку my_str_t, а
    //! потім вставляти. Навіть якщо компілятор зробив би це
    //! автоматично -- це повільно.
    void insert(size_t idx, char c);

    //! Аналогічна оптимізація для C-стрічок
    void insert(size_t idx, const char* cstr);

    friend bool operator==(const my_str_t& str1, const my_str_t& str2);
    friend bool operator!=(const my_str_t& str1, const my_str_t& str2);
    friend bool operator> (const my_str_t& str1, const my_str_t& str2);
    friend bool operator>=(const my_str_t& str1, const my_str_t& str2);
    friend bool operator< (const my_str_t& str1, const my_str_t& str2);
    friend bool operator<=(const my_str_t& str1, const my_str_t& str2);

    // Оператори порівняння для C-стрічки
    friend bool operator==(const my_str_t& str1, const char* cstr2);
    friend bool operator!=(const my_str_t& str1, const char* cstr2);
    friend bool operator> (const my_str_t& str1, const char* cstr2);
    friend bool operator>=(const my_str_t& str1, const char* cstr2);
    friend bool operator< (const my_str_t& str1, const char* cstr2);
    friend bool operator<=(const my_str_t& str1, const char* cstr2);

    friend bool operator==(const char* cstr1, const my_str_t& str2);
    friend bool operator!=(const char* cstr1, const my_str_t& str2);
    friend bool operator> (const char* cstr1, const my_str_t& str2);
    friend bool operator>=(const char* cstr1, const my_str_t& str2);
    friend bool operator< (const char* cstr1, const my_str_t& str2);
    friend bool operator<=(const char* cstr1, const my_str_t& str2);
};

#endif
