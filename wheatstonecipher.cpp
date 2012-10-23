#include "wheatstonecipher.h"
#include "ui_wheatstonecipher.h"
#include <QDebug>

WheatstoneCipher::WheatstoneCipher(QWidget *parent, QString text) :
    AbstractCipher(parent),
    ui(new Ui::WheatstoneCipher)
{
    ui->setupUi(this);
    qsrand(QTime::currentTime().msec());
    ui->textEdit->setText(text);
    QPair<int, int> size = CryptoHelper::tableSize(CryptoHelper::alphabet.length());
    ui->firstKeyTableWidget->setRowCount(size.first);
    ui->firstKeyTableWidget->setColumnCount(size.second);
    ui->secondKeyTableWidget->setRowCount(size.first);
    ui->secondKeyTableWidget->setColumnCount(size.second);
    fillTables();
}

WheatstoneCipher::~WheatstoneCipher()
{
    delete ui;
}

void WheatstoneCipher::fillTables()
{
    QString alphabet = CryptoHelper::alphabet + CryptoHelper::extAlphabet;
    int index;
    for(int i = 0; i < ui->firstKeyTableWidget->rowCount(); i++)
        for(int j = 0; j < ui->firstKeyTableWidget->columnCount(); j++)
        {
            index = qrand() % alphabet.length();
            ui->firstKeyTableWidget->setItem(i,j, new QTableWidgetItem(QString(alphabet[index]), Qt::DisplayRole));
            alphabet.remove(index, 1);
        }
    alphabet = CryptoHelper::alphabet + CryptoHelper::extAlphabet;
    for(int i = 0; i < ui->secondKeyTableWidget->rowCount(); i++)
        for(int j = 0; j < ui->secondKeyTableWidget->columnCount(); j++)
        {
            index = qrand() % alphabet.length();
            ui->secondKeyTableWidget->setItem(i,j, new QTableWidgetItem(QString(alphabet[index]), Qt::DisplayRole));
            alphabet.remove(index, 1);
        }
}

bool WheatstoneCipher::checkTables()
{
    for(int i = 0; i < ui->firstKeyTableWidget->rowCount(); i++)
        for(int j = 0; j < ui->firstKeyTableWidget->columnCount(); j++)
            if(ui->firstKeyTableWidget->item(i,j) == 0 || ui->firstKeyTableWidget->item(i,j) == 0)
                return false;
    QString alphabet = CryptoHelper::alphabet + CryptoHelper::extAlphabet;
    for(int i = 0; i < ui->firstKeyTableWidget->rowCount(); i++)
        for(int j = 0; j < ui->firstKeyTableWidget->columnCount(); j++)
        {
            if(alphabet.indexOf(ui->firstKeyTableWidget->item(i,j)->data(Qt::DisplayRole).toString()) != -1)
                alphabet.remove(ui->firstKeyTableWidget->item(i,j)->data(Qt::DisplayRole).toString());
            else
                return false;
        }
    alphabet = CryptoHelper::alphabet + CryptoHelper::extAlphabet;
    for(int i = 0; i < ui->secondKeyTableWidget->rowCount(); i++)
        for(int j = 0; j < ui->secondKeyTableWidget->columnCount(); j++)
        {
            if(alphabet.indexOf(ui->secondKeyTableWidget->item(i,j)->data(Qt::DisplayRole).toString()) != -1)
                alphabet.remove(ui->secondKeyTableWidget->item(i,j)->data(Qt::DisplayRole).toString());
            else
                return false;
        }
    return true;
}

void WheatstoneCipher::encryptText()
{
    if(checkTables())
    {
        QString inText = CryptoHelper::preW(ui->textEdit->toPlainText());
        if(inText.length() % 2 != 0)
        {
            emit encryptedText(QString::fromLocal8Bit("Количество букв в тексте должно быть четным!"));
            return;
        }
        QString outText;
        QTableWidgetItem *first;
        QTableWidgetItem *second;
        for(int i = 0; i < inText.length() / 2; i++)
        {
            first = ui->firstKeyTableWidget->findItems(QString(inText[0]), Qt::MatchStartsWith).first();
            second = ui->secondKeyTableWidget->findItems(QString(inText[1]), Qt::MatchStartsWith).first();
            inText = CryptoHelper::leftRotate(inText, 2);
            if(first->row() == second->row())
            {
                outText += ui->firstKeyTableWidget->item(second->row(), second->column())->data(Qt::DisplayRole).toString();
                outText += ui->secondKeyTableWidget->item(first->row(), first->column())->data(Qt::DisplayRole).toString();
            }
            else
            {
                outText += ui->secondKeyTableWidget->item(first->row(), second->column())->data(Qt::DisplayRole).toString();
                outText += ui->firstKeyTableWidget->item(second->row(), first->column())->data(Qt::DisplayRole).toString();
            }
        }
        outText = CryptoHelper::post(outText);
        emit encryptedText(outText);
    }
    else
        emit encryptedText(QString::fromLocal8Bit("Неверная таблица!"));
}
