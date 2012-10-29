#include "abstractcipherview.h"
#include "ui_abstractcipherview.h"

AbstractCipherView::AbstractCipherView(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AbstractCipherView)
{
    ui->setupUi(this);
    connect(ui->nextButton, SIGNAL(clicked()), this, SLOT(onNextButtonClick()));
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(onBackButtonClick()));
    m_cellRect.setX(10);
    m_cellRect.setY(10);
    m_cellRect.setWidth(CELL_SIZE);
    m_cellRect.setHeight(CELL_SIZE);
    ui->backButton->setEnabled(false);
    m_draw = false;
}

AbstractCipherView::~AbstractCipherView()
{
    delete ui;
}

void AbstractCipherView::setNextButtonEnabled(bool a)
{
    ui->nextButton->setEnabled(a);
}

void AbstractCipherView::setBackButtonEnabled(bool a)
{
    ui->backButton->setEnabled(a);
}

void AbstractCipherView::resetChars()
{
}

void AbstractCipherView::highlightChar(int index)
{
    QString text = m_text;
    text.insert(index + 1, "</font>");
    text.insert(index, "<font color = \"red\">");
    ui->inTextEdit->setText(text);
    text = m_encryptedText;
    text.insert(index + 1, "</font>");
    text.insert(index, "<font color = \"red\">");
    ui->outTextEdit->setText(text);
}

void AbstractCipherView::setResults(QString inText, QString outText)
{
    m_text = inText;
    m_encryptedText = outText;
    if(m_text.length() == 0 || m_text.length() == 1)
    {
        setNextButtonEnabled(false);
        setBackButtonEnabled(false);
        if(m_text.length())
            m_draw = true;
        else
            m_draw = false;
    }
    else
    {
        setNextButtonEnabled(true);
        setBackButtonEnabled(false);
        m_draw = true;
    }
    ui->inTextEdit->setText(inText);
    ui->outTextEdit->setText(outText);
    if(m_isShow)
        show();
    resetChars();
    update();
}

void AbstractCipherView::setIsShow(int a)
{
    m_isShow = a;
}

void AbstractCipherView::onNextButtonClick()
{
}

void AbstractCipherView::onBackButtonClick()
{
}