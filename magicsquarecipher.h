#ifndef MAGICSQUARECIPHER_H
#define MAGICSQUARECIPHER_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QPainter>
#include "abstractcipherview.h"
#include "cryptohelper.h"

class MagicSquareCipherView : public AbstractCipherView
{
    Q_OBJECT

public:
    explicit MagicSquareCipherView(QWidget *parent = 0, int a = 0);
    ~MagicSquareCipherView();

private:
    int m_currentChar;

protected:
    void paintEvent(QPaintEvent *);
    void onNextButtonClick();
    void onBackButtonClick();
    void resetChars();
};

namespace Ui {
class MagicSquareCipher;
}

class MagicSquareCipher : public AbstractCipher
{
    Q_OBJECT
    
public:
    explicit MagicSquareCipher(QWidget *parent = 0, QString text = "");
    ~MagicSquareCipher();
    
private slots:
    void on_spinBox_valueChanged(int arg1);
    void on_clearSquarePushButton_clicked();

private:
    Ui::MagicSquareCipher *ui;
    void generateEvenSquare();
    void generateOddSquare();
    bool checkOnMagic();

public slots:
    void encryptText();
};

#endif // MAGICSQUARECIPHER_H
