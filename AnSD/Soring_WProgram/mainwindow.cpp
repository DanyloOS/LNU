#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    SetupWindow();
    dataType = Integer;
    Data = new int[10];
    srtTime = nullptr;
    N = 10;
    srtMethod = static_cast<SortingMethod>(ui->comboBox_sortingMethod->currentIndex());
    wResult.setModal(true);
    ui->Widget_SortingMethod->hide();
    ui->label_dataPath->hide();
    ui->lineEdit_dataPath->hide();
    SetupSimpleSort();
    amountOfSortingMethods = 6;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_inputMethod_currentIndexChanged(int index)
{
    switch (index) {
    case 0: {
//        ui->MinorSettingsLayout->
        ui->label_dataPath->hide();
        ui->lineEdit_dataPath->hide();

        ui->label_range->show();
        ui->label_amountOfData->show();
        ui->doubleSpinBox_rangeMin->show();
        ui->doubleSpinBox_rangeMax->show();
        ui->spinBox_amountOfData->show();
        break;
    }
    case 1: {
        ui->label_range->hide();
        ui->label_amountOfData->hide();
        ui->doubleSpinBox_rangeMin->hide();
        ui->doubleSpinBox_rangeMax->hide();
        ui->spinBox_amountOfData->hide();

        ui->label_dataPath->show();
        ui->lineEdit_dataPath->show();
    }
    }
}
void MainWindow::SetupWindow()
{
    ui->label_range->show();
    ui->label_amountOfData->show();
    ui->doubleSpinBox_rangeMin->show();
    ui->doubleSpinBox_rangeMax->show();
    ui->spinBox_amountOfData->show();

    ui->doubleSpinBox_rangeMin->setRange(-1.7e+307,1.7e+307);
    ui->doubleSpinBox_rangeMax->setRange(-1.7e+307,1.7e+307);
    ui->doubleSpinBox_rangeMin->setValue(-5);
    ui->doubleSpinBox_rangeMax->setValue(10);

    ui->spinBox_amountOfData->setRange(2, 1000000);
    ui->spinBox_amountOfData->setValue(10);
}
void MainWindow::on_comboBox_sortingMethod_currentIndexChanged(int index)
{
    srtMethod = static_cast<SortingMethod>(index);
}
void MainWindow::on_pushButton_Sort_clicked()
{
    switch (ui->comboBox_workingMode->currentIndex()) {
    case 0: {
        InputRandom();
        CopyArr();
        //PrintOut();

        switch (dataType) {
        case Integer: {
            wResult.PrintUnsorted(static_cast<int*>(cData), N);
            Sorting<int>(static_cast<int*>(cData), N, srtMethod, srtTime);
            wResult.PrintSorted(static_cast<int*>(cData), N);
            break;
        }
        case Float: {
            wResult.PrintUnsorted(static_cast<float*>(cData), N);
            Sorting<float>(static_cast<float*>(cData), N, srtMethod, srtTime);
            wResult.PrintSorted(static_cast<float*>(cData), N);
            break;
        }
        case Double: {
            wResult.PrintUnsorted(static_cast<double*>(cData), N);
            Sorting<double>(static_cast<double*>(cData), N, srtMethod, srtTime);
            wResult.PrintSorted(static_cast<double*>(cData), N);
            break;
        }
        case Char: {
            wResult.PrintUnsorted(static_cast<char*>(cData), N);
            Sorting<char>(static_cast<char*>(cData), N, srtMethod, srtTime);
            wResult.PrintSorted(static_cast<char*>(cData), N);
            break;
        }
        case String: {
            wResult.PrintUnsorted(static_cast<QString*>(cData), N);
            Sorting<QString>(static_cast<QString*>(cData), N, srtMethod, srtTime);
            wResult.PrintSorted(static_cast<QString*>(cData), N);
            break;
        }
        }


        if (ui->checkBox_pTime->isChecked()) {
            ui->statusBar->showMessage("Your Data has been successfully sorted! Sorting took "
                                       + QString::number(*srtTime) + " seconds", 20000);
        } else ui->statusBar->showMessage("Your Data has been successfully sorted!", 10000);
        if (ui->checkBox_pResult->isChecked()) wResult.exec();
        break;
    }
    case 1: {}
        break;
    case 2: {
//        srtTimeAdv = new double*[10];
//        for (unsigned i = 0; i < 10; i++) {
//            srtTimeAdv[i] = new double[10];
//        }
        double srtTimeAdv[10][10];
        argSortingMethods = new bool[amountOfSortingMethods];
        if (ui->cB_BubbleSort->isChecked()) argSortingMethods[0] = 1;
        if (ui->cB_BubbleSort_m->isChecked()) argSortingMethods[1] = 1;
        if (ui->cB_InsertionSort->isChecked()) argSortingMethods[2] = 1;
        if (ui->cB_SelectionSort->isChecked()) argSortingMethods[3] = 1;
        if (ui->cB_ShellSort->isChecked()) argSortingMethods[4] = 1;
        if (ui->cB_MergeSort->isChecked()) argSortingMethods[5] = 1;

        for(unsigned i = 10; i <= 100000; i *= 10){
            N = i;
            int step = 0;
            InputRandom();
            for (unsigned j = 0; j < amountOfSortingMethods; j++) {
                if(argSortingMethods[j]){
                    CopyArr();
                    srtMethod = static_cast<SortingMethod>(j);

                    switch (dataType) {
                    case Integer:
                        Sorting<int>(static_cast<int*>(cData), N, srtMethod, srtTime);
                        break;
                    case Float:
                        Sorting<float>(static_cast<float*>(cData), N, srtMethod, srtTime);
                        break;
                    case Double:
                        Sorting<double>(static_cast<double*>(cData), N, srtMethod, srtTime);
                        break;
                    case Char:
                        Sorting<char>(static_cast<char*>(cData), N, srtMethod, srtTime);
                        break;
                    case String:
                        Sorting<QString>(static_cast<QString*>(cData), N, srtMethod, srtTime);
                        break;
                    }
                    //srtTimeAdv[j][step] = *srtTime;
//                    qDebug() << *srtTime;
                }
            }
            step++;
            DeleteArr(cData);
        }
        for (unsigned i = 0; i < amountOfSortingMethods; i++) {
            for (unsigned j = 0; j < 6; j++)
            {
                qDebug() << i << "\t" << j << "\t" << srtTimeAdv[i][j];
            }
        }
    }
    }


}

