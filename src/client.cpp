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
    qDebug() << "one";
    m_strMessagesUrl = QString(YAMMER_API_BASE_URL).append("/messages.json");

    qDebug() << "two";
    m_pNetworkManager = new QNetworkAccessManager(this);

    qDebug() << "three";
    connect(m_pNetworkManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(replyFinished(QNetworkReply*)));

    qDebug() << "four";
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
    qDebug() << "fetchMessages()" << m_strMessagesUrl;
    QUrl url(m_strMessagesUrl);
    qDebug() << "fetchMessages()2";
    url.addQueryItem("access_token", accessToken());
    qDebug() << "fetchMessages()4";
    qDebug() << "fetchMessages()5" << url.toString();
    m_pNetworkManager->get(QNetworkRequest(url));
    qDebug() << "END";
}

void Client::replyFinished(QNetworkReply* reply)
{
    qDebug() << "replyFinished()";

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

    qDebug() << data;
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
