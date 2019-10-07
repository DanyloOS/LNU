#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"
#include "dsignal.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pb_plot_clicked();
    void on_cb_scaled_stateChanged(int arg1);
    void on_cb_timeShifted_stateChanged(int arg1);
    void on_cb_expanded_stateChanged(int arg1);
    void graphClicked(QCPAbstractPlottable *plottable, int dataIndex);
    void on_cb_signalscount_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    bool args1[5] = {};
    bool args2[5] = {};
    QVector <double> x, y;
    QVector <double> signal1, signal2;
    QPen pen;

    double stepDscr;
    int sScaled;
    float sShifted;
    int sExpanded;

    void Setup();
    void Plot(int index);
    QVector<double> Parse(QString str);
};
#endif // MAINWINDOW_H
