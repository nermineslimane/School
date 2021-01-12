#ifndef TEACHER_H
#define TEACHER_H

#include <QString>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>

class Teacher
{
public:
    Teacher();
    Teacher(int ,QString , QString , QString , QString , QString );

    int get_cin();
    QString get_firstName();
    QString get_lastName();
    QString get_phone();
    QString get_email();
    QString get_salary();
    bool ajouter();
    QSqlQueryModel * afficher();
    float avgSalary();
    bool supprimer();
    bool modifier();

    QSqlQueryModel * getTeachersCIN();

    QSqlQueryModel* recherche(const QString &str);
private:
            QString firstName,lastName,email,phone, salary;
            int cin;
};

#endif // TEACHER_H
