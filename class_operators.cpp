#include "class_operators.h"

#include <string>
#include <iomanip>
#include <iostream>

class_operators::class_operators() {}

/// @brief Класс студента с именем, отчеством, фамилией.
/// @details Демонстрирует перегрузку операторов `+` (добавление строки к отчеству)
///          и `==` (сравнение всех полей).


class_operators::Student class_operators::Student::operator+(std::string n) const
{
    return Student(name, patronymic + n, last_name);
}

/// @brief Оператор равенства: сравнивает все три поля.
/// @return true, если все поля совпадают.
bool class_operators::Student::operator==(const Student &other) const
{
    return name == other.name && patronymic == other.patronymic && last_name == other.last_name;
}

// Реализация методов Student
class_operators::Student::Student(std::string n, std::string p, std::string l)
    : name(n)
    , patronymic(p)
    , last_name(l)
{}
std::string class_operators::Student::GetName() const
{
    return name;
}
std::string class_operators::Student::GetPatronymic() const
{
    return patronymic;
}
std::string class_operators::Student::GetLastName() const
{
    return last_name;
}


void class_operators::Demo(){
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 3. Операторы классов (Student)
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    std::cout << "       ---------------------------------" << std::endl << "       | *** Применение операторов *** |" << std::endl <<"       ---------------------------------" << std::endl;


    Student s1("Иван", "Иванович", "Иванов");
    Student s2 = s1 + " (монтажник)";

    std::cout << std::left << std::setw(20) << " Действие " << "| " << "Результат" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    std::cout << std::setw(20) << "s1 (Оригинал):" << "| " << s1.GetPatronymic() << std::endl;
    std::cout << std::setw(20) << "s2 (Результат +):" << "| " << s2.GetPatronymic() << std::endl;
    std::cout << std::string(60, '-') << std::endl;

    std::cout << std::setw(20) << "Сравнение (s1 == s2):";
    if (s1 == s2)
        std::cout << "| ОДИНАКОВЫ (ошибка логики?)" << std::endl;
    else
        std::cout << "| РАЗНЫЕ (оператор работает верно)" << std::endl;

    std::cout << std::setw(20) << "Сравнение (s1 == s1):";
    if (s1 == s1)
        std::cout << "| ОДИНАКОВЫ" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
}
