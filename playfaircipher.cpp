#include "playfaircipher.h"
#include "ui_playfaircipher.h"

void PlayfairCipherView::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen;
    painter.setRenderHint(QPainter::Antialiasing);
    pen.setColor(CryptoHelper::tableColor);
    painter.setPen(pen);
    QPair<int, int> tableSize = CryptoHelper::tableSize(m_table1.length());
    //table
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
    if(m_draw)
    {
        highlightChar(m_currentChar);
        int first = m_table1.indexOf(m_text[m_currentChar]);
        int second = m_table1.indexOf(m_text[m_currentChar + 1]);
        if(first % tableSize.second > second % tableSize.second)
        {
            first = first + second;
            second = first - second;
            first = first - second;
        }
        //source local rectangles
        pen.setColor(CryptoHelper::inCharsColor);
        pen.setWidth(3);
        painter.setPen(pen);
        painter.drawRect(10 + CELL_SIZE * (first % tableSize.second + 1), 10 + CELL_SIZE * (first / tableSize.second),
                         CELL_SIZE, CELL_SIZE);
        painter.drawRect(10 + CELL_SIZE * (second % tableSize.second + 1), 10 + CELL_SIZE * (second / tableSize.second),
                         CELL_SIZE, CELL_SIZE);
        //finish local rectangles
        pen.setColor(CryptoHelper::outCharsColor);
        pen.setWidth(3);
        painter.setPen(pen);
        if(first / tableSize.second == second / tableSize.second)
        {
            painter.drawRect(10 + CELL_SIZE * ((first % tableSize.second + 1) % tableSize.second + 1),
                             10 + CELL_SIZE * (first / tableSize.second),
                             CELL_SIZE, CELL_SIZE);
            painter.drawRect(10 + CELL_SIZE * ((second % tableSize.second + 1) % tableSize.second + 1),
                             10 + CELL_SIZE * (second / tableSize.second),
                             CELL_SIZE, CELL_SIZE);
        }
        else if(qAbs(first - second) % tableSize.second == 0)
        {
            painter.drawRect(10 + CELL_SIZE * (first % tableSize.second + 1),
                             10 + CELL_SIZE * ((first / tableSize.second + 1) % tableSize.first),
                             CELL_SIZE, CELL_SIZE);
            painter.drawRect(10 + CELL_SIZE * (second % tableSize.second + 1),
                             10 + CELL_SIZE * ((second / tableSize.second + 1) % tableSize.first),
                             CELL_SIZE, CELL_SIZE);
        }
        else
        {
            painter.drawRect(10 + CELL_SIZE * (first % tableSize.second + 1), 10 + CELL_SIZE * (second / tableSize.second),
                             CELL_SIZE, CELL_SIZE);
            painter.drawRect(10 + CELL_SIZE * (second % tableSize.second + 1), 10 + CELL_SIZE * (first / tableSize.second),
                             CELL_SIZE, CELL_SIZE);
        }
    }
}

PlayfairCipherView::PlayfairCipherView(QWidget *parent, int a) :
    AbstractCipherView(parent)
{
    m_isShow = a;
    m_currentChar = 0;
    m_token = 2;
    setFixedSize(100 + m_cellRect.x() + CELL_SIZE * CryptoHelper::tableSize(CryptoHelper::alphabet.length()).second,
                 200 + m_cellRect.y() * 2 + CELL_SIZE * CryptoHelper::tableSize(CryptoHelper::alphabet.length()).first);
    setWindowTitle(tr("Visualization Playfair cipher"));
}

PlayfairCipherView::~PlayfairCipherView()
{
}

PlayfairCipher::PlayfairCipher(QWidget *parent, QString text) :
    AbstractCipher(parent),
    ui(new Ui::PlayfairCipher)
{
    ui->setupUi(this);
    ui->textEdit->setText(text);
}

PlayfairCipher::~PlayfairCipher()
{
    emit text(ui->textEdit->toPlainText());
    delete ui;
}

void PlayfairCipher::encryptText()
{
    if(CryptoHelper::isUniq(ui->keyLineEdit->text()) && ui->keyLineEdit->text().length() <= CryptoHelper::alphabet.length())
    {
        if(ui->textEdit->toPlainText().length() % 2 != 0)
        {
            emit encryptedText(tr("Number of letters in the text should be even!"));
            return;
        }
        QString alphabet = CryptoHelper::alphabet;
        QString table;
        QString inText = CryptoHelper::pre(ui->textEdit->toPlainText());
        QString outText;
        int first;
        int second;
        int row = CryptoHelper::tableSize(alphabet.length()).first;
        int col = CryptoHelper::tableSize(alphabet.length()).second;
        ui->label_2->setText(tr("Table size: %1x%2").arg(row).arg(col));
        for(int i = 0; i < ui->keyLineEdit->text().length(); i++)
        {
            alphabet.remove(ui->keyLineEdit->text().toLower()[i]);
        }
        table = ui->keyLineEdit->text().toLower();
        table += alphabet;
        for(int i = 0; i < inText.length() / 2; i++)
        {
            first = table.indexOf(inText[0]);
            second = table.indexOf(inText[1]);
            inText = CryptoHelper::leftRotate(inText, 2);
            if(first / col == second / col)
            {
                outText += table[first / col * col + (first + 1) % col];
                outText += table[second / col * col + (second  + 1) % col];
            }
            else if(qAbs(first - second) % col == 0)
            {
                outText += table[(first + col) % CryptoHelper::alphabet.length()];
                outText += table[(second + col) % CryptoHelper::alphabet.length()];
            }
            else
            {
                outText += table[first / col * col + second % col];
                outText += table[second / col * col + first % col];
            }
        }
        emit results(table, inText, outText);
        outText = CryptoHelper::post(outText);
        emit encryptedText(outText);
    }
    else
        emit encryptedText(tr("Bad key"));
}
