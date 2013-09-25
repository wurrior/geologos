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

Measurement::Measurement(QObject *parent) :
    QObject(parent)
{
}

/**
 * @brief Measurement::startMeasurement
 * Measure, get data, move, measure ...
 */
void Measurement::startMeasurement()
{
//UUSI:
//cls
//screen 9:REM grafiikkatila
//kux=10:kuy=300:REM alkupiste k„yr„lle
//gx1=kux:gy1=kuy
//kk=alku
//'kerroin=1
//lippu1=0:REM onko eka data, jolla skaalataan k„yr„„
//lippu2=0
//gosub xakseli: REM piirr„ x-akseli
//for b=kk to vika
//		gosub laske
//        delay (1)
//	print #1,"M": input #1,s$
//		GOSUB TALTEEN
//	sound 333,1.5
//		gosub nosta
//	delay (1.5)
//	datay=0
//	print #1,"M":input #1,A$
//        datay=val(s$)
//        datay=datay-val(a$)
//	'if lippu1=0 then a=a: if datay<20 then kerroin=8 else kerroin=1:lippu1=1
//		GOSUB TALTEENILMA
//        datay=datay*kerroin
//        if datay>300 then datay=datay-300
//        gx2=gx1+hyppy:gy2=kuy-datay
//	if gx2>600 then line(10,kuy)-(gx2,kuy),7:gx2=10:gx1=10:kuy=kuy :cls:gosub xakseli: rem uusi alku
//	if lippu2=1 then a=a: line (gx1,gy1)-(gx2,gy2),15
//        circle(gx2,gy2),2
//	gx1=gx2:gy1=gy2
//        kux=kux+2

//	sound 500,1.0
//        if hyppy=2 then qkierros=1
//        if hyppy=4 then qkierros=2
//        if hyppy=6 then qkierros=3
//        if hyppy=8 then qkierros=4
//        if hyppy=10 then qkierros=5
//        	gosub monta
//        lippu2=1:rem viiva vasta tokalla kerralla
//        if inkey$<>"" then screen 0:goto menu
//	next b
//        screen 0
//GOTO MENU
}

void Measurement::stopMeasurement()
{
}
