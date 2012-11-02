#include "magicsquarecipher.h"
#include "ui_magicsquarecipher.h"
#include <QDebug>

void MagicSquareCipherView::paintEvent(QPaintEvent *)
{
    int m_squareSize = qSqrt(m_square.size());
    setFixedSize(100 + CELL_SIZE * m_squareSize, 150 + CELL_SIZE * m_squareSize);
    QPainter painter(this);
    QPen pen;
    painter.setRenderHint(QPainter::Antialiasing);
    //table
    for(int i = 0; i < m_squareSize; i++)
        for(int j = 0; j < m_squareSize; j++)
        {
            m_cellRect.setX(10 + CELL_SIZE * (j + 1));
            m_cellRect.setY(10 + CELL_SIZE * i);
            m_cellRect.setWidth(CELL_SIZE);
            m_cellRect.setHeight(CELL_SIZE);
            pen.setColor(Qt::black);
            pen.setWidth(1);
            painter.setPen(pen);
            painter.drawRect(m_cellRect);
            if(m_square[m_squareSize * i + j] <= (m_currentChar + 1) % m_square.size() || (m_currentChar + 1) % m_square.size() == 0)
            {
                pen.setColor(Qt::red);
                painter.setPen(pen);
                painter.drawText(m_cellRect.x() + CELL_SIZE / 3, m_cellRect.y() + CELL_SIZE / 2,
                                 QChar(m_text[m_square[i * m_squareSize + j] - 1 + m_currentChar / m_square.size() * m_square.size()]));
            }
            else
            {
                pen.setColor(Qt::black);
                painter.setPen(pen);
                painter.drawText(m_cellRect.x() + CELL_SIZE / 3, m_cellRect.y() + CELL_SIZE / 2,
                                 QString::number(m_square[m_squareSize * i + j]));
            }
        }
    if(m_draw)
    {
        int index = m_square.indexOf(m_currentChar % m_square.size() + 1);
        highlightChar(m_currentChar);
        pen.setColor(Qt::red);
        pen.setWidth(3);
        painter.setPen(pen);
        painter.drawRect(10 + CELL_SIZE * (index % m_squareSize + 1),
                         10 + CELL_SIZE * (index / m_squareSize),
                         CELL_SIZE, CELL_SIZE);
    }
}

void MagicSquareCipherView::onNextButtonClick()
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

void MagicSquareCipherView::onBackButtonClick()
{
    m_currentChar--;
    if(m_currentChar == 0)
        setBackButtonEnabled(false);
    setNextButtonEnabled(true);
    update();
}

void MagicSquareCipherView::resetChars()
{
    m_currentChar = 0;
}

MagicSquareCipherView::MagicSquareCipherView(QWidget *parent, int a) :
    AbstractCipherView(parent)
{
    m_isShow = a;
    m_currentChar = 0;
    m_token = 1;
    CELL_SIZE = 40;
    setWindowTitle(QString::fromLocal8Bit("Визуализация шифрования магическим квадратом"));
}

MagicSquareCipherView::~MagicSquareCipherView()
{
}

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
    emit text(ui->textEdit->toPlainText());
    delete ui;
}

void MagicSquareCipher::on_spinBox_valueChanged(int arg1)
{
    ui->tableWidget->setRowCount(arg1);
    ui->tableWidget->setColumnCount(arg1);
    on_clearSquarePushButton_clicked();
    if(arg1 % 4 == 0)
        generateEvenSquare();
    if(arg1 % 2 != 0)
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
    int n = ui->spinBox->value();
    int array[n][n];
    int number1 = 1;
    int number2 = n*n;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
        {
            if(i % 4 == 0 || i % 4 == 3)
            {
                if(j % 4 == 0 || j % 4 == 3)
                    array[i][j] = number1;
                else
                    array[i][j] = number2;
            }
            else
            {
                if(j % 4 == 1 || j % 4 == 2)
                    array[i][j] = number1;
                else
                    array[i][j] = number2;
            }
            number1++;
            number2--;
        }
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            ui->tableWidget->setItem(i, j, new QTableWidgetItem(QString::number(array[i][j]), Qt::DisplayRole));
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

bool MagicSquareCipher::checkOnMagic()
{
    int n = ui->spinBox->value();
    int checkSum = n * (n*n + 1) / 2;
    int sum = 0;
    //check on null cell
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            if(ui->tableWidget->item(i,j) == 0)
                return false;
    //check on sum
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
            sum += ui->tableWidget->item(i,j)->data(Qt::DisplayRole).toInt();
        if(checkSum != sum)
            return false;
        sum = 0;
        for(int j = 0; j < n; j++)
            sum += ui->tableWidget->item(j,i)->data(Qt::DisplayRole).toInt();
        if(checkSum != sum)
            return false;
        sum = 0;
    }
    //other checks
    QVector<int> vector;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; j++)
            vector.append(ui->tableWidget->item(i,j)->data(Qt::DisplayRole).toInt());
    for(int i = 1; i <= n*n; i++)
        if(vector.count(i) != 1)
            return false;
    return true;
}

void MagicSquareCipher::encryptText()
{
    if(checkOnMagic())
    {
        QString inText = CryptoHelper::pre(ui->textEdit->toPlainText());
        QString outText;
        int n = ui->spinBox->value();
        int itr = 0;
        while(!inText.isEmpty())
        {
            for(int i = 0; i < n; i++)
                for(int j = 0; j < n; j++)
                {
                    if(ui->tableWidget->item(i,j)->data(Qt::DisplayRole).toInt() <= inText.size())
                    {
                        outText += inText[ui->tableWidget->item(i,j)->data(Qt::DisplayRole).toInt() - 1];
                        itr++;
                    }
                }
            inText.remove(0, itr);
            itr = 0;
        }
        QVector<int> square;
        for(int i = 0; i < ui->tableWidget->rowCount(); i++)
            for(int j = 0; j < ui->tableWidget->columnCount(); j++)
                square.append(ui->tableWidget->item(i,j)->data(Qt::DisplayRole).toInt());
        emit results(square, CryptoHelper::pre(ui->textEdit->toPlainText()), outText);
        outText = CryptoHelper::post(outText);
        emit encryptedText(outText);
    }
    else
        emit encryptedText(QString::fromLocal8Bit("Данный квадрат не магический!"));
}
