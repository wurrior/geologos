#ifndef PARALLELPORTDRIVER_H
#define PARALLELPORTDRIVER_H

#include <QObject>

class PPort : public QObject
{
    Q_OBJECT
public:
    explicit PPort(QObject *parent = 0);
    bool write(quint16 chr);
signals:
    
public slots:
    
};

#endif // PARALLELPORTDRIVER_H
