//
// Created by owen on 6/10/21.
//

#include "qtbt.hpp"

class QBluetoothLocalDevice;

QTBT::QTBT(QWidget *parent) :
    QWidget(parent)
{
    // Create a discovery agent and connect to its signals
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);

    // UI Widget and layout setup
    scanButton = new QPushButton(tr("Scan"));
    scanButton->setFont(QFont("Courier", 10, QFont::Bold));
    scanButton->setMaximumWidth(100);

    clearButton = new QPushButton(tr("Clear"));
    clearButton->setFont(QFont("Courier", 10));
    clearButton->setMaximumWidth(100);

    domainInput = new QLineEdit();
    domainInput->setMaximumWidth(200);

    textOutput = new QTextBrowser();
    textOutput->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    textOutput->setMinimumSize(720, 480);

    QHBoxLayout *hLayout = new QHBoxLayout;
    QGridLayout *mainLayout = new QGridLayout;
    hLayout->addWidget(scanButton);
    hLayout->addWidget(clearButton);

    mainLayout->addLayout(hLayout, 0, 0);
    mainLayout->addWidget(textOutput, 1, 0);
    setLayout(mainLayout);
    setWindowTitle(tr("Qt Bluetooth Experiments"));

    // connections
    connect(scanButton, SIGNAL(released()), this, SLOT(onScanButtonReleased()));
    connect(clearButton, SIGNAL(released()), textOutput, SLOT(clear()));
    connect(discoveryAgent, SIGNAL(finished()),
            this, SLOT(scanFinished()));
}

// Destructor
QTBT::~QTBT()
{
    delete clearButton;
    delete scanButton;
    delete domainInput;
    delete textOutput;
}

// In your local slot, read information about the found devices
//void QTBT::deviceDiscovered(const QBluetoothDeviceInfo &device) {
//    qDebug() << "Found new device:" << device.name() << '(' << device.address().toString() << ')';
//}

void QTBT::scanFinished() {
    textOutput->append("Scan finished.");

    QList<QBluetoothDeviceInfo> devicesList = discoveryAgent->discoveredDevices();
    foreach( QBluetoothDeviceInfo devInfo, devicesList) {
        textOutput->append("Device Name:  " + devInfo.name());
        textOutput->append("  Dev. Addr:  " + devInfo.address().toString());
    }
    scanButton->setEnabled(true);
}

void QTBT::onScanButtonReleased() {
    textOutput->append("Scan intitiated...");
    discoveryAgent->start();
    scanButton->setDisabled(true);
}