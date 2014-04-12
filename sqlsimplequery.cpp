#include "sqlsimplequery.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QDebug>

SqlSimpleQuery::SqlSimpleQuery(QObject *parent) :
    QObject(parent)
{
    _bindings = new SqlQueryBindings(this);
}

SqlSimpleQuery::~SqlSimpleQuery()
{
    if (_bindings)
        _bindings->deleteLater();
}

QQmlListProperty<SqlQueryBinding> SqlSimpleQuery::bindings()
{
    return _bindings->bindings();
}

void SqlSimpleQuery::setQuery(const QString &query)
{
    _query = query;
    emit (queryChanged(query));
}

QString SqlSimpleQuery::queryString() const
{
    return _query;
}

bool SqlSimpleQuery::execute()
{
    QSqlQuery q;
    q.prepare(_query);
    _bindings->bindToQuery(&q);
    bool result = q.exec();
    lastError = q.lastError();
    return result;
}

QString SqlSimpleQuery::lastErrorText() const
{
    return lastError.text();
}
