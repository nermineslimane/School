#include "student.h"
#include "QDate"
#include "qdebug.h"
student::student()
{
    cin="";
    firstName="";
    lastName="";
    email="";
    phone="";
    dob=QDate();
    doj=QDate().currentDate();
    status="0";

}
student::student(QString cin,QString firstname,QString lastname,QString email,QString phone,QDate dob,QDate doj,QString status)
{
    this->cin=cin;
    this->firstName=firstname;
    this->lastName=lastname;
    this->email=email;
    this->phone=phone;
    this->dob=dob;
    this->doj=doj;
    this->status=status;
}
student::student(QString cin,QString firstname,QString lastname,QString email,QString phone )
{
    this->cin=cin;
    this->firstName=firstname;
    this->lastName=lastname;
    this->email=email;
    this->phone=phone;
}
QSqlQueryModel * student::afficher_students(){
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from student");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("First Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Last Name"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Phone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date of birth"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date of join"));

        return model;
}

QSqlQueryModel *student::getClassIDs()
{//   model->setQuery("select class_id from classroom where class_section=LIKE '"+s+"%' and academic_year LIKE '"+ay+"%' and class_year LIKE '"+y+"%' order by class_id");

   // if(s=="ALL"){

        QSqlQueryModel * model= new QSqlQueryModel();
        model->setQuery("select class_id from classroom order by class_id");
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("ID"));

        return model;
}
bool student::ajouter_student()
{
    QSqlQuery query;
    query.prepare("SELECT * FROM STUDENT WHERE STUDENT_EMAIL = ? ");
    query.bindValue(0,email);
    if(query.exec())
        qDebug()<<"asd";
    if(query.next()){
        return false;
    }else{
    QSqlQuery query;
    // QString res= QString::number(cin);

    query.prepare("INSERT INTO student (STUDENT_CIN, STUDENT_FIRSTNAME, STUDENT_LASTNAME, "
                   "STUDENT_EMAIL, STUDENT_PHONE,STUDENT_DOB,STUDNET_DOJ,STUDENT_STATUS) "
                        "VALUES (:cin,:first,:last,:email,:phone,:dob,:doj,:status)");
    query.bindValue(":cin", cin);
    query.bindValue(":first", firstName);
    query.bindValue(":last", lastName);
    query.bindValue(":email", email);
    query.bindValue(":phone", phone);
    query.bindValue(":dob", dob);
    query.bindValue(":doj", doj);
    query.bindValue(":status", status);
    qDebug()<<doj;
    qDebug()<<dob;
 return query.exec();}
}

bool student::affect_student_to_class(QString student_cin,QString class_id){

       QSqlQuery query,query2;

       query.prepare("insert into class_student (student_cin,class_id) values (?,?)");
       query.bindValue(0,student_cin);
       query.bindValue(1,class_id);
       query.exec();
       query2.prepare("Update STUDENT set STUDENT_STATUS=0 where STUDENT_CIN=?");
       query2.bindValue(0,student_cin);

        return (query.exec()&&query2.exec());

}

bool student::unaffect_student_from_class(QString student_cin,QString class_id){

       QSqlQuery query,query2;

       query.prepare("delete from class_student where student_cin=? and class_id=?");
       query.bindValue(0,student_cin);
       query.bindValue(1,class_id);
       query.exec();

       query2.prepare("Update STUDENT set STUDENT_STATUS=1 where STUDENT_CIN=?");
       query2.bindValue(0,student_cin);

        return (query.exec()&&query2.exec());
}

bool student::checkIfEmailUnique(QString e)
{


    QSqlQuery query;
    query.prepare("SELECT * FROM STUDENT WHERE STUDENT_EMAIL = ? ");
    query.bindValue(0,e);
    if(query.exec())
        qDebug()<<"asd";
    if(query.next()){
        qDebug()<<"trrr";
        return true;
    }
    return false;

}

bool student::supprimer_student(QString cin)
{ QSqlQuery query;
  //  QString res= QString::number(cin);
    query.prepare("DELETE from STUDENT where STUDENT_CIN=:cin");
    query.bindValue(":cin", cin);
    return    query.exec();

}
QSqlQueryModel * student::afficher_students_not_affected(){
    QSqlQueryModel * model= new QSqlQueryModel();
    model->setQuery("select * from student where student_status=1");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("First Name"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Last Name"));
    model->setHeaderData(3, Qt::Horizontal, QObject::tr("Email"));
    model->setHeaderData(4, Qt::Horizontal, QObject::tr("Phone"));
    model->setHeaderData(5, Qt::Horizontal, QObject::tr("Date of birth"));
    model->setHeaderData(6, Qt::Horizontal, QObject::tr("Date of join"));

        return model;
}
bool student::modifier_student()
{
    QSqlQuery query ;
   // QString res=QString::number(Cin);
    query.prepare("Update STUDENT set STUDENT_CIN=:cin, STUDENT_FIRSTNAME=:firstName, STUDENT_LASTNAME=:lastName,STUDENT_EMAIL=:email,STUDENT_PHONE=:phone where STUDENT_CIN=:cin ");
            query.bindValue(":cin",cin);
            query.bindValue(":firstName", firstName);
            query.bindValue(":lastName", lastName);
            query.bindValue(":phone", phone);
            query.bindValue(":email", email);

            return query.exec();
}
