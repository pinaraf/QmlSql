#ifndef QMLSQL_PLUGIN_H
#define QMLSQL_PLUGIN_H

#include <QQmlExtensionPlugin>

class QmlSqlPlugin : public QQmlExtensionPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
    void registerTypes(const char *uri);
    void initializeEngine(QQmlEngine *engine, const char *uri);
};

#endif // QMLSQL_PLUGIN_H

