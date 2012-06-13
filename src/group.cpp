#include "group.h"

Group::Group(QVariant attrs, QObject *parent) :
    QObject(parent)
{
    QVariantMap hash = attrs.toMap();

    m_llId = hash.value("id").toLongLong();

    m_strName         = hash.value("name").toString();
    m_strFullName     = hash.value("full_name").toString();
    m_strDescription  = hash.value("description").toString();
    m_strWebUrl       = hash.value("web_url").toString();
    m_strMugshotUrl   = hash.value("mugshot_url").toString();
}
