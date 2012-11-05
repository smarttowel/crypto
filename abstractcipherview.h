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
    QString m_table1;
    QString m_table2;
    QRect m_cellRect;
    int m_isShow;
    int m_token;
    int m_currentChar;
    QVector<int> m_square;
    bool m_draw;
    QTimer m_timer;
    int CELL_SIZE;
    void resetChars();
    void highlightChar(int index);

protected slots:
    void onNextButtonClick();
    void onBackButtonClick();
    void on_autoButton_clicked();

public slots:
    void setResults(QString inText, QString outText);
    void setResults(QString alphabet, QString inText, QString outText);
    void setResults(QString table1, QString table2, QString inText, QString outText);
    void setResults(QVector<int> square, QString inText, QString outText);
    void setIsShow(int a);

private:
    Ui::AbstractCipherView *ui;
};

#endif // ABSTRACTCIPHERVIEW_H
