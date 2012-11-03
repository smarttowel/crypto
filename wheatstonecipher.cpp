#include "wheatstonecipher.h"
#include "ui_wheatstonecipher.h"
#include <QDebug>

void WheatstoneCipherView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    painter.setRenderHint(QPainter::Antialiasing);
    pen.setColor(Qt::black);
    pen.setWidth(3);
    QPair<int, int> tableSize = CryptoHelper::tableSize(CryptoHelper::alphabet.length() + CryptoHelper::extAlphabet.length());
    //second table
    for(int i = 0; i < tableSize.first; i++)
        for(int j = 0; j < tableSize.second; j++)
        {
            m_cellRect.setX(10 + CELL_SIZE * (j + 1));
            m_cellRect.setY(10 + CELL_SIZE * i);
            m_cellRect.setWidth(CELL_SIZE);
            m_cellRect.setHeight(CELL_SIZE);
            painter.drawRect(m_cellRect);
            painter.drawText(m_cellRect.x() + CELL_SIZE / 3, m_cellRect.y() + CELL_SIZE / 2, QChar(m_table1[tableSize.second * i + j]));
        }
    //first table
    for(int i = 0; i < tableSize.first; i++)
        for(int j = 0; j < tableSize.second; j++)
        {
            m_cellRect.setX(30 + CELL_SIZE * (tableSize.second + j + 1));
            m_cellRect.setY(10 + CELL_SIZE * i);
            m_cellRect.setWidth(CELL_SIZE);
            m_cellRect.setHeight(CELL_SIZE);
            painter.drawRect(m_cellRect);
            painter.drawText(m_cellRect.x() + CELL_SIZE / 3, m_cellRect.y() + CELL_SIZE / 2, QChar(m_table2[tableSize.second * i + j]));
        }
    //
    if(m_draw)
    {
        highlightChar(m_currentChar);
        int first = m_table1.indexOf(m_text[m_currentChar]);
        int second = m_table2.indexOf(m_text[m_currentChar + 1]);
        //source local rectangles
        pen.setColor(Qt::green);
        painter.setPen(pen);
        painter.drawRect(10 + CELL_SIZE * (first % tableSize.second + 1), 10 + CELL_SIZE * (first / tableSize.second),
                         CELL_SIZE, CELL_SIZE);
        painter.drawRect(30 + CELL_SIZE * (tableSize.second + second % tableSize.second + 1), 10 + CELL_SIZE * (second / tableSize.second),
                         CELL_SIZE, CELL_SIZE);
        //finish local rectangles
        pen.setColor(Qt::red);
        painter.setPen(pen);
        if(first / tableSize.second == second / tableSize.second)
        {
            painter.drawRect(30 + CELL_SIZE * (tableSize.second + first % tableSize.second + 1), 10 + CELL_SIZE * (second / tableSize.second),
                             CELL_SIZE, CELL_SIZE);
            painter.drawRect(10 + CELL_SIZE * (second % tableSize.second + 1), 10 + CELL_SIZE * (first / tableSize.second),
                             CELL_SIZE, CELL_SIZE);
        }
        else
        {
            painter.drawRect(10 + CELL_SIZE * (first % tableSize.second + 1), 10 + CELL_SIZE * (second / tableSize.second),
                             CELL_SIZE, CELL_SIZE);
            painter.drawRect(30 + CELL_SIZE * (tableSize.second + second % tableSize.second + 1), 10 + CELL_SIZE * (first / tableSize.second),
                             CELL_SIZE, CELL_SIZE);
        }
    }
}

WheatstoneCipherView::WheatstoneCipherView(QWidget *parent, int a) :
    AbstractCipherView(parent)
{
    m_isShow = a;
    m_currentChar = 0;
    m_token = 2;
    setFixedSize(100 + m_cellRect.x() + CELL_SIZE * CryptoHelper::tableSize(CryptoHelper::alphabet.length()).second * 2,
                 200 + m_cellRect.y() * 2 + CELL_SIZE * CryptoHelper::tableSize(CryptoHelper::alphabet.length()).first);
    setWindowTitle(QString::fromLocal8Bit("Визуализация шифра Уитстона"));
}

WheatstoneCipherView::~WheatstoneCipherView()
{
}

WheatstoneCipher::WheatstoneCipher(QWidget *parent, QString text) :
    AbstractCipher(parent),
    ui(new Ui::WheatstoneCipher)
{
    ui->setupUi(this);
    qsrand(QTime::currentTime().msec());
    ui->textEdit->setText(text);
    QPair<int, int> size = CryptoHelper::tableSize(CryptoHelper::alphabet.length() + CryptoHelper::extAlphabet.length());
    ui->firstKeyTableWidget->setRowCount(size.first);
    ui->firstKeyTableWidget->setColumnCount(size.second);
    ui->secondKeyTableWidget->setRowCount(size.first);
    ui->secondKeyTableWidget->setColumnCount(size.second);
    fillTables();
}

WheatstoneCipher::~WheatstoneCipher()
{
    emit text(ui->textEdit->toPlainText());
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
        QString table1;
        QString table2;
        for(int i = 0; i < ui->firstKeyTableWidget->rowCount(); i++)
            for(int j = 0; j < ui->firstKeyTableWidget->columnCount(); j++)
            {
                table1 += ui->firstKeyTableWidget->item(i,j)->data(Qt::DisplayRole).toString();
                table2 += ui->secondKeyTableWidget->item(i,j)->data(Qt::DisplayRole).toString();
            }
        emit results(table1, table2, inText, outText);
        outText = CryptoHelper::post(outText);
        emit encryptedText(outText);
    }
    else
        emit encryptedText(QString::fromLocal8Bit("Неверная таблица!"));
}
