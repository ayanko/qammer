#include "logindialog.h"
#include "ui_logindialog.h"

#include <QWebView>
#include <QSettings>
#include <QDebug>

#define YAMMER_OAUTH_URL "https://www.yammer.com/dialog/oauth"
#define YAMMER_APP_CLIENT_ID "CwYVcY7fQfmDyfCoxuYobw"
#define YAMMER_APP_REDIRECT_URL "http://localhost"

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

    m_strLoginUrl.append(YAMMER_OAUTH_URL);
    m_strLoginUrl.append("?response_type=token");
    m_strLoginUrl.append("&client_id=");
    m_strLoginUrl.append(YAMMER_APP_CLIENT_ID);
    m_strLoginUrl.append("&redirect_uri=");
    m_strLoginUrl.append(YAMMER_APP_REDIRECT_URL);

    connect(ui->webView, SIGNAL(urlChanged(QUrl)), this, SLOT(urlChanged(QUrl)));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::urlChanged(const QUrl &url)
{
    qDebug() << "[LoginDialog::urlChanged]" << url.toString();

    QSettings settings;

    QStringList list = url.fragment().split("=");

    if (list[0] == "access_token") {
      settings.setValue("access_token", list[1]);
      QDialog::accept();
      emit loggedIn();
    }
}

void LoginDialog::login() {
    ui->webView->setUrl(QUrl(m_strLoginUrl));
}
