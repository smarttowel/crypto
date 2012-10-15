#ifndef CRYPTOHELPER_H
#define CRYPTOHELPER_H

#include <QObject>
#include <QString>

class CryptoHelper : public QObject
{
    Q_OBJECT
public:
    explicit CryptoHelper(QObject *parent = 0);
    static QString alphabet();
    static QString pre(QString text);
    static QString post(QString text, int tokenLength);

signals:
    
public slots:
    
};

#endif // CRYPTOHELPER_H
