#include "caesarcipher.h"
#include "ui_caesarcipher.h"
#include <QDebug>

CaesarCipher::CaesarCipher(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CaesarCipher)
{
    ui->setupUi(this);
}

CaesarCipher::~CaesarCipher()
{
    delete ui;
}

void CaesarCipher::encryptText()
{
    int index;
    QString text = ui->textEdit->toPlainText();
    text = CryptoHelper::pre(text);
    for(int i = 0; i < text.length(); i++)
    {
        index = (CryptoHelper::alphabet().indexOf(text[i]) + ui->spinBox->value()) % CryptoHelper::alphabet().length();
        text[i] = CryptoHelper::alphabet()[index];
    }
    text = CryptoHelper::post(text, m_tokenLength);
    emit encryptedText(text);
}

void CaesarCipher::setTokenLength(int length)
{
    m_tokenLength = length;
}
