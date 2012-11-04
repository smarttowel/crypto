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
    QSettings settings("settings", QSettings::IniFormat);
    CryptoHelper::alphabet = settings.value("alphabet", QString::fromLocal8Bit("абвгдежзийклмнопрстуфхцчшщъыьэюя")).toString();
    CryptoHelper::extAlphabet = settings.value("extAlphabet", QString::fromLocal8Bit(" :,.")).toString();
    CryptoHelper::tokenLength = settings.value("tokenLength", 4).toInt();
    CryptoHelper::tableColor = Qt::GlobalColor(settings.value("tableColor", 2).toInt());
    CryptoHelper::inCharsColor = Qt::GlobalColor(settings.value("inCharsColor", 8).toInt());
    CryptoHelper::outCharsColor = Qt::GlobalColor(settings.value("outCharsColor", 7).toInt());
    CryptoHelper::arrowColor = Qt::GlobalColor(settings.value("arrowColor", 7).toInt());
    CryptoHelper::interval = settings.value("interval", 1000).toInt();
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
    ui->tableColorComboBox->setCurrentIndex(int(CryptoHelper::tableColor) - 2);
    ui->inCharsColorComboBox->setCurrentIndex(int(CryptoHelper::inCharsColor) - 2);
    ui->outCharsColorComboBox->setCurrentIndex(int(CryptoHelper::outCharsColor) - 2);
    ui->ArrowColorComboBox->setCurrentIndex((CryptoHelper::arrowColor) - 2);
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
        QSettings settings("settings", QSettings::IniFormat);
        settings.setValue("alphabet", CryptoHelper::alphabet);
        settings.setValue("extAlphabet", CryptoHelper::extAlphabet);
        settings.setValue("tokenLength", CryptoHelper::tokenLength);
        settings.setValue("tableColor", int(CryptoHelper::tableColor));
        settings.setValue("inCharsColor", int(CryptoHelper::inCharsColor));
        settings.setValue("outCharsColor", int(CryptoHelper::outCharsColor));
        settings.setValue("arrowColor", int(CryptoHelper::arrowColor));
        settings.setValue("interval", CryptoHelper::interval);
        emit alphabetChanged();
        this->hide();
    }
    else
        ui->msgLabel->setText(QString::fromLocal8Bit("<font color = \"red\">Символы в алфавите не должны повторяться!</font>"));
}
