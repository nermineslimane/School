QT       += core gui
QT       += sql
QT       += printsupport
QT       += multimedia
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    classroom.cpp \
    db_connection.cpp \
    main.cpp \
    menu.cpp \
    module.cpp \
    student.cpp \
    teacher.cpp

HEADERS += \
    classroom.h \
    db_connection.h \
    menu.h \
    module.h \
    student.h \
    teacher.h

FORMS += \
    menu.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    images.qrc
LIBS += -LC:\OpenSSL-Win64\lib
INCLUDEPATH += C:\OpenSSL-Win64\include
