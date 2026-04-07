// =================================================================================================
/// @mainpage Учебный справочник по C++
///
/// Этот файл содержит коллекцию примеров для изучения:
/// - перегрузки функций и разрешения типов,
/// - передачи параметров (копия, ссылка, указатель),
/// - работы с памятью (куча, структура Vector),
/// - операторов классов (+, ==),
/// - указателей, арифметики указателей,
/// - битовых операций, IP-заголовков,
/// - стандартных алгоритмов (equal) и GUID,
/// - циклов по матрицам, switch,
/// - emplace_back и ссылок на элементы вектора.
///
/// @author Учебный код с комментариями Doxygen для Qt Creator
/// @date 2026
// =================================================================================================

#include <QCoreApplication>
#include <algorithm>
#include <bitset>
#include <charconv>
#include <cstdlib> // malloc, calloc, realloc, free
#include <cstring> // memcpy
#include <iomanip>
#include <iostream>
#include <memory> // unique_ptr
#include <optional>
#include <vector>
#include <winsock2.h> // только Windows, для CoCreateGuid
#include <ws2tcpip.h>

// ------------------------- Пространства имён ---------------------------------
using namespace std;
using std::nullopt;
using std::optional;

// =================================================================================================
#pragma region Структуры_и_классы
// =================================================================================================

/// @brief Структура задачи (todo-элемент).
/// @details Содержит идентификатор, название и статус выполнения.
struct Task
{
    int id;            ///< Уникальный номер задачи
    std::string title; ///< Описание задачи
    bool is_done;      ///< true — выполнено, false — ещё нет
};

/// @brief Класс студента с именем, отчеством, фамилией.
/// @details Демонстрирует перегрузку операторов `+` (добавление строки к отчеству)
///          и `==` (сравнение всех полей).
class Student
{
private:
    string name;       ///< Имя
    string patronymic; ///< Отчество
    string last_name;  ///< Фамилия
public:
    /// @brief Конструктор, инициализирующий все поля.
    Student(string n, string p, string l);

    /// @brief Геттер имени.
    string GetName() const;
    /// @brief Геттер отчества.
    string GetPatronymic() const;
    /// @brief Геттер фамилии.
    string GetLastName() const;

    /// @brief Оператор +: возвращает нового студента, дописывая строку к отчеству.
    /// @param n Строка, добавляемая в конец отчества.
    /// @return Новый объект Student с изменённым отчеством.
    Student operator+(string n) const { return Student(name, patronymic + n, last_name); }

    /// @brief Оператор равенства: сравнивает все три поля.
    /// @return true, если все поля совпадают.
    bool operator==(const Student &other) const
    {
        return (name == other.name && patronymic == other.patronymic
                && last_name == other.last_name);
    }
};

// Реализация методов Student
Student::Student(string n, string p, string l)
    : name(n)
    , patronymic(p)
    , last_name(l)
{}
string Student::GetName() const
{
    return name;
}
string Student::GetPatronymic() const
{
    return patronymic;
}
string Student::GetLastName() const
{
    return last_name;
}

#pragma endregion

// =================================================================================================
#pragma region Ручное_управление_памятью_структура_Vector
// =================================================================================================

/// @brief Самодельный вектор чисел double (учебный пример).
/// @details Хранит указатель на массив в куче и размер.
///          Показывает необходимость ручного освобождения памяти.
struct Vector
{
    double *elem = nullptr; ///< Указатель на динамический массив
    int sz = 0;             ///< Количество элементов
};

/// @brief Инициализирует вектор заданным размером, выделяя память в куче.
/// @param v  Ссылка на структуру Vector
/// @param s  Требуемый размер
void vector_init(Vector &v, int s)
{
    if (v.elem)
        delete[] v.elem;    // очистка предыдущего (безопасно)
    v.elem = new double[s]; // выделение
    v.sz = s;
}

/// @brief Освобождает память вектора и обнуляет указатель с размером.
/// @param v Ссылка на структуру Vector
void vector_destroy(Vector &v)
{
    if (v.elem)
        delete[] v.elem;
    v.elem = nullptr;
    v.sz = 0;
}

#pragma endregion

// =================================================================================================
#pragma region Передача_параметров_копия_ссылка_указатель
// =================================================================================================

