#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include "caesarcipher.h"
#include "caesarafcipher.h"
#include "caesarkwcipher.h"
#include "playfaircipher.h"
#include "trithemiuscipher.h"
#include "vigenerecipher.h"
#include "magicsquarecipher.h"
#include "wheatstonecipher.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    
private:
    Ui::MainWindow *ui;
    QString m_text;

private slots:
    void on_ciphiersComboBox_currentIndexChanged(int index);
    void textBuffer(QString text);
    void saveToFile();
};

#endif // MAINWINDOW_H
