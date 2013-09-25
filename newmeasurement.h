#ifndef NEWMEASUREMENT_H
#define NEWMEASUREMENT_H

#include <QDialog>

namespace Ui {
class NewMeasurement;
}

class NewMeasurement : public QDialog
{
    Q_OBJECT
    
public:
    explicit NewMeasurement(QWidget *parent = 0);
    ~NewMeasurement();
    
private:
    Ui::NewMeasurement *ui;
};

#endif // NEWMEASUREMENT_H
