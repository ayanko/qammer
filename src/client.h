#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QNetworkAccessManager>
#include <QNetworkDiskCache>
#include <QNetworkReply>

class Message;
class User;
class Group;

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);

    void fetchMessages();
    void fetchUsers();
    void fetchGroups();

    QString accessToken();
    Message* recentMessage();

    User* findUserById(qlonglong id);
    User* findUserByMessage(Message* message);

    void sendReplyMessage(const QString &body, qlonglong message_id);
    void sendGroupMessage(const QString &body, qlonglong group_id);

signals:
    void messagesReceived();
    void usersReceived();
    void groupsReceived();
    
public slots:

private slots:
    void replyFinished(QNetworkReply* reply);
    void cachedReplyFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager* m_pNetworkManager;
    QNetworkAccessManager* m_pCacheManager;
    QNetworkDiskCache* m_pNetworkCache;

    QString m_strMessagesUrl;
    QString m_strUsersUrl;
    QString m_strGroupsUrl;

    QList<Message*> m_tMessages; 
    QMap<qlonglong, User*> m_tUsers; 
    QMap<qlonglong, Group*> m_tGroups; 

    void parseMessages(const QByteArray &data);
    void parseUsers(const QByteArray &data);
    void parseGroups(const QByteArray &data);

public:
    QList<Message*> messages()       { return m_tMessages; }
    QMap<qlonglong, User*> users()   { return m_tUsers; }
    QMap<qlonglong, Group*> groups() { return m_tGroups; }

};

#endif // CLIENT_H
