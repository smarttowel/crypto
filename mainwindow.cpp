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
    AbstractCipher *widget;
    if(ui->codeInputLayout->itemAt(0) != 0)
        delete ui->codeInputLayout->takeAt(0)->widget();
    switch(index)
    {
        case 0:
        {
            widget = new CaesarCipher(0, m_text);
            break;
        }
        case 1:
        {
            widget = new CaesarAfCipher(0, m_text);
            break;
        }
        case 2:
        {
            widget = new CaesarKWCipher(0, m_text);
            break;
        }
        case 3:
        {
            widget = new PlayfairCipher(0, m_text);
            break;
        }
        case 4:
        {
            widget = new TrithemiusCipher(0, m_text);
            break;
        }
        case 5:
        {
            widget = new VigenereCipher(0, m_text);
            break;
        }
        case 6:
        {
            widget = new MagicSquareCipher(0, m_text);
            break;
        }
    }
    widget->setTokenLength(ui->spinBox->value());
    connect(ui->spinBox, SIGNAL(valueChanged(int)), widget, SLOT(setTokenLength(int)));
    connect(widget, SIGNAL(encryptedText(QString)), ui->codeOutTextEdit, SLOT(setText(QString)));
    connect(ui->encryptPushButton, SIGNAL(clicked()), widget, SLOT(encryptText()));
    connect(widget, SIGNAL(text(QString)), this, SLOT(textBuffer(QString)));
    ui->codeInputLayout->addWidget(widget);
}

void MainWindow::textBuffer(QString text)
{
    m_text = text;
}
