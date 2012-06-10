#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Message;

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

    void fetchMessages();

    QString accessToken();
    QList<Message*> messages();

signals:
    void messagesReceived();
    
public slots:

private slots:
    void replyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager* m_pNetworkManager;

    QString m_strMessagesUrl;

    QList<Message*> m_tMessages; 

    void parseMessages(const QByteArray &data);
};

#endif // CLIENT_H
