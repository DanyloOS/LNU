#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <cmath>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void paintEvent(QPaintEvent *event); //Створюємо подію, яка буде перемальовувати графік

private slots:
    void on_button1_clicked();
    void on_button2_clicked();

private:
    Ui::MainWindow *ui;

    double Xe [1000];
    double Ye [1000];

    double Kx, Ky, Zx, Zy;
    double a1, b1;
    int Ne, x1, y1;
    double maxx, maxy, minx, miny;
    double krx, kry, xx, yy, Gx, Gy;
    int KrokX, KrokY, L;
    int pb_Height;
    int pb_Width;
    QPen *pen1;
    QPen *pen2;
    QPen *pen3;
    QPen *pen4;
    QFont *font1;

    void TabF(double *Xe, double *Ye);
};

#endif // MAINWINDOW_H
