#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_fineLineEdit_textChanged(const QString &arg1)
{
    ui->textBrowser->setText("");
}

void MainWindow::on_keyLineEdit_textChanged(const QString &arg1)
{
    ui->textBrowser->setText("");
}

void MainWindow::on_findPushButton_clicked()
{
    QString inputFileName = ui->fineLineEdit->text().trimmed();
    QString targetWord = ui->keyLineEdit->text().trimmed();
    bool matchCase = ui->matchCheckBox->isChecked();

    if (inputFileName.isEmpty())
    {
        ui->textBrowser->setText("File not found");
        return;
    }

    QFile inputFile(inputFileName);
    if (!inputFile.exists())
    {
        ui->textBrowser->setText("File not found");
        return;
    }

    if (inputFile.exists()
            && targetWord.isEmpty())
    {
        ui->textBrowser->setText("Find found");
        return;
    }

    if (inputFile.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream lineInFile(&inputFile);
        bool targetWordFound = false;

        while (!lineInFile.atEnd())
        {
            QString line = lineInFile.readLine();
            if (matchCase)
            {
                if (line.contains(targetWord))
                {
                    targetWordFound = true;
                    break;
                }
            }
            else
            {
                if(line.toLower().
                        contains(targetWord.toLower()))
                {
                    targetWordFound = true;
                    break;
                }
            }
        }

        inputFile.close();

        if (targetWordFound)
        {
            ui->textBrowser->setText("Word found");
        }
        else
        {
            ui->textBrowser->setText("Word not found");
        }
    }


    else
    {
        ui->textBrowser->setText("Find not found");
    }
}



void MainWindow::on_matchCheckBox_stateChanged(int arg1)
{

}

