#include "settings.h"
#include "ui_settings.h"
#include <mainwindow.h>

Settings::Settings(MainWindow *mainwindow, QWidget *parent) :
    QDialog(parent),
    st(new Ui::Settings)
{
    mwindow = mainwindow;
    st->setupUi(this);
    st->doubleSpinBox->setRange(1.5, 3.5);
    st->doubleSpinBox->setValue(mwindow->graphPen.widthF());
    st->comboBox_penStyle->setCurrentIndex(mwindow->graphPen.style() - 1);
}

Settings::~Settings()
{
    mwindow->graphPen.setStyle(static_cast<Qt::PenStyle>(st->comboBox_penStyle->currentIndex() + 1));
    mwindow->graphPen.setWidthF(st->doubleSpinBox->value());
    delete st;
}
