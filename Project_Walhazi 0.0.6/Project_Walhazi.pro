QT       += core gui sql
QT       += charts
QT       += widgets printsupport
QT       += core gui network
<<<<<<<< HEAD:Project_Walhazi 0.0.6/Project_Walhazi.pro
QT       += serialport
========
>>>>>>>> 017f68f8ac2802c43806d0130038edb031543f35:Project_Walhazi 0.0.3/AAAAA/Dream-Beaver-main/Project_Walhazi 0.0.5/Project_Walhazi.pro

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11


# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    barcodeprinter.cpp \
    databaseconnection.cpp \
    entreprneur.cpp \
    equipments.cpp \
    formation.cpp \
    main.cpp \
    mainwindow.cpp \
    project.cpp \
<<<<<<<< HEAD:Project_Walhazi 0.0.6/Project_Walhazi.pro
========
    pub.cpp \
>>>>>>>> 017f68f8ac2802c43806d0130038edb031543f35:Project_Walhazi 0.0.3/AAAAA/Dream-Beaver-main/Project_Walhazi 0.0.5/Project_Walhazi.pro
    search_engine.cpp \
    sponsors.cpp

HEADERS += \
    barcodeprinter.h \
    databaseconnection.h \
    entreprneur.h \
    equipments.h \
    formation.h \
    mainwindow.h \
    project.h \
<<<<<<<< HEAD:Project_Walhazi 0.0.6/Project_Walhazi.pro
========
    pub.h \
>>>>>>>> 017f68f8ac2802c43806d0130038edb031543f35:Project_Walhazi 0.0.3/AAAAA/Dream-Beaver-main/Project_Walhazi 0.0.5/Project_Walhazi.pro
    search_engine.h \
    sponsors.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    Resources.qrc

DISTFILES += \
    home (2).svg
