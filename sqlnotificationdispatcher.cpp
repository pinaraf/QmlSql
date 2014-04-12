#include "sqlnotificationdispatcher.h"

#include <QSqlDatabase>

SqlNotificationDispatcher::SqlNotificationDispatcher(QObject *parent) :
    QObject(parent), notificationMapping()
{
}

SqlNotificationDispatcher* SqlNotificationDispatcher::getInstance()
{
    if (instance == nullptr)
    {
        instance = new SqlNotificationDispatcher();
    }
    return instance;
}

void SqlNotificationDispatcher::registerNotification(const QSqlDatabase &database, const QString &notificationName, QObject *target, const QString &signal)
{
    QPair<QSqlDriver *, QString> dbSignal(database.driver(), notificationName);
    QList<QPair<QObject*, QString>> mappedTargets;
    bool needToRegister = true;
    if (this->notificationMapping.contains(dbSignal))
    {
        mappedTargets = this->notificationMapping[dbSignal];
        needToRegister = false;
    }
    mappedTargets.append(QPair<QObject*, QString>(target, signal));
    notificationMapping[dbSignal] = mappedTargets;
    if (needToRegister)
    {
        database.driver()->subscribeToNotification(notificationName);
        connect(database.driver(), SIGNAL(notification(QString)), this, SLOT(notificationReceived(QString)));
    }
}

void SqlNotificationDispatcher::unregisterNotification(const QSqlDatabase &database, const QString &notificationName, QObject *target, const QString &signal)
{
    QPair<QSqlDriver *, QString> dbSignal(database.driver(), notificationName);
    if (this->notificationMapping.contains(dbSignal))
    {
        QList<QPair<QObject*, QString>> mappedTargets = notificationMapping[dbSignal];
        QPair<QObject*, QString> targetSignal(target, signal);
        mappedTargets.removeAll(targetSignal);
        if (mappedTargets.size() == 0)
            database.driver()->unsubscribeFromNotification(notificationName);
        notificationMapping[dbSignal] = mappedTargets;
    }
}

void SqlNotificationDispatcher::notificationReceived(const QString &name)
{
    QSqlDriver *driver = qobject_cast<QSqlDriver*>(QObject::sender());
    QPair<QSqlDriver *, QString> dbSignal(driver, name);
    if (notificationMapping.contains(dbSignal))
    {
        for (QPair<QObject*, QString> mappedTarget: notificationMapping[dbSignal])
        {
            QMetaObject::invokeMethod(mappedTarget.first, mappedTarget.second.toLocal8Bit(), Qt::QueuedConnection);
        }
    }
}

SqlNotificationDispatcher* SqlNotificationDispatcher::instance = nullptr;
