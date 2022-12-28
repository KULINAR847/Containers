#ifndef SIMULATEAREA_H
#define SIMULATEAREA_H

#include <QWidget>

namespace Ui {
class SimulateArea;
}

class SimulateArea : public QWidget
{
    Q_OBJECT

public:
    explicit SimulateArea(QWidget *parent = nullptr);
    ~SimulateArea();

private:
    Ui::SimulateArea *ui;
};

#endif // SIMULATEAREA_H
