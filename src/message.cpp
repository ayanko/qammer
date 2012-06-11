#include "message.h"
#include <QDebug>
/*
   ["id", "network_id", "system_message", "url", "body", "attachments", "privacy", "direct_message", "replied_to_id", "created_at", "thread_id", "sender_id", "client_url", "sender_type", "web_url", "group_id", "client_type", "liked_by", "message_type"] 
 */
Message::Message(QVariant attrs, QObject *parent) :
    QObject(parent)
{
    QVariantMap hash = attrs.toMap();

    m_llId = hash.value("id").toLongLong();
    m_llTreadId = hash.value("thread_id").toLongLong();
    m_llSenderId = hash.value("sender_id").toLongLong();
    m_strWebUrl = hash.value("web_url").toString();
    m_strBodyPlain = hash.value("body").toMap().value("plain").toString();
    m_strBodyParsed = hash.value("body").toMap().value("parsed").toString();
    m_strBodyRich = hash.value("body").toMap().value("rich").toString();
    m_strCreatedAt = hash.value("created_at").toString();
}

void Message::addChild(Message* message)
{
    m_pChildren.append(message);
}

QList<Message*> Message::children()
{
  return m_pChildren;
}

QString Message::webUrl()
{
    return m_strWebUrl;
}

QString Message::bodyPlain()
{
    return m_strBodyPlain;
}

QString Message::bodyParsed()
{
    return m_strBodyParsed;
}

QString Message::bodyRich()
{
    return m_strBodyRich;
}

QString Message::createdAt()
{
    return m_strCreatedAt;
}

qlonglong Message::id()
{
    return m_llId;
}

qlonglong Message::threadId()
{
    return m_llTreadId;
}

qlonglong Message::senderId()
{
    return m_llSenderId;
}
