#-------------------------------------------------
#
# Project created by QtCreator 2016-03-27T04:14:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = bd_pdg
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    Joueur.cpp \
    Liste.cpp \
    Personnage.cpp \
    Ajouter.cpp \
    xml.cpp \
    Class_Joueur.cpp \
    Class_Liste.cpp \
    Class_Personnage.cpp \
    systeme.cpp

HEADERS  += mainwindow.h \
    Joueur.h \
    Liste.h \
    Personnage.h \
    Ajouter.h \
    xml.h \
    Class_Joueur.h \
    Class_Liste.h \
    Class_Personnage.h \
    systeme.h

FORMS    += mainwindow.ui \
    Ajouter.ui