/// @brief Демонстрация различий передачи параметров.
/// @param v   Копия структуры (изменения не видны снаружи)
/// @param rv  Ссылка на оригинал (изменяет внешний объект)
/// @param pv  Указатель на оригинал (требует разыменования, может быть nullptr)
void access_to_structure(Vector v, Vector &rv, Vector *pv)
{
    cout << "\n--- [ ВХОД В ФУНКЦИЮ ] ---" << endl;
    cout << "Адрес v (копия):    " << &v << " | sz: " << v.sz << endl;
    cout << "Адрес rv (ссылка): " << &rv << " | sz: " << rv.sz << endl;
    cout << "Адрес *pv (указатель): " << pv << " | sz: " << (pv ? pv->sz : -1) << endl;
    cout << "---------------------------" << endl;
    cout << "Выполняем изменения..." << endl;
    v.sz = 1;
    cout << "  -> v.sz (копия) теперь 1" << endl;
    rv.sz = 2;
    cout << "  -> rv.sz (ссылка) теперь 2" << endl;
    if (pv) {
        pv->sz = 3;
        cout << "  -> pv->sz (указатель) теперь 3" << endl;
    }
    cout << "---------------------------" << endl;
    cout << "ИТОГ ВНУТРИ: v=" << v.sz << ", rv=" << rv.sz << ", pv=" << (pv ? pv->sz : -1) << endl;
    cout << "--- [ ВЫХОД ИЗ ФУНКЦИИ ] ---\n" << endl;
}

/// @brief Функция, увеличивающая переданный int на 1 и возвращающая указатель на него.
/// @param x Ссылка на целое число
/// @return Указатель на это же число
int *link_func(int &x)
{
    x++;
    return &x;
}

#pragma endregion

// =================================================================================================
#pragma region Перегрузка_функций_и_разрешение_типов
// =================================================================================================

/// @overload void my_sqrt(float x)
void my_sqrt(float x)
{ /* заглушка */
}

/// @overload void my_sqrt(double x)
void my_sqrt(double x)
{ /* заглушка */
}

/// @brief Вспомогательная функция для преобразования bool в строку "true"/"false".
/// @param b Логическое значение
/// @return Строковое представление
string bool_to_string(bool b)
{
    return b ? "true" : "false";
}

#pragma endregion

// =================================================================================================
#pragma region Основная_функция_main
// =================================================================================================

const int x_v = 5; ///< Глобальная константа для демонстрации размера массива

