#ifndef PLAYFAIRCIPHER_H
#define PLAYFAIRCIPHER_H

#include <QWidget>
#include <qmath.h>
#include "cryptohelper.h"

namespace Ui {
class PlayfairCipher;
}

class PlayfairCipher : public AbstractCipher
{
    Q_OBJECT
    
public:
    explicit PlayfairCipher(QWidget *parent = 0, QString text = "");
    ~PlayfairCipher();
    
private:
    Ui::PlayfairCipher *ui;
    QPair<int, int> tableSize(int alphabetLength);


public slots:
    void encryptText();
};

#endif // PLAYFAIRCIPHER_H