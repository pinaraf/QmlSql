#include "sqlquerymodel.h"
#include <QSqlRecord>
#include <QSqlField>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlDriver>
#include <QtQml>

#include "sqlnotificationdispatcher.h"


SqlQueryModel::SqlQueryModel(QObject *parent) :
    QSqlQueryModel(parent), _enabled(true)
{
    qDebug() << "constructor called";
    _bindings = new SqlQueryBindings(this);
    connect(_bindings, SIGNAL(bindingAdded(SqlQueryBinding*)), this, SLOT(connectBinding(SqlQueryBinding*)));
    connect(this, SIGNAL(enabledChanged()), this, SLOT(refreshQuery()));
}

SqlQueryModel::~SqlQueryModel()
{
    if (!_refreshNotification.isEmpty())
    {
        QSqlDriver *driver = QSqlDatabase::database().driver(); //TODO
        driver->unsubscribeFromNotification(_refreshNotification);
    }
}

void SqlQueryModel::setQuery(const QString &query)
{
    this->setQuery(query, QSqlDatabase::database());
}

void SqlQueryModel::setQuery(const QString &query, const QSqlDatabase &db)
{
    _query = query;
    this->refreshQuery(db);
}


QQmlListProperty<SqlQueryBinding> SqlQueryModel::bindings()
{
    return _bindings->bindings();
}

void SqlQueryModel::connectBinding(SqlQueryBinding *item)
{
    qDebug() << "Connecting bindings";
    connect(item, SIGNAL(valueChanged(QVariant)), this, SLOT(refreshQuery()));
    connect(item, SIGNAL(nameChanged(QString)), this, SLOT(refreshQuery()));
}

void SqlQueryModel::refreshQuery()
{
    this->refreshQuery(QSqlDatabase::database());
}

void SqlQueryModel::refreshQuery(const QSqlDatabase &db)
{
    qDebug() << "RefreshQuery called";
    if (_enabled)
    {
        QSqlQuery q(db);
        q.prepare(_query);
        _bindings->bindToQuery(&q);
        q.exec();
        QSqlQueryModel::setQuery(q);
    }
    else
    {
        qDebug() << "on a disabled query...";
    }
}

QString SqlQueryModel::queryString() const
{
    return _query;
}

void SqlQueryModel::setRefreshNotification(const QString &refreshNotification)
{
    SqlNotificationDispatcher *dispatcher = SqlNotificationDispatcher::getInstance();
    QSqlDatabase db = QSqlDatabase::database(); // TODO
    if (!_refreshNotification.isEmpty())
    {
        dispatcher->unregisterNotification(db, _refreshNotification, this, "refreshQuery");
    }
    dispatcher->registerNotification(db, refreshNotification, this, "refreshQuery");
    _refreshNotification = refreshNotification;
    emit(refreshNotificationChanged(refreshNotification));
}

void SqlQueryModel::notificationReceived(const QString &notificationName)
{
    if (notificationName == _refreshNotification)
        this->refreshQuery();
}

QHash<int, QByteArray> SqlQueryModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    for( int i = 0; i < record().count(); i++) {
        roles[Qt::UserRole + 1 + i] = record().fieldName(i).toLocal8Bit();
    }
    return roles;
}

QVariant SqlQueryModel::data(const QModelIndex &index, int role) const
{
    QVariant value = QSqlQueryModel::data(index, role);
    if(role < Qt::UserRole)
    {
        value = QSqlQueryModel::data(index, role);
    }
    else
    {
        int columnIdx = role - Qt::UserRole - 1;
        QModelIndex modelIndex = this->index(index.row(), columnIdx);
        value = QSqlQueryModel::data(modelIndex, Qt::DisplayRole);
    }
    return value;
}

QVariant SqlQueryModel::getValue (int row, QString columnName) const
{
    for( int columnId = 0; columnId < record().count(); columnId++) {
        if (record().fieldName(columnId) == columnName) {
            QModelIndex idx = this->index(row, columnId);
            return QSqlQueryModel::data(idx, Qt::DisplayRole);
        }
    }
    return QVariant();
}

