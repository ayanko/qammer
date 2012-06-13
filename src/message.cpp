#include "message.h"
#include "user.h"

#include <QDebug>
/*
   ["id", "network_id", "system_message", "url", "body", "attachments", "privacy", "direct_message", "replied_to_id", "created_at", "thread_id", "sender_id", "client_url", "sender_type", "web_url", "group_id", "client_type", "liked_by", "message_type"] 
 */
Message::Message(QVariant attrs, QObject *parent) :
    QObject(parent)
{
    QVariantMap hash = attrs.toMap();

    m_pUser = NULL;
    m_llId = hash.value("id").toLongLong();
    m_llTreadId = hash.value("thread_id").toLongLong();
    m_llSenderId = hash.value("sender_id").toLongLong();
    m_strWebUrl = hash.value("web_url").toString();
    m_strBodyPlain = hash.value("body").toMap().value("plain").toString();
    m_strBodyParsed = hash.value("body").toMap().value("parsed").toString();
    m_strBodyRich = hash.value("body").toMap().value("rich").toString();
    m_strCreatedAt = hash.value("created_at").toString();
    m_strClientUrl = hash.value("client_url").toString();
    m_strClientType = hash.value("client_type").toString();
}

void Message::addChild(Message* message)
{
    m_pChildren.append(message);
}

QList<Message*> Message::children() 
{
  return m_pChildren;
}

QString Message::senderName()
{
    return(m_pUser ? m_pUser->fullName() : "Unknown Sender");
}
