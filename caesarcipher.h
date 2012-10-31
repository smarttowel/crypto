#ifndef CAESARCIPHER_H
#define CAESARCIPHER_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include "cryptohelper.h"
#include "abstractcipherview.h"

class CaesarCipherView : public AbstractCipherView
{
    Q_OBJECT

public:
    explicit CaesarCipherView(QWidget *parent = 0, int a = 0);
    ~CaesarCipherView();

private:
    int m_currentChar;

protected:
    void paintEvent(QPaintEvent *);
    void onNextButtonClick();
    void onBackButtonClick();
    void resetChars();
};

namespace Ui {
class CaesarCipher;
}

class CaesarCipher : public AbstractCipher
{
    Q_OBJECT
    
public:
    explicit CaesarCipher(QWidget *parent = 0, QString text = "");
    ~CaesarCipher();
    QString getText();
    
private:
    Ui::CaesarCipher *ui;
    bool m_studyMode;

public slots:
    void encryptText();
};

#endif // CAESARCIPHER_H
