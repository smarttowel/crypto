#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QWidget>
#include <QDesktopWidget>
#include <QSettings>
#include "cryptohelper.h"

namespace Ui {
class SettingsDialog;
}

class SettingsDialog : public QWidget
{
    Q_OBJECT
    
public:
    explicit SettingsDialog(QWidget *parent = 0);
    ~SettingsDialog();
    
private slots:
    void on_cancelPushButton_clicked();
    void on_applyPushButton_clicked();

private:
    Ui::SettingsDialog *ui;

signals:
    void alphabetChanged();
};

#endif // SETTINGSDIALOG_H
