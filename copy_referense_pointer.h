#ifndef COPY_REFERENSE_POINTER_H
#define COPY_REFERENSE_POINTER_H

class copy_referense_pointer
{
public:
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
    #pragma endregion

    copy_referense_pointer();
    void Demo();
    static int* link_func(int &x);
    static void vector_init(Vector &v, int s);
    static void vector_destroy(Vector &v);
    static void access_to_structure(Vector v, Vector &rv, Vector *pv);

};

#endif // COPY_REFERENSE_POINTER_H
