TEMPLATE = app
CONFIG += console c++17
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += -std=c++17

VERSION=1.0.0.1
QMAKE_TARGET_COMPANY = OpenDBF Test
QMAKE_TARGET_PRODUCT = OpenDBF Test
QMAKE_TARGET_DESCRIPTION = OpenDBF Test
QMAKE_TARGET_COPYRIGHT = OpenDBF Test
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

nx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

isEmpty(TARGET_EXT) {
    win32 {
        #TARGET_CUSTOM_EXT = .exe
    }
    macx {
        TARGET_CUSTOM_EXT = .app
    }
} else {
    TARGET_CUSTOM_EXT = $${TARGET_EXT}
}

CONFIG(release, debug|release):{
     # release
     release: DESTDIR = "release"
     #DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/.executable/$${TARGET}$${TARGET_CUSTOM_EXT}))
     DEPLOY_TARGET = $$shell_quote($$shell_path(/.executable/$${TARGET}$${TARGET_CUSTOM_EXT}))
    MyMakefile = Makefile.Release
 }else:CONFIG(debug, debug|release):{
     # debug
     debug: DESTDIR = "debug"
     #DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/.executable/$${TARGET}$${TARGET_CUSTOM_EXT}))
     DEPLOY_TARGET = $$shell_quote($$shell_path(/.executable/$${TARGET}$${TARGET_CUSTOM_EXT}))
     #DEPLOY_TARGET = $$shell_quote($$shell_path($${OUT_PWD}/$${TARGET}$${TARGET_CUSTOM_EXT}))
     MyMakefile = Makefile.Debug
 }

OBJECTS_DIR = $$DESTDIR/.obj
MOC_DIR = $$DESTDIR/.moc
RCC_DIR = $$DESTDIR/.qrc
UI_DIR = $$DESTDIR/.ui
QMAKE_MAKEFILE = $$DESTDIR/Makefile
MAKEFILE = $$DESTDIR/$$MyMakefile
TARGET = $$DEPLOY_TARGET

win32: LIBS += -L$$PWD/libs/ -ljolLibOpenDBF1
win32: LIBS += -L$$PWD/libs/ -ljolSQLite33

INCLUDEPATH += $$PWD/libs
DEPENDPATH += $$PWD/libs

INCLUDEPATH += $$PWD/include
DEPENDPATH += $$PWD/include

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/libs/jolLibOpenDBF1.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/libs/libjolLibOpenDBF1.a

win32:!win32-g++: PRE_TARGETDEPS += $$PWD/libs/jolSQLite33.lib
else:win32-g++: PRE_TARGETDEPS += $$PWD/libs/libjolSQLite33.a

# MYFILE = $$OUT_PWD/$$DESTDIR/".executable"/$$TARGET
# DEPLOY_COMMAND = windeployqt --qmldir $$PWD
# QMAKE_POST_LINK = $${DEPLOY_COMMAND} $${MYFILE}".exe"

SOURCES += \
    src/dblite.cpp \
    src/main.cpp

HEADERS += \
    src/asprintf.h \
    src/dblite.h

DISTFILES += \
    README.md
