#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QMessageBox>
#include <QString>
#define PI 3.14159265359

using namespace std;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->label_Kmax->hide();
    ui->line_Kmax->hide();
    ui->comboBox_method->setCurrentIndex(-1);
    ui->comboBox_equation->setCurrentIndex(-1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_Exit_clicked()
{
    exit(0);
}
void MainWindow::on_comboBox_method_currentIndexChanged(int index)
{
    if(index) {
        ui->line_Kmax->show();
        ui->label_Kmax->show();
    }
    else {
        ui->line_Kmax->hide();
        ui->label_Kmax->hide();
    }
}
void MainWindow::on_pushButton_Solve_clicked()
{
    QString result = "";
    std::vector <double> x;
    std::vector <int> L;

    if (ui->line_a->text() == "")   { QMessageBox::warning(this, "Помилка", "Введіть 'a'!"); return; }   //Обробляємо випадки введення
    if (ui->line_b->text() == "")   { QMessageBox::warning(this, "Помилка", "Введіть 'b'!"); return; }  //невірних данних
    if (ui->line_N->text() == "")   { QMessageBox::warning(this, "Помилка", "Введіть 'N'!"); return; }
    if (ui->line_eps->text() == "") { QMessageBox::warning(this, "Помилка", "Введіть 'eps'!"); return; }
    if (ui->comboBox_method->currentIndex() == -1) { QMessageBox::warning(this, "Помилка", "Виберіть метод!"); return; }
    if (ui->comboBox_equation->currentIndex() == -1) { QMessageBox::warning(this, "Помилка", "Виберіть рівняння!"); return; }

    if (ui->line_eps->text().toDouble() < 1e-16 || ui->line_eps->text().toDouble() > 1e-2) {
        QMessageBox::warning(this, "Помилка", "Введіть eps в межах [1e-2; 1e-16] !");
        return;
    }

    if (ui->comboBox_method->currentIndex() == 1)
        if (ui->line_Kmax->text() == "") { QMessageBox::warning(this, "Помилка", "Введіть 'Kmax'!"); return; }
    MainWindow::Solve(x, L);        //Викликаємо метод Solve для розв'язання нашого рівняння
    MainWindow::ShowResult(x, L);   //виводимо результат на екран

}
void MainWindow::on_pushButton_Clear_clicked()
{
    ui->label_Kmax->hide();
    ui->line_Kmax->hide();
    ui->comboBox_method->setCurrentIndex(-1);
    ui->comboBox_equation->setCurrentIndex(-1);
    ui->line_a->setText("");
    ui->line_b->setText("");
    ui->line_N->setText("");
    ui->line_eps->setText("");
    ui->line_Kmax->setText("");
    ui->textBrowser_result->setText("");
}

double MainWindow::f (double x)
{
    if(ui->comboBox_equation->currentIndex() == 0) return x*x - 4.033;
    else return 3*x - 4*log(x) - 5;
}
double MainWindow::fp(double x,double D) {
    return ((MainWindow::f(x+D)-MainWindow::f(x))/D);
}
double MainWindow::f2p(double x,double D) {
    return ((fp(x+D,D)-fp(x,D))/D);
}
void MainWindow::MPN(double a, double b, vector <double> &x, vector <int> &L)
{
    L.push_back(0);
    double eps = ui->line_eps->text().toDouble();
    double c = a + 0.5*(b - a);

    if (f(a)*f(b) < 0) {
        while (fabs(a - b) > eps ) {
            L[L.size()-1]++;
            c = a + 0.5*(b - a);

            if (fabs(f(c)) < eps) {
                x.push_back(c);
                return;

            }
            if (f(a)*f(c) < 0)
                b = c;
            else
                a = c;
        }
    }
    x.push_back(c);
}
void MainWindow::MN(double a, double b, vector <double> &x, vector <int> &L) {
    double eps = ui->line_eps->text().toDouble();
    int Kmax = ui->line_Kmax->text().toInt();
    double Dx;
    int i;
    double D = eps/100.0;
    double x1 = b;


    if((MainWindow::f(x1)*MainWindow::f2p(x1, D) < 0))
        x1 = a;
    if(MainWindow::f(x1)*MainWindow::f2p(x1, D) < 0)
        QMessageBox::warning(nullptr, "Warning", "For this equation,the convergence of Newton`s method is not guaranteed");

    for(i = 0; i < Kmax; i++){
        Dx = f(x1)/fp(x1, D);
        x1 -= Dx;
        if (fabs(Dx) <= eps)
            break;
    }

    if (i == Kmax)
    {
        QMessageBox::warning(nullptr, "Fail", "With a total number of iterations the solution is not found!");
        return;
    }

    x.push_back(x1);
    L.push_back(i);

}
void MainWindow::Solve(vector <double> &x, vector <int> &L)
{
    double eps = ui->line_eps->text().toDouble();
    double a0 = ui->line_a->text().toDouble();
    double b0 = ui->line_b->text().toDouble();
    int N = ui->line_N->text().toInt();
    double step = fabs(a0 - b0)/N;
    double a, b, a0prev;
    if (fabs(f(a0)) < eps){         // Перевіряємо, чи на початку користувацького проміжку немає корення
        x.push_back(a0);            // Якщо а0 розв'язок, добавляємо його у вектор коренів
        L.push_back(0);             // Добавляємо "0" у вектор L
        a0 += step;                 // Зсуваємо початок проміжку, щоб не дублювати перевірку при одному
    }                               // значенні а0
    if (fabs(f(b0)) < eps ){        // Перевіряємо, чи на кінці проміжку немає корення
        x.push_back(b0);
        L.push_back(0);
        b0 -= step;
    }

    a0 += step;                     // Збільшуємо a0 на крок, щоб у циклі розпочинати перевірку попереднього
                                    // значення -- a0prev та a0
    while (a0 <= b0) {              // поки не кінець проміжку, виконуємо цикл
        a0prev = a0 - step;
        if (fabs(f(a0)) < eps)      // робимо перевірку на початку проміжку
                {
                    x.push_back(a0);
                    L.push_back(0);
                    a0 += step;
                }
        else if (f(a0prev) > 0 && f(a0) < 0) {
            if ((f(a0prev) > f(a0prev + eps)) &&  (f(a0 - eps) > f(a0))){
                a = (a0prev);
                b = (a0);
                if (ui->comboBox_method->currentIndex() == 0) MainWindow::MPN(a, b, x, L);
                    else MainWindow::MN(a, b, x, L);
            }
        }
        else if (f(a0prev) < 0 && f(a0) > 0) {
            if ((f(a0prev) < f(a0prev + eps)) &&  (f(a0 - eps) < f(a0))){
                a = a0prev;
                b = a0;
                if (ui->comboBox_method->currentIndex() == 0) MainWindow::MPN(a, b, x, L);
                    else MainWindow::MN(a, b, x, L);
            }
        }
        a0 += step;             // Збільшуємо значення а0, для перевірки наступного проміжку a0prev та a0
    }
}
void MainWindow::ShowResult(std::vector<double> &x, std::vector<int> L) {
    QString result = "";
    if (x.size() == 0) {
        QMessageBox::information(nullptr, "Увага", "Коренів рівняння не знайдено!:\n"
                                                "Спробуйте ввести інший проміжок\n"
                                                "Спробуйте ввести більше значення 'N'");
        return;
    }
    for (unsigned int i = 0; i < x.size(); i++) {
        result +=QString::number(x[i]) + "\t" + QString::number(L[i]) + "\n" ;
    }
    ui->textBrowser_result->setText(result);
}
