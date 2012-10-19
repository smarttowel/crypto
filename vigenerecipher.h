#ifndef VIGENERECIPHER_H
#define VIGENERECIPHER_H

#include <QWidget>
#include <cryptohelper.h>

namespace Ui {
class VigenereCipher;
}

class VigenereCipher : public AbstractCipher
{
    Q_OBJECT
    
public:
    explicit VigenereCipher(QWidget *parent = 0, QString text = "");
    ~VigenereCipher();
    
private:
    Ui::VigenereCipher *ui;

public slots:
    void encryptText();
};

#endif // VIGENERECIPHER_H
