#ifndef VIGENERECIPHER_H
#define VIGENERECIPHER_H

#include <QWidget>
#include <cryptohelper.h>
#include <QPainter>
#include <QDebug>
#include "abstractcipherview.h"

class VigenereCipherView : public AbstractCipherView
{
    Q_OBJECT

public:
    explicit VigenereCipherView(QWidget *parent = 0, int a = 0);
    ~VigenereCipherView();

private:
    int m_currentChar;

protected:
    void paintEvent(QPaintEvent *);
    void onNextButtonClick();
    void onBackButtonClick();
    void resetChars();
};

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
