#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH
#include <QMainWindow>
#include <QFile>
/*
 * namespaces are used to organize classes,
 * functions, and other entities.
 *
 * QT_BEGIN_NAMESPACE and QT_END_NAMESPACE macros
 * are used to define the beginning and end of the Qt namespace.
 *
 * a macro is a sequence of instructions or statements
 *  that is defined once and can be used multiple times.
 *
 *  macros are defined using the #define directive.
 *
 *  By using namespaces, it becomes easier to avoid
 *  naming conflicts and to organize code into logical groups.
 *   The QT_BEGIN_NAMESPACE and QT_END_NAMESPACE macros are used to ensure that the Qt namespace is properly defined and enclosed.
 */


QT_BEGIN_NAMESPACE //macro define the begining
namespace Ui { class MainWindow; }
//namespace named ui
//class MainWindow
QT_END_NAMESPACE

class MainWindow : public QMainWindow //goi ten me
{
    Q_OBJECT
    /*The Q_OBJECT macro is used to enable Qt's meta-object
     * system, which provides features like signals and slots,
     * dynamic property handling, and reflection.
     */

public:
    MainWindow(QWidget *parent = nullptr);
    //The MainWindow constructor is defined with
    //a default argument of nullptr for the parent parameter.
    //This means that if no parent is provided when creating a
    //MainWindow object, it will be assigned a null pointer.

    ~MainWindow();


private slots:

    void on_findPushButton_clicked();
    void on_matchCheckBox_stateChanged(int arg1);

private:
    //The Ui::MainWindow *ui pointer is a
    //private member variable of the MainWindow class,
    //which points to an object of type Ui::MainWindow.
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_HH
