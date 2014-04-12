#include "sqldatabase.h"

#include <QSqlDatabase>
#include <QSqlError>

SqlDatabase::SqlDatabase(QObject *parent) :
    QObject(parent)
{
}

bool SqlDatabase::addDatabase(const char *name, const QString &driver, const QString &host, const QString &dbname, const QString &user, const QString &password)
{
    QSqlDatabase db = QSqlDatabase::addDatabase(driver, name);
    db.setHostName(host);
    db.setDatabaseName(dbname);
    db.setUserName(user);
    db.setPassword(password);
    bool ok = db.open();
    lastError = db.lastError();
    return ok;
}

bool SqlDatabase::loadDefaultDatabase(const QString &driver, const QString &host, const QString &dbname, const QString &user, const QString &password)
{
    return addDatabase(QSqlDatabase::defaultConnection, driver, host, dbname, user, password);
}

QString SqlDatabase::lastErrorMessage()
{
    if (lastError.isValid())
        return lastError.databaseText();
    return QString::null;
}

QStringList SqlDatabase::databases() const
{
    return QSqlDatabase::connectionNames();
}

