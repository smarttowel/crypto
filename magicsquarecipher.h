#ifndef MAGICSQUARECIPHER_H
#define MAGICSQUARECIPHER_H

#include <QWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "cryptohelper.h"

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
};

#endif // MAGICSQUARECIPHER_H
