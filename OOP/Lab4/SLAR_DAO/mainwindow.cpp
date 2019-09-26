#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <cmath>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    N = 1;
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool Gauss(double A [6][6], double B[6], double C[6][6], int N, double X[6])
{
    double R; //
    int k, i, j;
    if (N == 1) {
        if (fabs(A[1][1]) < 1e-7) {
            return false;
        } else {
            X[1] = B[1]/A[1][1];
            goto label_X;
        }
    } else {
        for (i = 1; i <= N - 1; i++){
            k = i;
            R = fabs(A[i][i]);
            j = i + 1;
            for(j = i + 1; j <= N; j++)
                if (fabs(A[j][i]) > R) {
                    k = j;
                    R = fabs(A[j][i]);
                }

            if (R <= 1e-7)
                goto label_X;

            if (k != i) {
                R = B[k];
                B[k] = B[i];
                B[i] = R;

                for(j = i; j <= N; j++) {
                    R = A[k][j];
                    A[k][j] = A[i][j];
                    A[i][j] = R;
                }
            }
            R = A[i][i];
            B[i] = B[i]/R;
            for (j = 1; j <= N; j++) {
                A[i][j] = A[i][j] / R;
            }

            for (k = i + 1; k <= N; k++) {
                R = A[k][i];
                B[k] = B[k] - R*B[i];
                A[k][i] = 0;
                for (j = i + 1; j <= N; j++) {
                    A[k][j] = A[k][j] - R * A[i][j];
                }
            }
        }

        if (fabs(A[N][N]) < 1e-7) {
            goto label_X;
        }

        X[N] = B[N]/A[N][N];
        for (i = N - 1; i >= 1; i--) {
            R = B[i];
            for (j = i + 1; j <= N; j++)
                R = R - A[i][j]*X[j];
            X[i] = R;
        }
    //вихід Х
    label_X:
    for (int i = 0; i <= N; i++) {
        for (int j = 0; j <= N; j++) {
           C[i][j] = A[i][j];
        }
    }

    if (fabs(A[N][N]) <= 1E-7) {
        return false;
    }
    return true;
    }
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    N = arg1;

    ui->A_Matrix->setRowCount(N);
    ui->A_Matrix->setColumnCount(N);
    ui->C_Matrix->setRowCount(N);
    ui->C_Matrix->setColumnCount(N);
    ui->X_Vector->setRowCount(N);
    ui->B_Vector->setRowCount(N);
    for (int i = 0; i < N; i++) {
        ui->A_Matrix->setColumnWidth(i, (ui->A_Matrix->width() - 4)/N);
        ui->C_Matrix->setColumnWidth(i, (ui->C_Matrix->width() - 4)/N);
        ui->A_Matrix->setRowHeight  (i, (ui->A_Matrix->height() - 4)/N);
        ui->C_Matrix->setRowHeight  (i, (ui->C_Matrix->height() - 4)/N);
    }
}

void MainWindow::on_Solve_Button_clicked()
{
    for (int i = 1; i <= N; i++){
        B[i] = ui->B_Vector->item(i - 1, 0)->text().toDouble(); //записуємо значення із TableWidget
        for (int j = 1; j <= N; j++) {                          //у масиви
            A[i][j] = ui->A_Matrix->item(i - 1, j - 1)->text().toDouble();
        }
     }

     if (Gauss(A, B, C, N, X) == true){
         for (int i = 1; i <= N; i++) {
            QTableWidgetItem *itm = new QTableWidgetItem(QString::number(X[i]));
            ui->X_Vector->setItem(i - 1, 0, itm);
         }
         QMessageBox::information(this, "Успіх!", "Розв'язок знайдено");
     } else {
         for (int i = 1; i <= N; i++){
             QTableWidgetItem *itm = new QTableWidgetItem("?");
             ui->X_Vector->setItem(i - 1, 0, itm); //Виводимо "?" в клітинки для вектора Х,
         }                                         //якщо система вироджена
         QMessageBox::information(this, "Помилка!", "Система вироджена");
     }
     for (int i = 1; i <= N; i++){
         for (int j = 1; j <= N; j++) {
             QTableWidgetItem *itm = new QTableWidgetItem(QString::number(C[i][j]));
             ui->C_Matrix->setItem(i - 1, j - 1, itm); //Вbводимо значення з масиву в клітинкі для Матриці С
         }
      }
}

void MainWindow::on_Clear_Button_clicked()
{
    ui->A_Matrix->clear();
    ui->C_Matrix->clear();
    ui->X_Vector->clear();
    ui->B_Vector->clear();
}

void MainWindow::on_Exit_Button_clicked()
{
    close();
}
