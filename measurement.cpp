#include "measurement.h"
#include <QDebug>
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
    QString output("depth,sample,air");
    output.append('\n');

    if( results.size() > airValues.size() )
        airValues.append(0);
    if( results.size() < airValues.size() )
        results.append(0);

    for( int i = 0; i < results.size(); i++)
    {
        output.append( QString::number( MBegin + i ) );
        output.append(',');
        output.append( QString::number(results.at(i)) );
        output.append(',');
        output.append( QString::number(airValues.at(i)) );
        output.append('\n');
    }
    return output;
}

QList<int> Measurement::getValues()
{
    return results;
}

QList<int> Measurement::getAirValues()
{
    return airValues;
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
    results.append(val.toInt());
    qDebug() << "result: " << results.last();
}

void Measurement::addAirValue(QString val)
{
    airValues.append(val.toInt());
    qDebug() << "air: " << airValues.last();
}

Measurement::Measurement(QObject *parent) :
    QObject(parent)
{
}



