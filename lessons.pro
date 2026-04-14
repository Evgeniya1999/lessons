QT = core

CONFIG += c++17 cmdline

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        class_operators.cpp \
        copy_referense_pointer.cpp \
        init_class.cpp \
        main.cpp \
        pointer.cpp \
        quicksort.cpp \
        structures.cpp \
        typing_overloading.cpp
win32 {
    LIBS = -lrpcrt4 -lws2_32 -lole32
}
# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    class_operators.h \
    copy_referense_pointer.h \
    init_class.h \
    pointer.h \
    quicksort.h \
    structures.h \
    typing_overloading.h
