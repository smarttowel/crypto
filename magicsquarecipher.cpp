#include "magicsquarecipher.h"
#include "ui_magicsquarecipher.h"
#include <QDebug>

MagicSquareCipher::MagicSquareCipher(QWidget *parent, QString text) :
    AbstractCipher(parent),
    ui(new Ui::MagicSquareCipher)
{
    ui->setupUi(this);
    on_spinBox_valueChanged(ui->spinBox->value());
    ui->textEdit->setText(text);
}

MagicSquareCipher::~MagicSquareCipher()
{
    delete ui;
}

void MagicSquareCipher::on_spinBox_valueChanged(int arg1)
{
    ui->tableWidget->setRowCount(arg1);
    ui->tableWidget->setColumnCount(arg1);
    on_clearSquarePushButton_clicked();
    if(arg1 % 2 == 0)
        generateEvenSquare();
    else
        generateOddSquare();
}

void MagicSquareCipher::on_clearSquarePushButton_clicked()
{
    for(int i = 0; i < ui->tableWidget->rowCount(); i++)
        for(int j = 0; j < ui->tableWidget->columnCount(); j++)
            ui->tableWidget->setItem(i, j, new QTableWidgetItem("", Qt::DisplayRole));
}

void MagicSquareCipher::generateEvenSquare()
{

}

void MagicSquareCipher::generateOddSquare()
{
    //init
    int n = ui->spinBox->value();
    int mid = n / 2 + 1;
    int a = 0;
    int b = mid - 1;
    int array[n][n];
    //fill array
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            array[i][j] = 0;
    //generate magic square
    for(int i = 1; i <= n*n; i++)
    {
        array[a][b] = i;
        if(array[(a + 2) % n][(b + 1) % n] != 0)
            a = (a + 4) % n;
        else
        {
            a = (a + 2) % n;
            b = (b + 1) % n;
        }
    }
    //output
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(QString::number(array[i][j]), Qt::DisplayRole));
}
