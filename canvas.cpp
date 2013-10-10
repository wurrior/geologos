#include "canvas.h"
#include <QImage>
#include <QDebug>
#include <mainwindow.h>


Canvas::Canvas(QWidget *parent) :
    QWidget(parent)
{
    // create image and paint it black
    image = new QImage(imageWidth,1000, QImage::Format_ARGB32);
    ipainter = new QPainter(this->image);
    ipainter->setRenderHint(QPainter::Antialiasing, false);
    ipainter->setPen(QPen(Qt::gray, 1));
    clearCanvas();
    drawGrid();
}

Canvas::~Canvas()
{
    delete ipainter;
    delete image;
}

void Canvas::paintEvent(QPaintEvent*pe)
{
    QPainter painter(this);
    QImage display = this->image->scaled(
                this->width()-10,
                this->height()-10,
                Qt::IgnoreAspectRatio,
                Qt::SmoothTransformation);//.mirrored();
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

void Canvas::drawGrid(int steps)
{
    int x = 0;
    if(steps == 0) return;
    ipainter->save();
    ipainter->setPen(QPen(Qt::gray, 1));
    ipainter->drawLine(0,900,imageWidth,900); // x-axis

    for(int i = 0; i < steps; i++) // marks
    {
        x = (i*imageWidth)/steps;
        if( steps < 100 ) ipainter->drawLine( x,900,x,910 );
        if( (i % 10) == 0 )
        {
            if( steps < 100 ) ipainter->drawText(x+4,940,QString::number(i));
            if( (i % 100) == 0 )
            {
                ipainter->drawText(x+4,940,QString::number(i));
                if( (i % 1000) == 0 ) ipainter->drawLine( x,900,x,960 );
                else ipainter->drawLine( x,900,x,940 );
            }
            else ipainter->drawLine( x,900,x,920 );
        }
    }
    ipainter->restore();
}

QPainter *Canvas::getPainter()
{
    return ipainter;
}


void Canvas::drawCurve( QList<int> * curve,int interval, int offset )
{
    if(curve->size() == 0) return; // nothing to draw
    int x1=offset, x2=offset, steps=curve->size();
    int factor = (imageWidth*interval)/steps;
    ipainter->save();
    QMatrix m;
    m.translate( 0, 900 );
    m.scale( 1, -1 );
    ipainter->setMatrix( m );
    ipainter->setRenderHint(QPainter::Antialiasing, true);
    int lastYvalue = curve->at(0);
    for( int i = 1; i < curve->size(); i++)
    {
        x1 = (i+offset-1)*factor;
        x2 = (i+offset)*factor;
        ipainter->drawLine(x1,lastYvalue/10,x2,curve->at(i)/10);
        lastYvalue = curve->at(i);
    }
    ipainter->restore();
}


void Canvas::redraw()
{
    this->update();
}

void Canvas::clearCanvas()
{
    ipainter->fillRect(0,0,imageWidth,1000,Qt::black);
    lastX = lastY = 0;
    this->update();
}
