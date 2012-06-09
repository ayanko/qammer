#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QUrl>

namespace Ui {
class LoginDialog;
}

class LoginDialog : public QDialog
{
    Q_OBJECT

public:
    explicit LoginDialog(QWidget *parent = 0);
    ~LoginDialog();
    void login();

signals:
    void loggedIn();

private slots:
    void urlChanged(const QUrl &url);

private:
    Ui::LoginDialog *ui;
    QString m_strLoginUrl;
};

#endif // LOGINDIALOG_H
