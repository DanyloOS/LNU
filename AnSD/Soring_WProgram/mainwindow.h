#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "sorting.h"
#include "result.h"
#include "qtcustomplot/qcustomplot.h"
#include <string>
#include <random>
#include <ctime>

enum TypeOfData {Integer, Float, Double, Char, String};

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
    void on_comboBox_inputMethod_currentIndexChanged(int index);
    void on_pushButton_Sort_clicked();
    void on_comboBox_sortingMethod_currentIndexChanged(int index);

    void on_checkBox_pTime_stateChanged(int arg1);

    void on_comboBox_workingMode_currentIndexChanged(int index);

private:
    Ui::MainWindow *ui;
    int amountOfData;
    TypeOfData dataType;
    SortingMethod srtMethod;
    void* Data;
    void* cData;
    unsigned int N;
    unsigned amountOfSortingMethods;
    double rangeA;
    double rangeB;
    double *srtTime;
//    double **srtTimeAdv;
    bool* argSortingMethods;
    Result wResult;


private:
    void SetupWindow();
    void PrintOut();
    void InputRandom();
    void DeleteArr(void* arr);
    void NewArr(void* arr);

    void CopyArr();
    void SetupResearchMode();
    void SetupStudying();
    void SetupSimpleSort();

};

#endif // MAINWINDOW_H
