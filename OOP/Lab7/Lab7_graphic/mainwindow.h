#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QInputDialog>
#include "qcustomplot.h"



enum Function {quadStandart, trigSin, trigAdvanced};


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();//Сигнали взаємодії з нашою програмою
    void mousePress();
    void mouseWheel();
    void on_pushButton_Settings_clicked();
    void on_lineEdit_sizeOfArray_textChanged(const QString &arg1);
    void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);

private:
    Ui::MainWindow *ui;
    int sizeOfVector;
    QVector<double> x, y;
    QVector<bool> arg;
    double xMin, xMax;
    double yMin, yMax;
    QPen graphPen;

private:
    void SetupPlot(); //Початкове налаштування та ініціалізації усіх необхідних змінних з початковим параметром
    void writeXnY(QVector<double> &x, QVector<double> &y, double rangeLow, double rangeHigh, Function typeOfFunc); //Табуляція функції
    void Plot(int index); //Побудова графіка певної функції в залежності від аргумента


    friend class Settings; //Для вільного доступу до приватних змінних цього класу із класу Settings
};

#endif // MAINWINDOW_H
