#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QTextEdit>
#include <QDebug>
#include "cryptohelper.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->spinBox->setValue(4);
    on_ciphiersComboBox_currentIndexChanged(ui->ciphiersComboBox->currentIndex());
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ciphiersComboBox_currentIndexChanged(int index)
{
    switch(index)
    {
        case 0:
        {
            if(ui->codeInputLayout->itemAt(0) != 0)
                delete ui->codeInputLayout->takeAt(0)->widget();
            CaesarCipher *widget = new CaesarCipher;
            widget->setTokenLength(ui->spinBox->value());
            connect(ui->spinBox, SIGNAL(valueChanged(int)), widget, SLOT(setTokenLength(int)));
            connect(widget, SIGNAL(encryptedText(QString)), ui->codeOutTextEdit, SLOT(setText(QString)));
            connect(ui->encryptPushButton, SIGNAL(clicked()), widget, SLOT(encryptText()));
            ui->codeInputLayout->addWidget(widget);
            break;
        }
        case 1:
        {
            if(ui->codeInputLayout->itemAt(0) != 0)
                delete ui->codeInputLayout->takeAt(0)->widget();
            CaesarAfCipher *widget = new CaesarAfCipher;
            widget->setTokenLength(ui->spinBox->value());
            connect(ui->spinBox, SIGNAL(valueChanged(int)), widget, SLOT(setTokenLength(int)));
            connect(widget, SIGNAL(encryptedText(QString)), ui->codeOutTextEdit, SLOT(setText(QString)));
            connect(ui->encryptPushButton, SIGNAL(clicked()), widget, SLOT(encryptText()));
            ui->codeInputLayout->addWidget(widget);
            break;
        }
    }
}
