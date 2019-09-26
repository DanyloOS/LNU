#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    int N;
    double A [6][6];
    double B [6];
    double X [6];
    double C [6][6];

private slots:

    void on_spinBox_valueChanged(int arg1);

    void on_Solve_Button_clicked();

    void on_Clear_Button_clicked();

    void on_Exit_Button_clicked();
    
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
