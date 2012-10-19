#ifndef TRITHEMIUSCIPHER_H
#define TRITHEMIUSCIPHER_H

#include <QWidget>
#include "cryptohelper.h"

namespace Ui {
class TrithemiusCipher;
}

class TrithemiusCipher : public AbstractCipher
{
    Q_OBJECT
    
public:
    explicit TrithemiusCipher(QWidget *parent = 0, QString text = "");
    ~TrithemiusCipher();
    
private:
    Ui::TrithemiusCipher *ui;

public slots:
    void encryptText();
};

#endif // TRITHEMIUSCIPHER_H
