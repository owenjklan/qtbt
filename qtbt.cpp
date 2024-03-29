//
// Created by owen on 6/10/21.
//

#include "qtbt.hpp"

class QBluetoothLocalDevice;

QTBT::QTBT(QWidget *parent) :
    QWidget(parent)
{
    setupUiAndSignals(parent);

    // The necessary BlueTooth boiler plate and objects...
    setupBluetooth();
}

// Destructor
QTBT::~QTBT()
{
    // TODO: You need to actually think about all the things you used 'new'
    // for and clean ship up properly. Ie: Run valgrind already, would you?
    delete clearButton;
    delete scanButton;
    delete domainInput;
    delete textOutput;
    delete localBTDevice;
}

void QTBT::setupBluetooth() {
    // NOTE: We're assuming that the UI components have been set up already,
    // so that we can use them for output or error dialogs, if needed.
    localBTDevice = new QBluetoothLocalDevice();
    QString localDeviceName;

// Check if Bluetooth is available on this device
    if (!localBTDevice->isValid()) {
        QMessageBox::warning(this, tr("Local Bluetooth Issue"),
                             "No valid local Bluetooth device was found!");
        return;
    }
    // Read local device name
    localDeviceName = localBTDevice->name();
    textOutput->append("Local Bluetooth device: " + localDeviceName);

    // Turn Bluetooth on
    textOutput->append("Powering on Bluetooth...");
    localBTDevice->powerOn();

    // Make it visible to others
    localBTDevice->setHostMode(QBluetoothLocalDevice::HostDiscoverable);

    // Get connected devices
    QList<QBluetoothAddress> remotes;
    remotes = localBTDevice->connectedDevices();
}

void QTBT::setupUiAndSignals(QWidget *parent) {
    // Create a discovery agent and connect to its signals
    discoveryAgent = new QBluetoothDeviceDiscoveryAgent(this);

    // UI Widget and layout setup
    scanButton = new QPushButton(tr("Scan"));
    scanButton->setFont(QFont("Courier", 10, QFont::Bold));
    scanButton->setMaximumWidth(100);

    abortButton = new QPushButton(tr("Abort"));
    abortButton->setFont(QFont("Courier", 10));
    abortButton->setMaximumWidth(100);
    abortButton->setDisabled(true);

    clearButton = new QPushButton(tr("Clear"));
    clearButton->setFont(QFont("Courier", 10));
    clearButton->setMaximumWidth(100);

    domainInput = new QLineEdit();
    domainInput->setMaximumWidth(200);

    textOutput = new QTextBrowser();
    textOutput->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    textOutput->setMinimumSize(720, 480);

    devicesListWidget = new QListWidget(this);
    devicesListWidget->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    devicesListWidget->setMinimumSize(360, 200);

    listLabel = new QLabel("Found Devices");
    messagesLabel = new QLabel("Output Message");

    QHBoxLayout *hLayout = new QHBoxLayout;
    QGridLayout *mainLayout = new QGridLayout;
    hLayout->addWidget(scanButton);
    hLayout->addWidget(abortButton);
    hLayout->addWidget(clearButton);

    mainLayout->addLayout(hLayout, 0, 0);
    mainLayout->addWidget(listLabel);
    mainLayout->addWidget(devicesListWidget);
    mainLayout->addWidget(messagesLabel);
    mainLayout->addWidget(textOutput);
    setLayout(mainLayout);
    setWindowTitle(tr("Qt Bluetooth Experiments"));

    // connections
    connect(scanButton, SIGNAL(released()), this, SLOT(onScanButtonReleased()));
    connect(abortButton, SIGNAL(released()), this, SLOT(onAbortButtonReleased()));
    connect(clearButton, SIGNAL(released()), textOutput, SLOT(clear()));
    connect(devicesListWidget, SIGNAL(itemDoubleClicked(QListWidgetItem *)),
            this, SLOT(onDeviceListDoubleClick(QListWidgetItem *)));
    connect(discoveryAgent, SIGNAL(finished()),
            this, SLOT(scanFinished()));
}

void QTBT::scanFinished() {
    textOutput->append("Scan finished.");

    QList<QBluetoothDeviceInfo> devicesList = discoveryAgent->discoveredDevices();
    foreach( QBluetoothDeviceInfo devInfo, devicesList) {
        QString listText = QString("%1 (%2)").arg(devInfo.address().toString(), devInfo.name());
//        textOutput->append("Device Name:  " + devInfo.name());
//        textOutput->append("  Dev. Addr:  " + devInfo.address().toString());
        devicesListWidget->addItem(listText);
    }
    scanButton->setEnabled(true);
    abortButton->setDisabled(true);

    //
    textOutput->append(tr("Beginning service discovery..."));
    getServicesFromDevice(localBTDevice->address());
}

void QTBT::serviceDiscoveryFinished() {
    textOutput->append("Service discovery finished.");
}

void QTBT::onScanButtonReleased() {
    textOutput->append("Scan intitiated...");
    discoveryAgent->start();
    scanButton->setDisabled(true);
    abortButton->setEnabled(true);
}

void QTBT::onAbortButtonReleased() {
    textOutput->append("Scan aborted!");
    discoveryAgent->stop();
    scanButton->setEnabled(true);
    abortButton->setDisabled(true);
}

void QTBT::onDeviceListDoubleClick(QListWidgetItem *item) {
    textOutput->append(item->text());
//    QBluetoothAddress targetAddr = QBluetoothAddress("49:42:08:00:1b:02");
//    getServicesFromDevice(targetAddr);
}

void QTBT::serviceDiscovered(const QBluetoothServiceInfo svc) {
    textOutput->append("Service Discovered: " + svc.serviceName());
    QBluetoothDeviceInfo svcDevice = svc.device();
    textOutput->append("  -> Device: " + svcDevice.name());

    if (svcDevice.isValid()) {
        textOutput->append("  -> Device Valid: True");
    } else {
        textOutput->append("  -> Device Valid: FALSE!");
    }

    textOutput->append("Service Valid: " + (svc.isComplete()) ? "True" : "False");
}

void QTBT::getServicesFromDevice(QBluetoothAddress addr) {
    serviceAgent = new QBluetoothServiceDiscoveryAgent(addr);

    // Check error()
    if (serviceAgent->error() == \
        QBluetoothServiceDiscoveryAgent::InvalidBluetoothAdapterError)
    {
        QMessageBox::warning(this, tr("Warning"),
            tr("An 'Invalid Bluetooth Adapter Error' was received "
               "while attempting to scan for services!")
        );
        return;
    }
    textOutput->append("Service discovery beginning on " + addr.toString());
    connect(serviceAgent, SIGNAL(finished()),
            this, SLOT(serviceDiscoveryFinished()));
    connect(serviceAgent, SIGNAL(serviceDiscovered(const QBluetoothServiceInfo &)),
            this, SLOT(serviceDiscovered(const QBluetoothServiceInfo)));
    serviceAgent->start();
}