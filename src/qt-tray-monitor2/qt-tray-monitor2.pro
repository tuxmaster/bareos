
QT += core gui widgets

TARGET = bin/qt-tray-monitor2
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

CONFIG   += c++14 no_keywords

#use gold linker under linux gcc
if (linux-g++) {
    QMAKE_LFLAGS += -fuse-ld=gold
}

#warn on unclean code
gcc {
    QMAKE_CXXFLAGS += -Wold-style-cast
}

UI_DIR = tmp/ui
MOC_DIR = tmp/moc
OBJECTS_DIR = tmp/obj
RCC_DIR = tmp/rcc


TRANSLATIONS = translations/qt-tray-monitor2_de.ts

SOURCES += \
	sources/start.cpp \
	sources/MainWindow.cpp \
    sources/TrayIcon.cpp

HEADERS += \
	sources/MainWindow.h \
    sources/TrayIcon.h

FORMS += \
	forms/MainWindow.ui

# build the translation files
QMAKE_EXTRA_COMPILERS += lrelease
lrelease.input = TRANSLATIONS
lrelease.output = ${QMAKE_FILE_BASE}.qm
lrelease.commands = $$[QT_INSTALL_BINS]/lrelease-qt5 ${QMAKE_FILE_IN} -qm translations/${QMAKE_FILE_BASE}.qm
lrelease.CONFIG  += no_link target_predeps

RESOURCES += \
    Resourcen.qrc
