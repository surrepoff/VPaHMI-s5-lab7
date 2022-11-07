#ifndef MYGRAPHICS_H
#define MYGRAPHICS_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsEllipseItem>
#include <QTime>
#include <QTimer>

class MyGraphics : public QGraphicsScene
{
    Q_OBJECT
public:
    MyGraphics(QObject* parent= nullptr);
    QGraphicsItem* itemCollidesWith(QGraphicsItem* item);
    void Init();
private:
    QGraphicsRectItem* walls[4];
    QGraphicsPixmapItem* bird;

    double dx, dy;

public slots:
    void MoveBird();
};

#endif // MYGRAPHICS_H
