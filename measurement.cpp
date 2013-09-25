#include "measurement.h"

/**
 * @brief Measurement::Measurement
 * Setups a new Measurement
 * @param begin
 * @param end
 * @param interval
 * @param multiplier
 * @param parent
 */
Measurement::Measurement(int begin, int end, int interval, int multiplier, QObject *parent) :
    QObject(parent),
    MBegin(begin),
    MEnd(end),
    MInterval(interval),
    MMulti(multiplier)
{
}

QString Measurement::toString()
{
    QString output;
    for( int i = 0; i < results.size(); i++)
    {
        output.append( results.at(i) );
        output.append(',');
        output.append( airValues.at(i) );
        output.append('\n');
    }
    return output;
}

QList<QString> Measurement::getValues()
{
    return results;
}

int Measurement::getBegin()
{
    return MBegin;
}

int Measurement::getEnd()
{
    return MEnd;
}

int Measurement::getMulti()
{
    return MMulti;
}

int Measurement::getInterval()
{
    return MInterval;
}

void Measurement::addResult(QString val)
{
    results.append(val);
}

void Measurement::addAirValue(QString val)
{
    airValues.append(val);
}

Measurement::Measurement(QObject *parent) :
    QObject(parent)
{
}


