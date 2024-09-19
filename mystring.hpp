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

    //! Додає стрічку чи літеру в кінці стрічки.
    //! Обробка помилок:
        //! Не повинні заважати пропагуванню виключення
        //! std::bad_alloc.
    void append(const my_str_t& str);

    void append(char c);

    void append(const char* cstr);

    //! Видаляє size літер, починаючи з індексу begin.
    //! Літери праворуч від видаленого шматка зсуваються
    //! на size ліворуч.
    //! Обробка помилок:
    //! Якщо begin > size_m -- кидає виключення std::out_of_range.
    //! Але якщо стрічка містить менше символів для стирання,
    //! ніж потрібно -- це не помилка, видаляє всі до кінця.
    void erase(size_t begin, size_t size);

    //! Наступні функції повертають розмір стрічки та
    //! зарезервований блок пам'яті.
    //! Правильніше б назвати get_size() та get_capacity(),
    //! але історично в std::string прийнято
    //! так, то будемо наслідувати його
    size_t size() const noexcept;
    size_t capacity() const noexcept;

    //! Повертає вказівник на С-стрічку, яка відповідає
    //! цьому об'єкту. Якщо виділяти один зайвий байт,
    //! як описано в документації на конструтор, то їй
    //! достатньо зберегти нульовий байт у позиції
    //! data_m[size_m] і повернути data_m.
    const char* c_str() const;

    //! Функції find шукають вказану літеру чи стрічку,
    //! починаючи із idx. Якщо не знайдено, повертає
    //! константу my_str_t::not_found
    //! Обробка помилок:
    //! Якщо idx > size_m -- кидає виключення std::out_of_range.
    static constexpr size_t not_found = -1;
    size_t find(char c, size_t idx = 0);
    size_t find(const std::string& str, size_t idx = 0);
    size_t find(const char* cstr, size_t idx = 0);

    //! Скопіювати підстрічку, із begin включно,
    //! по begin+size не включно ([begin, begin+size)).
    //! Якщо end за межами початкової стрічки -- це не помилка,
    //! копіювати всі символи до кінця.
    //! beg має бути в її межах -- якщо begin>size, це помилка.
    //! Обробка помилок:
    //! Якщо begin > size_m -- кидає виключення std::out_of_range.
    my_str_t substr(size_t begin, size_t size);

    // Author: Kassiia Tserkovna
    friend std::ostream& operator<<(std::ostream& stream, const my_str_t& str);
    // Author: Kassiia Tserkovna
    friend std::istream& operator>>(std::istream& stream, my_str_t& str);

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

    friend std::istream& readline(std::istream& stream, my_str_t& str);
};

#endif
