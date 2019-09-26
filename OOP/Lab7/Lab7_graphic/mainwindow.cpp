#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include <cmath>

const double PI = 3.14159265359;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetupPlot();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::writeXnY(QVector<double> &x, QVector<double> &y, double rangeLow, double rangeHigh, Function typeOfFunc)
{
    double step = (rangeHigh - rangeLow)/(sizeOfVector - 1);
    switch (typeOfFunc) {
    case quadStandart: {
        for (int i = 0; i < sizeOfVector; i++, rangeLow += step) {
            x[i] = rangeLow;
            y[i] = x[i]*x[i];
        }
        break;
    }
    case trigSin: {
        for (int i = 0; i < sizeOfVector; i++, rangeLow += step) {
            x[i] = rangeLow;
            y[i] = qSin(x[i]);
        }
        break;
    }
    case trigAdvanced: {
        for (int i = 0; i < sizeOfVector; i++, rangeLow += step) {
            x[i] = rangeLow;
            y[i] = qCos(4*x[i]*PI)+qSin(8*x[i]*PI);

        }
    }
    }
}

void MainWindow::SetupPlot()
{   //Створюємо події, з якими будемо працювати
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);

    ui->customPlot->legend->setVisible(true);

    // Зв'язуємо слоти із сигналами
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));

    connect(ui->customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)),
            this, SLOT(graphClicked(QCPAbstractPlottable*,int)));

    sizeOfVector = 100; //Ініціазілуємо змінні з початковими значеннями
    xMin = 0; xMax = 5;
    yMin = 0; yMax = 0;

    ui->checkBox_qdStan->setChecked(true);
    ui->lineEdi_xMax->setText("5");
    ui->lineEdit_xMin->setText("0");
    ui->lineEdit_sizeOfArray->setText("100");

    graphPen.setWidthF(2);//rand()/(double)RAND_MAX*2+1);

    arg.resize(3);
    arg = {1, 0, 0};

    for (int i = 0; i < arg.size(); i++)
        if (arg[i]) Plot(i); //Залежно від параметрів у CheckBox'і будуємо відповідний графік
}

void MainWindow::Plot(int index)
{
    if (sizeOfVector != x.size()) { //змінюємо розмір вектора точок, якщо користувач змінив кількість точок
    x.resize(sizeOfVector);
    y.resize(sizeOfVector);
    }

    writeXnY(x, y, xMin, xMax, static_cast<Function>(index));

    yMin = y[0];
    yMax = y[0];
    for(int i = 0; i < y.size(); i++) {
        if (yMin > y[i]) yMin = y[i];
        if (yMax < y[i]) yMax = y[i];
    }

    ui->customPlot->addGraph();

    switch (static_cast<Function>(index)) {
    case quadStandart:  ui->customPlot->plottable()->setName("y = x^2"); break;
    case trigSin:       ui->customPlot->plottable()->setName("y = sin(x)"); break;
    case trigAdvanced:  ui->customPlot->plottable()->setName("y = cos(4*pi*x) + sin(8*pi*x)"); break;
    }

    ui->customPlot->xAxis->setRange(xMin, xMax);             //
    ui->customPlot->yAxis->setRange(yMin, yMin+(xMax-xMin)); //Маштабуємо графік
    ui->customPlot->graph()->setData(x, y);

    graphPen.setColor(QColor(rand()%245+10, rand()%245+10, rand()%245+10)); //Параметри ліній графіка
    ui->customPlot->graph()->setPen(graphPen);

    ui->customPlot->replot();
}

void MainWindow::on_pushButton_clicked()
{
    xMin = ui->lineEdit_xMin->text().toDouble();
    xMax = ui->lineEdi_xMax->text().toDouble();

    if (xMax < xMin) std::swap (xMax, xMin);

    arg.resize(0);
    ui->customPlot->clearGraphs();

    arg.push_back(ui->checkBox_qdStan->checkState());
    arg.push_back(ui->checkBox_tgSin->checkState());
    arg.push_back(ui->checkBox_tgAdv->checkState());

    for (int i = 0; i < arg.size(); i++) {
        if (arg[i]) Plot(i);
    }

}

void MainWindow::mousePress()
{

  if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeDrag(ui->customPlot->xAxis->orientation());
  else if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeDrag(ui->customPlot->yAxis->orientation());
  else
    ui->customPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);
}

void MainWindow::mouseWheel()
{

  if (ui->customPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeZoom(ui->customPlot->xAxis->orientation());
  else if (ui->customPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
    ui->customPlot->axisRect()->setRangeZoom(ui->customPlot->yAxis->orientation());
  else
    ui->customPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void MainWindow::on_pushButton_Settings_clicked()
{
    Settings stngsWindow(this);
    stngsWindow.setWindowTitle("Settings");
    stngsWindow.setModal(true);
    stngsWindow.exec();
}

void MainWindow::on_lineEdit_sizeOfArray_textChanged(const QString &arg1)
{
    if(!arg1.isEmpty())
            sizeOfVector = ui->lineEdit_sizeOfArray->text().toInt();
}

void MainWindow::graphClicked(QCPAbstractPlottable *plottable, int dataIndex)
{
  double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
  QString message = QString("Clicked on graph '%1' at x = %2 and y = %3.").arg(plottable->name()).arg(x[dataIndex]).arg(dataValue);
  ui->statusBar->showMessage(message, 5000);
}
