#ifndef CRYPTOHELPER_H
#define CRYPTOHELPER_H

#include <QObject>
#include <QWidget>
#include <QString>

class CryptoHelper : public QObject
{
    Q_OBJECT
public:
    explicit CryptoHelper(QObject *parent = 0);
    static QString alphabet();
    static QString pre(QString text);
    static QString post(QString text, int tokenLength);

signals:
    
public slots:
    
};

class AbstractCipher : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractCipher(QObject *parent = 0);

protected:
    int m_tokenLength;

public slots:
    virtual void encryptText();
    void setTokenLength(int length);

signals:
    void encryptedText(QString str);
    void text(QString text);
};

#endif // CRYPTOHELPER_H
