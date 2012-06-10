#include "message.h"
#include <QDebug>
/*
   ["id", "network_id", "system_message", "url", "body", "attachments", "privacy", "direct_message", "replied_to_id", "created_at", "thread_id", "sender_id", "client_url", "sender_type", "web_url", "group_id", "client_type", "liked_by", "message_type"] 
 */
Message::Message(QVariant attrs, QObject *parent) :
    QObject(parent)
{
    QVariantMap hash = attrs.toMap();

    qDebug() << hash.value("web_url").toString();
    qDebug() << hash.value("body").toMap().value("plain").toString();
    qDebug() << hash.value("thread_id").toLongLong();
    qDebug() << "\t-" << hash;
}
