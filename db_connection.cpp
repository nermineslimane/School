#include "db_connection.h"
#include <QDebug>

db_connection::db_connection()
{

}

bool db_connection::connect(){
    bool test=false;
    QSqlDatabase db = QSqlDatabase::addDatabase("QODBC");
    db.setDatabaseName("QtProject");
    db.setUserName("nermine");//inserer nom de l'utilisateur
    db.setPassword("nermine");//inserer mot de passe de cet utilisateur


    if (db.open())
    {
        qDebug() << "Connection successful.";
        test=true;
    }

    else
        qDebug() << "Connection FAILED.";
        return  test;

}
