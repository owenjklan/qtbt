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

// This is the declaration of our MainWidget class
// The definition/implementation is in qis_widget.cpp
class QTBT : public QWidget
{
Q_OBJECT

public:
    explicit QTBT(QWidget *parent = 0); //Constructor
    ~QTBT(); // Destructor

private slots:
    void onScanButtonReleased();

private:
    QPushButton *scanButton;
    QLineEdit *domainInput;
    QTextBrowser *textOutput;
};

#endif //QTBT_QTBT_HPP
