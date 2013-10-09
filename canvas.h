#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QPainter>

class Canvas : public QWidget
{
    Q_OBJECT
public:
    explicit Canvas(QWidget *parent = 0);
    ~Canvas();

    void setPoint(QPainter* painter,double x, double y);
    void clearCanvas();
    void drawCurve(QList<int> *valuesList);
signals:
    
public slots:
    void redraw();

protected:
    void paintEvent(QPaintEvent *pe);
private:
    QImage *image;
    double lastX;
    double lastY;
};

#endif // CANVAS_H
