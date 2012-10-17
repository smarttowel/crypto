#ifndef CAESARKWCIPHER_H
#define CAESARKWCIPHER_H

#include <QWidget>
#include "cryptohelper.h"

namespace Ui {
class CaesarKWCipher;
}

class CaesarKWCipher : public AbstractCipher
{
    Q_OBJECT
    
public:
    explicit CaesarKWCipher(QWidget *parent = 0, QString text = "");
    ~CaesarKWCipher();
    
private:
    Ui::CaesarKWCipher *ui;

public slots:
    void encryptText();
};

#endif // CAESARKWCIPHER_H
