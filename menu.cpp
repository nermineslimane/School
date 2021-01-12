#include "menu.h"
#include "ui_menu.h"

Menu::Menu(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
    ui->tabTeacher->setModel(tmpteacher.afficher());
    //calculate average salary of all teacher's
    float avg=tmpteacher.avgSalary();
    ui->avgSalary->setText("Average of salaries : "+QString::number(avg)+" Dt");
    //fill list of all modules
    ui->listModules->setModel(tmpmodule.afficher_modules());
   /* module md;
    Teacher te;*/
    //fill in comboboxes with primary keys of both classes
    ui->CINTeacher->setModel(tmpteacher.getTeachersCIN());
    ui->IDModule->setModel((tmpmodule.getModulesID()));
    //ui->classID->setModel(tmpclass.getClassIDs());
    ui->classView->setModel(tmpclass.getClassIDs(ui->classST->currentText(),
                                                 ui->classLV->currentText(),
                                                 ui->classAY->currentText()
                                                 ));
    ui->studentclass->setModel(tmpstudent.getClassIDs());
    ui->studentstableview->setModel(tmpstudent.afficher_students());
    ui->s_email->setReadOnly(true);
}

Menu::~Menu()
{
    delete ui;
}

//BEGIN Manage teacher's section
void Menu::on_addTeacher_clicked()
{

    //User Regular expressions and QTValidator to validate form iput
    QRegularExpression rx("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b",
                              QRegularExpression::CaseInsensitiveOption);
    QRegularExpression rxphone("^[0-9]{8}$");
    QRegularExpression rxsalary("^[0-[+]?[0-9]*\.?[0-9]*");
    ui->email->setValidator(new QRegularExpressionValidator(rx, this));
    ui->cin->setValidator(new QRegularExpressionValidator(rxphone,this));
    ui->phone->setValidator(new QRegularExpressionValidator(rxphone,this));
    ui->salary->setValidator(new QRegularExpressionValidator(rxsalary,this));

    QString firstName=ui->name->text();
    QString lastName=ui->lastname->text();

        if(

                ui->email->hasAcceptableInput()
                &&(ui->phone->hasAcceptableInput())
                &&(ui->cin->hasAcceptableInput())
                &&(ui->salary->hasAcceptableInput())
                ){

             QString email=ui->email->text();
             QString phone=ui->phone->text();
             int cin=ui->cin->text().toInt();
             QString salary=ui->salary->text();
             Teacher t(cin,firstName,lastName,phone,email,salary);
             qInfo()<<cin;
             bool test= t.ajouter();
             if(test)
              {
                 ui->tabTeacher->setModel(tmpteacher.afficher());
                  QMessageBox::information(nullptr, QObject::tr("Add teacher"),
                  QObject::tr("Teacher added successfully"), QMessageBox::Ok);
                  float avg=tmpteacher.avgSalary();
                   ui->avgSalary->setText("Average of salaries : "+QString::number(avg)+" Dt");
                   ui->CINTeacher->clear();
                   ui->name->clear();
                   ui->lastname->clear();
                   ui->phone->clear();
                   ui->salary->clear();
                   ui->email->clear();


              }
              else
                QMessageBox::critical(nullptr, QObject::tr("Add teacher"),
                            QObject::tr("Error !"), QMessageBox::Cancel);

         }else {

         QMessageBox::warning(this, tr("Verification"),tr("Invalid input."), QMessageBox::Ok);
            return;
        }
}

