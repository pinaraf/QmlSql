#ifndef SQLQUERYMODEL_H
#define SQLQUERYMODEL_H

#include <QSqlQueryModel>
#include <QQmlListProperty>

#include "sqlquerybinding.h"

class SqlQueryModel : public QSqlQueryModel
{
    Q_OBJECT

    Q_PROPERTY(QString query READ queryString WRITE setQuery NOTIFY queryChanged);
    Q_PROPERTY(QString refreshNotification READ refreshNotification
                                           WRITE setRefreshNotification
                                           NOTIFY refreshNotificationChanged);

    Q_PROPERTY(QQmlListProperty<SqlQueryBinding> bindings READ bindings);

    Q_PROPERTY(bool enabled READ isEnabled WRITE setEnabled NOTIFY enabledChanged);

public:
    explicit SqlQueryModel(QObject *parent = 0);
    ~SqlQueryModel();

    bool isEnabled() const { return _enabled; }
    void setEnabled (bool enabled) { _enabled = enabled; emit enabledChanged(); }

    void setQuery(const QString &query);
    void setQuery(const QString &query, const QSqlDatabase &db);
    QString queryString() const;

    QVariant data(const QModelIndex &index, int role) const;
    virtual QHash<int, QByteArray> roleNames() const;

    Q_INVOKABLE QVariant getValue (int row, QString columnName) const;

    QQmlListProperty<SqlQueryBinding> bindings();


    void setRefreshNotification(const QString &refreshNotification);
    QString refreshNotification() const { return _refreshNotification; }

signals:
    void queryChanged(const QString &query);

    void enabledChanged();

    void refreshNotificationChanged(const QString &refreshNotification);

public slots:
    void refreshQuery();

private slots:
    void connectBinding(SqlQueryBinding *item);
    void notificationReceived(const QString &notificationName);

private:
    void refreshQuery(const QSqlDatabase &db);

    SqlQueryBindings *_bindings;
    QString _query;
    QString _refreshNotification;
    bool _enabled;
};

#endif // SQLQUERYMODEL_H
