#include "batteryinfo.h"
#include <iostream>
#include <iomanip>
#include <Windows.h>
#include <WinIoCtl.h>
#include <ntddscsi.h>
#include <conio.h>
#include <QMessageBox>
#include <winbase.h>

using namespace std;

void BatteryInfo::run()
{
    while(true)
        getInfo();
}

void BatteryInfo::getInfo()
{
    SYSTEM_POWER_STATUS batteryState;
    GetSystemPowerStatus(&batteryState);

    setTypeOfEnergy(batteryState.ACLineStatus);
    setBatteryPercent(batteryState.BatteryLifePercent);
    setSavingMode(batteryState.Reserved1 == 1 ? true : false);
    setBatteryTime(batteryState.BatteryFullLifeTime);
}

BatteryInfo::BatteryInfo(BatteryWindow* parent)
{
    connect(this, &BatteryInfo::sendBatteryPercent, parent, &BatteryWindow::setBatteryPercent);
    connect(this, &BatteryInfo::sendTypeOfEnergy, parent, &BatteryWindow::setTypeOfEnergy);
    connect(this, &BatteryInfo::sendSavingMode, parent, &BatteryWindow::setSavingMode);
    connect(this, &BatteryInfo::sendBatteryTime, parent, &BatteryWindow::setBatteryTime);
}

void BatteryInfo::setTypeOfEnergy(unsigned char type)
{
    QString typeOfEnergyString;
    switch (type)
    {
    case 0:
    typeOfEnergyString = "Battery";
    break;
    case 1:
    typeOfEnergyString = "ACLine";
    break;
    default:
    typeOfEnergyString = "Unknown";
    break;
    }
    emit sendTypeOfEnergy(typeOfEnergyString);
}

void BatteryInfo::setBatteryPercent(unsigned char percent)
{
    emit sendBatteryPercent(percent);
}

void BatteryInfo::setSavingMode(bool flag)
{
    QString savingModeString = "Battery saver is ";
    if (flag)
        savingModeString += "on";
    else
        savingModeString += "off";
    emit sendSavingMode(savingModeString);
}

void BatteryInfo::setBatteryTime(unsigned long time)
{
    emit sendBatteryTime(time);
}
