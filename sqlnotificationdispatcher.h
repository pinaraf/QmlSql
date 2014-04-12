#ifndef SQLNOTIFICATIONDISPATCHER_H
#define SQLNOTIFICATIONDISPATCHER_H

#include <QObject>
#include <QMap>
#include <QPair>
#include <QList>
#include <QSqlDriver>

class SqlNotificationDispatcher : public QObject
{
    Q_OBJECT
private:
    explicit SqlNotificationDispatcher(QObject *parent = 0);

    // Connects dbd -> signalName to QObject -> slotName...
    QMap<QPair<QSqlDriver *, QString>, QList<QPair<QObject*, QString>>> notificationMapping;
    static SqlNotificationDispatcher *instance;
public:
    static SqlNotificationDispatcher *getInstance();

    void registerNotification (const QSqlDatabase &database, const QString &notificationName, QObject *target, const QString &signal);
    void unregisterNotification (const QSqlDatabase &database, const QString &notificationName, QObject *target, const QString &signal);
signals:

private slots:
    void notificationReceived (const QString &name);
};

#endif // SQLNOTIFICATIONDISPATCHER_H
