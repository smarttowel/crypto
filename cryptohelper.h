#ifndef CRYPTOHELPER_H
#define CRYPTOHELPER_H

#include <QObject>
#include <QWidget>
#include <QString>
#include <qmath.h>
#include <QPushButton>

class CryptoHelper : public QObject
{
    Q_OBJECT

public:
    explicit CryptoHelper(QObject *parent = 0);
    static QString pre(QString text);
    static QString preW(QString text);
    static QString post(QString text);
    static bool isUniq(QString text);
    static QString leftRotate(QString text, int count);
    static QString rightRotate(QString text, int count);
    static QPair<int, int> tableSize(int alphabetLength);
    static void setAlphabet(QString alphabet);
    static QString alphabet;
    static QString extAlphabet;
    static int tokenLength;

signals:
    
public slots:
    
};

class AbstractCipher : public QWidget
{
    Q_OBJECT
public:
    explicit AbstractCipher(QWidget *parent = 0);

public slots:
    virtual void encryptText();

signals:
    void encryptedText(QString str);
    void text(QString text);
    void results(QString inText, QString outText);
    void results(QString alphabet, QString inText, QString outText);
    void results(QVector<int> square, QString inText, QString outText);
};
#endif // CRYPTOHELPER_H
