#include "settingsdialog.h"
#include "ui_settingsdialog.h"

SettingsDialog::SettingsDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SettingsDialog)
{
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);
}

SettingsDialog::~SettingsDialog()
{
    delete ui;
}

void SettingsDialog::on_cancelPushButton_clicked()
{
    ui->alphabetLineEdit->setText(CryptoHelper::alphabet);
    ui->extAlphabetLineEdit->setText(CryptoHelper::extAlphabet);
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
        ui->msgLabel->setText("");
        emit alphabetChanged();
        this->hide();
    }
    else
        ui->msgLabel->setText(QString::fromLocal8Bit("<font color = \"red\">Символы в алфавите не долнжы повторяться!</font>"));
}
