#ifndef TRITHEMIUSCIPHER_H
#define TRITHEMIUSCIPHER_H

#include <QWidget>
#include <QPainter>
#include "abstractcipherview.h"
#include "cryptohelper.h"

class TrithemiusCipherView : public AbstractCipherView
{
    Q_OBJECT

public:
    explicit TrithemiusCipherView(QWidget *parent = 0, int a = 0);
    ~TrithemiusCipherView();

protected:
    void paintEvent(QPaintEvent *);
};

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
