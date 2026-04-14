#ifndef INIT_CLASS_H
#define INIT_CLASS_H

#include "typing_overloading.h"
#include "copy_referense_pointer.h"
#include "class_operators.h"
#include "structures.h"
#include "pointer.h"

#include <QObject>

class init_class : public QObject
{
    Q_OBJECT
public:
    explicit init_class (QObject *parent = nullptr);
    ~init_class();

    void demoTypingOverloading() {
        m_typing->Demo();
    }
    void demoCopyReferensePointer(){
        m_ref_point->Demo();
    }
    void demoClassOperators(){
        m_operator->Demo();
    }
    void demoStructures(){
        m_structures->Demo();
    }
    void demoPointer(){
        m_pointer->Demo();
    }
    int* link_func(int &x);
    void vector_init(copy_referense_pointer::Vector &v, int s);

private:
    typing_overloading *m_typing;
    copy_referense_pointer *m_ref_point;
    class_operators *m_operator;
    structures *m_structures;
    pointer *m_pointer;
};

#endif // INIT_CLASS_H
