#include "graphicclasses.h"

#include <QDebug>
#include <QMenu>
#include <QAction>
#include <QPoint>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>

#include "moveitem.h"


CustomView::CustomView(QWidget *parent):
QGraphicsView(parent)
{
    scene.setSceneRect(QRectF(0, 0, 500, 500));
    setScene(&scene);

    setContextMenuPolicy(Qt::CustomContextMenu);
    connect(this, SIGNAL(customContextMenuRequested(const QPoint &)),
            this, SLOT(ShowContextMenu(const QPoint &)));
}

void CustomView::mousePressEvent(QMouseEvent *event)
{
    qDebug() << "Custom view clicked.";
    QGraphicsView::mousePressEvent(event);
    mousePos = event->pos();
    qDebug()  << "mousePos   " << mousePos;
    qDebug()  << "mousePos g " << mapToGlobal(mousePos);
    //if(event->button() == Qt::RightButton)
}

void CustomView::ShowContextMenu(const QPoint &pos)
{    

    QMenu contextMenu(tr("Context menu"), this);

    QAction action1(tr("Add Item"), this);
    connect(&action1, SIGNAL(triggered()), this, SLOT(addItemAction()));
    contextMenu.addAction(&action1);

    contextMenu.exec(mapToGlobal(pos));
}

void CustomView::addItemAction()
{
    qDebug() << "Add item " << mousePos - mapToGlobal(this->pos());
    qDebug()  << "mousePos " << mousePos;
    qDebug()  << "apToGlobal(pos()) " << mapToGlobal(this->pos());

//    CustomItem *item = new CustomItem();
//    item->setRect( QRect( mousePos, QSize(60,60)));
//    scene.addItem(item);

    MoveItem *item = new MoveItem();
    item->setPos(mousePos);
    scene.addItem(item);
//    QSharedPointer<CustomItem> item = QSharedPointer<CustomItem>(new CustomItem());
//    item.data()->setRect(20, 20, 60, 60);
//    scene.addItem(item.data());
}


