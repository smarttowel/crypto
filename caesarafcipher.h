#ifndef CAESARAFCIPHER_H
#define CAESARAFCIPHER_H

#include <QWidget>
#include "cryptohelper.h"

namespace Ui {
class CaesarAfCipher;
}

class CaesarAfCipher : public AbstractCipher
{
    Q_OBJECT
    
public:
    explicit CaesarAfCipher(QWidget *parent = 0, QString text = "");
    ~CaesarAfCipher();
    
private:
    Ui::CaesarAfCipher *ui;
    int gcd(int a, int b);

public slots:
    void encryptText();
};

#endif // CAESARAFCIPHER_H
