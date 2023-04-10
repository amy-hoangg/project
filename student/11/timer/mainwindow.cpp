#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    //may cai nay la private ca
    timer(new QTimer(this)),
    ui(new Ui::MainWindow),
    seconds(0),
    minutes(0)
{
    ui->setupUi(this);

    //lan nay minh se khong connect cai
    //click nua ma torng cai click co timer san roi
    //thi lan nay phai connect cai timer, neu
    //timeout thi sao
    connect(timer,
            &QTimer::timeout,
            this,
            &MainWindow::updateTimer);

    //khi minh click thi minh se can den cai funciton nao
    connect(ui->startButton,
            &QPushButton::clicked,
            this,
            &MainWindow::on_startButton_clicked);

    connect(ui->resetButton,
            &QPushButton::clicked,
            this,
            &MainWindow::on_resetButton_clicked);

    connect(ui->stopButton,
            &QPushButton::clicked,
            this,
            &MainWindow::on_stopButton_clicked);

    connect(ui->closeButton,
            &QPushButton::clicked,
            this,
            &MainWindow::on_closeButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_closeButton_clicked()
{
    timer->stop();
    close();
}

void MainWindow::on_startButton_clicked()
{
    //cho cai qtimer start
    //default cua no la msc milisecond
    timer->start(1000);
}


void MainWindow::on_resetButton_clicked()
{
    seconds = 0;
    minutes = 0;
    //update the display
    ui->lcdNumberMin->display(minutes);
    ui->lcdNumberSec->display(seconds);
}


void MainWindow::on_stopButton_clicked()
{
    timer->stop();
}

void MainWindow::updateTimer()
{
    seconds++;
    if (seconds == 60)
    {
        seconds = 0;
        minutes++;
    }

    //update the display
    ui->lcdNumberMin->display(minutes);
    ui->lcdNumberSec->display(seconds);
}

