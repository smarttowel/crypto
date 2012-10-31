#ifndef ABSTRACTCIPHERVIEW_H
#define ABSTRACTCIPHERVIEW_H

#include <QWidget>
#include <QTimer>
#include "cryptohelper.h"

namespace Ui {
class AbstractCipherView;
}

class AbstractCipherView : public QWidget
{
    Q_OBJECT
    
public:
    explicit AbstractCipherView(QWidget *parent = 0);
    ~AbstractCipherView();

protected:
    QString m_text;
    QString m_encryptedText;
    QString m_alphabet;
    QRect m_cellRect;
    int m_isShow;
    int m_token;
    bool m_draw;
    QTimer m_timer;
    int CELL_SIZE;
    void setNextButtonEnabled(bool a);
    void setBackButtonEnabled(bool a);
    virtual void resetChars();
    void highlightChar(int index);

protected slots:
    virtual void onNextButtonClick();
    virtual void onBackButtonClick();
    void on_autoButton_clicked();

public slots:
    void setResults(QString inText, QString outText);
    void setResults(QString alphabet, QString inText, QString outText);
    void setIsShow(int a);

private:
    Ui::AbstractCipherView *ui;
};

#endif // ABSTRACTCIPHERVIEW_H
