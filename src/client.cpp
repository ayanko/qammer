#include "client.h"
#include "message.h"
#include "user.h"
#include "group.h"

#include "../qt-json/json.h"
#include <QSettings>
#include <QUrl>
#include <QDir>
#include <QDebug>

#define YAMMER_API_BASE_URL "https://www.yammer.com/api/v1"

Client::Client(QObject *parent) :
    QObject(parent)
{
    QString cacheDir = QDir::homePath().append("/.qammer/cache");

    m_strMessagesUrl = QString(YAMMER_API_BASE_URL).append("/messages.json");
    m_strUsersUrl = QString(YAMMER_API_BASE_URL).append("/users.json");
    m_strGroupsUrl = QString(YAMMER_API_BASE_URL).append("/groups.json");

    m_pNetworkManager = new QNetworkAccessManager(this);
    connect(m_pNetworkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    m_pCacheManager = new QNetworkAccessManager(this);
    m_pNetworkCache = new QNetworkDiskCache(this);
    m_pNetworkCache->setCacheDirectory(cacheDir);
    m_pCacheManager->setCache(m_pNetworkCache);
    connect(m_pCacheManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(cachedReplyFinished(QNetworkReply*)));
}


QString Client::accessToken()
{
    QSettings settings;
    return settings.value("access_token").toString();
}

void Client::fetchMessages()
{
    QUrl url(m_strMessagesUrl);
    url.addQueryItem("threaded", "extended");
    url.addQueryItem("access_token", accessToken());
    m_pNetworkManager->get(QNetworkRequest(url));
}

void Client::fetchUsers()
{
    QUrl url(m_strUsersUrl);
    url.addQueryItem("access_token", accessToken());
    m_pNetworkManager->get(QNetworkRequest(url));
}

void Client::fetchGroups()
{
    QUrl url(m_strGroupsUrl);
    url.addQueryItem("access_token", accessToken());
    m_pNetworkManager->get(QNetworkRequest(url));
}

void Client::replyFinished(QNetworkReply* reply)
{
    QString url = reply->url().toString();

    if(reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error" << reply->error();
        return;
    }

    QByteArray data = reply->readAll();

    if ( url.contains(m_strMessagesUrl) ) {
      parseMessages(data);
    } else if (url.contains(m_strUsersUrl) ) {
      parseUsers(data);
    } else if (url.contains(m_strGroupsUrl) ) {
      parseGroups(data);
    } else {
        qDebug() << "Unknown url:" << url;
    }
    reply->deleteLater();
}

void Client::cachedReplyFinished(QNetworkReply* reply)
{
    QString url = reply->url().toString();

    qDebug() << "cachedReplyFinished:" << url;

    if(reply->error() != QNetworkReply::NoError) {
        qDebug() << "Error" << reply->error();
        return;
    }

    QByteArray data = reply->readAll();
    foreach(User* user, m_tUsers.values()) {
        if (user->mugshotUrl() == url) {
            QPixmap pixmap;
            pixmap.loadFromData(data);
            user->setMugshot(pixmap);
        }
    }

    reply->deleteLater();
}

void Client::parseMessages(const QByteArray &data)
{
    bool ok;

    QVariant result = QtJson::Json::parse(data, ok); 

    if(!ok) {
      qFatal("An error occurred during parsing");
      exit(1);
    }

    while (!m_tMessages.isEmpty())
        delete m_tMessages.takeFirst();

    QVariantMap children_map = result.toMap().value("threaded_extended").toMap();

    foreach (QVariant item, result.toMap().value("messages").toList()) {
        Message* message = new Message(item);
        message->setUser(findUserByMessage(message));
        QString threadId = QString::number(message->threadId());

        if (children_map.contains(threadId)) {
            foreach(QVariant child_item, children_map.value(threadId).toList()) {
                Message* child = new Message(child_item, message);
                child->setUser(findUserByMessage(child));
                message->addChild(child);
            }
        }
        m_tMessages.append(message);
    }
    
    qDebug() << "Received messages: " << m_tMessages.size();
    emit messagesReceived();
}

void Client::parseUsers(const QByteArray &data)
{
    bool ok;

    QVariant result = QtJson::Json::parse(data, ok); 

    if(!ok) {
      qFatal("An error occurred during parsing");
      exit(1);
    }

    while (!m_tUsers.values().isEmpty())
        delete m_tUsers.values().takeFirst();

    m_tUsers.clear();

    foreach (QVariant item, result.toList()) {
        User* user = new User(item);
        m_pCacheManager->get(QNetworkRequest(user->mugshotUrl()));
        m_tUsers[user->id()] = user;
    }

    qDebug() << "Received users: " << m_tUsers.size();
    emit usersReceived();
}

void Client::parseGroups(const QByteArray &data)
{
    bool ok;

    QVariant result = QtJson::Json::parse(data, ok); 

    if(!ok) {
      qFatal("An error occurred during parsing");
      exit(1);
    }

    while (!m_tGroups.values().isEmpty())
        delete m_tGroups.values().takeFirst();

    m_tGroups.clear();

    foreach (QVariant item, result.toList()) {
        Group* group = new Group(item);
        m_tGroups[group->id()] = group;
    }

    qDebug() << "Received groups: " << m_tGroups.size();
    emit groupsReceived();
}

User* Client::findUserById(qlonglong id)
{
    return m_tUsers.value(id);
}

User* Client::findUserByMessage(Message* message)
{
    return findUserById(message->senderId());
}

Message* Client::recentMessage()
{
    if (m_tMessages.empty())
      return NULL;

    Message* message = m_tMessages.first();

    if (message->children().empty())
      return message;

    return message->children().first();
}
