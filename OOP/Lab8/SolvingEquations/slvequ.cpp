#include "slvequ.h"


double slvequ::fp(double x,double D) {
    return ((f(x+D)-f(x))/D);
}
double slvequ::f2p(double x,double D) {
    return ((fp(x+D,D)-fp(x,D))/D);
}

void slvequ::Solve(double a0, double b0, double function(double), std::vector <double> &x, std::vector <int> &L,
                   const int amountOfTab, const int amountOfDiv, const double accuracy, const MethodOfSolving method)
{
    N = amountOfTab;
    Kmax = amountOfDiv;
    eps = accuracy;
    f = function;

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
                if (method == 0) MPN(a, b, x, L);
                    else MN(a, b, x, L);
            }
        }
        else if (f(a0prev) < 0 && f(a0) > 0) {
            if ((f(a0prev) < f(a0prev + eps)) &&  (f(a0 - eps) < f(a0))){
                a = a0prev;
                b = a0;
                if (method == 0) MPN(a, b, x, L);
                    else MN(a, b, x, L);
            }
        }
        a0 += step;             // Збільшуємо значення а0, для перевірки наступного проміжку a0prev та a0
    }
}

void slvequ::Solve(double a0, double b0, double function(double), std::vector<double> &x, std::vector<int> &L, const MethodOfSolving method)
{
    f = function;

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
                if (method == 0) MPN(a, b, x, L);
                    else MN(a, b, x, L);
            }
        }
        else if (f(a0prev) < 0 && f(a0) > 0) {
            if ((f(a0prev) < f(a0prev + eps)) &&  (f(a0 - eps) < f(a0))){
                a = a0prev;
                b = a0;
                if (method == 0) MPN(a, b, x, L);
                    else MN(a, b, x, L);
            }
        }
        a0 += step;             // Збільшуємо значення а0, для перевірки наступного проміжку a0prev та a0
    }
}

void slvequ::setEps(double eps)
{
    this->eps = eps;
}
void slvequ::setKmax(int Kmax)
{
    this->Kmax = Kmax;
}
void slvequ::setN(int N)
{
    this->N = N;
}
/*//void slvequ::ShowResult(std::vector<double> &x, std::vector<int> L) {
//    QString result = "";
//    if (x.size() == 0) {
//        std::information(nullptr, "Увага", "Коренів рівняння не знайдено!:\n"
//                                                "Спробуйте ввести інший проміжок\n"
//                                                "Спробуйте ввести більше значення 'N'");
//        return;
//    }
//    for (unsigned int i = 0; i < x.size(); i++) {
//        result +=QString::number(x[i]) + "\t" + QString::number(L[i]) + "\n" ;
//    }
//    ui->textBrowser_result->setText(result);
//}*/

void slvequ::MN(double a, double b, std::vector <double> &x, std::vector <int> &L)
{
    double Dx;
    int i = 0;
    double D = eps/100.0;
    double x1 = b;


    if((f(x1)*f2p(x1, D) < 0))
        x1 = a;
    /*try {
        if(f(x1)*f2p(x1, D) < 0)
            throw -1001;
    } catch () {

    }*///if(f(x1)*f2p(x1, D) < 0)
        //QMessageBox::warning(nullptr, "Warning", "For this equation,the convergence of Newton`s method is not guaranteed");

    for(i = 0; i < Kmax; i++){
        Dx = f(x1)/fp(x1, D);
        x1 -= Dx;
        if (fabs(Dx) <= eps)
            break;
    }

    if (i == Kmax)
    {
        //QMessageBox::warning(nullptr, "Fail", "With a total number of iterations the solution is not found!");
        return;
    }

    x.push_back(x1);
    L.push_back(i);

}

void slvequ::MPN(double a, double b, std::vector <double> &x, std::vector <int> &L)
{
    L.push_back(0);

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
