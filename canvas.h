#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>
#define imageWidth 2000

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = 0);
    ~Canvas();

    void setPoint(QPainter* painter,double x, double y);
    void clearCanvas();
    void drawCurve(QList<int> *curve, int interval=2, int offset = 0);
    void drawGrid(int steps = imageWidth);
    QPainter * getPainter();
signals:
    
public slots:
    void redraw();

protected:
    void paintEvent(QPaintEvent *pe);
private:
    QPainter * ipainter;
    QImage *image;
    double lastX;
    double lastY;
};

#endif // CANVAS_H
