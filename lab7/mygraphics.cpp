#include "mygraphics.h"

void MyGraphics::Init()
{
    QPixmap newImage;
    if (!newImage.load(QStringLiteral(":/images/tree.png")))
    {
        return;
    }

    QGraphicsPixmapItem* tree;
    tree = addPixmap(newImage);
    tree->setPos(300,312);
    tree->setScale(0.18);
    tree->setData(0,"Tree");
    tree->setFlags(QGraphicsItem::ItemIsMovable);



    QGraphicsEllipseItem *apple[3];
    for (int i = 0; i < 3; i++)
    {
        apple[i] = addEllipse(QRectF(0,0,30,30), QPen(Qt::black), QBrush(QColor(240,50,50)));
        apple[i]->setFlags(QGraphicsItem::ItemIsMovable);
        apple[i]->setData(0, "Tree");
    }

    apple[0]->setPos(330, 430);
    apple[1]->setPos(400, 355);
    apple[2]->setPos(470, 440);



    if (!newImage.load(QStringLiteral(":/images/bird.png"))) {
        return;
    }

    bird = addPixmap(newImage);
    bird->setScale(0.1);
    bird->setPos(300, 100);
    bird->setData(0, "Bird");

    walls[0] = addRect(QRectF(0,0,10,600),QPen(Qt::black), QBrush(QColor(120, 220, 60)));
    walls[1] = addRect(QRectF(800,0,10,600), QPen(Qt::black), QBrush(QColor(120, 220, 60)));
    walls[2] = addRect(QRectF(0,0,800,10), QPen(Qt::black), QBrush(QColor(120, 220, 60)));
    walls[3] = addRect(QRectF(0,600,800,10), QPen(Qt::black), QBrush(QColor(120, 220, 60)));

    for(int i = 0; i < 4; i++)
    {
        walls[i]->setData(0,"Wall");
    }
}

void MyGraphics::MoveBird(){
    QTransform transform = bird->transform();

    transform.translate(dx,0);
    bird->setTransform(transform);

    QGraphicsItem* barrierX = itemCollidesWith(bird);
    transform=bird->transform();

    if(barrierX){
        if(barrierX->data(0) == "Wall" || barrierX->data(0) == "Tree"){
            dx = -dx;

            transform.translate(dx,0);
            bird->setTransform(transform);

            dy=rand() % 7 - 3;
        }
    }

    transform.translate(0,dy);
    bird->setTransform(transform);

    QGraphicsItem* barrierY = itemCollidesWith(bird);
    transform=bird->transform();

    if(barrierY){
        if(barrierY->data(0) == "Wall" || barrierY->data(0) == "Tree"){
            dy = -dy;

            transform.translate(0,dy);
            bird->setTransform(transform);

            dx=rand() % 7 - 3;
        }
    }
}


MyGraphics::MyGraphics(QObject* parent):QGraphicsScene (parent)
{
    Init();
    dx = 1;
    dy = 1;

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    QTimer* timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(MoveBird()));
    timer->start(10);
}


QGraphicsItem * MyGraphics::itemCollidesWith(QGraphicsItem *item)
{
    QList<QGraphicsItem *> collisions = collidingItems(item);
    foreach (QGraphicsItem *it, collisions){
        if(it == item)
            continue;
        return it;
    }
    return nullptr;
}
