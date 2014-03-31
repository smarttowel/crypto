#include "vigenerecipher.h"
#include "ui_vigenerecipher.h"

void VigenereCipherView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    painter.setRenderHint(QPainter::Antialiasing);
    pen.setColor(CryptoHelper::tableColor);
    painter.setPen(pen);
    //draw horizontal alphabet for source text
    for(int i = 0; i < CryptoHelper::alphabet.length(); i++)
    {
        m_cellRect.setX(10 + CELL_SIZE * (i + 2));
        m_cellRect.setY(10);
        m_cellRect.setWidth(CELL_SIZE);
        m_cellRect.setHeight(CELL_SIZE);
        painter.drawText(m_cellRect.x() + CELL_SIZE / 3, m_cellRect.y() + CELL_SIZE * 0.75, QChar(CryptoHelper::alphabet[i]));
    }
    //draw vertical alphabet for key
    for(int i = 0; i < CryptoHelper::alphabet.length(); i++)
    {
        m_cellRect.setX(10 + CELL_SIZE);
        m_cellRect.setY(10 + CELL_SIZE * (i + 1));
        m_cellRect.setWidth(CELL_SIZE);
        m_cellRect.setHeight(CELL_SIZE);
        painter.drawText(m_cellRect.x() + CELL_SIZE / 3, m_cellRect.y() + CELL_SIZE * 0.75, QChar(CryptoHelper::alphabet[i]));
    }
    //draw big table
    for(int i = 0; i < CryptoHelper::alphabet.length(); i++)
        for(int j = 0; j < CryptoHelper::alphabet.length(); j++)
        {
            m_cellRect.setX(10 + CELL_SIZE * (j + 2));
            m_cellRect.setY(10 + CELL_SIZE * (i + 1));
            m_cellRect.setWidth(CELL_SIZE);
            m_cellRect.setHeight(CELL_SIZE);
            painter.drawRect(m_cellRect);
            painter.drawText(m_cellRect.x() + CELL_SIZE / 3, m_cellRect.y() + CELL_SIZE * 0.75,
                             QChar(CryptoHelper::leftRotate(CryptoHelper::alphabet, i)[j]));
        }
    if(m_draw)
    {
        int alIndex = CryptoHelper::alphabet.indexOf(m_text[m_currentChar]);
        int keyIndex = CryptoHelper::alphabet.indexOf(m_table1[m_currentChar % m_table1.length()]);
        highlightChar(m_currentChar);
        pen.setColor(CryptoHelper::inCharsColor);
        pen.setWidth(3);
        painter.setPen(pen);
        m_cellRect.setX(10 + CELL_SIZE * (alIndex + 2));
        m_cellRect.setY(10);
        m_cellRect.setWidth(CELL_SIZE);
        m_cellRect.setHeight(CELL_SIZE);
        painter.drawRect(m_cellRect);
        pen.setColor(Qt::yellow);
        pen.setWidth(3);
        painter.setPen(pen);
        m_cellRect.setX(10 + CELL_SIZE);
        m_cellRect.setY(10 + CELL_SIZE * (keyIndex + 1));
        m_cellRect.setWidth(CELL_SIZE);
        m_cellRect.setHeight(CELL_SIZE);
        painter.drawRect(m_cellRect);
        pen.setColor(CryptoHelper::outCharsColor);
        pen.setWidth(3);
        painter.setPen(pen);
        m_cellRect.setX(10 + CELL_SIZE * (alIndex + 2));
        m_cellRect.setY(10 + CELL_SIZE * (keyIndex + 1));
        m_cellRect.setWidth(CELL_SIZE);
        m_cellRect.setHeight(CELL_SIZE);
        painter.drawRect(m_cellRect);
    }
}

VigenereCipherView::VigenereCipherView(QWidget *parent, int a) :
    AbstractCipherView(parent)
{
    m_isShow = a;
    m_currentChar = 0;
    m_token = 1;
    CELL_SIZE = 18;
    setFixedSize(100 + m_cellRect.x() + CELL_SIZE * CryptoHelper::alphabet.length(),
                 130 + m_cellRect.y() * 2 + CELL_SIZE * CryptoHelper::alphabet.length());
    setWindowTitle(tr("Visualization Vigenere cipher"));
}

VigenereCipherView::~VigenereCipherView()
{
}

VigenereCipher::VigenereCipher(QWidget *parent, QString text) :
    AbstractCipher(parent),
    ui(new Ui::VigenereCipher)
{
    ui->setupUi(this);
    ui->textEdit->setText(text);
}

VigenereCipher::~VigenereCipher()
{
    emit text(ui->textEdit->toPlainText());
    delete ui;
}

void VigenereCipher::encryptText()
{
    if(!ui->lineEdit->text().isEmpty())
    {
        QString inText = CryptoHelper::pre(ui->textEdit->toPlainText());
        QString key = ui->lineEdit->text().toLower();
        QString outText;
        QString alphabet = CryptoHelper::alphabet;
        for(int i = 0; i < inText.length(); i++)
        {
            outText += alphabet[(alphabet.indexOf(inText[i]) + alphabet.indexOf(key[i % key.length()])) % alphabet.length()];
        }
        emit results(key, inText, outText);
        outText = CryptoHelper::post(outText);
        emit encryptedText(outText);
    }
    else
        emit encryptedText(tr("Key cannot be empty!"));
}
