#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "airportdialog.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void fillTable();

private slots:
    void on_actionExit_triggered();

    void on_actionAddAirport_triggered();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
