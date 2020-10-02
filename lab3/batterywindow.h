#ifndef BATTERYWINDOW_H
#define BATTERYWINDOW_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QHBoxLayout>

namespace Ui { class BatteryWindow; }

class BatteryWindow : public QWidget
{
    Q_OBJECT
public:
    explicit BatteryWindow(QWidget *parent = nullptr);
    ~BatteryWindow();

private:
    QLabel* typeOfEnergyLabel;
    QLabel* batteryPercentLabel;
    QProgressBar* batteryPercentBar;
    QLabel* savingModeLabel;
    QLabel* batteryTimeLabel;

    QHBoxLayout* typeOfEnergyLayout();
    QHBoxLayout* batteryPercentLayout();
    QHBoxLayout* savingModeLayout();
    QHBoxLayout* batteryTimeLayout();

public slots:
    void setTypeOfEnergy(QString type);
    void setBatteryPercent(unsigned char value);
    void setSavingMode(QString type);
    void setBatteryTime(unsigned long type);
};

#endif // BATTERYWINDOW_H
