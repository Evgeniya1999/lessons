#include "pointer.h"
#include "copy_referense_pointer.h"

#include <iomanip>
#include <iostream>


pointer::pointer() {}

void pointer::Demo() {
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 5. Указатели: обход строки
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    std::cout << "        ---------------------" << std::endl << "        | *** Указатели *** |" << std::endl <<"        ---------------------" << std::endl;

    char str[] = "12345";
    char *p = str;
    char target = '3';
    int matches = 0;

    std::cout << std::left << std::setw(20) << "Адрес p"
         << "| " << std::setw(10) << "*p"
         << "| " << "Состояние matches" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    if (p != nullptr) {
        for (; *p != '\0'; ++p) {
            bool found = (*p == target);
            if (found)
                ++matches;
            std::cout << std::setw(20) << (void *) p << "| " << std::setw(10) << *p << "| "
                 << (found ? " НАЙДЕНО! -> " : " ") << matches << std::endl;
        }
    }
    std::cout << std::string(60, '-') << std::endl;
    std::cout << "Итого совпадений для '" << target << "': " << matches << std::endl;

    // Дополнительные иллюстрации ссылок и указателей
    int y = 5;
    int &t = y;
    t = 7;
    int *a = &y;
    *a = 3;
    y = 1;
    std::cout << y << " " << &y << " " << t << " " << *a << std::endl;

    int arr[10];
    std::cout << sizeof(int) << std::endl;
    std::cout << sizeof(arr) << std::endl;
    std::cout << sizeof(arr[0]) << std::endl;

    int value = 1;
    int *val = copy_referense_pointer::link_func(value);
    std::cout << *val << " " << value << std::endl;

}
