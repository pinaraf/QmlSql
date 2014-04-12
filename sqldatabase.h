#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#include <QObject>
#include <QSqlError>
#include <QStringList>

class SqlDatabase : public QObject
{
    Q_OBJECT
public:
    explicit SqlDatabase(QObject *parent = 0);

    Q_INVOKABLE QStringList databases() const;
    Q_INVOKABLE bool addDatabase(const char *name, const QString &driver, const QString &host, const QString &dbname, const QString &user, const QString &password);
    Q_INVOKABLE bool loadDefaultDatabase(const QString &driver, const QString &host, const QString &dbname, const QString &user, const QString &password);
    Q_INVOKABLE QString lastErrorMessage();
signals:

public slots:

private:
    QSqlError lastError;
};

#endif // SQLDATABASE_H
