#include "typing_overloading.h"
#include <iostream>
#include <string>
#include <iomanip>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 1. Типизация и перегрузки
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

typing_overloading::typing_overloading() {}

/// @overload void my_sqrt(float x)
void typing_overloading::my_sqrt(float x)
{ /* заглушка */
}

/// @overload void my_sqrt(double x)
void typing_overloading::my_sqrt(double x)
{ /* заглушка */
}
void typing_overloading::Demo(){    

    std::cout << "       ---------------------------------- " << std::endl << "       | *** Типизация и перегрузки *** | " << std::endl << "       ----------------------------------" << std::endl;

    double da = 9.0;
    float fla = 9.0f;
    int i = 42;
    short s_val = 10;

    std::cout << "INIT PARAMS: \n";
    std::cout << "     double da = 9.0;\n "
                 "    float fla = 9.0f;\n "
                 "    int i = 42;\n "
                 "    short s_val = 10;\n\n";

    std::cout << std::left << std::setw(25) << " Вход (Аргумент) " << std::setw(20) << " Тип (typeid) "
         << " Результат / Статус компиляции " << std::endl;
    std::cout << std::string(85, '-') << std::endl;

    std::cout << std::setw(25) << "da (variable)" << std::setw(20) << typeid(da).name() << "Вызов: my_sqrt(double)"
         << std::endl;
    std::cout << std::setw(25) << "fla (variable)" << std::setw(20) << typeid(fla).name()
         << "Вызов: my_sqrt(float)" << std::endl;
    std::cout << std::setw(25) << "9.0 (literal)" << std::setw(20) << typeid(9.0).name()
         << "Вызов: my_sqrt(double) [Default]" << std::endl;
    std::cout << std::setw(25) << "9.0f (literal)" << std::setw(20) << typeid(9.0f).name()
         << "Вызов: my_sqrt(float) [Suffix]" << std::endl;
    std::cout << std::string(85, '-') << std::endl;

    std::cout << std::setw(25) << "i (int variable)" << std::setw(20) << typeid(i).name()
         << "ОШИБКА: Ambiguous(двусмысленность) (float? double?)" << std::endl;
    std::cout << std::setw(25) << "s_val (short variable)" << std::setw(20) << typeid(s_val).name()
         << "ОШИБКА: Ambiguous (float? double?)" << std::endl;
    std::cout << std::setw(25) << "100 (int literal)" << std::setw(20) << typeid(100).name()
         << "ОШИБКА: Ambiguous (float? double?)" << std::endl;
    std::cout << std::string(85, '-') << std::endl;

    std::cout << std::setw(25) << "static_cast<float>(i)" << std::setw(20) << "float (forced)"
         << "Вызов: my_sqrt(float) [Manual]" << std::endl;
    std::cout << std::setw(25) << "static_cast<double>(s_val)" << std::setw(20) << "double (forced)"
         << "Вызов: my_sqrt(double) [Manual]" << std::endl;
    std::cout << std::string(85, '-') << std::endl;
}
