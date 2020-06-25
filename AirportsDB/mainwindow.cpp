#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    fillTable();

    QObject::connect(&Data::airportDb, &AirportDB::OnDbUpdated, this, &MainWindow::fillTable);
    QObject::connect(ui->tblAirports, &QWidget::customContextMenuRequested, this, &MainWindow::on_ShowContextMenu);
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

void MainWindow::on_ShowContextMenu(const QPoint &pos) {
    QTableWidgetItem* item = ui->tblAirports->itemAt(pos);
    int row = item->row();

    const Airport* airport = getAirportByTblRowIndex(row);
    if (airport == nullptr)
        return;

    QMenu contextMenu("Context menu", this);

    QAction actionDelete("Delete " + airport->mICAO, this);
    actionDelete.setObjectName("del_" + airport->mICAO);
    connect(&actionDelete, &QAction::triggered, this, &MainWindow::on_deleteAirport);
    contextMenu.addAction(&actionDelete);

    QAction actionEdit("Edit " + airport->mICAO, this);
    actionEdit.setObjectName("edi_" + airport->mICAO);
    connect(&actionEdit, &QAction::triggered, this, &MainWindow::on_editAirport);
    contextMenu.addAction(&actionEdit);

    contextMenu.exec(mapToGlobal(pos));
}

const Airport* MainWindow::getAirportByTblRowIndex(int row) {
    QTableWidgetItem* icaoItem = ui->tblAirports->item(row, 0);
    QString sICAO = icaoItem->text();
    return Data::airportDb.getAirport(sICAO);
}

const Airport* MainWindow::getAirportFromContextMenuAction() {
    QAction* action = (QAction*) QObject::sender();
    QString sICAO = action->objectName().mid(4);
    return Data::airportDb.getAirport(sICAO);
}

void MainWindow::on_deleteAirport() {
    const Airport* airport = getAirportFromContextMenuAction();
    if (airport == nullptr)
        return;

    QMessageBox msgBox;
    msgBox.setText("Flugplatz wirklich löschen?");
    msgBox.addButton(QMessageBox::StandardButton::Yes);
    msgBox.addButton(QMessageBox::StandardButton::No);
    if (msgBox.exec() == QMessageBox::StandardButton::Yes) {
        Data::airportDb.deleteAirport(*airport);
    }
}

void MainWindow::on_editAirport() {
    const Airport* airport = getAirportFromContextMenuAction();
    if (airport == nullptr)
        return;

    AirportDialog* airportDialog = new AirportDialog(this, AirportDialog::eModes::EditAirport, airport);
    airportDialog->exec();
}

void MainWindow::on_tblAirports_cellDoubleClicked(int row, int column)
{
    const Airport* airport = getAirportByTblRowIndex(row);
    if (airport == nullptr)
        return;

    AirportDialog* airportDialog = new AirportDialog(this, AirportDialog::eModes::DetailView, airport);
    airportDialog->exec();
}
