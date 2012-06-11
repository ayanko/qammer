#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QVariant>

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QVariant attrs, QObject *parent = 0);
    
    QString webUrl();
    QString bodyPlain();
    QString bodyParsed();
    QString bodyRich();
    QString createdAt();
    qlonglong threadId();
    qlonglong senderId();
signals:
    
public slots:

private:
    QString m_strWebUrl;
    QString m_strBodyPlain;
    QString m_strBodyParsed;
    QString m_strBodyRich;
    QString m_strCreatedAt;
    qlonglong m_llTreadId;
    qlonglong m_llSenderId;
};

#endif // MESSAGE_H
