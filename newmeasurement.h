#ifndef NEWMEASUREMENT_H
#define NEWMEASUREMENT_H

#include <QDialog>
#include "measurement.h"

namespace Ui {
class NewMeasurement;
}

class NewMeasurement : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewMeasurement(QWidget *parent = 0);
    ~NewMeasurement();
    Measurement *getCurrentMeasurement();
    
private slots:
    void on_buttonBox_accepted();

    void on_interval_valueChanged(int arg1);

private:
    Ui::NewMeasurement *ui;
    Measurement *m;
};

#endif // NEWMEASUREMENT_H
