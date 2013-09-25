#ifndef CONTROL_H
#define CONTROL_H

#include <QObject>
#include <QSerialPort>
#include <QSettings>
#include <QMutex>
#include "parallelportdriver.h"

class Control : public QObject
{
    Q_OBJECT
public:
    explicit Control(QObject *parent = 0);
    ~Control();
    QString measurePoint();

signals:
    
public slots:
    void stop();
    void lift();
    void lower();
    void zeroing();
    void stepForward();
    void stepBack();

 private:
    QSerialPort * portti;
    QSettings * settings;
    PPort * pPortti;
    QMutex smutex;
    QMutex pmutex;
};

#endif // CONTROL_H
