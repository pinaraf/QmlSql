#include "qmlsql_plugin.h"
#include "sqlquerymodel.h"
#include "sqlquerybinding.h"
#include "sqlsimplequery.h"
#include "sqldatabase.h"

#include <qqml.h>
#include <QQmlEngine>
#include <QQmlContext>
#include <QDebug>

void QmlSqlPlugin::registerTypes(const char *uri)
{
    qDebug() << "registerTypes ? adding database types";
    // @uri com.sql
    qmlRegisterType<SqlQueryModel>(uri, 1, 0, "SqlQueryModel");
    qmlRegisterType<SqlQueryBinding>(uri, 1, 0, "SqlQueryBinding");
    qmlRegisterType<SqlSimpleQuery>(uri, 1, 0, "SqlSimpleQuery");
}

void QmlSqlPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    Q_UNUSED(uri);
    qDebug() << "Initializing engine ? adding database property";
    engine->rootContext()->setContextProperty("database", new SqlDatabase(engine));
}
