#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <QObject>

class Measurement : public QObject
{
    Q_OBJECT
public:
    explicit Measurement(QObject *parent = 0);
    Measurement(int begin, int end ,int interval, int multiplier ,QObject *parent = 0 );
    
signals:
    
public slots:
    void startMeasurement();
    void stopMeasurement();

private:
    // measurement variables:
    int MBegin;
    int MEnd;
    int MInterval;
    int MMulti;
};

#endif // MEASUREMENT_H
