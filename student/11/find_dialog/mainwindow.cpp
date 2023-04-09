#include "mainwindow.hh"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //connect function being used to establish between signals
    //and slots in the GUI application

    //member function
    connect(ui->findPushButton,
            &QPushButton::clicked,
            this,
            &MainWindow::on_findPushButton_clicked);
    //signal: clicked of
    //object, instance: ui->findPushButton
    //class:  QPushButton

    //send to
    //object: MainWindow
    //slot: on_findPushButton_clicked()

    //This means that whenever the
    //user clicks on the findPushButton button,
    //the on_findPushButton_clicked() function will be called.

    connect(ui->matchCheckBox,
            &QCheckBox::stateChanged,
            this,
            &MainWindow::on_matchCheckBox_stateChanged);
    //objects can emit signals
    //objects can emit signals
    //-> executing a slot
    //-> respond to those signals

    //object: ui->matchCheckBox
    //class: QCheckbox
    //signal: statechanged

    //object nhan: Mainwindow
    //slot: on_matchCheckBox_stateChanged
    //tuc la cu khi nao
    //co statechanged la function on_matchCheckBox_stateChanged
    //lai duoc called
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_findPushButton_clicked()
{
    QString inputFileName = ui->fileLineEdit->text().trimmed();
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
    Q_UNUSED(arg1);
}

