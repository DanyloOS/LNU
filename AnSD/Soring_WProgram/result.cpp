#include "result.h"
#include "ui_result.h"

Result::Result(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Result)
{
    ui->setupUi(this);
}

Result::~Result()
{
    delete ui;
}

void Result::PrintSorted(int arr[], unsigned size)
{
    QString qResult = "";
    for (unsigned i = 0; i < size; i++){
        qResult += QString::number(arr[i]) + "\n";
    }
    ui->textEdit_sorted->clear();
    ui->textEdit_sorted->setText(qResult);
}

void Result::PrintSorted(float arr[], unsigned size)
{
    QString qResult = "";
    for (unsigned i = 0; i < size; i++){
        qResult += QString::number(static_cast<double>(arr[i])) + "\n";
    }
    ui->textEdit_sorted->clear();
    ui->textEdit_sorted->setText(qResult);
}

void Result::PrintSorted(double arr[], unsigned size)
{
    QString qResult = "";
    for (unsigned i = 0; i < size; i++){
        qResult += QString::number(arr[i]) + "\n";
    }
    ui->textEdit_sorted->clear();
    ui->textEdit_sorted->setText(qResult);
}

void Result::PrintSorted(char arr[], unsigned size)
{
    QString qResult = "";
    for (unsigned i = 0; i < size; i++){
        qResult += arr[i];
        qResult += "\n";
    }
    ui->textEdit_sorted->clear();
    ui->textEdit_sorted->setText(qResult);
}

void Result::PrintSorted(QString arr[], unsigned size)
{
    QString qResult = "";
    for (unsigned i = 0; i < size; i++){
        for (int j = 0; j < arr->size(); j++) {
            qResult += arr[i];
        }
        qResult += "\n";
    }
    ui->textEdit_sorted->clear();
    ui->textEdit_sorted->setText(qResult);
}


void Result::PrintUnsorted(int arr[], unsigned size)
{
    QString qResult = "";
    for (unsigned i = 0; i < size; i++){
        qResult += QString::number(arr[i]) + "\n";
    }
    ui->textEdit_unsorted->clear();
    ui->textEdit_unsorted->setText(qResult);
}

void Result::PrintUnsorted(float arr[], unsigned size)
{
    QString qResult = "";
    for (unsigned i = 0; i < size; i++){
        qResult += QString::number(static_cast<double>(arr[i])) + "\n";
    }
    ui->textEdit_unsorted->clear();
    ui->textEdit_unsorted->setText(qResult);
}

void Result::PrintUnsorted(double arr[], unsigned size)
{
    QString qResult = "";
    for (unsigned i = 0; i < size; i++){
        qResult += QString::number(arr[i]) + "\n";
    }
    ui->textEdit_unsorted->clear();
    ui->textEdit_unsorted->setText(qResult);
}

void Result::PrintUnsorted(char arr[], unsigned size)
{
    QString qResult = "";
    for (unsigned i = 0; i < size; i++){
        qResult += arr[i];
        qResult += "\n";
    }
    ui->textEdit_unsorted->clear();
    ui->textEdit_unsorted->setText(qResult);
}

void Result::PrintUnsorted(QString arr[], unsigned size)
{
    QString qResult = "";
    for (unsigned i = 0; i < size; i++){
        for (int j = 0; j < arr->size(); j++) {
            qResult += arr[i];
        }
        qResult += "\n";
    }
    ui->textEdit_unsorted->clear();
    ui->textEdit_unsorted->setText(qResult);
}
