#include "trithemiuscipher.h"
#include "ui_trithemiuscipher.h"
#include <QDebug>

void TrithemiusCipherView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    painter.setRenderHint(QPainter::Antialiasing);
    pen.setColor(Qt::black);
    pen.setWidth(3);
    QPair<int, int> tableSize = CryptoHelper::tableSize(m_alphabet.length());
    //table
    for(int i = 0; i < tableSize.first; i++)
        for(int j = 0; j < tableSize.second; j++)
        {
            m_cellRect.setX(10 + CELL_SIZE * (j + 1));
            m_cellRect.setY(10 + CELL_SIZE * i);
            m_cellRect.setWidth(CELL_SIZE);
            m_cellRect.setHeight(CELL_SIZE);
            painter.drawRect(m_cellRect);
            painter.drawText(m_cellRect.x() + CELL_SIZE / 3, m_cellRect.y() + CELL_SIZE / 2, QChar(m_alphabet[tableSize.second * i + j]));
        }
    if(m_draw)
    {
        highlightChar(m_currentChar);
        int index = m_alphabet.indexOf(m_text[m_currentChar]);
        //source local rectangles
        pen.setColor(Qt::green);
        painter.setPen(pen);
        painter.drawRect(10 + CELL_SIZE * (index % tableSize.second + 1), 10 + CELL_SIZE * (index / tableSize.second),
                         CELL_SIZE, CELL_SIZE);
        //finish local rectangles
        pen.setColor(Qt::red);
        painter.setPen(pen);
        painter.drawRect(10 + CELL_SIZE * (index % tableSize.second + 1),
                         10 + CELL_SIZE * ((index / tableSize.second + 1) % tableSize.first),
                         CELL_SIZE, CELL_SIZE);
    }
}

void TrithemiusCipherView::onNextButtonClick()
{
    m_currentChar++;
    setBackButtonEnabled(true);
    if(m_currentChar == m_text.length() - 1)
    {
        setNextButtonEnabled(false);
        if(m_timer.isActive())
            on_autoButton_clicked();
    }
    update();
}

void TrithemiusCipherView::onBackButtonClick()
{
    m_currentChar--;
    if(m_currentChar == 0)
        setBackButtonEnabled(false);
    setNextButtonEnabled(true);
    update();
}

void TrithemiusCipherView::resetChars()
{
    m_currentChar = 0;
}

TrithemiusCipherView::TrithemiusCipherView(QWidget *parent, int a) :
    AbstractCipherView(parent)
{
    m_isShow = a;
    m_currentChar = 0;
    m_token = 1;
    setFixedSize(100 + m_cellRect.x() + CELL_SIZE * CryptoHelper::tableSize(CryptoHelper::alphabet.length()).second,
                 200 + m_cellRect.y() * 2 + CELL_SIZE * CryptoHelper::tableSize(CryptoHelper::alphabet.length()).first);
    setWindowTitle(QString::fromLocal8Bit("Визуализация шифрующей таблицы Трисемуса"));
}

TrithemiusCipherView::~TrithemiusCipherView()
{
}

TrithemiusCipher::TrithemiusCipher(QWidget *parent, QString text) :
    AbstractCipher(parent),
    ui(new Ui::TrithemiusCipher)
{
    ui->setupUi(this);
    ui->textEdit->setText(text);
}

TrithemiusCipher::~TrithemiusCipher()
{
    emit text(ui->textEdit->toPlainText());
    delete ui;
}

void TrithemiusCipher::encryptText()
{
    if(CryptoHelper::isUniq(ui->lineEdit->text()) && ui->lineEdit->text().length() <= CryptoHelper::alphabet.length())
    {
        QString inText = CryptoHelper::pre(ui->textEdit->toPlainText());
        QString outText;
        QString table;
        QString alphabet = CryptoHelper::alphabet;
        int row = CryptoHelper::tableSize(alphabet.length()).first;
        int col = CryptoHelper::tableSize(alphabet.length()).second;
        ui->label_2->setText(QString::fromLocal8Bit("Размер таблицы: %1x%2").arg(row).arg(col));
        for(int i = 0; i < ui->lineEdit->text().length(); i++)
        {
            alphabet.remove(ui->lineEdit->text()[i]);
        }
        table = ui->lineEdit->text();
        table += alphabet;
        for(int i = 0; i < inText.length(); i++)
        {
            outText += table[(table.indexOf(inText[i]) + col) % CryptoHelper::alphabet.length()];
        }
        emit results(table, inText, outText);
        outText = CryptoHelper::post(outText);
        emit encryptedText(outText);
    }
    else
        emit encryptedText(QString::fromLocal8Bit("Этот ключ не подходит!"));
}
