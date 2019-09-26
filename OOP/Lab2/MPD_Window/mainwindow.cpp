#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <cmath>
#define PI 3.14159265359

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

double f (double x)
{
    return cos(4*x*PI)+sin(8*x*PI);
}
void MPN(double a, double b, std::vector<double> &x, std::vector<int> &L, double eps);
void Solve(double a0, double b0, int N, std::vector <double> &x, std::vector <int> &L, double eps = 1e-3);


void MainWindow::on_pushButton_Exit_clicked()
{
    exit(0);
}

void MainWindow::on_pushButton_Solve_clicked()
{
    double a0, b0, eps;         // Оголошуємо змінні, для подальшого ініціалізування введеними користувачем данними
    int N;
    std::vector <double> x;     // Оголошуємо вектор Х для подальшого добавляння у нього знайденних коренів рівняння
    std::vector <int> L;

    if (ui->line_a->text() == "")   { QMessageBox::warning(this, "Помилка", "Введіть 'a'!"); return; } // Перевірка на введення
    if (ui->line_b->text() == "")   { QMessageBox::warning(this, "Помилка", "Введіть 'b'!"); return; } // данних
    if (ui->line_N->text() == "")   { QMessageBox::warning(this, "Помилка", "Введіть 'N'!"); return; }
    if (ui->line_eps->text() == "") { QMessageBox::warning(this, "Помилка", "Введіть 'eps'!"); return; }

    a0 = ui->line_a->text().toDouble();
    b0 = ui->line_b->text().toDouble();
    N = ui->line_N->text().toInt();
    eps = ui->line_eps->text().toDouble();

    if (eps < 1e-15 || eps > 1e-2) {
        QMessageBox::warning(this, "Помилка", "Введіть eps в межах [1e-2; 1e-15] !");      // Перевірка на правильність
        return;                                                                            // введеного eps
    }
    if (b0 < a0) std::swap (a0, b0);    // міняємо місцями b0 i a0, якщо b0 < a0
    Solve(a0, b0, N, x, L, eps);        // викликаємо функцію для розв'язку рівняння

    if (x.size() == 0) {                // якщо вектор коренів пустий, рівняння розв'язати не вдалось
        QMessageBox::information(this, "Увага", "Коренів рівняння не знайдено!:\n"
                                                "Перевірте правильність введених даних\n"
                                                "Спробуйте ввести більше значення 'N'");
    }
    QString text;                       // змінна, для виведення у textBrowser знайдених коренів
    for (unsigned long long i = 0; i < x.size(); i++) {
        text +=QString::number(x[i]) + "\t\t" + QString::number(L[i]) + "\n" ; // записуємо усі знайденні корені у змінну
    }
    ui->textBrowser->setText(text);
}

void MPN(double a, double b, std::vector <double> &x, std::vector <int> &L, double eps)
{
    L.push_back(0);                 //Добавляємо елемент рівний 0 у вектор L
    double c = a + 0.5*(b - a);
    while (fabs(a - b) > eps ) {    //Цикл, який ділить проміжок на 2, поки він більший за епсилон
        L[L.size()-1]++;            //Збільшуємо останній елемент у векторі L на 1
        c = a + 0.5*(b - a);        //Знаходимо середину відрізку

        if (fabs(f(c)) < eps) {     //Перевіряємо, чи на середині відрізку немає кореня
            x.push_back(c);
            return;

        }
        if (f(a)*f(c) < 0)          //Присвоюємо нові межі відрізку в залежності
            b = c;                  //від розміщення кореня
        else
            a = c;
    }
    x.push_back(c);                 //Добавляємо знайдений корінь в вектор 'x'
}

void Solve(double a0, double b0, int N, std::vector <double> &x, std::vector <int> &L, double eps)
{
    double a, b;                    // Для подальшого запису у них проміжків із кореннями
    double step = fabs(a0 - b0)/N;  // Крок для табуляції
    double a0prev;                  // Вводимо додаткову змінну, для кращого візуального сприйняття коду
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
        else if (f(a0prev) > 0 && f(a0) < 0) {// Якщо функція в данних двох точках має і додадтнє, і від'ємне значення
            if ((f(a0prev) > f(a0prev + eps)) &&  (f(a0 - eps) > f(a0))){
                a = (a0prev);
                b = (a0);
                MPN(a, b, x, L, eps);
            }
        }
        else if (f(a0prev) < 0 && f(a0) > 0) {
            if ((f(a0prev) < f(a0prev + eps)) &&  (f(a0 - eps) < f(a0))){
                a = a0prev;
                b = a0;
                MPN(a, b, x, L, eps);
            }
        }
        a0 += step;             // Збільшуємо значення а0, для перевірки наступного проміжку a0prev та a0
    }
}
