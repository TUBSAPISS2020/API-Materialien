#ifndef AIRPORTDIALOG_H
#define AIRPORTDIALOG_H

#include <QDialog>

#include "data.h"

namespace Ui {
class AirportDialog;
}

class AirportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AirportDialog(QWidget *parent = nullptr);
    ~AirportDialog();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::AirportDialog *ui;
};

#endif // AIRPORTDIALOG_H
