QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Models/IntRangeValidator.cpp \
    Models/Vecteur.cpp \
    binarydisplay.cpp \
    main.cpp \
    calculatrice.cpp

HEADERS += \
    Models/IntRangeValidator.h \
    binarydisplay.h \
    calculatrice.h

FORMS += \
    calculatrice.ui

TRANSLATIONS += \
    Calculatrice_fr_FR.ts
CONFIG += lrelease
CONFIG += embed_translations

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
