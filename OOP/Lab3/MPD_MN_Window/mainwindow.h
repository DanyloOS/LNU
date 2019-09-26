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
public:

    Ui::MainWindow *ui;


private slots:
    void on_pushButton_Exit_clicked();
    void on_comboBox_method_currentIndexChanged(int index);
    void on_pushButton_Solve_clicked();
    void on_pushButton_Clear_clicked();

private:
    void MPN(double a, double b, std::vector <double> &x, std::vector <int> &L);
    void MN(double a, double b, std::vector<double> &x, std::vector<int> &L);
    void Solve(std::vector <double> &x, std::vector <int> &L);
    void ShowResult(std::vector<double> &x, std::vector<int> L);
    double f (double x);
    double fp(double x,double D);
    double f2p(double x,double D);

};

#endif // MAINWINDOW_H
