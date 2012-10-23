#include "caesarcipher.h"
#include "ui_caesarcipher.h"
#include <QDebug>

CaesarCipher::CaesarCipher(QWidget *parent, QString text) :
    AbstractCipher(parent),
    ui(new Ui::CaesarCipher)
{
    ui->setupUi(this);
    ui->textEdit->setText(text);
}

CaesarCipher::~CaesarCipher()
{
    emit text(ui->textEdit->toPlainText());
    delete ui;
}

void CaesarCipher::encryptText()
{
    int index;
    QString text = ui->textEdit->toPlainText();
    text = CryptoHelper::pre(text);
    for(int i = 0; i < text.length(); i++)
    {
        index = (CryptoHelper::alphabet.indexOf(text[i]) + ui->spinBox->value()) % CryptoHelper::alphabet.length();
        text[i] = CryptoHelper::alphabet[index];
    }
    text = CryptoHelper::post(text);
    emit encryptedText(text);
}
