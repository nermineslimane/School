#ifndef STUDENT_H
#define STUDENT_H


#include <QString>
#include <QDate>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>

class student
{
public:
    student();
    student(QString,QString,QString,QString,QString,QDate,QDate,QString);
    student(QString ,QString ,QString ,QString ,QString );
    QString get_cin();
    QString get_firstName();
    QString get_lastName();
    QString get_email();
    QString get_phone();
    QDate get_dob();
    QDate get_doj();
    QString get_status();
    //CRUD
    bool ajouter_student();
    QSqlQueryModel * afficher_students();
    bool supprimer_student(QString);
    bool modifier_student();
    bool affect_student_to_class(QString,QString);
    bool unaffect_student_from_class(QString,QString);
    QSqlQueryModel * getClassIDs();
    bool checkIfEmailUnique(QString email);

    QSqlQueryModel * afficher_students_not_affected();
    //END CRUD

private:
            QString cin,firstName,lastName,email,phone, status;
            QDate dob,doj;
};

#endif // STUDENT_H
