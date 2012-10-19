#include "vigenerecipher.h"
#include "ui_vigenerecipher.h"

VigenereCipher::VigenereCipher(QWidget *parent, QString text) :
    AbstractCipher(parent),
    ui(new Ui::VigenereCipher)
{
    ui->setupUi(this);
    ui->textEdit->setText(text);
}

VigenereCipher::~VigenereCipher()
{
    delete ui;
}

void VigenereCipher::encryptText()
{
    QString inText = CryptoHelper::pre(ui->textEdit->toPlainText());
    QString key = ui->lineEdit->text();
    QString outText;
    QString alphabet = CryptoHelper::alphabet();
    for(int i = 0; i < inText.length(); i++)
    {
        outText += alphabet[alphabet.indexOf(inText[i]) + alphabet.indexOf(key[i % key.length()]) % alphabet.length()];
    }
    outText = CryptoHelper::post(outText, m_tokenLength);
    emit encryptedText(outText);
}
