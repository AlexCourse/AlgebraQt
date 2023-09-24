QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
        Algebra.cpp \
        Algebra_node.cpp \
        Derivate.cpp \
        Enumerate.cpp \
        PrintColourConsole.cpp \
        Shunting_yard.cpp \
        Token.cpp \
        main.cpp \
        simplify.cpp \
        vector_cl.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    Algebra.h \
    Algebra_node.h \
    Derivate.h \
    Enumerate.h \
    PrintColourConsole.h \
    Shunting_yard.h \
    Token.h \
    simplify.h \
    vector_cl.h
