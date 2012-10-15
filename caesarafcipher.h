#ifndef CAESARAFCIPHER_H
#define CAESARAFCIPHER_H

#include <QWidget>

namespace Ui {
class CaesarAfCipher;
}

class CaesarAfCipher : public QWidget
{
    Q_OBJECT
    
public:
    explicit CaesarAfCipher(QWidget *parent = 0);
    ~CaesarAfCipher();
    
private:
    Ui::CaesarAfCipher *ui;
    int m_tokenLength;
    int gcd(int a, int b);

public slots:
    void encryptText();
    void setTokenLength(int length);

signals:
    void encryptedText(QString str);
};

#endif // CAESARAFCIPHER_H
