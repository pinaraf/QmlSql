#ifndef SQLQUERYBINDING_H
#define SQLQUERYBINDING_H

#include <QObject>
#include <QVariant>
#include <QQmlListProperty>

class QSqlQuery;

class SqlQueryBinding : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QString name READ name WRITE setName NOTIFY nameChanged);
    Q_PROPERTY(QVariant value READ value WRITE setValue NOTIFY valueChanged);

public:
    explicit SqlQueryBinding(QObject *parent = 0);

    QString name() const { return _name; }
    QVariant value() const { return _value; }

    void setName(const QString &name) { _name = name; emit nameChanged(name); }
    void setValue(const QVariant &val) { _value = val; emit valueChanged(val); }

private:
    QString _name;
    QVariant _value;

signals:
    void nameChanged (const QString &name);
    void valueChanged (const QVariant &value);
};


class SqlQueryBindings : public QObject
{
    Q_OBJECT
public:
    explicit SqlQueryBindings(QObject *parent = 0);

    QQmlListProperty<SqlQueryBinding> bindings();
    void bindToQuery(QSqlQuery *q);
signals:
    void bindingAdded(SqlQueryBinding *item);
private:
    QList<SqlQueryBinding*> _bindingsList;
};

#endif // SQLQUERYBINDING_H
