#include "playfaircipher.h"
#include "ui_playfaircipher.h"
#include <QDebug>

PlayfairCipher::PlayfairCipher(QWidget *parent, QString text) :
    AbstractCipher(parent),
    ui(new Ui::PlayfairCipher)
{
    ui->setupUi(this);
    ui->textEdit->setText(text);
}

PlayfairCipher::~PlayfairCipher()
{
    delete ui;
}

QPair<int, int> PlayfairCipher::tableSize(int alphabetLength)
{
    int a = qSqrt(alphabetLength);
    while(alphabetLength % a != 0)
    {
        a--;
    }
    return QPair<int, int>(a, alphabetLength / a);
}

void PlayfairCipher::encryptText()
{
    if(CryptoHelper::isUniq(ui->keyLineEdit->text()) && ui->keyLineEdit->text().length() <= CryptoHelper::alphabet().length())
    {
        if(ui->textEdit->toPlainText().length() % 2 != 0)
        {
            emit encryptedText(QString::fromLocal8Bit("Количество букв в тексте должно быть четным!"));
            return;
        }
        QString alphabet = CryptoHelper::alphabet();
        QString table;
        QString inText = CryptoHelper::pre(ui->textEdit->toPlainText());
        QString outText;
        int first;
        int second;
        int row = tableSize(alphabet.length()).first;
        int col = tableSize(alphabet.length()).second;
        for(int i = 0; i < ui->keyLineEdit->text().length(); i++)
        {
            alphabet.remove(ui->keyLineEdit->text()[i]);
        }
        table = ui->keyLineEdit->text();
        table += alphabet;
        for(int i = 0; i < inText.length() / 2; i++)
        {
            first = table.indexOf(inText[0]);
            second = table.indexOf(inText[1]);
            inText = CryptoHelper::leftRotate(inText, 2);
            if(first / col == second / col)
            {
                outText += table[first / col * col + (first + 1) % col];
                outText += table[second / col * col + (second  + 1) % col];
            }
            else if(qAbs(first - second) % col == 0)
            {
                outText += table[(first + col) % CryptoHelper::alphabet().length()];
                outText += table[(second + col) % CryptoHelper::alphabet().length()];
            }
            else
            {
                outText += table[first / col * col + second % col];
                outText += table[second / col * col + first % col];
            }
        }
        outText = CryptoHelper::post(outText, m_tokenLength);
        emit encryptedText(outText);
    }
    else
        emit encryptedText(QString::fromLocal8Bit("Данный ключ не подходит"));
}
