#include "cryptohelper.h"
#include <QDebug>

CryptoHelper::CryptoHelper(QObject *parent) :
    QObject(parent)
{
}

QString CryptoHelper::alphabet()
{
    return QString::fromLocal8Bit("абвгдежзийклмнопрстуфхцчшщьыъэюя");
}

QString CryptoHelper::pre(QString text)
{
    text = text.toLower();
    for(int i = 0; i < text.length(); i++)
    {
        if(!alphabet().contains(text[i]))
            text.replace(i, 1, ' ');
    }
    return text.replace(" ", "");
}

QString CryptoHelper::post(QString text, int tokenLength)
{
    for(int i = tokenLength; i < text.length(); i += tokenLength + 1)
        text.insert(i, " ");
    return text;
}


AbstractCipher::AbstractCipher(QObject *parent)
{
}

void AbstractCipher::encryptText()
{
}

void AbstractCipher::setTokenLength(int length)
{
    m_tokenLength = length;
}