void Menu::on_print_clicked()
{
    QPdfWriter pdf("C:/Users/nermine/teachers.pdf");
    QPainter painter(&pdf);
   int i = 4000;
        painter.setPen(Qt::black);
        painter.setFont(QFont("Helvetica [Cronyx]", 20));
        painter.drawText(3500,1400,"List of teachers");
        painter.setPen(Qt::black);
        painter.setFont(QFont("Helvetica [Cronyx]", 15));
       // painter.drawText(1100,2000,afficheDC);
        painter.drawRect(100,100,7300,2600);
        //painter.drawPixmap(QRect(7600,70,2000,2600),QPixmap("C:/Users/Rafik/Desktop/img.jpg"));
        painter.drawRect(0,3000,9600,500);
        painter.setFont(QFont("Helvetica [Cronyx]", 9));
        painter.drawText(300,3300,"CIN");
        painter.drawText(2300,3300,"First Name");
        painter.drawText(4300,3300,"Last Name");
        painter.drawText(6300,3300,"Phone");
        painter.drawText(8300,3300,"Email");
        painter.drawText(10300,3300,"Salary");

        QSqlQuery query;
        query.prepare("select * from teacher");
        query.exec();
        while (query.next())
        {
            painter.drawText(300,i,query.value(0).toString());
            painter.drawText(2300,i,query.value(1).toString());
            painter.drawText(4500,i,query.value(2).toString());
            painter.drawText(6500,i,query.value(3).toString());
            painter.drawText(8000,i,query.value(4).toString());
            painter.drawText(10000,i,query.value(5).toString());

           i = i + 500;
        }
        int reponse = QMessageBox::question(this, "Génerer PDF", "<PDF Enregistré>...Vous Voulez Affichez Le PDF ?", QMessageBox::Yes |  QMessageBox::No);
            if (reponse == QMessageBox::Yes)
            {

                QDesktopServices::openUrl(QUrl::fromLocalFile("C:/Users/nermine/teachers.pdf"));

                painter.end();
            }
            if (reponse == QMessageBox::No)
            {
                 painter.end();
            }

}

