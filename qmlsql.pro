TEMPLATE = lib
TARGET = QmlSql
QT += qml quick sql
CONFIG += qt plugin c++11

TARGET = $$qtLibraryTarget($$TARGET)
uri = com.sql

# Input
SOURCES += \
    qmlsql_plugin.cpp \
    sqlquerymodel.cpp \
    sqlquerybinding.cpp \
    sqlnotificationdispatcher.cpp \
    sqlsimplequery.cpp \
    sqldatabase.cpp

HEADERS += \
    qmlsql_plugin.h \
    sqlquerymodel.h \
    sqlquerybinding.h \
    sqlnotificationdispatcher.h \
    sqlsimplequery.h \
    sqldatabase.h

OTHER_FILES = qmldir

!equals(_PRO_FILE_PWD_, $$OUT_PWD) {
    copy_qmldir.target = $$OUT_PWD/qmldir
    copy_qmldir.depends = $$_PRO_FILE_PWD_/qmldir
    copy_qmldir.commands = $(COPY_FILE) \"$$replace(copy_qmldir.depends, /, $$QMAKE_DIR_SEP)\" \"$$replace(copy_qmldir.target, /, $$QMAKE_DIR_SEP)\"
    QMAKE_EXTRA_TARGETS += copy_qmldir
    PRE_TARGETDEPS += $$copy_qmldir.target
}

qmldir.files = qmldir
unix {
    installPath = $$[QT_INSTALL_QML]/$$replace(uri, \\., /)
    qmldir.path = $$installPath
    target.path = $$installPath
    INSTALLS += target qmldir
}

