#include "teacher.h"

#include <QtDebug>
Teacher::Teacher()
{
       cin=0;
       firstName="";
       lastName="";
       phone="";
       email="";
       salary="0";
}
Teacher::Teacher(int cin,QString firstName, QString lastName, QString phone, QString email, QString salary)
{
    this->cin=cin;
    this->firstName=firstName;
    this->lastName=lastName;
    this->phone=phone;
    this->email=email;
    this->salary=salary;

}

int Teacher::get_cin(){return cin;}
QString Teacher::get_firstName(){return firstName;}
QString Teacher::get_lastName(){return lastName;}
QString Teacher::get_phone(){return phone;}
QString Teacher::get_email(){return email;}
QString Teacher::get_salary(){return salary;}

bool Teacher::ajouter()
{
    QSqlQuery query;

    QString res= QString::number(cin);
    query.prepare("INSERT INTO teacher (CIN, FIRSTNAME, LASTNAME, PHONE, EMAIL,SALARY) "
                        "VALUES (:cin, :firstName, :lastName, :phone, :email,:salary)");
    query.bindValue(":cin", res);
    query.bindValue(":firstName", firstName);
    query.bindValue(":lastName", lastName);
    query.bindValue(":phone", phone);
    query.bindValue(":email", email);
    query.bindValue(":salary", salary);


    return    query.exec();
}


QSqlQueryModel * Teacher::afficher()
{
QSqlQueryModel * model= new QSqlQueryModel();
model->setQuery("select * from teacher");
model->setHeaderData(0, Qt::Horizontal, QObject::tr("CIN"));
model->setHeaderData(1, Qt::Horizontal, QObject::tr("First Name"));
model->setHeaderData(2, Qt::Horizontal, QObject::tr("Last Name"));
model->setHeaderData(3, Qt::Horizontal, QObject::tr("Phone"));
model->setHeaderData(4, Qt::Horizontal, QObject::tr("Email"));
model->setHeaderData(5, Qt::Horizontal, QObject::tr("Salary"));
    return model;
}
bool Teacher::supprimer()
{ QSqlQuery query;
    QString res= QString::number(cin);
    query.prepare("DELETE from TEACHER where CIN=:cin");
    query.bindValue(":cin", res);
    return    query.exec();

}

bool Teacher::modifier()
{
    QSqlQuery query ;
   // QString res=QString::number(Cin);
    query.prepare("Update TEACHER set CIN=:cin, FIRSTNAME=:firstName, LASTNAME=:lastName,PHONE=:phone,EMAIL=:email, SALARY=:salary where CIN=:cin ");
            query.bindValue(":cin",cin);
            query.bindValue(":firstName", firstName);
            query.bindValue(":lastName", lastName);
            query.bindValue(":phone", phone);
            query.bindValue(":email", email);
            query.bindValue(":salary", salary);

            return query.exec();
}


QSqlQueryModel* Teacher::recherche(const QString &str)
{
    QSqlQueryModel * model=new QSqlQueryModel() ;
    QSqlQuery q;
    q.prepare("SELECT * FROM teacher where (CIN LIKE '"+str+"%' OR FIRSTNAME LIKE '"+str+"%' OR LASTNAME  LIKE '"+str+"%' OR EMAIL LIKE '"+str+"%')")  ;
    q.exec() ;
    model->setQuery(q);
    return model;
}

QSqlQueryModel *Teacher::getTeachersCIN()
{
    QSqlQueryModel * model= new QSqlQueryModel();

    model->setQuery("select cin,firstname,lastname from teacher");
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("cin"));
  //  model->setHeaderData(1, Qt::Horizontal, QObject::tr("firstname"));
   // model->setHeaderData(2, Qt::Horizontal, QObject::tr("lastname"));

    return model;
}

float Teacher::avgSalary()
{    QSqlQuery q1;
     float tmp=0.00;
     q1.prepare("SELECT AVG(CAST(salary AS FLOAT)) FROM teacher");
     q1.exec();
      if (q1.next()) {
          tmp= q1.value(0).toFloat();
          }
     return tmp;
}


