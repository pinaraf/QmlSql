#include "qmlsql_plugin.h"
#include "sqlquerymodel.h"
#include "sqlquerybinding.h"
#include "sqlsimplequery.h"
#include "sqldatabase.h"

#include <qqml.h>
#include <QQmlEngine>

void QmlSqlPlugin::registerTypes(const char *uri)
{
    // @uri com.sql
    qmlRegisterType<SqlQueryModel>(uri, 1, 0, "SqlQueryModel");
    qmlRegisterType<SqlQueryBinding>(uri, 1, 0, "SqlQueryBinding");
    qmlRegisterType<SqlSimpleQuery>(uri, 1, 0, "SqlSimpleQuery");
}

void QmlSqlPlugin::initializeEngine(QQmlEngine *engine, const char *uri)
{
    engine->globalObject().setProperty("database", engine->newQObject(new SqlDatabase(this)));
}
