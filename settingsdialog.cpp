#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);
    move(QApplication::desktop()->geometry().width() / 2 - this->geometry().width() / 2,
         QApplication::desktop()->geometry().height() / 2 - this->geometry().height() / 2);
    QStringList list;
    list << "black" << "white" << "darkGray" << "gray" << "lightGray" << "red"  << "green"  << "blue" << "cyan" << "magenta" << "yellow" <<
         "darkRed" << "darkGreen" << "darkBlue" << "darkCyan"  << "darkMagenta" << "darkYellow";
    ui->tableColorComboBox->addItems(list);
    ui->inCharsColorComboBox->addItems(list);
    ui->outCharsColorComboBox->addItems(list);
    ui->ArrowColorComboBox->addItems(list);
    //
    CryptoHelper::alphabet = QString::fromLocal8Bit("абвгдежзийклмнопрстуфхцчшщъыьэюя");
    CryptoHelper::extAlphabet = QString::fromLocal8Bit(" :,.");
    CryptoHelper::tokenLength = 4;
    CryptoHelper::tableColor = Qt::black;
    CryptoHelper::inCharsColor = Qt::green;
    CryptoHelper::outCharsColor = Qt::red;
    CryptoHelper::arrowColor = Qt::red;
    CryptoHelper::interval = 1000;
    ui->alphabetLineEdit->setText(CryptoHelper::alphabet);
    ui->extAlphabetLineEdit->setText(CryptoHelper::extAlphabet);
    ui->tokenLengthSpinBox->setValue(CryptoHelper::tokenLength);
    ui->tableColorComboBox->setCurrentIndex(int(CryptoHelper::tableColor) - 2);
    ui->inCharsColorComboBox->setCurrentIndex(int(CryptoHelper::inCharsColor) - 2);
    ui->outCharsColorComboBox->setCurrentIndex(int(CryptoHelper::outCharsColor) - 2);
    ui->ArrowColorComboBox->setCurrentIndex((CryptoHelper::arrowColor) - 2);
    ui->intervalSpinBox->setValue(CryptoHelper::interval);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_cancelPushButton_clicked()
{
    ui->alphabetLineEdit->setText(CryptoHelper::alphabet);
    ui->extAlphabetLineEdit->setText(CryptoHelper::extAlphabet);
    ui->tokenLengthSpinBox->setValue(CryptoHelper::tokenLength);
    ui->tableColorComboBox->setCurrentIndex(int(CryptoHelper::tableColor) + 2);
    ui->inCharsColorComboBox->setCurrentIndex(int(CryptoHelper::inCharsColor) + 2);
    ui->outCharsColorComboBox->setCurrentIndex(int(CryptoHelper::outCharsColor) + 2);
    ui->ArrowColorComboBox->setCurrentIndex((CryptoHelper::arrowColor) + 2);
    ui->intervalSpinBox->setValue(CryptoHelper::interval);
    ui->msgLabel->setText("");
    this->hide();
}

void SettingsDialog::on_applyPushButton_clicked()
{
    if(CryptoHelper::isUniq(ui->alphabetLineEdit->text()) && CryptoHelper::isUniq(ui->extAlphabetLineEdit->text())
            && CryptoHelper::isUniq(ui->alphabetLineEdit->text() + ui->extAlphabetLineEdit->text()))
    {
        CryptoHelper::alphabet = ui->alphabetLineEdit->text();
        CryptoHelper::extAlphabet = ui->extAlphabetLineEdit->text();
        CryptoHelper::tokenLength = ui->tokenLengthSpinBox->value();
        CryptoHelper::tableColor = Qt::GlobalColor(ui->tableColorComboBox->currentIndex() + 2);
        CryptoHelper::inCharsColor = Qt::GlobalColor(ui->inCharsColorComboBox->currentIndex() + 2);
        CryptoHelper::outCharsColor = Qt::GlobalColor(ui->outCharsColorComboBox->currentIndex() + 2);
        CryptoHelper::arrowColor = Qt::GlobalColor(ui->ArrowColorComboBox->currentIndex() + 2);
        CryptoHelper::interval = ui->intervalSpinBox->value();
        ui->msgLabel->setText("");
        emit alphabetChanged();
        this->hide();
    }
    else
        ui->msgLabel->setText(QString::fromLocal8Bit("<font color = \"red\">Символы в алфавите не должны повторяться!</font>"));
}
