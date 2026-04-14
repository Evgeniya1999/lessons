#include "init_class.h"
#include "typing_overloading.h"
#include "class_operators.h"
#include "structures.h"
#include "pointer.h"

init_class::init_class(QObject *parent) : QObject(parent) {

    m_typing = new typing_overloading();
    m_ref_point = new copy_referense_pointer();
    m_operator = new class_operators();
    m_structures = new structures();
    m_pointer = new pointer();
}

init_class::~init_class(){
    delete m_typing;
    delete m_ref_point;
    delete m_operator;
    delete m_structures;
    delete m_pointer;
}

int* init_class::link_func(int &x){
    return copy_referense_pointer::link_func(x);
}
void init_class::vector_init(copy_referense_pointer::Vector &v, int s) {
    return copy_referense_pointer::vector_init(v, s);
}
