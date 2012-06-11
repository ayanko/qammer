#ifndef MESSAGE_H
#define MESSAGE_H

#include <QObject>
#include <QVariant>

class User;

class Message : public QObject
{
    Q_OBJECT
public:
    explicit Message(QVariant attrs, QObject *parent = 0);

    void addChild(Message* message);
    QList<Message*> children();
signals:
    
public slots:

private:
    QList<Message*> m_pChildren;
    User* m_pUser;

    QString m_strWebUrl;
    QString m_strBodyPlain;
    QString m_strBodyParsed;
    QString m_strBodyRich;
    QString m_strCreatedAt;
    qlonglong m_llId;
    qlonglong m_llTreadId;
    qlonglong m_llSenderId;

public:
    User* user() { return m_pUser; }
    void setUser(User* user) { m_pUser = user; }

    qlonglong id() { return m_llId; }
    qlonglong threadId() { return m_llTreadId; }
    qlonglong senderId() { return m_llSenderId; }
    QString webUrl() { return m_strWebUrl; }
    QString bodyPlain() { return m_strBodyPlain; }
    QString bodyParsed() { return m_strBodyParsed; }
    QString bodyRich() { return m_strBodyRich; }
    QString createdAt() { return m_strCreatedAt; }

    QString senderName();
};

#endif // MESSAGE_H
