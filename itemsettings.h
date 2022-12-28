#ifndef ITEMSETTINGS_H
#define ITEMSETTINGS_H

#include <QWidget>
#include <QDialog>
#include <QVector>
#include <QVariant>

class MoveItem;
class PyRun;
//class PinInfo;

namespace Ui {
class ItemSettings;
}

struct PinInfo
{
    QString label;
    QVariant state;
};

class ItemSettings : public QDialog
{
    Q_OBJECT

public:
    explicit ItemSettings(MoveItem *parent = nullptr);
    ~ItemSettings();

    PyRun *pyRun;

    QVector<PinInfo> Vin;
    QVector<PinInfo> Vout;
    int pinInCounter;
    int pinOutCounter;

    QString formParamsStrInCode();
    void exchangeParamsInCode();

private slots:
    void on_pbRunTest_clicked();
    void on_pbAddIn_clicked();



    void on_pbAddOut_clicked();

private:
    Ui::ItemSettings *ui;
};

#endif // ITEMSETTINGS_H
