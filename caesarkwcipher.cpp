#include "caesarkwcipher.h"
#include "ui_caesarkwcipher.h"

void CaesarKWCipherView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    painter.setRenderHint(QPainter::Antialiasing);
    pen.setColor(CryptoHelper::tableColor);
    painter.setPen(pen);
    //first alphabet
    for(int i = 0; i < CryptoHelper::alphabet.length(); i++)
    {
        m_cellRect.setX(10 + CELL_SIZE * (i + 1));
        m_cellRect.setY(10);
        m_cellRect.setWidth(CELL_SIZE);
        m_cellRect.setHeight(CELL_SIZE);
        painter.drawRect(m_cellRect);
        painter.drawText(m_cellRect.x() + CELL_SIZE / 3, m_cellRect.y() + CELL_SIZE / 2, QChar(CryptoHelper::alphabet[i]));
    }
    //second alphabet
    for(int i = 0; i < m_table1.length(); i++)
    {
        m_cellRect.setX(10 + CELL_SIZE * (i + 1));
        m_cellRect.setY(10 + CELL_SIZE * 3);
        m_cellRect.setWidth(CELL_SIZE);
        m_cellRect.setHeight(CELL_SIZE);
        painter.drawRect(m_cellRect);
        painter.drawText(m_cellRect.x() + CELL_SIZE / 3, m_cellRect.y() + CELL_SIZE / 2, QChar(m_table1[i]));
    }
    if(m_draw)
    {
        pen.setColor(CryptoHelper::inCharsColor);
        pen.setWidth(3);
        painter.setPen(pen);
        highlightChar(m_currentChar);
        //draw rectangles
        m_cellRect.setX(10 + CELL_SIZE * (CryptoHelper::alphabet.indexOf(m_text[m_currentChar]) + 1));
        m_cellRect.setY(10);
        m_cellRect.setWidth(CELL_SIZE);
        m_cellRect.setHeight(CELL_SIZE);
        painter.drawRect(m_cellRect);
        pen.setColor(CryptoHelper::outCharsColor);
        pen.setWidth(3);
        painter.setPen(pen);
        m_cellRect.setX(10 + CELL_SIZE * (m_table1.indexOf(m_encryptedText[m_currentChar]) + 1));
        m_cellRect.setY(10 + CELL_SIZE * 3);
        m_cellRect.setWidth(CELL_SIZE);
        m_cellRect.setHeight(CELL_SIZE);
        painter.drawRect(m_cellRect);
        painter.drawRect(m_cellRect);
        pen.setColor(CryptoHelper::arrowColor);
        pen.setWidth(3);
        //draw lines
        painter.drawLine(10 + CELL_SIZE / 2 + CELL_SIZE * (CryptoHelper::alphabet.indexOf(m_text[m_currentChar]) + 1), 10 + CELL_SIZE,
                         10 + CELL_SIZE / 2 + CELL_SIZE * (m_table1.indexOf(m_encryptedText[m_currentChar]) + 1), 10 + CELL_SIZE * 3);
        //draw arrow
        painter.drawLine(10 + CELL_SIZE / 2 + CELL_SIZE * (m_table1.indexOf(m_encryptedText[m_currentChar]) + 1), 10 + CELL_SIZE * 3,
                         10 + CELL_SIZE / 2 + CELL_SIZE * (m_table1.indexOf(m_encryptedText[m_currentChar]) + 1) + 8, 10 + CELL_SIZE * 3 - 8);
        painter.drawLine(10 + CELL_SIZE / 2 + CELL_SIZE * (m_table1.indexOf(m_encryptedText[m_currentChar]) + 1), 10 + CELL_SIZE * 3,
                         10 + CELL_SIZE / 2 + CELL_SIZE * (m_table1.indexOf(m_encryptedText[m_currentChar]) + 1) - 8, 10 + CELL_SIZE * 3 - 8);

    }
}

CaesarKWCipherView::CaesarKWCipherView(QWidget *parent, int a) :
    AbstractCipherView(parent)
{
    m_isShow = a;
    m_currentChar = 0;
    m_token = 1;
    setFixedSize(m_cellRect.x() * 6 + m_cellRect.width() * CryptoHelper::alphabet.length(),
                 200 + m_cellRect.y() * 2 + m_cellRect.height());
    setWindowTitle(tr("Visualization Caesar cipher"));
}

CaesarKWCipherView::~CaesarKWCipherView()
{
}

CaesarKWCipher::CaesarKWCipher(QWidget *parent, QString text) :
    AbstractCipher(parent),
    ui(new Ui::CaesarKWCipher)
{
    ui->setupUi(this);
    ui->textEdit->setText(text);
    ui->firstKeySpinBox->setMaximum(CryptoHelper::alphabet.length());
}

CaesarKWCipher::~CaesarKWCipher()
{
    emit text(ui->textEdit->toPlainText());
    delete ui;
}

void CaesarKWCipher::encryptText()
{
    if(CryptoHelper::isUniq(ui->secondKeyLineEdit->text()) || ui->secondKeyLineEdit->text().length() > CryptoHelper::alphabet.length())
    {
        QString alphabet = CryptoHelper::alphabet;
        QString newAlphabet;
        QString inText = CryptoHelper::pre(ui->textEdit->toPlainText());
        QString outText;
        for(int i = 0; i < ui->secondKeyLineEdit->text().length(); i++)
        {
            alphabet.remove(ui->secondKeyLineEdit->text()[i]);
        }
        newAlphabet = ui->secondKeyLineEdit->text();
        newAlphabet += alphabet;
        newAlphabet = CryptoHelper::rightRotate(newAlphabet, ui->firstKeySpinBox->value() - 1);
        for(int i = 0; i < inText.length(); i++)
            outText += newAlphabet[CryptoHelper::alphabet.indexOf(inText[i])];
        emit results(newAlphabet, inText, outText);
        outText = CryptoHelper::post(outText);
        emit encryptedText(outText);
    }
    else
        emit encryptedText(tr("In keyword must not be repeated letters!"));
}
