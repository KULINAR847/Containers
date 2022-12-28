#include "itemsettings.h"
#include "ui_itemsettings.h"

#include "moveitem.h"
#include "pyrun.h"
#include <QDebug>
#include <QString>
#include <QStringList>

ItemSettings::ItemSettings(MoveItem *parent) :
    QDialog(),
    ui(new Ui::ItemSettings)
{
    ui->setupUi(this);

    pyRun = new PyRun("");
    pinInCounter = 1;
    pinOutCounter = 1;
    // Добавим код
    ui->teCode->setText("def eval(a, b):\n    return a+b");
}

ItemSettings::~ItemSettings()
{
    delete ui;
    if(pyRun) delete pyRun;
}

void ItemSettings::on_pbRunTest_clicked()
{
    qDebug() << ui->teCode->toPlainText();
    ui->textBrowserResult->setText(pyRun->eval(ui->teCode->toPlainText()));
//    ui->textBrowserResult->setText("");
//    QStringList commands = ui->teCode->toPlainText().split("\n");
//    foreach (const QString &command, commands)
//    {
//        qDebug() << command;
//        ui->textBrowserResult->setText(ui->textBrowserResult->toPlainText() + pyRun->runPythonExpression(command) + "\n");
//    }
}

void ItemSettings::on_pbAddIn_clicked()
{
    PinInfo pin;
    pin.label = "IN" + QString::number(pinInCounter);
    pinInCounter++;
    pin.state = 0;

    Vin.push_back(pin);
    exchangeParamsInCode();
    qDebug() << "add param in";
}

void ItemSettings::exchangeParamsInCode()
{
    QString code = ui->teCode->toPlainText();
    code = code.mid(code.indexOf(":"));
    code = "def eval(" + formParamsStrInCode() + ")" + code;
    ui->teCode->setText(code);
}

QString ItemSettings::formParamsStrInCode()
{
    QString Result = "";
    foreach (PinInfo value, Vin)
        Result += value.label + ", ";

    foreach (PinInfo value, Vout)
        Result += value.label + ", ";

    return Result;
}

void ItemSettings::on_pbAddOut_clicked()
{
    PinInfo pin;
    pin.label = "OUT" + QString::number(pinOutCounter);
    pinOutCounter++;
    pin.state = 0;

    Vout.push_back(pin);
    exchangeParamsInCode();
    qDebug() << "add param in";
}
