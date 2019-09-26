#ifndef RESULT_H
#define RESULT_H

#include <QDialog>
class MainWindow;

namespace Ui {
class Result;
}

class Result : public QDialog
{
    Q_OBJECT

public:
    explicit Result(QWidget *parent = nullptr);
    ~Result();
    void PrintSorted(int arr[], unsigned size);
    void PrintSorted(float arr[], unsigned size);
    void PrintSorted(double arr[], unsigned size);
    void PrintSorted(char arr[], unsigned size);
    void PrintSorted(QString arr[], unsigned size);

    void PrintUnsorted(int arr[], unsigned size);
    void PrintUnsorted(float arr[], unsigned size);
    void PrintUnsorted(double arr[], unsigned size);
    void PrintUnsorted(char arr[], unsigned size);
    void PrintUnsorted(QString arr[], unsigned size);

private:
    Ui::Result *ui;
};

#endif // RESULT_H
