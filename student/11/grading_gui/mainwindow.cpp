#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)

    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->spinBoxN->setMinimum(0);
    ui->spinBoxN->setMaximum(MAX_N_POINTS);

    ui->spinBoxG->setMinimum(0);
    ui->spinBoxG->setMaximum(MAX_G_POINTS);

    ui->spinBoxP->setMinimum(0);
    ui->spinBoxP->setMaximum(MAX_P_POINTS);

    ui->spinBoxE->setMinimum(0);

    connect(ui->calculatePushButton,
                &QPushButton::clicked,
                this,
                &MainWindow::on_calculatePushButton_clicked);
    //chi khi minh click thi minh moi can thay doi thoi

}
MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_calculatePushButton_clicked()
{
    int n_points = ui->spinBoxN->value();
    int g_points = ui->spinBoxG->value();
    int p_points = ui->spinBoxP->value();
    int e_points = ui->spinBoxE->value();

    unsigned int scoreFromWeeklyExercises
            = score_from_weekly_exercises(n_points,
                                          g_points);
    unsigned int scoreFromProjects
            = score_from_projects(p_points);

    unsigned int calculateTotalGrade = calculate_total_grade(n_points,
                                                             g_points,
                                                             p_points,
                                                             e_points);

    QString result = "W-Score: " + QString::number(scoreFromWeeklyExercises) + "\n" +
                     "P-Score: " + QString::number(scoreFromProjects) + "\n" +
                     "Total grade: " + QString::number(calculateTotalGrade);

    ui->textBrowser->setText(result);
}


