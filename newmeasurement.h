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
    
private slots:
    void on_buttonBox_accepted();

private:
    Ui::NewMeasurement *ui;
    Measurement *m;
};

#endif // NEWMEASUREMENT_H
