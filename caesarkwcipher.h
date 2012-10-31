#ifndef CAESARKWCIPHER_H
#define CAESARKWCIPHER_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include "cryptohelper.h"
#include "abstractcipherview.h"

class CaesarKWCipherView : public AbstractCipherView
{
    Q_OBJECT

public:
    explicit CaesarKWCipherView(QWidget *parent = 0, int a = 0);
    ~CaesarKWCipherView();

private:
    int m_currentChar;

protected:
    void paintEvent(QPaintEvent *);
    void onNextButtonClick();
    void onBackButtonClick();
    void resetChars();
};

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
