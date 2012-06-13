#ifndef GROUP_H
#define GROUP_H

#include <QObject>
#include <QVariant>

class Group : public QObject
{
    Q_OBJECT
public:
    explicit Group(QVariant attrs, QObject *parent = 0);
    
signals:
    
public slots:

private:
    qlonglong m_llId;
    QString m_strName;
    QString m_strFullName;
    QString m_strDescription;
    QString m_strWebUrl;
    QString m_strMugshotUrl;
    
public:
    qlonglong id()        { return m_llId; }
    QString name()        { return m_strName; }
    QString fullName()    { return m_strFullName; }
    QString description() { return m_strDescription; }
    QString webUrl()      { return m_strWebUrl; }
    QString mugshotUrl()  { return m_strMugshotUrl; }
};

#endif // GROUP_H
