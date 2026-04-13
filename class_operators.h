#ifndef CLASS_OPERATORS_H
#define CLASS_OPERATORS_H

#include <string>

class class_operators
{
public:
    class_operators();
    void Demo();
    class Student
    {
    private:
        std::string name;
        std::string patronymic;
        std::string last_name;
    public:

        /// @brief Конструктор, инициализирующий все поля.
        Student(std::string n, std::string p, std::string l);
        /// @brief Геттер имени.
        std::string GetName() const;
        /// @brief Геттер отчества.
        std::string GetPatronymic() const;
        /// @brief Геттер фамилии.
        std::string GetLastName() const;
        /// @brief Оператор +: возвращает нового студента, дописывая строку к отчеству.
        /// @param n Строка, добавляемая в конец отчества.
        /// @return Новый объект Student с изменённым отчеством.
        Student operator+(std::string n) const;
        /// @brief Оператор равенства: сравнивает все три поля.
        /// @return true, если все поля совпадают.
        bool operator==(const Student &other) const;
    };
};

#endif // CLASS_OPERATORS_H
