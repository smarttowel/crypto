#include "caesarcipher.h"
#include "ui_caesarcipher.h"
#include <QDebug>

void CaesarCipherView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    painter.setRenderHint(QPainter::Antialiasing);
    pen.setColor(Qt::black);
    pen.setWidth(3);
    for(int i = 0; i < CryptoHelper::alphabet.length(); i++)
    {
        m_cellRect.setX(10 + CELL_SIZE * (i + 1));
        m_cellRect.setWidth(CELL_SIZE);
        m_cellRect.setHeight(CELL_SIZE);
        painter.drawRect(m_cellRect);
        painter.drawText(m_cellRect.x() + CELL_SIZE / 3, m_cellRect.y() + CELL_SIZE / 2, QChar(CryptoHelper::alphabet[i]));
    }
    if(m_draw)
    {
        pen.setColor(Qt::red);
        pen.setWidth(3);
        painter.setPen(pen);
        highlightChar(m_currentChar);
        //draw rectangles
        m_cellRect.setX(10 + CELL_SIZE * (CryptoHelper::alphabet.indexOf(m_text[m_currentChar]) + 1));
        m_cellRect.setWidth(CELL_SIZE);
        m_cellRect.setHeight(CELL_SIZE);
        painter.drawRect(m_cellRect);
        m_cellRect.setX(10 + CELL_SIZE * (CryptoHelper::alphabet.indexOf(m_encryptedText[m_currentChar]) + 1));
        m_cellRect.setWidth(CELL_SIZE);
        m_cellRect.setHeight(CELL_SIZE);
        painter.drawRect(m_cellRect);
        //draw lines
        painter.drawLine(10 + CELL_SIZE / 2 + CELL_SIZE * (CryptoHelper::alphabet.indexOf(m_text[m_currentChar]) + 1), 10 + CELL_SIZE,
                         10 + CELL_SIZE / 2 + CELL_SIZE * (CryptoHelper::alphabet.indexOf(m_text[m_currentChar]) + 1), 10 + CELL_SIZE + 50);
        painter.drawLine(10 + CELL_SIZE / 2 + CELL_SIZE * (CryptoHelper::alphabet.indexOf(m_text[m_currentChar]) + 1), 10 + CELL_SIZE + 50,
                         10 + CELL_SIZE / 2 + CELL_SIZE * (CryptoHelper::alphabet.indexOf(m_encryptedText[m_currentChar]) + 1), 10 + CELL_SIZE + 50);
        painter.drawLine(10 + CELL_SIZE / 2 + CELL_SIZE * (CryptoHelper::alphabet.indexOf(m_encryptedText[m_currentChar]) + 1), 10 + CELL_SIZE + 50,
                         10 + CELL_SIZE / 2 + CELL_SIZE * (CryptoHelper::alphabet.indexOf(m_encryptedText[m_currentChar]) + 1), 10 + CELL_SIZE);
        //draw arrow
        painter.drawLine(10 + CELL_SIZE / 2 + CELL_SIZE * (CryptoHelper::alphabet.indexOf(m_encryptedText[m_currentChar]) + 1), 10 + CELL_SIZE,
                         10 + CELL_SIZE / 2 + CELL_SIZE * (CryptoHelper::alphabet.indexOf(m_encryptedText[m_currentChar]) + 1) + 8, 10 + CELL_SIZE + 8);
        painter.drawLine(10 + CELL_SIZE / 2 + CELL_SIZE * (CryptoHelper::alphabet.indexOf(m_encryptedText[m_currentChar]) + 1), 10 + CELL_SIZE,
                         10 + CELL_SIZE / 2 + CELL_SIZE * (CryptoHelper::alphabet.indexOf(m_encryptedText[m_currentChar]) + 1) - 8, 10 + CELL_SIZE + 8);

    }
}

void CaesarCipherView::onNextButtonClick()
{
    m_currentChar++;
    setBackButtonEnabled(true);
    if(m_currentChar == m_text.length() - 1)
    {
        setNextButtonEnabled(false);
        if(m_timer.isActive())
        {
            on_autoButton_clicked();
            m_currentChar = 0;
            setBackButtonEnabled(false);
            setNextButtonEnabled(true);
        }
    }
    update();
}

void CaesarCipherView::onBackButtonClick()
{
    m_currentChar--;
    if(m_currentChar == 0)
        setBackButtonEnabled(false);
    setNextButtonEnabled(true);
    update();
}

void CaesarCipherView::resetChars()
{
    m_currentChar = 0;
}

CaesarCipherView::CaesarCipherView(QWidget *parent, int a) :
    AbstractCipherView(parent)
{
    m_isShow = a;
    m_currentChar = 0;
    setFixedSize(m_cellRect.x() * 6 + m_cellRect.width() * CryptoHelper::alphabet.length(),
                 200 + m_cellRect.y() * 2 + m_cellRect.height());
    setWindowTitle(QString::fromLocal8Bit("Визуализация шифра Цезаря"));
}

CaesarCipherView::~CaesarCipherView()
{
}

CaesarCipher::CaesarCipher(QWidget *parent, QString text) :
    AbstractCipher(parent),
    ui(new Ui::CaesarCipher)
{
    ui->setupUi(this);
    ui->textEdit->setText(text);
}

CaesarCipher::~CaesarCipher()
{
    emit text(ui->textEdit->toPlainText());
    delete ui;
}

QString CaesarCipher::getText()
{
    return CryptoHelper::pre(ui->textEdit->toPlainText());
}

void CaesarCipher::encryptText()
{
    int index;
    QString text = ui->textEdit->toPlainText();
    text = CryptoHelper::pre(text);
    for(int i = 0; i < text.length(); i++)
    {
        index = (CryptoHelper::alphabet.indexOf(text[i]) + ui->spinBox->value()) % CryptoHelper::alphabet.length();
        text[i] = CryptoHelper::alphabet[index];
    }
    emit results(CryptoHelper::pre(ui->textEdit->toPlainText()), text);
    text = CryptoHelper::post(text);
    emit encryptedText(text);
}
