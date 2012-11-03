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
    m_visualization = 0;
    move(QApplication::desktop()->geometry().width() / 2 - this->geometry().width() / 2,
         QApplication::desktop()->geometry().height() / 2 - this->geometry().height() / 2);
    CryptoHelper::alphabet = QString::fromLocal8Bit("абвгдежзийклмнопрстуфхцчшщъыьэюя");
    CryptoHelper::tokenLength = 4;
    on_ciphiersComboBox_currentIndexChanged(ui->ciphiersComboBox->currentIndex());
    connect(ui->action_saveToFile, SIGNAL(triggered()), this, SLOT(saveToFile()));
    connect(ui->action_aboutQt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->action_Exit, SIGNAL(triggered()), qApp, SLOT(quit()));
    connect(ui->action_settings, SIGNAL(triggered()), &m_settings, SLOT(show()));
    connect(&m_settings, SIGNAL(alphabetChanged()), this, SLOT(reloadCipher()));
    connect(ui->action_aboutProgram, SIGNAL(triggered()), &m_about, SLOT(show()));
    connect(ui->encryptPushButton, SIGNAL(clicked()), ui->codeOutTextEdit, SLOT(clear()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_ciphiersComboBox_currentIndexChanged(int index)
{
    if(ui->codeInputLayout->itemAt(0) != 0)
        delete ui->codeInputLayout->takeAt(0)->widget();
    if(m_visualization != 0)
        delete m_visualization;
    switch(index)
    {
        case 0:
        {
            m_cipher = new CaesarCipher(0, m_text);
            m_visualization = new CaesarCipherView(0, int(ui->trainingModeCheckBox->checkState()));
            break;
        }
        case 1:
        {
            m_cipher = new CaesarAfCipher(0, m_text);
            m_visualization = new CaesarCipherView(0, int(ui->trainingModeCheckBox->checkState()));
            break;
        }
        case 2:
        {
            m_cipher = new CaesarKWCipher(0, m_text);
            m_visualization = new CaesarKWCipherView(0, int(ui->trainingModeCheckBox->checkState()));
            break;
        }
        case 3:
        {
            m_cipher = new PlayfairCipher(0, m_text);
            m_visualization = new PlayfairCipherView(0, int(ui->trainingModeCheckBox->checkState()));
            break;
        }
        case 4:
        {
            m_cipher = new TrithemiusCipher(0, m_text);
            m_visualization = new TrithemiusCipherView(0, int(ui->trainingModeCheckBox->checkState()));
            break;
        }
        case 5:
        {
            m_cipher = new VigenereCipher(0, m_text);
            m_visualization = new VigenereCipherView(0, int(ui->trainingModeCheckBox->checkState()));
            break;
        }
        case 6:
        {
            m_cipher = new MagicSquareCipher(0, m_text);
            m_visualization = new MagicSquareCipherView(0, int(ui->trainingModeCheckBox->checkState()));
            break;
        }
        case 7:
        {
            m_cipher = new WheatstoneCipher(0, m_text);
            m_visualization = new WheatstoneCipherView(0, int(ui->trainingModeCheckBox->checkState()));
            break;
        }
    }
    connect(m_cipher, SIGNAL(encryptedText(QString)), ui->codeOutTextEdit, SLOT(setText(QString)));
    connect(ui->encryptPushButton, SIGNAL(clicked()), m_cipher, SLOT(encryptText()));
    connect(m_cipher, SIGNAL(text(QString)), this, SLOT(textBuffer(QString)));
    connect(m_cipher, SIGNAL(results(QString,QString)), m_visualization, SLOT(setResults(QString,QString)));
    connect(m_cipher, SIGNAL(results(QString,QString,QString)), m_visualization, SLOT(setResults(QString,QString,QString)));
    connect(m_cipher, SIGNAL(results(QVector<int>,QString,QString)), m_visualization, SLOT(setResults(QVector<int>,QString,QString)));
    connect(m_cipher, SIGNAL(results(QString,QString,QString,QString)), m_visualization, SLOT(setResults(QString,QString,QString,QString)));
    connect(ui->trainingModeCheckBox, SIGNAL(stateChanged(int)), m_visualization, SLOT(setIsShow(int)));
    ui->codeInputLayout->addWidget(m_cipher);
}

void MainWindow::textBuffer(QString text)
{
    m_text = text;
}

void MainWindow::saveToFile()
{
    QString filename = QFileDialog::getSaveFileName(this, QString::fromLocal8Bit("Сохранить в..."), "",
                                                    QString("Text files (*.txt)"));
    QFile file;
    file.setFileName(filename);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QTextStream stream(&file);
    stream << ui->codeOutTextEdit->toPlainText();
    file.close();
}

void MainWindow::reloadCipher()
{
    on_ciphiersComboBox_currentIndexChanged(ui->ciphiersComboBox->currentIndex());
}
