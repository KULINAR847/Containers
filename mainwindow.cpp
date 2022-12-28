#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "pyrun.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pyRun = new PyRun("");
    ui->teW->setText("def eval(a, b):\n    import os\n    return os.__doc__\n");
}

MainWindow::~MainWindow()
{
    delete ui;
    if(pyRun) delete pyRun;
}


void MainWindow::on_pushButton_clicked()
{    
    ui->teO->setText(pyRun->eval(ui->teW->toPlainText()));
}
