#include "caesarkwcipher.h"
#include "ui_caesarkwcipher.h"
#include <QDebug>

CaesarKWCipher::CaesarKWCipher(QWidget *parent, QString text) :
    AbstractCipher(parent),
    ui(new Ui::CaesarKWCipher)
{
    ui->setupUi(this);
    ui->textEdit->setText(text);
    ui->firstKeySpinBox->setMaximum(CryptoHelper::alphabet().length());
}

CaesarKWCipher::~CaesarKWCipher()
{
    delete ui;
}

void CaesarKWCipher::encryptText()
{
    if(CryptoHelper::isUniq(ui->secondKeyLineEdit->text()) || ui->secondKeyLineEdit->text().length() > CryptoHelper::alphabet().length())
    {
        QString alphabet = CryptoHelper::alphabet();
        QString newAlphabet;
        QString inText = CryptoHelper::pre(ui->textEdit->toPlainText());
        QString outText;
        for(int i = 0; i < ui->secondKeyLineEdit->text().length(); i++)
        {
            alphabet.remove(ui->secondKeyLineEdit->text()[i]);
        }
        newAlphabet = ui->secondKeyLineEdit->text();
        newAlphabet += alphabet;
        newAlphabet = CryptoHelper::rightRotate(newAlphabet, ui->firstKeySpinBox->value() - 1);
        for(int i = 0; i < inText.length(); i++)
            outText += newAlphabet[CryptoHelper::alphabet().indexOf(inText[i])];
        outText = CryptoHelper::post(outText, m_tokenLength);
        emit encryptedText(outText);
    }
    else
        emit encryptedText(QString::fromLocal8Bit("В ключевом слове не должны повторяться буквы!"));
}
