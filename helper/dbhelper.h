#ifndef DBHELPER_H
#define DBHELPER_H

#include <QObject>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMutex>

class DBHelper : public QObject
{
    Q_OBJECT
public:
    explicit DBHelper(QObject *parent = 0);

public:
    void initDB();
private:
    bool openDB();
    void closeDB();

private:
    QSqlDatabase db;
    QMutex mLockDB;

signals:

public slots:
};

#endif // DBHELPER_H
