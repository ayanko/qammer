#include "user.h"
/*
 "network_id",
 "guid",
 "mugshot_url",
 "hire_date",
 "verified_admin",
 "full_name",
 "previous_companies",
 "id",
 "network_name",
 "mugshot_url_template",
 "state",
 "admin",
 "stats",
 "external_urls",
 "contact",
 "significant_other",
 "expertise",
 "schools",
 "name",
 "can_broadcast",
 "settings",
 "birth_date",
 "type",
 "summary",
 "interests",
 "kids_names",
 "activated_at",
 "location",
 "network_domains",
 "job_title",
 "web_url",
 "department",
 "timezone",
 "url"
 */
User::User(QVariant attrs, QObject *parent) :
    QObject(parent)
{
    QVariantMap hash = attrs.toMap();

    m_llId = hash.value("id").toLongLong();
    m_strName = hash.value("name").toString();
    m_strFullName = hash.value("full_name").toString();
    m_strMugshotUrl = hash.value("mugshot_url").toString();
    m_strWebUrl = hash.value("web_url").toString();

    m_pMugshot.load(":/images/no_photo.jpg");
}

void User::setMugshot(const QPixmap& pixmap)
{
    m_pMugshot = pixmap;
}
