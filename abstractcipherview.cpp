#include "abstractcipherview.h"
#include "ui_abstractcipherview.h"

AbstractCipherView::AbstractCipherView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AbstractCipherView)
{
    ui->setupUi(this);
    CELL_SIZE = 30;
    m_cellRect.setX(10);
    m_cellRect.setY(10);
    m_cellRect.setWidth(CELL_SIZE);
    m_cellRect.setHeight(CELL_SIZE);
    ui->backButton->setEnabled(false);
    m_draw = false;
    connect(ui->nextButton, SIGNAL(clicked()), this, SLOT(onNextButtonClick()));
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(onBackButtonClick()));
    connect(&m_timer, SIGNAL(timeout()), this, SLOT(onNextButtonClick()));
}

AbstractCipherView::~AbstractCipherView()
{
    delete ui;
}

void AbstractCipherView::resetChars()
{
    m_currentChar = 0;
}

void AbstractCipherView::highlightChar(int index)
{
    QString text = m_text;
    text.insert(index + m_token, "</font>");
    text.insert(index, "<font color = \"green\">");
    ui->inTextEdit->setText(text);
    text = m_encryptedText;
    text.insert(index + m_token, "</font>");
    text.insert(index, "<font color = \"red\">");
    ui->outTextEdit->setText(text);
}

void AbstractCipherView::setResults(QString inText, QString outText)
{
    m_text = inText;
    m_encryptedText = outText;
    if(m_text.length() == 0 || m_text.length() == m_token)
    {
        ui->nextButton->setEnabled(false);
        ui->backButton->setEnabled(false);
        if(m_text.length())
            m_draw = true;
        else
            m_draw = false;
    }
    else
    {
        ui->nextButton->setEnabled(true);
        ui->backButton->setEnabled(false);
        m_draw = true;
    }
    ui->inTextEdit->setText(inText);
    ui->outTextEdit->setText(outText);
    if(m_isShow)
        show();
    resetChars();
    update();
}

void AbstractCipherView::setResults(QString alphabet, QString inText, QString outText)
{
    m_table1 = alphabet;
    setResults(inText, outText);
}

void AbstractCipherView::setResults(QString table1, QString table2, QString inText, QString outText)
{
    m_table2 = table2;
    setResults(table1, inText, outText);
}

void AbstractCipherView::setResults(QVector<int> square, QString inText, QString outText)
{
    m_square = square;
    setResults(inText, outText);
}

void AbstractCipherView::setIsShow(int a)
{
    m_isShow = a;
}

void AbstractCipherView::onNextButtonClick()
{
    m_currentChar += m_token;
    ui->backButton->setEnabled(true);
    if(m_currentChar + m_token / 2 == m_text.length() - 1)
    {
        ui->nextButton->setEnabled(false);
        if(m_timer.isActive())
        {
            on_autoButton_clicked();
            ui->autoButton->setEnabled(false);
        }
    }
    update();
}

void AbstractCipherView::onBackButtonClick()
{
    m_currentChar -= m_token;
    if(m_currentChar == 0)
        ui->backButton->setEnabled(false);
    ui->nextButton->setEnabled(true);
    ui->autoButton->setEnabled(true);
    update();
}

void AbstractCipherView::on_autoButton_clicked()
{
    if(m_timer.isActive())
    {
        m_timer.stop();
        ui->autoButton->setText(QString::fromLocal8Bit("Авто"));
    }
    else
    {
        m_timer.start(CryptoHelper::interval);
        ui->autoButton->setText(QString::fromLocal8Bit("Стоп"));
    }
}
