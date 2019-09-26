#include "mainwindow.h"
#include "ui_mainwindow.h"


double f (double x)
{
    return x * sin(x);
}

void MainWindow::TabF(double *Xe, double *Ye)
{
    double h;
    h = (b1 - a1) / Ne;
    Xe[0] = a1;
    for (int i = 0; i <= Ne - 1; i++)
    {
        Ye[i]	  = f(Xe[i]);
        Xe[i + 1] = Xe[i] + h;
    }
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->numericUpDown1->setValue(3);
    ui->numericUpDown2->setValue(2);
    ui->numericUpDown3->setValue(1);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
    x1 = ui->widget->x(); //Отримуємо ліву верхню координату віджета
    y1 = ui->widget->y(); //Щоб будувати графік на ньому

    pen1 = new QPen(Qt::blue);  //Колір графіка         //Створюємо об'єкти Pen
    pen2 = new QPen(Qt::red);   //Колір осей координат  //для візуального налаштування графіка
    pen3 = new QPen(Qt::green); //Колір гратки
    pen4 = new QPen(Qt::black); //Колір цифр
    font1 = new QFont("Times", 8); //Шрифт цифр

    pen1->setWidth(ui->numericUpDown1->value()); //Отримуємо параметри налаштування
    pen2->setWidth(ui->numericUpDown2->value()); //від користувача
    pen3->setWidth(ui->numericUpDown3->value());

    pb_Height = ui->widget->height();   // Висота віджета
    pb_Width = ui->widget->width();     // Ширина віджета
    L = 40;                             // Відступ від країв віджета

    a1 = ui->textBox1->text().toDouble(); //Вводимо область визначення і
    b1 = ui->textBox2->text().toDouble(); //побудови графіка
    Ne = ui->textBox3->text().toInt();

    TabF(Xe, Ye);       //Табулюємо функцію із записом усіх результатів в Xe, Ye

    minx = Xe[0]; maxx = Xe[Ne - 1];// Для визачення коефіцієнтівв маштабування
    miny = Ye[0]; maxy = Ye[0]; //вводимо початкові значення minx, maxx, miny, maxy;
    for (int i = 1; i <= Ne - 1; i++) {
        if (maxy < Ye[i]) maxy = Ye[i]; //Шукаємо miny та maxy
        if (miny > Ye[i]) miny = Ye[i];
    }

    Kx = (pb_Width - 2 * L) / (maxx - minx);       //Коефіцієнти маштабування
    Ky = (pb_Height - 2 * L) / (miny - maxy);
    Zx = (pb_Width * minx - L * (maxx + minx)) / (minx - maxx);
    Zy = (pb_Height * maxy - L * (miny + maxy)) / (maxy - miny);


    // Обчислюємо розташування рухомих осей координат
    if (minx * maxx <= 0.0)					Gx = 0.0;
    if (minx * maxx > 0.0)					Gx = minx;
    if (minx * maxx > 0.0 && minx < 0.0)	Gx = maxx;
    if (miny * maxy <= 0.0)					Gy = 0.0;
    if (miny * maxy > 0.0 && miny > 0.0)	Gy = miny;
    if (miny * maxy > 0.0 && miny < 0.0)	Gy = maxy;

    // Обчислюємо ціличисельні відстані між лініями гратки
    KrokX = (pb_Width - 2 * L) / 10;
    KrokY = (pb_Height - 2 * L) / 9;

    // Виводимо гратку
    QPainter painter(this); //Передаємо в painter посилання на віджет на якому будемо будувати графік
    //Примітка// Ми не можемо передати посилання на наш widget, тому що тоді виникне помилка
    //        // компілювання. Ми можемо передавати в painter посилання тільки на той клас,
    //        // у якому ми створили подію void paintEvent(QPaintEvent *event);
    painter.setPen(*pen3);
    for (int i = 1; i < 7; i++) {
        painter.drawLine(L + x1, y1 + Ky * Gy + Zy + i * KrokY, x1 + pb_Width - L,
                                 y1 + Ky * Gy + Zy + i * KrokY);
        painter.drawLine(L + x1, y1 + Ky * Gy + Zy - i * KrokY, x1 + pb_Width - L,
                                 y1 + Ky * Gy + Zy - i * KrokY);
     }

    for (int i = 1; i < 9; i++) {
        int a1 = x1 + Kx * Gx + Zx + i * KrokX;
        int a2 = x1 + Kx * Gx + Zx - i * KrokX;
        if (a1 < x1 || a1 > x1 + pb_Width) continue;
        painter.drawLine(x1 + Kx * Gx + Zx + i * KrokX, y1 + L - 20,
                         x1 + Kx * Gx + Zx + i * KrokX, y1 + pb_Height - L + 30);
        if (a2 < x1 || a2 > x1 + pb_Width) continue;
        painter.drawLine(x1 + Kx * Gx + Zx - i * KrokX, y1 + L - 20,
                         x1 + Kx * Gx + Zx - i * KrokX, y1 + pb_Height - L + 30);
     }

    //Програмуємо підписи маштабних поділок на осях координат
    xx = minx; yy = maxy; //Для виведення осей координат та їхніх підписів
    krx = (maxx - minx) / 10.0;
    kry = (maxy - miny) / 10.6;

    painter.setFont(*font1);
    painter.setPen(*pen4);
    for (int i = 0; i < 12; i++)
    {
        painter.drawText(x1 + L + 4 + i * KrokX, Ky*Gy + Zy - L + 70.0f,
                         QString::number(round(xx*10)/10));
        painter.drawText(x1 + Kx * Gx + Zx - L + 10.0f, (float)(y1 + L + (i + 1) * KrokY) - 24.0f,
                         QString::number(round(yy*10)/10));
        xx += krx;
        yy -= kry;
    }

    //Малюємо осі координат
    painter.setPen(*pen2);
    painter.drawLine(x1 + L, y1 + Ky * Gy + Zy,
                     x1 + pb_Width - 10, y1 + Ky * Gy + Zy);
    painter.drawLine(x1 + Kx * Gx + Zx, y1 + 10,
                     x1 + Kx * Gx + Zx, y1 + pb_Height - 10);

    //Малюємо графік функції
    painter.setPen(*pen1);
    for (int i = 1; i <= Ne - 1; i++)
    {
        painter.drawLine(x1 + Kx * Xe[i - 1] + Zx, y1 + Ky * Ye[i - 1] + Zy,
                         x1 + Kx * Xe[i] + Zx,     y1 + Ky * Ye[i] + Zy);
    }

    delete pen1;        //Вивільняємо пам'ять
    delete pen2;
    delete pen3;
    delete pen4;
    delete font1;
}

void MainWindow::on_button1_clicked()
{
    ui->centralWidget->repaint();
}

void MainWindow::on_button2_clicked()
{
    close();
}
