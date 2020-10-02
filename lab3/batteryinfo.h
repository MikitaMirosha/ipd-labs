#ifndef BATTERYINFO_H
#define BATTERYINFO_H

#include <QThread>
#include <QObject>
#include "batterywindow.h"

class BatteryWindow;

class BatteryInfo : public QThread
{
private:
    Q_OBJECT
    void setTypeOfEnergy(unsigned char status);
    void setBatteryPercent(unsigned char percent);
    void setSavingMode(bool);
    void setBatteryTime(unsigned long type);

public:
    BatteryInfo(BatteryWindow* parent);
    void getInfo();
    void run();

signals:
    void sendTypeOfEnergy(QString type);
    void sendBatteryPercent(unsigned char value);
    void sendSavingMode(QString type);
    void sendBatteryTime(unsigned long type);
};

#endif // BATTERYINFO_H
