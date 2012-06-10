#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QVariant>

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QVariant attrs, QObject *parent = 0);
    
signals:
    
public slots:
    
};

#endif // MESSAGE_H
