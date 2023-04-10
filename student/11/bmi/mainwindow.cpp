#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->countButton,
            &QPushButton::clicked,
            this,
            &MainWindow::on_countButton_clicked);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_countButton_clicked()
{

    height = ui->heightLineEdit->text().toFloat();
    weight = ui->weightLineEdit->text().toFloat();

    if(ui->heightLineEdit->text().isEmpty()
            || height == 0)
    {
        ui->resultLabel->setText("Cannot count.");

    }
    else
    {
        //tinh bmi
        bmi = weight/(height*height)*10000;

        QString bmiString = QString::number(bmi);
        ui->resultLabel->setText(bmiString);

        if(bmi<18.5)
        {
            ui->infoTextBrowser->setText("You are underweight.");
        }

        else if(bmi >= 18.5 && bmi <= 25)
        {
            ui->infoTextBrowser->setText("Your weight is normal.");
        }

        else if(bmi>25)
        {
            ui->infoTextBrowser->setText("You are overweight.");
        }
    }
}


void MainWindow::on_closeButton_clicked()
{
    close();
}

