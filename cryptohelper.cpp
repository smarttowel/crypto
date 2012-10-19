#include "cryptohelper.h"
#include <QDebug>

CryptoHelper::CryptoHelper(QObject *parent) :
    QObject(parent)
{
}

QString CryptoHelper::alphabet()
{
    return QString::fromLocal8Bit("абвгдежзийклмнопрстуфхцчшщъыьэюя");
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

bool CryptoHelper::isUniq(QString text)
{
    QString key;
    for(int i = 0; i < text.length(); i++)
        if(key.contains(text[i]))
            return false;
        else
            key += text[i];
    return true;
}

QString CryptoHelper::leftRotate(QString text, int count)
{
    QChar c;
    for(int j = 0; j < count; j++)
    {
        c = text[0];
        for(int i = 0; i < text.length() - 1; i++)
            text[i] = text[i + 1];
        text[text.length() - 1] = c;
    }
    return text;
}

QString CryptoHelper::rightRotate(QString text, int count)
{
    QChar c;
    for(int j = 0; j < count; j++)
    {
        c = text[text.length() - 1];
        for(int i = text.length() - 1; i != 0 ; i--)
            text[i] = text[i - 1];
        text[0] = c;
    }
    return text;
}

QPair<int, int> CryptoHelper::tableSize(int alphabetLength)
{
    int a = qSqrt(alphabetLength);
    while(alphabetLength % a != 0)
    {
        a--;
    }
    return QPair<int, int>(a, alphabetLength / a);
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
