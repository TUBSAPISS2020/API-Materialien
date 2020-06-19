#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fillTable();

    QObject::connect(&Data::airportDb, &AirportDB::OnDbUpdated, this, &MainWindow::fillTable);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_actionExit_triggered()
{
    this->close();
}

void MainWindow::on_actionAddAirport_triggered()
{
    AirportDialog* airportDialog = new AirportDialog(this, AirportDialog::eModes::AddAirport, nullptr);
    airportDialog->exec();
}

void MainWindow::fillTable() {
    ui->tblAirports->setRowCount(0);
    for (int i = 0; i < Data::airportDb.getAirports().size(); i++) {
        Airport airport = Data::airportDb.getAirports().at(i);
        ui->tblAirports->insertRow(ui->tblAirports->rowCount());
        ui->tblAirports->setItem(ui->tblAirports->rowCount() - 1, 0, new QTableWidgetItem(airport.mICAO));
        ui->tblAirports->setItem(ui->tblAirports->rowCount() - 1, 1, new QTableWidgetItem(airport.mName));
    }
}