void Menu::on_deleteTeacher_clicked()
{

    if(ui->tabTeacher->currentIndex().row()==-1)
            QMessageBox::information(nullptr, QObject::tr("Suppression"),
                              QObject::tr("Veuillez Choisir un utilisateur.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        else
        {
            tmpteacher=Teacher(
                       ui->tabTeacher->model()->data(ui->tabTeacher->model()->index(ui->tabTeacher->currentIndex().row(),0)).toInt(),
                       ui->name->text(),
                       ui->lastname->text(),
                       ui->phone->text(),
                       ui->email->text(),
                       ui->salary->text()
                       );
            if(tmpteacher.supprimer())
            {
                ui->tabTeacher->setModel(tmpteacher.afficher());

                QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                  QObject::tr("Success.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
                float avg=tmpteacher.avgSalary();

                ui->avgSalary->setText("Average of salaries : "+QString::number(avg)+" Dt");

            }
            else
            {
                QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                  QObject::tr("Erreur.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
            }
        }
}

void Menu::on_updateTeacher_clicked()
{
    if(ui->tabTeacher->currentIndex().row()==-1)
           QMessageBox::information(nullptr, QObject::tr("Modification"),
                             QObject::tr("Veuillez Choisir un utilisateur.\n"
                                         "Click Cancel to exit."), QMessageBox::Cancel);
       else
       {

            Teacher  tmpteacher=Teacher(
                        ui->tabTeacher->model()->data(ui->tabTeacher->model()->index(ui->tabTeacher->currentIndex().row(),0)).toInt(),
                        ui->name->text(),
                        ui->lastname->text(),
                        ui->phone->text(),
                        ui->email->text(),
                        ui->salary->text()
                        );
            if(tmpteacher.modifier())
           {
               ui->tabTeacher->setModel(tmpteacher.afficher());

               QMessageBox::information(nullptr, QObject::tr("Modification"),
                                 QObject::tr("Success.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
               float avg=tmpteacher.avgSalary();

                ui->avgSalary->setText("Average of salaries : "+QString::number(avg)+" Dt");
    ui->CINTeacher->clear();
    ui->name->clear();
    ui->lastname->clear();
    ui->phone->clear();
    ui->salary->clear();
    ui->email->clear();
           }
           else
           {
               QMessageBox::information(nullptr, QObject::tr("Modification"),
                                 QObject::tr("Erreur.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
           }
       }
}

void Menu::on_find_textEdited(const QString &arg1)
{
    QString str=ui->find->text();
    QSqlQueryModel* model=tmpteacher.recherche(str);
    ui->tabTeacher-> setModel(model);
}

void Menu::on_tabTeacher_doubleClicked(const QModelIndex &index)
{
    ui->cin->setText(ui->tabTeacher->model()->data(ui->tabTeacher->model()->index(ui->tabTeacher->currentIndex().row(),0)).toString());
    ui->name->setText(ui->tabTeacher->model()->data(ui->tabTeacher->model()->index(ui->tabTeacher->currentIndex().row(),1)).toString());
    ui->lastname->setText(ui->tabTeacher->model()->data(ui->tabTeacher->model()->index(ui->tabTeacher->currentIndex().row(),2)).toString());
    ui->phone->setText(ui->tabTeacher->model()->data(ui->tabTeacher->model()->index(ui->tabTeacher->currentIndex().row(),3)).toString());
    ui->email->setText(ui->tabTeacher->model()->data(ui->tabTeacher->model()->index(ui->tabTeacher->currentIndex().row(),4)).toString());
    ui->salary->setText(ui->tabTeacher->model()->data(ui->tabTeacher->model()->index(ui->tabTeacher->currentIndex().row(),5)).toString());

}

//END manage teachers section

//*********************************************************************************************************************************************//

//BEGIN  manage modules
void Menu::on_addModule_clicked()
{
    ui->listModules->setModel(tmpmodule.afficher_modules());
    int moduleId=ui->moduleId->text().toInt();
    QString moduleName=ui->moduleName->text();
    int moduleEtcs=ui->moduleEtcs->text().toInt();
    module m(moduleId,moduleName,moduleEtcs);

    bool test= m.ajouter_module();
    if(test)
     {
        ui->listModules->setModel(m.afficher_modules());
        ui->IDModule->setModel((m.getModulesID()));
         QMessageBox::information(nullptr, QObject::tr("Add Module"),
         QObject::tr("Module added successfully"), QMessageBox::Ok);

         ui->moduleName->clear();
         ui->moduleEtcs->clear();
         ui->moduleId->clear();
         ui->moduleId->setReadOnly(false);


     }
     else
       QMessageBox::critical(nullptr, QObject::tr("Add Module"),
                   QObject::tr("Error !"), QMessageBox::Cancel);

}

void Menu::on_deleteModule_clicked()
{
    if(ui->listModules->currentIndex().row()==-1)
            QMessageBox::information(nullptr, QObject::tr("Suppression"),
                              QObject::tr("Veuillez Choisir un module.\n"), QMessageBox::Cancel);
        else
        {
            tmpmodule=module(
                       ui->listModules->model()->data(ui->listModules->model()->index(ui->listModules->currentIndex().row(),0)).toInt(),
                       ui->moduleName->text(),
                       ui->moduleEtcs->text().toInt()
                        );
            if(tmpmodule.supprimer())
            {
                ui->listModules->setModel(tmpmodule.afficher_modules());
                ui->listteachers->setModel(tmpmodule.teachersOfModule(ui->IDModule->currentText()));
                ui->IDModule->setModel(tmpmodule.getModulesID());
                QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                  QObject::tr("Success.\n"), QMessageBox::Cancel);

            }
            else
            {
                QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                  QObject::tr("Erreur.\n"), QMessageBox::Cancel);
            }
        }

}

void Menu::on_updateModule_clicked()
{
    if(ui->listModules->currentIndex().row()==-1)
           QMessageBox::information(nullptr, QObject::tr("Modification"),
                             QObject::tr("Veuillez Choisir un Module !"), QMessageBox::Cancel);
       else
       {

             module tmpmodule=module(
                        ui->listModules->model()->data(ui->listModules->model()->index(ui->listModules->currentIndex().row(),0)).toInt(),
                        ui->moduleName->text(),
                        ui->moduleEtcs->text().toInt()
                        );
            if(tmpmodule.modifier_module())
           {
               ui->listModules->setModel(tmpmodule.afficher_modules());

               QMessageBox::information(nullptr, QObject::tr("Update"),
                                 QObject::tr("Success."), QMessageBox::Cancel);
            ui->moduleName->clear();
            ui->moduleEtcs->clear();
            ui->moduleId->clear();
            ui->moduleId->setReadOnly(false);
            }
           else
           {
               QMessageBox::information(nullptr, QObject::tr("Update"),
                                 QObject::tr("Error.\n"), QMessageBox::Cancel);
           }
       }
}

void Menu::on_affect_clicked()
{

    if( ui->CINTeacher->currentText().isEmpty()&&ui->IDModule->currentText().isEmpty())
    {
          QMessageBox::information(this," ERROR "," Please select a teacher and a module !") ;
    }
    else if(tmpmodule.checkIfAffected(ui->CINTeacher->currentText().toInt(),ui->IDModule->currentText().toInt()))
    {
         QMessageBox::information(this," ERROR "," Teacher already affected to this module !") ;
    }
     else if(tmpmodule.affectTeacherToModule(ui->CINTeacher->currentText().toInt(),ui->IDModule->currentText().toInt()))
           {

                ui->listteachers->setModel(tmpmodule.teachersOfModule(ui->IDModule->currentText()));

               //ui->data->setModel(tmp.afficher());
               //ui->lineEdit_id_6->setText("");
               //ui->id_match->setModel(tmp.getIDs());
               QMessageBox::information(nullptr, QObject::tr("Affect"),
                                 QObject::tr("Success.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
           }
           else
           {
               QMessageBox::information(nullptr, QObject::tr("Affect"),
                                 QObject::tr("Error.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
           }
}

void Menu::on_unaffect_clicked()
{


    if(ui->listteachers->currentIndex().row()==-1)
            QMessageBox::information(nullptr, QObject::tr("Suppression"),
                              QObject::tr("Choose a teacher to unaffect  from module.\n"), QMessageBox::Cancel);
        else
        {
        int cin =  ui->listteachers->model()->data(ui->listteachers->model()->index(ui->listteachers->currentIndex().row(),0)).toInt();
          int mID=ui->IDModule->currentText().toInt();
          qDebug()<<cin;
          qDebug()<<mID;

                  if(tmpmodule.unaffectTeacherFromModule(mID,cin))
            {
 ui->listteachers->setModel(tmpmodule.teachersOfModule(ui->IDModule->currentText()));

                QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                  QObject::tr("Success.\n"), QMessageBox::Cancel);

            }
            else
            {
                QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                  QObject::tr("Erreur.\n"), QMessageBox::Cancel);
            }
        }


}
void Menu::on_IDModule_currentIndexChanged(int index)
{

    module tmp;
    ui->listteachers->setModel(tmp.teachersOfModule(ui->IDModule->currentText()));
}


void Menu::on_listModules_doubleClicked(const QModelIndex &index)
{
    ui->moduleId->setText(ui->listModules->model()->data(ui->listModules->model()->index(ui->listModules->currentIndex().row(),0)).toString());
    ui->moduleId->setReadOnly(true);
    ui->moduleName->setText(ui->listModules->model()->data(ui->listModules->model()->index(ui->listModules->currentIndex().row(),1)).toString());
    ui->moduleEtcs->setValue(ui->listModules->model()->data(ui->listModules->model()->index(ui->listModules->currentIndex().row(),2)).toInt());

}

//END manage modules
//********************************************************************************************************************************
//BEGIN Manage classes
void Menu::on_addClass_clicked()
{
    QString classlevel="";
      if(ui->level1->isChecked())
   {
      classlevel="1";

   }
   else if (ui->level2->isChecked())
      {
         classlevel="2";

      }
      else if (ui->level3->isChecked())
            {
               classlevel="3";

            }else if (ui->level4->isChecked())
      {
         classlevel="4";

      }
      else if (ui->level5->isChecked())
            {
               classlevel="5";

            }
    else {
          QMessageBox::information(nullptr, QObject::tr("LEvel"),
                            QObject::tr("Please choose a level.\n"), QMessageBox::Cancel);

      }
     qDebug()<<classlevel;
     if (classlevel!="")
     {
         //treatement of acadmeic  year
         int ay=ui->classacademicyear->text().toInt()+1;
         QString acy=ui->classacademicyear->text()+"/"+QString::number(ay);
         classroom tmpclass(classlevel,ui->classSection->currentText(),ui->classNumber->text(),acy);
        if( tmpclass.addClassroom())
            QMessageBox::information(nullptr, QObject::tr("add new class"),
                              QObject::tr("Class added successfully\n"), QMessageBox::Cancel);
        else
            QMessageBox::information(nullptr, QObject::tr("add new class"),
                              QObject::tr("Class already exists\n"), QMessageBox::Cancel);
     }
}

void Menu::on_classLV_currentIndexChanged(int index)
{

QString st,lv,ay;

if (st=="ALL")
    st="";
else st=ui->classST->currentText();
if (lv=="ALL")
    lv="";
else
    lv=ui->classLV->currentText();
if (ay=="ALL")
    ay="";
else ay=ui->classAY->currentText();

qDebug()<<st +"/"+lv +"/"+ay;
qDebug()<<index;
ui->classView->setModel(tmpclass.getClassIDs(st,lv,ay));
}

void Menu::on_classST_currentIndexChanged(int index)
{
    QString st,lv,ay;

    if (st=="ALL")
        st="";
    else st=ui->classST->currentText();
    if (lv=="ALL")
        lv="";
    else
        lv=ui->classLV->currentText();
    if (ay=="ALL")
        ay="";
    else ay=ui->classAY->currentText();

    qDebug()<<st +"/"+lv +"/"+ay;
    qDebug()<<index;
    ui->classView->setModel(tmpclass.getClassIDs(st,lv,ay));
}

void Menu::on_classAY_currentIndexChanged(int index)
{
    QString st,lv,ay;

    if (st=="ALL")
        st="";
    else st=ui->classST->currentText();
    if (lv=="ALL")
        lv="";
    else
        lv=ui->classLV->currentText();
    if (ay=="ALL")
        ay="";
    else ay=ui->classAY->currentText();

    qDebug()<<st +"/"+lv +"/"+ay;
    qDebug()<<index;
    ui->classView->setModel(tmpclass.getClassIDs(st,lv,ay));
}

//**********************************************************************************************************************************
//BEGIN manage students
void Menu::on_s_lastname_textEdited(const QString &arg1)
{
    ui->s_email->setText(ui->s_firstname->text()+"."+ ui->s_lastname->text()+"@school.tn");

}

void Menu::on_addStudent_clicked()
{
    QRegularExpression rxcin("^[0-9]{8}$");
    QDate doj=QDate::currentDate();
    ui->s_cin->setValidator(new QRegularExpressionValidator(rxcin, this));
    ui->s_phone->setValidator(new QRegularExpressionValidator(rxcin, this));
    if (ui->s_cin->hasAcceptableInput() && ui->phone->hasAcceptableInput()){
    student tmpstudent(ui->s_cin->text(),
                       ui->s_firstname->text(),
                       ui->s_lastname->text(),
                        ui->s_email->text(),
                       ui->s_phone->text(),
                       ui->s_dob->date(),
                       doj,
                       "0");


        if(tmpstudent.ajouter_student())
            { qDebug()<<"t3ada l if thenya";

              { if(tmpstudent.affect_student_to_class(ui->s_cin->text(),ui->studentclass->currentText()))
               {

               qDebug()<<"t3ada l if theltha";
                   ui->studentstableview->setModel(tmpstudent.afficher_students());
                   QMessageBox::information(nullptr, QObject::tr("add new student"),
                                      QObject::tr("Student added and affected to class successfully\n"), QMessageBox::Cancel);}
                else{
                    QMessageBox::information(nullptr, QObject::tr("add new student"),
                                      QObject::tr("error\n"), QMessageBox::Cancel);}
             }
        }else {
            QMessageBox::information(nullptr, QObject::tr("add new student"),
                              QObject::tr("Change email,it is not unique\n"), QMessageBox::Cancel);
            ui->s_email->setReadOnly(false);
        }



}
    else {
        QMessageBox::information(nullptr, QObject::tr("add new student"),
                                 QObject::tr("Check your input format !\n"), QMessageBox::Cancel);

 }
}
//END manage students


void Menu::on_classView_doubleClicked(const QModelIndex &index)
{
    QString cid=ui->classView->model()->data(ui->classView->model()->index(ui->classView->currentIndex().row(),0)).toString();
    qDebug()<<tmpclass.studentsOfClass(ui->classView->model()->data(ui->classView->model()->index(ui->classView->currentIndex().row(),0)).toString())->rowCount();
     int nbr=tmpclass.countStudentsPerClass(cid);
    if (nbr==0)
        ui->studlab->setText("This class has no students yet");
    else
        ui->studlab->setText("Students of the class "+cid+" : "+QString::number(nbr)+"  students/class : ");

    ui->classStudentView->setModel(tmpclass.studentsOfClass(ui->classView->model()->data(ui->classView->model()->index(ui->classView->currentIndex().row(),0)).toString()));

}


void Menu::on_unaffectstudent_clicked()
{
    if(ui->classStudentView->currentIndex().row()==-1)
            QMessageBox::information(nullptr, QObject::tr("Suppression"),
                              QObject::tr("Choose a student to unaffect  from class.\n"), QMessageBox::Cancel);
     else
        {
        QString cin =  ui->classStudentView->model()->data(ui->classStudentView->model()->index(ui->classStudentView->currentIndex().row(),0)).toString();
        QString cid =  ui->classView->model()->data(ui->classView->model()->index(ui->classView->currentIndex().row(),0)).toString();
        qDebug()<<cin;
        qDebug()<<cid;
       if(tmpstudent.unaffect_student_from_class(cin,cid))
       {
           QMessageBox::information(nullptr, QObject::tr("unaffect student from class"),
                             QObject::tr("Student removed from class.\n"), QMessageBox::Cancel);
           ui->classStudentView->setModel(tmpclass.studentsOfClass(cid));
           ui->studentstableview->setModel(tmpstudent.afficher_students());
       }else {

           QMessageBox::information(nullptr, QObject::tr("unaffect student from class"),
                             QObject::tr("Error .\n"), QMessageBox::Cancel);
}
    }
}

void Menu::on_deleteStudent_clicked()
{
    QString cin =  ui->studentstableview->model()->data(ui->studentstableview->model()->index(ui->studentstableview->currentIndex().row(),0)).toString();

    if(ui->studentstableview->currentIndex().row()==-1)
            QMessageBox::information(nullptr, QObject::tr("Suppression"),
                              QObject::tr("Please select a student to delete.\n"
                                          "Click Cancel to exit."), QMessageBox::Cancel);
        else if(tmpstudent.supprimer_student(cin))
            {
                ui->studentstableview->setModel(tmpstudent.afficher_students());

                QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                  QObject::tr("Success.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);


            }
            else
            {
                QMessageBox::information(nullptr, QObject::tr("Suppression"),
                                  QObject::tr("Erreur.\n"
                                              "Click Cancel to exit."), QMessageBox::Cancel);
            }
        }


void Menu::on_studentstableview_doubleClicked(const QModelIndex &index)
{
    ui->s_cin->setText(ui->studentstableview->model()->data(ui->studentstableview->model()->index(ui->studentstableview->currentIndex().row(),0)).toString());
    ui->s_firstname->setText(ui->studentstableview->model()->data(ui->studentstableview->model()->index(ui->studentstableview->currentIndex().row(),1)).toString());
    ui->s_lastname->setText(ui->studentstableview->model()->data(ui->studentstableview->model()->index(ui->studentstableview->currentIndex().row(),2)).toString());
    ui->s_email->setText(ui->studentstableview->model()->data(ui->studentstableview->model()->index(ui->studentstableview->currentIndex().row(),3)).toString());
    ui->s_phone->setText(ui->studentstableview->model()->data(ui->studentstableview->model()->index(ui->studentstableview->currentIndex().row(),4)).toString());
    ui->s_dob->setDate(ui->studentstableview->model()->data(ui->studentstableview->model()->index(ui->studentstableview->currentIndex().row(),5)).toDate());
    ui->s_email->setReadOnly(true);
    ui->s_cin->setReadOnly(true);
    ui->addStudent->setEnabled(false);
}

void Menu::on_notAffected_clicked()
{
    ui->studentstableview->setModel(tmpstudent.afficher_students_not_affected());
}

void Menu::on_UpdateStudent_clicked()
{
    student tmpstudent(ui->s_cin->text(),
                       ui->s_firstname->text(),
                       ui->s_lastname->text(),
                        ui->s_email->text(),
                       ui->s_phone->text());
    if(tmpstudent.modifier_student())
    {
        if(tmpstudent.affect_student_to_class(ui->s_cin->text(),ui->studentclass->currentText())){
        ui->classStudentView->setModel(tmpstudent.afficher_students());
        QMessageBox::information(nullptr, QObject::tr("Update"),
                          QObject::tr("Student updated and reaffected .\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);}

    }else{
        QMessageBox::information(nullptr, QObject::tr("Update"),
                          QObject::tr("Error.\n"
                                      "Click Cancel to exit."), QMessageBox::Cancel);

    }
}
