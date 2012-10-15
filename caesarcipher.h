#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include <QWidget>
#include "cryptohelper.h"

namespace Ui {
class CaesarCipher;
}

class CaesarCipher : public QWidget
{
    Q_OBJECT
    
public:
    explicit CaesarCipher(QWidget *parent = 0);
    ~CaesarCipher();
    
private:
    Ui::CaesarCipher *ui;
    int m_tokenLength;

public slots:
    void encryptText();
    void setTokenLength(int length);

signals:
    void encryptedText(QString str);
};

#endif // CAESARCIPHER_H
