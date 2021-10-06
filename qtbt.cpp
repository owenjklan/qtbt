//
// Created by owen on 6/10/21.
//

#include "qtbt.hpp"

QTBT::QTBT(QWidget *parent) :
    QWidget(parent)
{
    // UI Widget and layout setup
    scanButton = new QPushButton(tr("GeoIP Lookup"));
    scanButton->setFont(QFont("Courier", 10, QFont::Bold));
    scanButton->setMaximumWidth(100);

    domainInput = new QLineEdit();
    domainInput->setMaximumWidth(200);

    textOutput = new QTextBrowser();
    textOutput->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
    textOutput->setMinimumSize(720, 480);

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(scanButton, 0, 0);
    mainLayout->addWidget(textOutput, 1, 0);
    setLayout(mainLayout);
    setWindowTitle(tr("Qt Bluetooth Experiments"));

    // connections
    connect(scanButton, SIGNAL(released()), this, SLOT(onScanButtonReleased()));
//    connect(netManager, SIGNAL(finished(QNetworkReply *)), this, SLOT(netManagerFinished(QNetworkReply *)));
}

// Destructor
QTBT::~QTBT()
{
    delete scanButton;
    delete domainInput;
    delete textOutput;
}

void QTBT::onScanButtonReleased() {
    textOutput->append("Scan intitiated...");
}