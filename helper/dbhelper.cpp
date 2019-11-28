#include "dbhelper.h"
#include <QMutexLocker>
#include <QDebug>
#include <QSqlError>

DBHelper::DBHelper(QObject *parent)
    : QObject(parent)
{
    //    db = QSqlDatabase::database("min", true);
}

void DBHelper::initDB()
{
    QMutexLocker lock(&this->mLockDB);
    const QString connectionName = "min_db";
    if(QSqlDatabase::contains(connectionName)) {
        db = QSqlDatabase::database(connectionName);
        qDebug() << "数据库已存在，直接打开" << endl;
    } else {
        db = QSqlDatabase::addDatabase("QSQLITE", connectionName);
        db.setDatabaseName("min.db");
        if(!this->openDB()) {
            return;
        }
        QSqlQuery sqlQuery(db);
        QString isExistTabelSql = "select count(*) from sqlite_master where type='table' and name = 'setting'";
        if(!sqlQuery.exec(isExistTabelSql)) {
            qDebug() << sqlQuery.lastError();
        } else {
            if(sqlQuery.next()) {
                int num = sqlQuery.value(0).toInt();
                if(num == 0) {
                    // 创建表
                    QString createTableSql = "create table setting(name varchar(50), value varchar(100), primary key(name))";
                    if(!sqlQuery.exec(createTableSql)) {
                        qDebug() << sqlQuery.lastError();
                    } else {
                        qDebug() << "创建成功";
                    }
                }
            } else {
                qDebug() << "aaa";
            }
        }
        this->closeDB();
    }
}

bool DBHelper::openDB()
{
    return db.open();
}

void DBHelper::closeDB()
{
    db.close();
}
