#include "aboutdialog.h"
#include "ui_aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    setWindowModality(Qt::ApplicationModal);
    move(QApplication::desktop()->geometry().width() / 2 - this->geometry().width() / 2,
         QApplication::desktop()->geometry().height() / 2 - this->geometry().height() / 2);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}

void AboutDialog::on_pushButton_clicked()
{
    this->hide();
}
