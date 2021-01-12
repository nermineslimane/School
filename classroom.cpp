#include "classroom.h"
#include "QString"
#include <qdebug.h>

classroom::classroom()
{
classroomId="";
classroomNumber="";
classroomSection="";
classroomYear="";
academicYear="";
}

classroom::classroom(QString classroomId,QString classroomYear ,QString classroomSection ,QString classroomNumber,QString academicYear)
{
this->classroomId=classroomId;
this->classroomNumber=classroomNumber;
this->classroomSection=classroomSection;
this->classroomYear=classroomYear;
this->academicYear=academicYear;
}
classroom::classroom(QString classroomYear ,QString classroomSection ,QString classroomNumber,QString academicYear)
{
this->classroomId=classroomYear+classroomSection+classroomNumber;
this->classroomNumber=classroomNumber;
this->classroomSection=classroomSection;
this->classroomYear=classroomYear;
this->academicYear=academicYear;
}
QString classroom::get_classroomID(){return classroomId;}
QString classroom::get_classroomYear(){return classroomYear;}
QString classroom::get_classroomSection(){return classroomSection;}
QString classroom::get_classAcademicYear(){return academicYear;}

bool classroom::addClassroom()
{
    QSqlQuery query;
    query.prepare("SELECT CLASS_ID, CLASS_YEAR,CLASS_SECTION,CLASS_NUMBER,ACADEMIC_YEAR FROM CLASSROOM  WHERE CLASS_ID = ? and ACADEMIC_YEAR = ? ");
    query.bindValue(0,classroomId);
    query.bindValue(1,academicYear );
    if(query.exec())
    if(query.next()){

        return false;
    }
    else
    {
        QSqlQuery insert;
        insert.prepare("INSERT INTO CLASSROOM (CLASS_ID, CLASS_YEAR,CLASS_SECTION,CLASS_NUMBER,ACADEMIC_YEAR)"
                        " VALUES (:class_id, :class_year, :class_section,:class_number,:class_academicyear)");
        insert.bindValue(":class_id", classroomId);
        qDebug()<<classroomId;
        insert.bindValue(":class_year", classroomYear);
        insert.bindValue(":class_section", classroomSection);
        insert.bindValue(":class_number", classroomNumber);
        insert.bindValue(":class_academicyear", academicYear);

        return insert.exec();
    }
}

QSqlQueryModel *classroom::getClassIDs(QString s,QString y,QString ay)
{//   model->setQuery("select class_id from classroom where class_section = '"+s+"' and academic_year = '"+ay+"' and class_year = '"+y+"' order by class_id");

   // if(s=="ALL"){

        QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select class_id from classroom where class_section LIKE '"+s+"%'and academic_year LIKE '"+ay+"%' and class_year LIKE '"+y+"%' order by class_id");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));

        return model;
 /*   }
    else if(y=="ALL"){

        QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select class_id from classroom where class_section=LIKE '"+s+"%'and class_year LIKE '"+y+"%' order by class_id");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        qDebug()<<"trrr3";
        return model;
    }
    else if(ay=="ALL"){

        QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select class_id from classroom where class_section=LIKE '"+s+"%' and academic_year LIKE '"+ay+"%' order by class_id");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        qDebug()<<"trrr4";
         return model;
    }

    else if (s=="ALL"&&y=="ALL")

    {

        QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select class_id from classroom where academic_year LIKE '"+ay+"%' order by class_id");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
        qDebug()<<"trrr5";
        return model;
    }
    else if (s=="ALL"&&ay=="ALL")
        {

        QSqlQueryModel * model= new QSqlQueryModel();
            model->setQuery("select class_id from classroom where class_year LIKE '"+y+"%' order by class_id");
            model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
            qDebug()<<"trrr6";
            return model;
        }
    else if(y=="ALL"&& ay=="ALL"){

        QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select class_id from classroom where class_section=LIKE '"+s+"%' order by class_id");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
         qDebug()<<"trrr7";
        return model;
    }
    else if((y=="ALL") && (ay=="ALL") && (s=="ALL")){

        QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select class_id from classroom order by class_id");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));
         qDebug()<<"trrr8";
        return model;
    }



*/
}
//SELECT s.student_cin ,s.student_firstname,s.student_lastname,s.student_email FROM class_student cs INNER JOIN student s ON s.student_cin = cs.student_cin WHERE cs.class_id=

QSqlQueryModel *classroom::studentsOfClass(QString cls)
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("SELECT s.student_cin ,s.student_firstname,s.student_lastname,s.student_email FROM class_student "
        "cs INNER JOIN student s ON s.student_cin = cs.student_cin WHERE cs.class_id ='" +cls+"'");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("FIRSTNAME"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("LASTNAME"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("EMAIL"));
    return model;
}
//SELECT COUNT(*)FROM class_student cs INNER JOIN student s ON s.student_cin = cs.student_cin WHERE cs.class_id='

int classroom::countStudentsPerClass(QString cls)
{    QSqlQuery q1;
     float tmp=0.00;
     q1.prepare("SELECT COUNT(*)FROM class_student cs INNER JOIN student s ON s.student_cin = cs.student_cin WHERE cs.class_id='"+cls+"'");
     q1.exec();
      if (q1.next()) {
          tmp= q1.value(0).toInt();
          }
     return tmp;
}
