#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <QSerialPort>

class Control : public QObject
{
    Q_OBJECT
public:
    explicit Control(QObject *parent = 0);
    
    QString measurePoint();
signals:
    
public slots:
    void lift();
    void lower();
    void zeroing();

 private:
    QSerialPort *portti;
};

#endif // CONTROL_H
