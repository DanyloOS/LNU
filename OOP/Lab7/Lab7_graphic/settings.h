#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <mainwindow.h>

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(MainWindow *mainwindow, QWidget *parent = nullptr);
    ~Settings();

private:
    Ui::Settings *st;
    MainWindow *mwindow;
};

#endif // SETTINGS_H