void MainWindow::InputRandom()
{
    rangeA = ui->doubleSpinBox_rangeMin->value();
    rangeB = ui->doubleSpinBox_rangeMax->value();
    N = ui->spinBox_amountOfData->text().toUInt();


    DeleteArr(Data);
    dataType = static_cast<TypeOfData>(ui->comboBox_typeOfData->currentIndex());
    /*NewArr(Data);*/
    switch (dataType){
    case Integer:   Data = new int[N]; break;
    case Float:     Data = new float[N]; break;
    case Double:    Data = new double[N]; break;
    case Char:      Data = new char[N]; break;
    case String:    Data = new QString[N]; break;
    }

    std::random_device dev;
    std::mt19937 rng(dev());
    rng.seed(static_cast<unsigned int>(std::time(nullptr)));
    std::uniform_int_distribution<> distI(static_cast<int>(rangeA), static_cast<int>(rangeB));
    std::uniform_real_distribution<> distR(rangeA, rangeB);
//    void* dist;
//    switch (dataType){
//    case Integer: dist =  new std::uniform_int_distribution<int>(static_cast<int>(rangeA), static_cast<int>(rangeB)); break;
//    case Float: new std::uniform_int_distribution<float>(rangeA,rangeB); break;
//    case Double: new std::uniform_int_distribution<double>(rangeA,rangeB); break;
//    case Char: new std::uniform_int_distribution<char>(static_cast<char>(rangeA), static_cast<char>(rangeB)); break;
//    case String: new std::uniform_int_distribution<std::string>(rangeA,rangeB); break;
//    }

//    if (dataType == Integer)
//        for(unsigned int i = 0; i < N; i++){
//            ((int*)Data)[i] = distI(rng);
//        }
//    else {
//        switch
//    }
    unsigned int i;
    switch (dataType){
    case Integer:
        for(i = 0; i < N; i++){
            static_cast<int*>(Data)[i] = distI(rng);
        }break;

    case Float:
        for(i = 0; i < N; i++){
            static_cast<float*>(Data)[i] = static_cast<float>(distR(rng));
        }break;

    case Double:
        for(i = 0; i < N; i++){
            //static_cast<double*>(Data)[i] = distR(rng);
            static_cast<double*>(Data)[i] = distR(rng);
        }break;

    case Char:
        for(i = 0; i < N; i++){
            static_cast<char*>(Data)[i] = static_cast<char>(distI(rng));
        }break;

    case String:
        for(i = 0; i < N; i++){
            static_cast<std::string*>(Data)[i] = static_cast<char>(distI(rng));
        }break;
    }
}

