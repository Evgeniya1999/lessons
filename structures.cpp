#include "structures.h"
#include "copy_referense_pointer.h"
//#include "init_class.h"

#include <string>
#include <iomanip>
#include <iostream>

structures::structures() {}

void structures::Demo(){
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 4. Структуры (метафора рюкзака)
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    std::cout << "       ---------------------" << std::endl << "       | *** Структуры *** |" << std::endl <<"       ---------------------" << std::endl;

    copy_referense_pointer::Vector v;
    std::cout << std::left << std::setw(25) << " Этап " << "| " << "Состояние памяти" << std::endl;
    std::cout << std::string(65, '-') << std::endl;
    std::cout << std::setw(25) << "После создания:" << "| " << (v.elem == nullptr ? "nullptr" : "есть мусор")
         << ", sz: " << v.sz << std::endl;
    copy_referense_pointer::vector_init(v, 5);
    std::cout << std::setw(25) << "После vector_init(5):" << "| " << "Адрес в heap: " << v.elem
         << ", sz: " << v.sz << std::endl;
    delete[] v.elem;
    v.elem = nullptr;
}
