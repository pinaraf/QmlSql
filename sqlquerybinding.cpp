#include "sqlquerybinding.h"
#include <QDebug>
#include <QSqlQuery>

SqlQueryBinding::SqlQueryBinding(QObject *parent) :
    QObject(parent)
{
    qDebug() << "constructor called for SqlQueryBinding";
}



SqlQueryBindings::SqlQueryBindings(QObject *parent) :
    QObject(parent)
{
    qDebug() << "constructor called for SqlQueryBindings";
}


QQmlListProperty<SqlQueryBinding> SqlQueryBindings::bindings()
{
    QQmlListProperty<SqlQueryBinding>::CountFunction counter = [=] (QQmlListProperty<SqlQueryBinding> *prop) -> int {
        return (static_cast<QList<SqlQueryBinding*>*>(prop->data))->size();
    };
    QQmlListProperty<SqlQueryBinding>::AtFunction at      = [=] (QQmlListProperty<SqlQueryBinding> *prop, int idx) -> SqlQueryBinding* {
        return (static_cast<QList<SqlQueryBinding*>*>(prop->data))->at(idx);
    };
    QQmlListProperty<SqlQueryBinding>::ClearFunction clear   = [=] (QQmlListProperty<SqlQueryBinding> *prop) {
        qDeleteAll(*(static_cast<QList<SqlQueryBinding*>*>(prop->data)));
        (static_cast<QList<SqlQueryBinding*>*>(prop->data))->clear();
    };
    QQmlListProperty<SqlQueryBinding>::AppendFunction append      = [=] (QQmlListProperty<SqlQueryBinding> *prop, SqlQueryBinding *item) {
        (static_cast<QList<SqlQueryBinding*>*>(prop->data))->append(item);
        emit(qobject_cast<SqlQueryBindings*>(prop->object)->bindingAdded(item));
        return;
    };
    return QQmlListProperty<SqlQueryBinding>(this, &this->_bindingsList, append, counter, at, clear);
}

void SqlQueryBindings::bindToQuery(QSqlQuery *q)
{
    foreach (SqlQueryBinding *binding, _bindingsList)
    {
        qDebug() << "Binding with " << binding->name() << " for " << binding->value();
        q->bindValue(binding->name(), binding->value());
    }
}