void MainWindow::DeleteArr(void *arr)
{
    switch (dataType){
    case Integer: delete [] static_cast<int*>(arr); break;
    case Float: delete [] static_cast<float*>(arr); break;
    case Double: delete [] static_cast<double*>(arr); break;
    case Char: delete [] static_cast<char*>(arr); break;
    case String: delete [] static_cast<std::string*>(arr); break;
    }
}

void MainWindow::NewArr(void *arr)
{
    switch (dataType){
    case Integer: arr = new int[N]; break;
    case Float: arr = new float[N]; break;
    case Double: arr = new double[N]; break;
    case Char: arr = new char[N]; break;
    case String: arr = new QString[N]; break;
    }
}

void MainWindow::SetupResearchMode()
{
    ui->Widget_DataPath->hide();
    ui->Widget_SortingMethod->show();
    ui->Widget_RandomData->hide();
    ui->label_inputMethod->hide();
    ui->comboBox_inputMethod->hide();
    ui->comboBox_sortingMethod->hide();
    ui->label_sortingMethod->hide();
}

void MainWindow::SetupStudying()
{

}

void MainWindow::SetupSimpleSort()
{
    ui->Widget_DataPath->hide();
    ui->Widget_SortingMethod->hide();
    ui->Widget_RandomData->show();
    ui->label_inputMethod->show();
    ui->comboBox_inputMethod->show();
    ui->comboBox_sortingMethod->show();
    ui->label_sortingMethod->show();
}

/*//void MainWindow::PrintOut()
//{
//    unsigned int i, j;
//    QString label = "";
//    switch (dataType){
//    case Integer:
//        for(i = 0; i < N; i++){
//            qDebug() << static_cast<int*>(Data)[i];
//        }break;

//    case Float:
//        for(i = 0; i < N; i++){
//            qDebug() << static_cast<float*>(Data)[i];
//        }break;

//    case Double:
//        for(i = 0; i < N; i++){
//            qDebug() << static_cast<double*>(Data)[i];
//        }break;

//    case Char:
//        for(i = 0; i < N; i++){
//            qDebug() << static_cast<char*>(Data)[i];
//        }break;

//    case String:
//        for(i = 0; i < N; i++){
//            for(j = 0; j < static_cast<std::string*>(Data)->size(); j++)
//                label += static_cast<std::string*>(Data)[j][i];
//            qDebug() << label;
//            label = "";
//        }break;
//    }
//    Result rsWindow;
//    rsWindow.setModal(true);

//    rsWindow.exec();
//}*/

void MainWindow::on_checkBox_pTime_stateChanged(int arg1)
{
    if (arg1){
        srtTime = new double;
        *srtTime = -1;
    } else {
        delete srtTime;
    }
}

void MainWindow::on_comboBox_workingMode_currentIndexChanged(int index)
{
    switch (index) {
    case 0: SetupSimpleSort();
        break;
    case 1: SetupStudying();
        break;
    case 2: SetupResearchMode();
        break;
    }
}

void MainWindow::CopyArr()
{
    switch(dataType){
    case Integer:{
        cData = new int[N];
        for (unsigned i = 0; i < N; i++)
            static_cast<int*>(cData)[i] = static_cast<int*>(Data)[i];
        break;
    }
    case Float:{
        cData = new float[N];
        for (unsigned i = 0; i < N; i++)
            static_cast<float*>(cData)[i] = static_cast<float*>(Data)[i];
        break;
    }
    case Double:{
        cData = new double[N];
        for (unsigned i = 0; i < N; i++)
            static_cast<double*>(cData)[i] = static_cast<double*>(Data)[i];
        break;
    }
    case Char:{
        cData = new char[N];
        for (unsigned i = 0; i < N; i++)
            static_cast<char*>(cData)[i] = static_cast<char*>(Data)[i];
        break;
    }
    case String:{
        cData = new std::string[N];
        for (unsigned i = 0; i < N; i++)
            static_cast<std::string*>(cData)[i] = static_cast<std::string*>(Data)[i];
        break;
    }
    }
}
