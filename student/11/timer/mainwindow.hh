#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QTimer> //da khai bao cai object qtimer o day
//roi thi khong can them cai gi nua

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    //nay no chi la cai macro tell la co slot thoi

public:
    //constructor
    explicit MainWindow(QWidget *parent = 0);

    //destructor
    ~MainWindow();

    //private method no co gom timer
    QTimer *timer;

private slots:

    void on_closeButton_clicked();

    void on_startButton_clicked();

    void on_resetButton_clicked();

    void on_stopButton_clicked();

    void updateTimer();
private:
    Ui::MainWindow *ui;
    int seconds;
    int minutes;
};

#endif // MAINWINDOW_HH
