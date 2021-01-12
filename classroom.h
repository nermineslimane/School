#ifndef CLASSROOM_H
#define CLASSROOM_H
#include "QString"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlQueryModel>
class classroom
{
public:
    classroom();
    classroom(QString,QString,QString,QString,QString);
    classroom(QString,QString,QString,QString);
    QString get_classroomID();
    QString get_classroomSection();
    QString get_classroomNumber();
    QString get_classroomYear();
    QString get_classAcademicYear();
    bool addClassroom();
    QSqlQueryModel * display_classrooms();
    bool delete_classroom();
    QSqlQueryModel * getClassIDs(QString,QString,QString);

    QSqlQueryModel * studentsOfClass(QString );

    int countStudentsPerClass(QString );

private:
    QString classroomId,classroomSection,classroomNumber,classroomYear,academicYear;
};

#endif // CLASSROOM_H
