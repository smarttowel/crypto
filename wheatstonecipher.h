#ifndef WHEATSTONECIPHER_H
#define WHEATSTONECIPHER_H

#include <QWidget>
#include <QTime>
#include <QPainter>
#include <QPen>
#include "cryptohelper.h"
#include "abstractcipherview.h"

class WheatstoneCipherView : public AbstractCipherView
{
    Q_OBJECT

public:
    explicit WheatstoneCipherView(QWidget *parent = 0, int a = 0);
    ~WheatstoneCipherView();

protected:
    void paintEvent(QPaintEvent *);
};

namespace Ui {
class WheatstoneCipher;
}

class WheatstoneCipher : public AbstractCipher
{
    Q_OBJECT
    
public:
    explicit WheatstoneCipher(QWidget *parent = 0, QString text = "");
    ~WheatstoneCipher();
    
private:
    void fillTables();
    bool checkTables();
    Ui::WheatstoneCipher *ui;

public slots:
    void encryptText();
};

#endif // WHEATSTONECIPHER_H
