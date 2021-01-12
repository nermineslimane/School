#ifndef DB_CONNECTION_H
#define DB_CONNECTION_H

#include <QtSql/QSqlDatabase>
#include<QtSql/QSqlError>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QDebug>
class db_connection
{
public:
    db_connection();
    QSqlDatabase mydb;
    bool connect();
       void connClose()
       {
           mydb.close();
       }
};

#endif // DB_CONNECTION_H
