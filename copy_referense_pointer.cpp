#include "copy_referense_pointer.h"

#include <iostream>
#include <string>
#include <iomanip>

// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
// 2. Копия, ссылка, указатель (демонстрация)
// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

copy_referense_pointer::copy_referense_pointer() {

}

/// @brief Инициализирует вектор заданным размером, выделяя память в куче.
/// @param v  Ссылка на структуру Vector
/// @param s  Требуемый размер
void copy_referense_pointer::vector_init(copy_referense_pointer::Vector &v, int s)
{
    if (v.elem)
        delete[] v.elem;    // очистка предыдущего (безопасно)
    v.elem = new double[s]; // выделение
    v.sz = s;
}

/// @brief Освобождает память вектора и обнуляет указатель с размером.
/// @param v Ссылка на структуру Vector
void copy_referense_pointer::vector_destroy(copy_referense_pointer::Vector &v)
{
    if (v.elem)
        delete[] v.elem;
    v.elem = nullptr;
    v.sz = 0;
}

/// @brief Демонстрация различий передачи параметров.
/// @param v   Копия структуры (изменения не видны снаружи)
/// @param rv  Ссылка на оригинал (изменяет внешний объект)
/// @param pv  Указатель на оригинал (требует разыменования, может быть nullptr)
void copy_referense_pointer::access_to_structure(copy_referense_pointer::Vector v, copy_referense_pointer::Vector &rv, copy_referense_pointer::Vector *pv)
{
    std::cout << "\n--- [ ВХОД В ФУНКЦИЮ ] ---" << std::endl;
    std::cout << "Адрес v (копия):    " << &v << " | sz: " << v.sz << std::endl;
    std::cout << "Адрес rv (ссылка): " << &rv << " | sz: " << rv.sz << std::endl;
    std::cout << "Адрес *pv (указатель): " << pv << " | sz: " << (pv ? pv->sz : -1) << std::endl;
    std::cout << "---------------------------" << std::endl;
    std::cout << "Выполняем изменения..." << std::endl;
    v.sz = 1;
    std::cout << "  -> v.sz (копия) теперь 1" << std::endl;
    rv.sz = 2;
    std::cout << "  -> rv.sz (ссылка) теперь 2" << std::endl;
    if (pv) {
        pv->sz = 3;
        std::cout << "  -> pv->sz (указатель) теперь 3" << std::endl;
    }
    std::cout << "---------------------------" << std::endl;
    std::cout << "ИТОГ ВНУТРИ: v=" << v.sz << ", rv=" << rv.sz << ", pv=" << (pv ? pv->sz : -1) << std::endl;
    std::cout << "--- [ ВЫХОД ИЗ ФУНКЦИИ ] ---\n" << std::endl;
}

/// @brief Функция, увеличивающая переданный int на 1 и возвращающая указатель на него.
/// @param x Ссылка на целое число
/// @return Указатель на это же число
int* copy_referense_pointer::link_func(int &x)
{
    x++;
    return &x;
}

void copy_referense_pointer::Demo(){

    std::cout << "       ------------------------------------ " << std::endl << "       | *** Копия, ссылка, указатель *** | " << std::endl << "       ------------------------------------" << std::endl;

    copy_referense_pointer::Vector val_v;
    copy_referense_pointer::Vector link_v;
    copy_referense_pointer::Vector pointer_v;

    vector_init(val_v, 10);
    vector_init(link_v, 20);
    vector_init(pointer_v, 30);

    std::cout << std::left << std::setw(15) << " Состояние "
         << "| " << std::setw(15) << "val_v (Value)"
         << "| " << std::setw(15) << "link_v (Ref&)"
         << "| " << std::setw(15) << "ptr_v (Ptr*)" << std::endl;
    std::cout << std::string(65, '-') << std::endl;

    std::cout << std::setw(15) << " ДО вызова "
         << "| " << std::setw(15) << val_v.sz << "| " << std::setw(15) << link_v.sz << "| " << std::setw(15)
         << pointer_v.sz << std::endl;

    // Ключевой вызов
    access_to_structure(val_v, link_v, &pointer_v);

    std::cout << std::setw(15) << " ПОСЛЕ вызова "
         << "| " << std::setw(15) << val_v.sz << "| " << std::setw(15) << link_v.sz << "| " << std::setw(15)
         << pointer_v.sz << std::endl;
    std::cout << std::string(65, '-') << std::endl;

    std::cout << " ИНСАЙТЫ ДЛЯ ПАМЯТИ: " << std::endl;
    std::cout << " 1. Value:  Создан новый объект в стеке. Оригинал в безопасности. (Дорого по памяти)"
         << std::endl;
    std::cout << " 2. Ref&:   Функция работает с оригиналом напрямую под другим именем. (Быстро)"
         << std::endl;
    std::cout << " 3. Ptr*:   Передали адрес. Нужно разыменование (->). Можно передать nullptr. (Гибко)"
         << std::endl;

    vector_destroy(val_v);
    vector_destroy(link_v);
    vector_destroy(pointer_v);
}
