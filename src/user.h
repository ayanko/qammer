#ifndef USER_H
#define USER_H

#include <QObject>
#include <QVariant>

class User : public QObject
{
    Q_OBJECT
public:
    explicit User(QVariant attrs, QObject *parent = 0);
    
signals:
    
public slots:

private:
    qlonglong m_llId;
    QString m_strName;
    QString m_strFullName;
    QString m_strMugshotUrl;
    QString m_strWebUrl;

public:
    qlonglong id() { return m_llId; }
    QString name() { return m_strName; }
    QString fullName() { return m_strFullName; }
    QString mugshotUrl() { return m_strMugshotUrl; }
    QString webUrl() { return m_strWebUrl; }
};

#endif // USER_H
