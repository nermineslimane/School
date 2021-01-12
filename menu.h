#ifndef MENU_H
#define MENU_H

#include <QMainWindow>
#include "teacher.h"

#include<QDebug>
#include <QDialog>
#include <QValidator>
#include <QDialog>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QFormLayout>
#include <QPushButton>
#include <QValidator>
#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QPainter>
#include <QPdfWriter>
#include <QPrinter>
#include <QtPrintSupport>
#include <QPrintDialog>
#include "module.h"
#include "classroom.h"
#include "student.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Menu; }
QT_END_NAMESPACE

class Menu : public QMainWindow
{
    Q_OBJECT

public:
    Menu(QWidget *parent = nullptr);
    ~Menu();

private slots:
    //action on button addTeacher
    void on_addTeacher_clicked();
      //action on button print pdf list of teachers
    void on_print_clicked();
      //action on button delete teacher
    void on_deleteTeacher_clicked();
      //action on button update teacher
    void on_updateTeacher_clicked();
      //action on find text edited
    void on_find_textEdited(const QString &arg1);
    //fill teacher's update form
    void on_tabTeacher_doubleClicked(const QModelIndex &index);
    //action to add module
    void on_addModule_clicked();
    //action to  delete module
    void on_deleteModule_clicked();
    //action to update module
    void on_updateModule_clicked();
    //action to affect teacher to module
    void on_affect_clicked();
    // action to unaffect teacher from module
    void on_unaffect_clicked();

    void on_IDModule_currentIndexChanged(int index);

    void on_listModules_doubleClicked(const QModelIndex &index);

    void on_addClass_clicked();

    void on_classLV_currentIndexChanged(int index);

    void on_addStudent_clicked();

    void on_classST_currentIndexChanged(int index);

    void on_classAY_currentIndexChanged(int index);

    void on_classView_doubleClicked(const QModelIndex &index);

    void on_s_lastname_textEdited(const QString &arg1);

    void on_unaffectstudent_clicked();

    void on_deleteStudent_clicked();

    void on_studentstableview_doubleClicked(const QModelIndex &index);

    void on_notAffected_clicked();

    void on_UpdateStudent_clicked();

private:
    Ui::Menu *ui;
    //instance of class teacher
    Teacher tmpteacher;
    //instance of class module
    module tmpmodule;
    //instance of classroom
    classroom tmpclass;
    //instance of student
    student tmpstudent;

};
#endif // MENU_H
