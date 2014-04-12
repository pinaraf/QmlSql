#ifndef SQLSIMPLEQUERY_H
#define SQLSIMPLEQUERY_H

#include <QObject>
#include <QSqlError>
#include "sqlquerybinding.h"

class QSqlDatabase;

class SqlSimpleQuery : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString query READ queryString WRITE setQuery NOTIFY queryChanged);
    Q_PROPERTY(QString lastError READ lastErrorText);
    Q_PROPERTY(QQmlListProperty<SqlQueryBinding> bindings READ bindings);

public:
    explicit SqlSimpleQuery(QObject *parent = 0);
    ~SqlSimpleQuery();

    QQmlListProperty<SqlQueryBinding> bindings();

    void setQuery(const QString &query);
    void setQuery(const QString &query, const QSqlDatabase &db);
    QString queryString() const;

    Q_INVOKABLE bool execute();

    QString lastErrorText() const;
signals:
    void queryChanged(const QString &query);

public slots:

private:
    SqlQueryBindings *_bindings;
    QSqlError lastError;
    QString _query;
};

#endif // SQLSIMPLEQUERY_H
