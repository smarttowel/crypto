#include "trithemiuscipher.h"
#include "ui_trithemiuscipher.h"
#include <QDebug>

TrithemiusCipher::TrithemiusCipher(QWidget *parent, QString text) :
    AbstractCipher(parent),
    ui(new Ui::TrithemiusCipher)
{
    ui->setupUi(this);
    ui->textEdit->setText(text);
}

TrithemiusCipher::~TrithemiusCipher()
{
    delete ui;
}

void TrithemiusCipher::encryptText()
{
    if(CryptoHelper::isUniq(ui->lineEdit->text()) && ui->lineEdit->text().length() <= CryptoHelper::alphabet().length())
    {
        QString inText = CryptoHelper::pre(ui->textEdit->toPlainText());
        QString outText;
        QString table;
        QString alphabet = CryptoHelper::alphabet();
        int row = CryptoHelper::tableSize(alphabet.length()).first;
        int col = CryptoHelper::tableSize(alphabet.length()).second;
        for(int i = 0; i < ui->lineEdit->text().length(); i++)
        {
            alphabet.remove(ui->lineEdit->text()[i]);
        }
        table = ui->lineEdit->text();
        table += alphabet;
        qDebug() << table.left(8);
        qDebug() << table.mid(8, 8);
        qDebug() << table.mid(16, 8);
        qDebug() << table.right(8);
        for(int i = 0; i < inText.length(); i++)
        {
            outText += table[(table.indexOf(inText[i]) + col) % CryptoHelper::alphabet().length()];
        }
        outText = CryptoHelper::post(outText, m_tokenLength);
        emit encryptedText(outText);
    }
    else
        emit encryptedText(QString::fromLocal8Bit("Этот ключ не подходит!"));
}
