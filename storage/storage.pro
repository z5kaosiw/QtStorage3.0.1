QT += widgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
qtHaveModule(printsupport): QT += printsupport
HEADERS       = mainwindow.h \
    comboboxdelegate.h \
    register.h \
    memorandum.h \
    pieview.h \
    button.h \
    calculator.h \
    login.h
QT       += core gui
QT       += sql
TARGET = storage
TEMPLATE = app

RC_FILE = logo.rc
SOURCES += main.cpp\
        storage.cpp \
    comboboxdelegate.cpp \
    register.cpp \
    memorandum.cpp \
    pieview.cpp \
    button.cpp \
    calculator.cpp \
    login.cpp

HEADERS  += storage.h

RESOURCES += \
    images.qrc \
    Charts.qrc

# install
target.path = $$[QT_INSTALL_EXAMPLES]/widgets/mainwindows/application
INSTALLS += target

FORMS += \
    register.ui

DISTFILES +=


