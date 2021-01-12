#ifndef MODULE_H
#define MODULE_H

#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>

class module
{
public:
    module();
    module(int,QString, int);
    bool ajouter_module();

    bool affectTeacherToModule(int,int);
    QSqlQueryModel *afficher_modules();
    QSqlQueryModel *getModulesID();
    QSqlQueryModel *teachersOfModule(QString cls);
    bool supprimer();
    bool unaffectTeacherFromModule(int,int);
    bool checkIfAffected(int,int);
    bool modifier_module();
private:
    int module_id,module_etcs;
    QString module_name;
};

#endif // MODULE_H
