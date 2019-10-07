#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Setup();
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pb_plot_clicked()
{
    ui->customPlot->clearGraphs();
    stepDscr = ui->dsb_stepDscr->value();

    if (ui->cb_signalscount->currentIndex() == 0) {
        args1[0] = ui->cb_input->checkState();
        args1[1] = ui->cb_scaled->checkState();
        args1[2] = ui->cb_reversed->checkState();
        args1[3] = ui->cb_timeShifted->checkState();
        args1[4] = ui->cb_expanded->checkState();

//        QString str = ui->te_inputSignal1->toPlainText();
        signal1 = Parse(ui->te_inputSignal1->toPlainText());

        sScaled = ui->dsb_scaled->value();
        sShifted = ui->sb_timeShifted->value();
        sExpanded = ui->sb_expanded->value();

        for (int i = 0; i < 5; i++)
            if(args1[i]) Plot(i);
    } else {
        args2[0] = ui->cb_input1->checkState();
        args2[1] = ui->cb_input2->checkState();
        args2[2] = ui->cb_addition->checkState();
        args2[3] = ui->cb_multiplication->checkState();
        args2[4] = ui->cb_conv->checkState();

        signal1 = Parse(ui->te_inputSignal1->toPlainText());
        signal2 = Parse(ui->te_inputSignal2->toPlainText());

        for (int i = 0; i < 5; i++)
            if(args2[i]) Plot(i);
    }

}

void MainWindow::on_cb_scaled_stateChanged(int arg1)
{
    ui->dsb_scaled->setEnabled(arg1);
}
void MainWindow::on_cb_timeShifted_stateChanged(int arg1)
{
    ui->sb_timeShifted->setEnabled(arg1);
}
void MainWindow::on_cb_expanded_stateChanged(int arg1)
{
    ui->sb_expanded->setEnabled(arg1);
}
void MainWindow::Plot(int index)
{
    ui->customPlot->addGraph();

    if (ui->cb_signalscount->currentIndex() == 0) {
        switch (index) {
        case 0: {
            y = signal1;
            ui->customPlot->plottable()->setName("Input signal");
            break;
        }
        case 1: {
            y = dSignal::Scale(signal1,sScaled);
            ui->customPlot->plottable()->setName("Scaled");
            break;
        }
        case 2: {
            y = dSignal::Reverse(signal1);
            ui->customPlot->plottable()->setName("Reversed");
            break;
        }
        case 3: {
            y = dSignal::Time_shift(signal1,sShifted/stepDscr);
            ui->customPlot->plottable()->setName("Time shifted");
            break;
        }
        case 4: {
            y = dSignal::Expand(signal1,sExpanded);
            ui->customPlot->plottable()->setName("Expanded");
            break;
        }
        }
    } else {
        switch (index) {
        case 0: {
            y = signal1;
            ui->customPlot->plottable()->setName("Input signal1");
            break;
        }
        case 1: {
            y = signal2;
            ui->customPlot->plottable()->setName("Input signal2");
            break;
        }
        case 2: {
            y = dSignal::Addition(signal1, signal2);
            ui->customPlot->plottable()->setName("Addition");
            break;
        }
        case 3: {
            y = dSignal::Multiplication(signal1, signal2);
            ui->customPlot->plottable()->setName("Multiplication");
            break;
        }
        case 4: {
            y = dSignal::Conv(signal1, signal2);
            ui->customPlot->plottable()->setName("Convertation");
            break;
        }
        }
    }

    x.resize(y.size());
    double temp = 0;
    double yMax = y[0];
    for (int i = 0; i < y.size(); ++i) {
        x[i] = temp;
        temp += stepDscr;
        if (yMax < y[i]) yMax = y[i];
    }


    pen.setColor(QColor(qrand() % 255, qrand() % 255, qrand() % 255));
    ui->customPlot->graph()->setPen(pen);

    ui->customPlot->yAxis->setRange(-yMax-1, yMax+1);
    ui->customPlot->xAxis->setRange(0, 0.5*y.size());
    ui->customPlot->graph()->setData(x,y);
    ui->customPlot->graph()->setLineStyle(QCPGraph::lsImpulse);
    ui->customPlot->graph()->setScatterStyle(QCPScatterStyle::ssCircle);
//    ui->customPlot->graph()->setScatterSkip(2)
    ui->customPlot->replot();
}
QVector<double> MainWindow::Parse(QString str)
{
    QStringList list = str.split(" ",QString::SkipEmptyParts);
    QVector<double> signal;
    foreach(QString num, list)
        signal.push_back(num.toDouble());
    return signal;
}
void MainWindow::Setup()
{   //Створюємо події, з якими будемо працювати
    ui->customPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                    QCP::iSelectLegend | QCP::iSelectPlottables);

    ui->customPlot->legend->setVisible(true);

    // Зв'язуємо слоти із сигналами
    connect(ui->customPlot, SIGNAL(mousePress(QMouseEvent*)), this, SLOT(mousePress()));
    connect(ui->customPlot, SIGNAL(mouseWheel(QWheelEvent*)), this, SLOT(mouseWheel()));
    connect(ui->customPlot, SIGNAL(plottableClick(QCPAbstractPlottable*,int,QMouseEvent*)),
            this, SLOT(graphClicked(QCPAbstractPlottable*,int)));


    pen.setWidthF(2);//rand()/(double)RAND_MAX*2+1);

    ui->cb_input->setCheckState(Qt::Checked);
    ui->dsb_scaled->setEnabled(0);
    ui->sb_expanded->setEnabled(0);
    ui->sb_timeShifted->setEnabled(0);
    ui->dsb_stepDscr->setValue(0.5);

    ui->w_signal2->hide();
    ui->w_wtp2->hide();

    sScaled = 0;
    sShifted = 0;
    sExpanded = 1;
    stepDscr = 0.5;
}
void MainWindow::graphClicked(QCPAbstractPlottable *plottable, int dataIndex)
{
  double dataValue = plottable->interface1D()->dataMainValue(dataIndex);
  QString message = QString("Clicked on graph '%1' at x = %2 and y = %3.").arg(plottable->name()).arg(x[dataIndex]).arg(dataValue);
  ui->statusbar->showMessage(message, 5000);
}
void MainWindow::on_cb_signalscount_currentIndexChanged(int index)
{
    if (index == 0) {
        ui->w_signal2->hide();
        ui->w_wtp2->hide();
        ui->w_wtp1->show();
    } else {
        ui->w_wtp1->hide();
        ui->w_wtp2->show();
        ui->w_signal2->show();
    }
}
