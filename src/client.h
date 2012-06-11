#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkReply>

class Message;
class User;

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

    void fetchMessages();
    void fetchUsers();

    QString accessToken();
    QList<Message*> messages();
    QMap<qlonglong, User*> users();
    Message* recentMessage();

    User* findUserById(qlonglong id);
    User* findUserByMessage(Message* message);

signals:
    void messagesReceived();
    void usersReceived();
    
public slots:

private slots:
    void replyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager* m_pNetworkManager;

    QString m_strMessagesUrl;
    QString m_strUsersUrl;

    QList<Message*> m_tMessages; 
    QMap<qlonglong, User*> m_tUsers; 

    void parseMessages(const QByteArray &data);
    void parseUsers(const QByteArray &data);
};

#endif // CLIENT_H
