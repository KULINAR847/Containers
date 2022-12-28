#ifndef GRAPHICCLASSES_H
#define GRAPHICCLASSES_H

#include <QWidget>
#include <QGraphicsView>
#include <QGraphicsRectItem>


class CustomView : public QGraphicsView
{
    Q_OBJECT
public:
    CustomView(QWidget *parent=nullptr);

    QGraphicsScene scene;
    QPoint mousePos;

protected:
    void mousePressEvent(QMouseEvent *event);

private slots:
    void ShowContextMenu(const QPoint &pos);

    void addItemAction();

};



#endif // GRAPHICCLASSES_H
