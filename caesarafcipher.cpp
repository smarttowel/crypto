#include "caesarafcipher.h"
#include "ui_caesarafcipher.h"

CaesarAfCipher::CaesarAfCipher(QWidget *parent, QString text) :
    AbstractCipher(parent),
    ui(new Ui::CaesarAfCipher)
{
    ui->setupUi(this);
    ui->textEdit->setText(text);
    ui->firstKeyspinBox->setMaximum(CryptoHelper::alphabet.length());
    ui->secondKeyspinBox->setMaximum(CryptoHelper::alphabet.length());
}

CaesarAfCipher::~CaesarAfCipher()
{
    emit text(ui->textEdit->toPlainText());
    delete ui;
}

int CaesarAfCipher::gcd(int a, int b)
{
    if(a == b)
        return a;
    else if(a > b)
        return gcd(a - b, b);
    else
        return gcd(b, a);
}

void CaesarAfCipher::encryptText()
{
    QString text;
    text = ui->textEdit->toPlainText();
    if(gcd(ui->firstKeyspinBox->value(), CryptoHelper::alphabet.length()) == 1)
    {
        text = CryptoHelper::pre(text);
        for(int i = 0; i < text.length(); i++)
            text[i] = CryptoHelper::alphabet[ui->firstKeyspinBox->value() * i +
                    ui->secondKeyspinBox->value() % CryptoHelper::alphabet.length()];
        emit results(CryptoHelper::pre(ui->textEdit->toPlainText()), CryptoHelper::pre(CryptoHelper::post(text)));
    }
    else
        text = QString::fromLocal8Bit("a и m не взаимно простые!");
    text = CryptoHelper::post(text);
    emit encryptedText(text);
}
