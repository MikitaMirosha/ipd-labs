#include "batterywindow.h"
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QProgressBar>
#include <QVariant>
#include "batteryinfo.h"

using namespace std;

const unsigned char maxPercent = 100;

BatteryWindow::BatteryWindow(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addLayout(typeOfEnergyLayout());
    mainLayout->addLayout(batteryPercentLayout());
    mainLayout->addLayout(savingModeLayout());
    mainLayout->addLayout(batteryTimeLayout());
    setLayout(mainLayout);

    BatteryInfo* batteryInfo = new BatteryInfo(this);
    batteryInfo->start();
}

BatteryWindow::~BatteryWindow() {}

QHBoxLayout* BatteryWindow::typeOfEnergyLayout()
{
    QHBoxLayout* typeOfEnergyLayout = new QHBoxLayout;
    QLabel* label = new QLabel("Energy type:", this);

    typeOfEnergyLabel = new QLabel(this);
    typeOfEnergyLayout->addWidget(label);
    typeOfEnergyLayout->addWidget(typeOfEnergyLabel);
    return typeOfEnergyLayout;
}

void BatteryWindow::setTypeOfEnergy(QString type)
{
    typeOfEnergyLabel->setText(type);
}

QHBoxLayout* BatteryWindow::batteryPercentLayout()
{
    QHBoxLayout* percentBarLayout = new QHBoxLayout;
    QLabel* label = new QLabel("Charge level:", this);

    batteryPercentBar = new QProgressBar(this);
    batteryPercentBar->setMaximum(maxPercent);
    batteryPercentLabel = new QLabel(this);
    percentBarLayout->addWidget(label);
    percentBarLayout->addWidget(batteryPercentLabel);
    percentBarLayout->addWidget(batteryPercentBar);
    return percentBarLayout;
}

void BatteryWindow::setBatteryPercent(unsigned char value)
{
    if (value > maxPercent) return;
    QString percentString = "";
    if (value == 255)
        percentString = "Unknown";
    else
        batteryPercentBar->setValue(value);
    batteryPercentLabel->setText(percentString);
}

QHBoxLayout* BatteryWindow::savingModeLayout()
{
    QHBoxLayout* savingModeLayout = new QHBoxLayout;
    QLabel* label = new QLabel("Saving mode:", this);

    savingModeLabel = new QLabel(this);
    savingModeLayout->addWidget(label);
    savingModeLayout->addWidget(savingModeLabel);
    return savingModeLayout;
}

void BatteryWindow::setSavingMode(QString type)
{
    savingModeLabel->setText(type);
}

QHBoxLayout* BatteryWindow::batteryTimeLayout()
{
    QHBoxLayout* timeLayout = new QHBoxLayout;
    QLabel* label = new QLabel("Battery time:", this);

    batteryTimeLabel = new QLabel(this);
    timeLayout->addWidget(label);
    timeLayout->addWidget(batteryTimeLabel);
    return timeLayout;
}

void BatteryWindow::setBatteryTime(unsigned long value)
{
    unsigned long batteryTimeValue = value;
    QString batteryTimeString = QString::number(batteryTimeValue);
    batteryTimeLabel->setText(batteryTimeString);
}
