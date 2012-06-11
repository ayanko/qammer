#include "client.h"
#include "message.h"

#include "../qt-json/json.h"
#include <QSettings>
#include <QUrl>
#include <QDebug>

#define YAMMER_API_BASE_URL "https://www.yammer.com/api/v1"

Client::Client(QObject *parent) :
    QObject(parent)
{
    m_strMessagesUrl = QString(YAMMER_API_BASE_URL).append("/messages.json");

    m_pNetworkManager = new QNetworkAccessManager(this);

    connect(m_pNetworkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));
}

QList<Message*> Client::messages()
{
    return m_tMessages;
}

QString Client::accessToken()
{
    QSettings settings;
    return settings.value("access_token").toString();
}

void Client::fetchMessages()
{
    QUrl url(m_strMessagesUrl);
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

    //if ( url == m_strMessagesUrl) {
      parseMessages(data);
    //}
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

    foreach (QVariant item, result.toMap().value("messages").toList()) {
        m_tMessages.append(new Message(item));
    }
    
    emit messagesReceived();
}
