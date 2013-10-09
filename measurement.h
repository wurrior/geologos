#ifndef MEASUREMENT_H
#define MEASUREMENT_H

#include <QObject>
#include <QList>

class Measurement : public QObject
{
    Q_OBJECT
public:
    explicit Measurement(QObject *parent = 0);
    Measurement(int begin, int end ,int interval, int multiplier ,QObject *parent = 0 );
    QString toString();
    QList<QString> getValues();
    int getBegin();
    int getEnd();
    int getMulti();
    int getInterval();
    void addResult(QString val);
    void addAirValue(QString val);
    
signals:
    void valueAdded();

public slots:

private:
    // measurement variables:
    int MBegin;
    int MEnd;
    int MInterval;
    int MMulti;
    // results
    QList<QString> results;
    QList<QString> airValues;
};

#endif // MEASUREMENT_H
