#include "module.h"

#include<QDebug>
module::module()
{

}

module::module(int module_id,QString module_name,int module_etcs)
{
    this->module_id=module_id;
    this->module_name=module_name;
    this->module_etcs=module_etcs;
}
bool module::ajouter_module()
{
        QSqlQuery query;
        query.prepare("INSERT INTO module (module_id, module_name,module_etcs) VALUES (:module_id, :module_name, :module_etcs)");
        query.bindValue(":module_id", module_id);
        query.bindValue(":module_name", module_name);
        query.bindValue(":module_etcs", module_etcs);

        return    query.exec();
}

QSqlQueryModel *module::afficher_modules()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select * from module");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("MODULE'S NAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("NUMBER OF ETCS"));
    return model;
}
QSqlQueryModel *module::getModulesID()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select module_id,module_name from module");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("module_id"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("module_name"));
   // model->setHeaderData(2, Qt::Horizontal, QObject::tr("lastname"));

    return model;
}
bool module::affectTeacherToModule(int idModule,int cinTeacher)
{
        QSqlQuery query;
        query.prepare("INSERT INTO MODULE_TEACHER (TEACHER_CIN, MODULE_ID) VALUES (:module_id, :teacher_cin)");
        query.bindValue(":module_id", idModule);
        query.bindValue(":teacher_cin", cinTeacher);

        return    query.exec();
}
QSqlQueryModel *module::teachersOfModule(QString cls)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT t.cin ,t.firstname,t.lastname ,t.email FROM module_teacher mt "
                    "INNER JOIN teacher t ON t.cin = mt.teacher_cin WHERE mt.module_id =  " +cls);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("FIRSTNAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("LASTNAME"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
    return model;
}

bool module::supprimer()
{
    QSqlQuery query;
    QString res= QString::number(module_id);
    query.prepare("DELETE from MODULE where MODULE_ID=:id");
    query.bindValue(":id", res);
    return    query.exec();

}


bool module::unaffectTeacherFromModule(int idModule,int cinTeacher)
{
    QSqlQuery query;
    query.prepare("DELETE FROM MODULE_TEACHER  WHERE teacher_cin=:cin and module_id=:module_id");
    query.bindValue(":cin", cinTeacher);
     query.bindValue(":module_id", idModule);
    return    query.exec();

}

bool module::checkIfAffected(int cinTeacher,int idModule)
{


    QSqlQuery query;
    query.prepare("SELECT MODULE_ID, TEACHER_CIN FROM MODULE_TEACHER  WHERE MODULE_ID = ? and TEACHER_CIN = ? ");
    query.bindValue(0,idModule);
    query.bindValue(1,cinTeacher );
    if(query.exec())
        qDebug()<<"asd";
    if(query.next()){
        qDebug()<<"trrr";
        return true;
    }
    return false;

}

bool module::modifier_module()
{
    QSqlQuery query ;
   // QString res=QString::number(Cin);
    query.prepare("Update MODULE set MODULE_NAME=?, MODULE_ETCS=? where MODULE_ID=?");

            query.bindValue(0,module_name);
            query.bindValue(1,module_etcs);
            query.bindValue(2,module_id);
            qDebug()<<module_name;
              qDebug()<<module_etcs;
              qDebug()<<module_id;
            return query.exec();
}

