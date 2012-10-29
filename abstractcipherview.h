#ifndef ABSTRACTCIPHERVIEW_H
#define ABSTRACTCIPHERVIEW_H

#include <QWidget>

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
    int m_isShow;
    QRect m_cellRect;
    bool m_draw;
    static const int CELL_SIZE = 30;
    void setNextButtonEnabled(bool a);
    void setBackButtonEnabled(bool a);
    virtual void resetChars();
    void highlightChar(int index);

protected slots:
    virtual void onNextButtonClick();
    virtual void onBackButtonClick();

public slots:
    void setResults(QString inText, QString outText);
    void setIsShow(int a);

private:
    Ui::AbstractCipherView *ui;
};

#endif // ABSTRACTCIPHERVIEW_H
