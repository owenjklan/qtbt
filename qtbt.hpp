//
// Created by owen on 6/10/21.
//

#ifndef QTBT_QTBT_HPP
#define QTBT_QTBT_HPP

#include <QFont>
#include <QString>
#include <QTextBrowser>
#include <QLineEdit>
#include <QtWidgets>
#include <QBluetoothLocalDevice>
#include <QBluetoothDeviceDiscoveryAgent>
#include <QBluetoothServiceDiscoveryAgent>
#include <QBluetoothDeviceInfo>
#include <QBluetoothServiceInfo>

// This is the declaration of our MainWidget class
// The definition/implementation is in qis_widget.cpp
class QTBT : public QWidget
{
Q_OBJECT

public:
    explicit QTBT(QWidget *parent = 0); //Constructor
    ~QTBT(); // Destructor
    void getServicesFromDevice(QBluetoothAddress addr);

private slots:
    void setupUiAndSignals(QWidget *parent);
    void setupBluetooth();
    void onScanButtonReleased();
    void onAbortButtonReleased();
    void onDeviceListDoubleClick(QListWidgetItem *);
    void scanFinished();
    void serviceDiscoveryFinished();
    void serviceDiscovered(const QBluetoothServiceInfo svc);

private:
    QBluetoothLocalDevice *localBTDevice;
    QBluetoothDeviceDiscoveryAgent *discoveryAgent;
    QBluetoothServiceDiscoveryAgent *serviceAgent;
    QPushButton *scanButton;
    QPushButton *clearButton;
    QPushButton *abortButton;
    QLineEdit *domainInput;
    QTextBrowser *textOutput;
    QListWidget *devicesListWidget;

    QLabel *listLabel;
    QLabel *messagesLabel;
};

#endif //QTBT_QTBT_HPP
