#include "canvas.h"
#include <QImage>
#include <QDebug>

Canvas::Canvas(QWidget *parent) :
    QWidget(parent)
{
    // create image and paint it black
    image = new QImage(1024,1024, QImage::Format_ARGB32);
    clearCanvas();
}

Canvas::~Canvas()
{
    delete image;
}

void Canvas::paintEvent(QPaintEvent*pe)
{
    QPainter painter(this);
    QImage display = this->image->scaled(
                this->width()-10,
                this->height()-10,
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation);
    painter.drawImage(QPoint(5,5),display,this->rect());
}

void Canvas::setPoint(QPainter * painter,double x, double y )
{
    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(QPen(Qt::yellow, 2));

    painter->drawLine(QPointF(lastX,lastY),
                     QPointF(x,y));

    lastX = x;
    lastY = y;
}

/*
 * Might need fixing
 */
void Canvas::drawCurve( QList<int> valuesList )
{
    clearCanvas();
    qDebug() << "listSize" << valuesList.size();
    QPainter painter(this->image);
    painter.setRenderHint(QPainter::Antialiasing, false);
    painter.setPen(QPen(Qt::gray, 1));


    int x = 0, xMaxValue = 0, y = 0, yMaxValue = 10;
    double yMod, xMod;
    foreach( int value, valuesList )
    {
        y = value;
        if( y > yMaxValue ) yMaxValue = y;
        xMaxValue++;

    }
    qDebug() << "xMax: " << xMaxValue;
    xMod = 1024.0/(xMaxValue+1);
    yMod = 1000.0/yMaxValue;

    // draw grid
    if( yMaxValue < 1000000 )
    for(int i = 0; i < yMaxValue; i++)
    {
        if( !(i%10) )
        {
            painter.drawLine(0,1000-i*yMod,1024,1000-i*yMod); // y axis
        }
    }

    for(int i = 0; i < xMaxValue; i++)
    {
        if( !(i%256) )
        {
            painter.drawLine(i*xMod,0,i*xMod,1000); // x axis
        }
    }

    // draw curve
    foreach (int value, valuesList) {
        setPoint(&painter, x*xMod, 1000-(  value*yMod ) );
        x++;
    }
    qDebug() << "xMod" << xMod;
    this->update();
}

void Canvas::clearCanvas()
{
    QPainter painter(this->image);
    painter.fillRect(0,0,1024,1024,Qt::black);
    lastX = lastY = 0;
    this->update();
}
