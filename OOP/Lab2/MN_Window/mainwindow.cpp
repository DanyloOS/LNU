#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QString>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

double f(double x){
    return x*x*x - 8.0123;
}

double fp(double x,double D){
    return ((f(x+D)-f(x))/D);
}

double f2p(double x,double D){
    return ((fp(x+D,D)-fp(x,D))/D);
}

void MainWindow::on_pushButton_Exit_clicked()
{
    exit(0);
}

void MainWindow::on_pushButton_Solve_clicked()
{
    double a, b;        // а,б -- початок і кінець проміжку, на якому будемо  шукати корінь
    double eps;         // задана точність для пошуку кореня рівняння
    double x, Dx = 0;   // x -- корінь рівняння, Dx --
    int L, Kmax;        // L -- кількість поділів при знаходженні корення,

    ui->label_x->hide();
    ui->label_L->hide();
                                          // Перевіряємо, чи є пусті поля
    if (ui->lineEdit_a->text() == "")   { QMessageBox::warning(this, "Error", "Input 'a'!"); return; }
    if (ui->lineEdit_b->text() == "")   { QMessageBox::warning(this, "Error", "Input 'b'!"); return; }
    if (ui->lineEdit_Kmax->text() == ""){ QMessageBox::warning(this, "Error", "Input 'Kmax'!"); return; }
    if (ui->lineEdit_eps->text() == "") { QMessageBox::warning(this, "Error", "Input 'eps'!"); return; }

    if (ui->lineEdit_Kmax->text().toInt() > 150) QMessageBox::warning(this, "Warning",
                                                                      "Inputing a large 'Kmax' may cause lags!");
    if (ui->lineEdit_eps->text().toDouble() < 1e-11 || ui->lineEdit_eps->text().toDouble() > 1e-1) {
        QMessageBox::warning(this, "Error", "Input 'eps' in [1e-1; 1e-11]!");
        return;
    }

    a = ui->lineEdit_a->text().toDouble();
    b = ui->lineEdit_b->text().toDouble();
    Kmax = ui->lineEdit_Kmax->text().toInt();
    eps = ui->lineEdit_eps->text().toDouble();
    double D = eps/100.0;

    x = b;

    if((f(x)*f2p(x,D)<0))
        x = a;
    if((f(x)*f2p(x,D)<0)) // Перевіряємо графік функції на опуклість
        QMessageBox::warning(this, "Warning",
                             "For this equation,the convergence of Newton`s method is not guaranteed");

    for(L = 0; L < Kmax; L++){
        Dx = f(x)/fp(x, D);
        x -= Dx;
        if (fabs(Dx) <= eps)
            break;
    }

    if (L == Kmax) // Якщо L стало рівним Kmax, значить, закінчивши цикл, корінь не був знайдений
    {
        QMessageBox::warning(this, "Fail",
                             "With a total number of iterations the solution is not found!");
        return;
    }

    QMessageBox::information(this, "Succes", "Solution is found!");
    ui->label_x->setText("x* = " + QString::number(x));
    ui->label_L->setText("Кількість поділів: " + QString::number(L));
    ui->label_x->show();
    ui->label_L->show();
}
