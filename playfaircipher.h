#ifndef PLAYFAIRCIPHER_H
#define PLAYFAIRCIPHER_H

#include <QWidget>
#include <QPainter>
#include <QPen>
#include "cryptohelper.h"
#include "abstractcipherview.h"

class PlayfairCipherView : public AbstractCipherView
{
    Q_OBJECT

public:
    explicit PlayfairCipherView(QWidget *parent = 0, int a = 0);
    ~PlayfairCipherView();

private:
    int m_currentChar;

protected:
    void paintEvent(QPaintEvent *);
    void onNextButtonClick();
    void onBackButtonClick();
    void resetChars();
};

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

public slots:
    void encryptText();
};

#endif // PLAYFAIRCIPHER_H
