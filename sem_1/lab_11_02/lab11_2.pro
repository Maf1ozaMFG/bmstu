TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        infomethods.c \
        main.c \
        menumethods.c \
        mymalloc.c \
        mystring.c

HEADERS += \
    infomethods.h \
    menumethods.h \
    mymalloc.h \
    mystring.h
