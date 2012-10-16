#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include <QWidget>
#include "cryptohelper.h"

namespace Ui {
class CaesarCipher;
}

class CaesarCipher : public AbstractCipher
{
    Q_OBJECT
    
public:
    explicit CaesarCipher(QWidget *parent = 0, QString text = "");
    ~CaesarCipher();
    
private:
    Ui::CaesarCipher *ui;

public slots:
    void encryptText();
};

#endif // CAESARCIPHER_H
