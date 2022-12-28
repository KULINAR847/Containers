#include "simulatearea.h"
#include "ui_simulatearea.h"


SimulateArea::SimulateArea(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SimulateArea)
{
    ui->setupUi(this);
}

SimulateArea::~SimulateArea()
{
    delete ui;
}