int main()
{
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 1. Типизация и перегрузки
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    cout << "       ---------------------------------- " << endl << "       | *** Типизация и перегрузки *** | " << endl << "       ----------------------------------" << endl;

    double da = 9.0;
    float fla = 9.0f;
    int i = 42;
    short s_val = 10;

    cout << left << setw(25) << " Вход (Аргумент) " << setw(20) << " Тип (typeid) "
         << " Результат / Статус компиляции " << endl;
    cout << string(85, '-') << endl;

    cout << setw(25) << "da (variable)" << setw(20) << typeid(da).name() << "Вызов: my_sqrt(double)"
         << endl;
    cout << setw(25) << "fla (variable)" << setw(20) << typeid(fla).name()
         << "Вызов: my_sqrt(float)" << endl;
    cout << setw(25) << "9.0 (literal)" << setw(20) << typeid(9.0).name()
         << "Вызов: my_sqrt(double) [Default]" << endl;
    cout << setw(25) << "9.0f (literal)" << setw(20) << typeid(9.0f).name()
         << "Вызов: my_sqrt(float) [Suffix]" << endl;
    cout << string(85, '-') << endl;

    cout << setw(25) << "i (int variable)" << setw(20) << typeid(i).name()
         << "ОШИБКА: Ambiguous (float? double?)" << endl;
    cout << setw(25) << "s_val (short variable)" << setw(20) << typeid(s_val).name()
         << "ОШИБКА: Ambiguous (float? double?)" << endl;
    cout << setw(25) << "100 (int literal)" << setw(20) << typeid(100).name()
         << "ОШИБКА: Ambiguous (float? double?)" << endl;
    cout << string(85, '-') << endl;

    cout << setw(25) << "static_cast<float>(i)" << setw(20) << "float (forced)"
         << "Вызов: my_sqrt(float) [Manual]" << endl;
    cout << setw(25) << "static_cast<double>(s_val)" << setw(20) << "double (forced)"
         << "Вызов: my_sqrt(double) [Manual]" << endl;
    cout << string(85, '-') << endl;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 2. Копия, ссылка, указатель (демонстрация)
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    cout << "       ------------------------------------ " << endl << "       | *** Копия, ссылка, указатель *** | " << endl << "       ------------------------------------" << endl;


    Vector val_v;
    Vector link_v;
    Vector pointer_v;

    vector_init(val_v, 10);
    vector_init(link_v, 20);
    vector_init(pointer_v, 30);

    cout << left << setw(15) << " Состояние "
         << "| " << setw(15) << "val_v (Value)"
         << "| " << setw(15) << "link_v (Ref&)"
         << "| " << setw(15) << "ptr_v (Ptr*)" << endl;
    cout << string(65, '-') << endl;

    cout << setw(15) << " ДО вызова "
         << "| " << setw(15) << val_v.sz << "| " << setw(15) << link_v.sz << "| " << setw(15)
         << pointer_v.sz << endl;

    // Ключевой вызов
    access_to_structure(val_v, link_v, &pointer_v);

    cout << setw(15) << " ПОСЛЕ вызова "
         << "| " << setw(15) << val_v.sz << "| " << setw(15) << link_v.sz << "| " << setw(15)
         << pointer_v.sz << endl;
    cout << string(65, '-') << endl;

    cout << " ИНСАЙТЫ ДЛЯ ПАМЯТИ: " << endl;
    cout << " 1. Value:  Создан новый объект в стеке. Оригинал в безопасности. (Дорого по памяти)"
         << endl;
    cout << " 2. Ref&:   Функция работает с оригиналом напрямую под другим именем. (Быстро)"
         << endl;
    cout << " 3. Ptr*:   Передали адрес. Нужно разыменование (->). Можно передать nullptr. (Гибко)"
         << endl;

    vector_destroy(val_v);
    vector_destroy(link_v);
    vector_destroy(pointer_v);

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 3. Операторы классов (Student)
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    cout << "       ---------------------------------" << endl << "       | *** Применение операторов *** |" << endl <<"       ---------------------------------" << endl;


    Student s1("Иван", "Иванович", "Иванов");
    Student s2 = s1 + " (монтажник)";

    cout << left << setw(20) << " Действие " << "| " << "Результат" << endl;
    cout << string(60, '-') << endl;
    cout << setw(20) << "s1 (Оригинал):" << "| " << s1.GetPatronymic() << endl;
    cout << setw(20) << "s2 (Результат +):" << "| " << s2.GetPatronymic() << endl;
    cout << string(60, '-') << endl;

    cout << setw(20) << "Сравнение (s1 == s2):";
    if (s1 == s2)
        cout << "| ОДИНАКОВЫ (ошибка логики?)" << endl;
    else
        cout << "| РАЗНЫЕ (оператор работает верно)" << endl;

    cout << setw(20) << "Сравнение (s1 == s1):";
    if (s1 == s1)
        cout << "| ОДИНАКОВЫ" << endl;
    cout << string(60, '-') << endl;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 4. Структуры (метафора рюкзака)
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    cout << "       ---------------------" << endl << "       | *** Структуры *** |" << endl <<"       ---------------------" << endl;

    Vector v;
    cout << left << setw(25) << " Этап " << "| " << "Состояние памяти" << endl;
    cout << string(65, '-') << endl;
    cout << setw(25) << "После создания:" << "| " << (v.elem == nullptr ? "nullptr" : "есть мусор")
         << ", sz: " << v.sz << endl;
    vector_init(v, 5);
    cout << setw(25) << "После vector_init(5):" << "| " << "Адрес в heap: " << v.elem
         << ", sz: " << v.sz << endl;
    delete[] v.elem;
    v.elem = nullptr;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 5. Указатели: обход строки
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    cout << "        ---------------------" << endl << "        | *** Указатели *** |" << endl <<"        ---------------------" << endl;

    char str[] = "12345";
    char *p = str;
    char target = '3';
    int matches = 0;

    cout << left << setw(20) << "Адрес p"
         << "| " << setw(10) << "*p"
         << "| " << "Состояние matches" << endl;
    cout << string(60, '-') << endl;
    if (p != nullptr) {
        for (; *p != '\0'; ++p) {
            bool found = (*p == target);
            if (found)
                ++matches;
            cout << setw(20) << (void *) p << "| " << setw(10) << *p << "| "
                 << (found ? " НАЙДЕНО! -> " : " ") << matches << endl;
        }
    }
    cout << string(60, '-') << endl;
    cout << "Итого совпадений для '" << target << "': " << matches << endl;

    // Дополнительные иллюстрации ссылок и указателей
    int y = 5;
    int &t = y;
    t = 7;
    int *a = &y;
    *a = 3;
    y = 1;
    cout << y << " " << &y << " " << t << " " << *a << endl;

    int arr[10];
    std::cout << sizeof(int) << std::endl;
    std::cout << sizeof(arr) << std::endl;
    std::cout << sizeof(arr[0]) << std::endl;

    int value = 1;
    int *val = link_func(value);
    cout << *val << " " << value << endl;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 6. Алгоритмы equal, GUID
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    vector<int> array1 = {1, 2, 3, 5, 4};
    vector<int> array2 = {1, 2, 3, 4, 5};
    bool isEqual = equal(array1.begin(), array1.end(), array2.begin());
    cout << bool_to_string(isEqual) << endl;

    uint8_t guid1[16];
    HRESULT hr1 = CoCreateGuid(reinterpret_cast<GUID *>(guid1));
    if (FAILED(hr1)) {
        cerr << "CoCreateGuid failed" << endl;
        return {};
    }
    uint8_t guid2[16];
    HRESULT hr2 = CoCreateGuid(reinterpret_cast<GUID *>(guid2));
    if (FAILED(hr2)) {
        cerr << "CoCreateGuid failed" << endl;
        return {};
    }
    bool isEqualGuid = equal(begin(guid1), end(guid1), begin(guid2));
    cout << bool_to_string(isEqualGuid) << endl;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 7. Битовые операции и IP-заголовок
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    uint8_t first_byte = 0x45;
    uint8_t ihl = first_byte & 0x0F;
    size_t ip_header_len = ihl * 4;
    std::cout << "First byte: 0x" << std::hex << (int) first_byte << std::dec << std::endl;
    std::cout << "IHL (raw value): " << (int) ihl << std::endl;
    std::cout << "IP Header Length in bytes: " << ip_header_len << std::endl;

    int v4 = 4, v8 = 8, v16 = 16;
    cout << "4  | bit: " << bitset<8>(v4) << " | & 0x0F: " << bitset<8>(v4 & 0x0F) << endl;
    cout << "8  | bit: " << bitset<8>(v8) << " | & 0x0F: " << bitset<8>(v8 & 0x0F) << endl;
    cout << "16 | bit: " << bitset<8>(v16) << " | & 0x0F: " << bitset<8>(v16 & 0x0F)
         << " (обнулился!)" << endl;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 8. Обход строки через указатель (альтернативный)
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    auto s = "Hello";
    while (*s != '\0') {
        std::cout << *s << " ";
        s++;
    }
    cout << endl;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 9. Двумерный массив (матрица)
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int matrix[5][10];
    int count = 1;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 10; j++) {
            matrix[i][j] = 10 + count++;
        }
    }
    // Диапазонные for (демонстрация)
    for (int (&row)[10] : matrix) {
        for (int(&el) : row) {
            el = 1;
        }
        for (int(el) : row) {
            el = 2;
        } // Обратите внимание: это не меняет оригинал, т.к. el – копия
    }
    for (int (&row)[10] : matrix) {
        for (int(el) : row) {
            cout << el << " ";
        }
        cout << endl;
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 10. Switch без break (fall-through)
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int x_null_one_helloword = 0;
    switch (x_null_one_helloword) {
    case 1:
        cout << "Один" << endl;
    case 0:
        cout << "Нуль" << endl;
    case 2:
        cout << "Привет мир" << endl;
    }

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 11. Массив переменного размера (VLA) — расширение GCC, осторожно
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int x_v_arr[x_v]; // использует константу x_v = 5
    // int fun(int x_v);  // объявление функции — закомментировано, чтобы избежать конфликта

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 12. Пример с emplace_back и ссылкой на элемент вектора
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    std::vector<Task> todo_list;
    todo_list.emplace_back();      // создаёт объект Task прямо внутри вектора
    Task &task = todo_list.back(); // ссылка на последний элемент (без копирования)
    task.id = 1;
    task.title = "Дописать пинг на С++";
    task.is_done = false;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    // 13. Получение цифр числа
    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
    int x_num = 4569;
    int d1 = x_num % 10;
    int d2 = (x_num / 10) % 10;
    int d3 = (x_num / 100) % 10;
    int d4 = (x_num / 1000) % 10;
    cout << d1 << d2 << d3 << d4 << endl;

    return 0;
}
#pragma endregion
